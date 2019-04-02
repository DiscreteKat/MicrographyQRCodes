#include "stdafx.h"
#include "HKEdgeLinking.h"

using namespace HKCV;
using namespace HKUtils;
using namespace cv;

//////////////////////////////////////////////////////////////////////////
/// Direction masks:		
///   N	   S	 W     E		
static	int	thin_masks[] = { 0200, 0002, 0040, 0010 };

/*	True if pixel neighbor map indicates the pixel is 8-simple and	*/
/*	not an end point and thus can be deleted.  The neighborhood	*/
/*	map is defined as an integer of bits abcdefghi with a non-zero	*/
/*	bit representing a non-zero pixel.  The bit assignment for the	*/
/*	neighborhood is:						*/
/*									*/
/*				a b c					*/
/*				d e f					*/
/*				g h i					*/
static	unsigned char thin_delete[512] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int Check_Neighbor(uchar _node,  uchar* _flag)
{
	if((*_flag) == 0) /// not processed
	{
		if(_node == 1) /// an intermediate node
		{
			(*_flag) = 1;
			return 0; /// move on
		}
		else if(_node == 2) /// an end node
		{
			(*_flag) = 1;
			return 1; /// stop tracking
		}
		else if(_node == 3) /// a junction node
		{
			return 2; /// stop tracking
		}
	}
	return -1;
}

bool Trace_Edge(Mat& _edge_map, Mat& _flag_map, HKCEdgeLink* _line_seg, cv::Point _start_pnt, HKCEdgeLink::PntT _offset)
{
	HKCEdgeLink::VecPnt& pnts = _line_seg->Points();

	/// add the first point
	pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));

	cv::Point	crnr_pnt;
	uchar*		val_ptr[3];
	uchar*		flag_ptr[3];
	bool		go_next;
	int			state;

	/// tracking the edge until we meet
	/// 1. a junction node (excluded)
	/// 2. an end node (included)
	while(1)
	{
		go_next = false;

		/// check 4-connected neighbors first
		/// top row
		crnr_pnt.x = _start_pnt.x-1;
		crnr_pnt.y = _start_pnt.y-1;
		val_ptr[0]  = _edge_map.ptr<uchar>(crnr_pnt.y);		//CV_MAT_ELEM_PTR_FAST((*_pxl_map), crnr_pnt[1], crnr_pnt[0], sizeof(uchar));
		flag_ptr[0] = _flag_map.ptr<uchar>(crnr_pnt.y);  //CV_MAT_ELEM_PTR_FAST((*_flg_map), crnr_pnt[1], crnr_pnt[0], sizeof(uchar));

		/// check (x, y-1)
		state = Check_Neighbor(val_ptr[0][crnr_pnt.x+1], &(flag_ptr[0][crnr_pnt.x+1]));
		if(state == 0)
		{
			_start_pnt.x = crnr_pnt.x+1;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			continue;
		}
		else if(state == 1 || state == 2)
		{
			_start_pnt.x = crnr_pnt.x+1;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			return true;
		}

		/// middle row
		crnr_pnt.y = _start_pnt.y;
		val_ptr[1]  = _edge_map.ptr<uchar>(crnr_pnt.y); // CV_MAT_ELEM_PTR_FAST((*_pxl_map), crnr_pnt[1], crnr_pnt[0], sizeof(uchar));
		flag_ptr[1] = _flag_map.ptr<uchar>(crnr_pnt.y); //CV_MAT_ELEM_PTR_FAST((*_flg_map), crnr_pnt[1], crnr_pnt[0], sizeof(uchar));

		/// check (x-1, y)
		state = Check_Neighbor(val_ptr[1][crnr_pnt.x], &(flag_ptr[1][crnr_pnt.x]));
		if(state == 0)
		{
			_start_pnt = crnr_pnt;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			continue;
		}
		else if(state == 1 || state == 2)
		{
			_start_pnt = crnr_pnt;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			return true;
		}

		/// check (x+1, y)
		state = Check_Neighbor(val_ptr[1][crnr_pnt.x+2], &(flag_ptr[1][crnr_pnt.x+2]));
		if(state == 0)
		{
			_start_pnt.x = crnr_pnt.x+2;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			continue;
		}
		else if(state == 1 || state == 2)
		{
			_start_pnt.x = crnr_pnt.x+2;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			return true;
		}

		/// bottom row
		crnr_pnt.y = _start_pnt.y+1;
		val_ptr[2]  = _edge_map.ptr<uchar>(crnr_pnt.y); //CV_MAT_ELEM_PTR_FAST((*_pxl_map), crnr_pnt[1], crnr_pnt[0], sizeof(uchar));
		flag_ptr[2] = _flag_map.ptr<uchar>(crnr_pnt.y); //CV_MAT_ELEM_PTR_FAST((*_flg_map), crnr_pnt[1], crnr_pnt[0], sizeof(uchar));

		/// check (x, y+1)
		state = Check_Neighbor(val_ptr[2][crnr_pnt.x+1], &(flag_ptr[2][crnr_pnt.x+1]));
		if(state == 0)
		{
			_start_pnt.x = crnr_pnt.x+1;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			continue;
		}
		else if(state == 1 || state == 2)
		{
			_start_pnt.x = crnr_pnt.x+1;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			return true;
		}

		/// check 8-connected neighbors
		/// top row
		crnr_pnt.y = _start_pnt.y-1;

		/// check (x-1, y-1)
		state = Check_Neighbor(val_ptr[0][crnr_pnt.x], &(flag_ptr[0][crnr_pnt.x]));
		if(state == 0)
		{
			_start_pnt = crnr_pnt;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			continue;
		}
		else if(state == 1 || state == 2)
		{
			_start_pnt = crnr_pnt;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			return true;
		}

		/// check (x+1, y-1)
		state = Check_Neighbor(val_ptr[0][crnr_pnt.x+2], &(flag_ptr[0][crnr_pnt.x+2]));
		if(state == 0)
		{
			_start_pnt.x = crnr_pnt.x+2;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			continue;
		}
		else if(state == 1 || state == 2)
		{
			_start_pnt.x = crnr_pnt.x+2;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			return true;
		}

		/// bottom row
		crnr_pnt.y = _start_pnt.y+1;

		/// check (x-1, y+1)
		state = Check_Neighbor(val_ptr[2][crnr_pnt.x], &(flag_ptr[2][crnr_pnt.x]));
		if(state == 0)
		{
			_start_pnt = crnr_pnt;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			continue;
		}
		else if(state == 1 || state == 2)
		{
			_start_pnt = crnr_pnt;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			return true;
		}

		/// check (x+1, y+1)
		state = Check_Neighbor(val_ptr[2][crnr_pnt.x+2], &(flag_ptr[2][crnr_pnt.x+2]));
		if(state == 0)
		{
			_start_pnt.x = crnr_pnt.x+2;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			continue;
		}
		else if(state == 1 || state == 2)
		{
			_start_pnt.x = crnr_pnt.x+2;
			_start_pnt.y = crnr_pnt.y;
			pnts.push_back(HKCEdgeLink::PntT(_start_pnt.x+_offset.x, _start_pnt.y+_offset.y));
			return true;
		}

		if(!go_next) break;
	}

	return true;
}

/// Convert the edge map into edge links and remove edges with short length (in terms of pixel count)
void HKCV::Edge_Linking(Mat& _edge_map, VecEdgeLink& _edge_links, HKCEdgeLink::PntT _offset, int _thrsh)
{
	if(!_edge_map.data || _edge_map.type() != CV_8UC1)
	{
		printf("error");
		CV_Error(CV_StsBadArg, "_edge_map has incorrect data or type (not CV_8UC1)");
		return;
	}

	/// expand the edge map
	cv::Size	exp_size = cv::Size(_edge_map.cols+2, _edge_map.rows+2);
	Rect		exp_roi  = cv::Rect(1, 1, _edge_map.cols, _edge_map.rows);
	Mat			exp_map	 = Mat::zeros(exp_size, _edge_map.type());
	_edge_map.copyTo(exp_map(exp_roi));
	_offset += HKCEdgeLink::PntT(-1, -1);

	/// detect node type
	//////////////////////////////////////////////////////////////////////////
	/// detect end nodes and junction nodes
	/// 9 2 3
	/// 8 1 4
	/// 7 6 5
	uchar*	val_ptr;
	uchar	nn_labls[9];
	int		nn_cnt;
	for(int y = 1; y < exp_map.rows-1; ++y)
	{
		val_ptr = exp_map.ptr<uchar>(y);

		uchar* wnd_ptr1 = exp_map.ptr<uchar>(y-1);
		uchar* wnd_ptr2 = val_ptr;
		uchar* wnd_ptr3 = exp_map.ptr<uchar>(y+1);
		for(int x = 1; x < exp_map.cols-1; ++x)
		{
			if(val_ptr[x] == 1) /// a edge node
			{
				nn_cnt = 0;
				memset(nn_labls, 0, 9*sizeof(uchar));

				/// 1st row
				if(wnd_ptr1[x-1] != 0) ///P_9
				{
					nn_labls[8] = 1;
					nn_cnt++;
				}
				if(wnd_ptr1[x] != 0) ///P_2
				{
					nn_labls[1] = 1;
					nn_cnt++;
				}
				if(wnd_ptr1[x+1] != 0) ///P_3
				{
					nn_labls[2] = 1;
					nn_cnt++;
				}

				/// 2nd row
				if(wnd_ptr2[x-1] != 0) ///P_8
				{
					nn_labls[7] = 1;
					nn_cnt++;
				}
				if(wnd_ptr2[x+1] != 0) ///P_4
				{
					nn_labls[3] = 1;
					nn_cnt++;
				}

				/// 3rd row
				if(wnd_ptr3[x-1] != 0) ///P_7
				{
					nn_labls[6] = 1;
					nn_cnt++;
				}
				if(wnd_ptr3[x] != 0) ///P_6
				{
					nn_labls[5] = 1;
					nn_cnt++;
				}
				if(wnd_ptr3[x+1] != 0) ///P_5
				{
					nn_labls[4] = 1;
					nn_cnt++;
				}

				if(nn_cnt == 0)
					val_ptr[x] = 0; /// isolated node
				else if(nn_cnt == 1)
					val_ptr[x] = 2; /// a end node
				else
				{
					int ts_cnt = 0;
					for(int i = 2; i < 9; ++i)
					{
						if(nn_labls[i] != nn_labls[i-1])
							ts_cnt++;
					}
					if(nn_labls[8] != nn_labls[1]) ts_cnt++;

					if(ts_cnt >= 6)
						val_ptr[x] = 3; /// a junction node
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////

	/// tracking edges (loop is not supported right now)
	//////////////////////////////////////////////////////////////////////////
	/// clear original data
	Free_VecPtr(_edge_links);

	/// create a help map, indicate which node is processed
	Mat flag_map = Mat::zeros(exp_map.size(), CV_8UC1);

	cv::Point	junc_pnt; /// junction point
	cv::Point	crnr_pnt; /// corner point
	uchar*		val_ptr2;
	uchar*		flag_ptr;
	uchar*		flag_ptr2;
	for(int y = 1; y < exp_map.rows-1; ++y)
	{
		val_ptr	 = exp_map.ptr<uchar>(y);
		flag_ptr = flag_map.ptr<uchar>(y);
		for(int x = 1; x < exp_map.cols-1; ++x)
		{
			if(val_ptr[x] == 2 && flag_ptr[x] == 0) /// find an end node
			{
				/// set the node to be processed
				flag_ptr[x] = 1;

				/// starting a new edge link
				HKCEdgeLink* el_pt = new HKCEdgeLink;

				/// trace the edge
				if(Trace_Edge(exp_map, flag_map, el_pt, cv::Point(x,y), _offset))
				{
					/// add the new edge to the list
					_edge_links.push_back(el_pt);
				}
				else
					delete el_pt;
			}
			else if(val_ptr[x] == 3) /// a junction node
			{
				/// set the node to be a emitted source
				flag_ptr[x] = 1;

				/// current junction point
				junc_pnt.x = x;
				junc_pnt.y = y;

				/// current corner point
				crnr_pnt.x = x-1;
				crnr_pnt.y = y-1;

				/// go through its one-ring nodes and emit a edge
				for(int i = 0; i < 3; ++i)
				{
					val_ptr2	= exp_map.ptr<uchar>(crnr_pnt.y+i);
					flag_ptr2	= flag_map.ptr<uchar>(crnr_pnt.y+i);
					for(int j = 0; j < 3; ++j)
					{
						if(i == 1 && j == 1) continue;

						int x = crnr_pnt.x+j;
						if(flag_ptr2[x] == 0 && val_ptr2[x] != 0)
						{
							/// set the node to be processed
							flag_ptr2[x] = 1;

							/// starting a new line segment
							HKCEdgeLink* el_pt = new HKCEdgeLink;
							el_pt->Points().push_back(HKCEdgeLink::PntT(HKCEdgeLink::ValT(junc_pnt.x), HKCEdgeLink::ValT(junc_pnt.y))+_offset);

							/// trace the edge
							if(Trace_Edge(exp_map, flag_map, el_pt, cv::Point(crnr_pnt.x+j, crnr_pnt.y+i), _offset))
							{
								/// add the new edge to the list
								_edge_links.push_back(el_pt);
							}
							else
								delete el_pt;
						}
					}
				}
			}
		}
	}
	//printf("linking!!!!!!\n");
	for (int y = 1; y < exp_map.rows - 1; ++y)
	{
		val_ptr = exp_map.ptr<uchar>(y);
		flag_ptr = flag_map.ptr<uchar>(y);
		for (int x = 1; x < exp_map.cols - 1; ++x)
		{
			if (val_ptr[x] == 1 & flag_ptr[x] == 0) /// find an unprocessed edge node
			{
				/// set the node to be processed
				flag_ptr[x] = 1;

				/// starting a new edge link
				HKCEdgeLink* el_pt = new HKCEdgeLink;

				/// trace the edge
				Trace_Edge(exp_map, flag_map, el_pt, cv::Point(x, y), _offset);
				/// add the new edge to the list
				_edge_links.push_back(el_pt);
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////

	/// Remove edges with short length (in terms of pixel count)
	//////////////////////////////////////////////////////////////////////////
	vector<int> rmv_list;
	for(int i = (int)_edge_links.size()-1; i >= 0; --i)
	{
		HKCEdgeLink* el_pt = _edge_links[i];
		if(el_pt->Pix_Num() < _thrsh)
			rmv_list.push_back(i);
	}

	for(unsigned i = 0; i < rmv_list.size(); ++i)
		_edge_links.erase(_edge_links.begin()+rmv_list[i]);
	//////////////////////////////////////////////////////////////////////////
}

bool HKCV::Thinning(Mat& _img)
{
	if(!_img.data || _img.type() != CV_8UC1)
	{
		CV_Error(CV_StsBadArg, "_img has incorrect data or type (not CV_8UC1)");	
		return false;
	}

	int		xsize, ysize;	/// Image resolution
	int		x, y;			/// Pixel location		
	int		i;				/// Pass index			
	int		pc = 0;			/// Pass count			
	int		count = 1;		/// Deleted pixel count	
	int     pre_cnt = -1;
	int     rep_cnt = 0;
	int		p, q;			/// Neighborhood maps of adjacent
	int		m;				/// scanline : Deletion direction mask
	uchar*  qb;				/// cells : Neighborhood maps of previous		

	xsize = _img.cols;
	ysize = _img.rows;

	qb = new uchar[xsize];
	qb[xsize-1] = 0;		/* Used for lower-right pixel	*/

	uchar* val_ptr;
	uchar* val_ptr2;

	/// Scan image while deletions
	while( count ) 
	{		
		pc++;
		count = 0;
		for( i = 0 ; i < 4 ; i++ ) 
		{
			m = thin_masks[i];

			/// Build initial previous scan buffer.		
			val_ptr = _img.ptr<uchar>(0);
			p = val_ptr[0] != 0;
			for ( x = 0 ; x < xsize-1 ; x++ )
				qb[x] = p = ((p<<1)&0006) | (val_ptr[x+1] != 0);

			/// Scan image for pixel deletion candidates.
			for( y = 0 ; y < ysize-1 ; y++ ) 
			{
				val_ptr2 = _img.ptr<uchar>(y);
				val_ptr  = _img.ptr<uchar>(y+1);

				q = qb[0];
				p = ((q<<3)&0110) | (val_ptr[0] != 0);

				for ( x = 0 ; x < xsize-1 ; x++ ) 
				{
					q = qb[x];
					p = ((p<<1)&0666) | ((q<<3)&0110) |
						(val_ptr[x+1] != 0);
					qb[x] = p;
					if ( ((p&m) == 0) && thin_delete[p] ) 
					{
						count++;
						val_ptr2[x] = 0;
					}
				}

				/// Process right edge pixel.
				p = (p<<1)&0666;
				if	( (p&m) == 0 && thin_delete[p] ) 
				{
					count++;
					val_ptr2[xsize-1] = 0;
				}
			}

			/// Process bottom scan line.
			val_ptr = _img.ptr<uchar>(ysize-1);
			for( x = 0 ; x < xsize ; x++ ) 
			{
				q = qb[x];
				p = ((p<<1)&0666) | ((q<<3)&0110);
				if( (p&m) == 0 && thin_delete[p] ) 
				{
					count++;
					val_ptr[x] = 0;
				}
			}
		}

		if(pre_cnt != count)
		{
			pre_cnt = count;
			rep_cnt = 0;
		}
		else
			rep_cnt++;

		if(rep_cnt >= 5)
		{
			delete [] qb;
			qb = NULL;
			return false;
		}
	}

	delete [] qb;
	qb = NULL;

	return true;
}
/*
/// Down sample edge link (in terms of pixel count)
void HKCV::Edge_DownSample(HKCEdgeLink* _edge_link, int _size)
{
	HKCEdgeLink::VecPnt& el_pnts = _edge_link->Points();
	HKCEdgeLink::VecPnt src_pnts = el_pnts;
	HKCEdgeLink::VecPnt aprox_pnts;

	/// Approximates a polygonal curve(s) with the specified precision.
	approxPolyDP(el_pnts, aprox_pnts, 1.0, false);

	/// fit the original edge link to polygonal curve
	/// create a KD-tree for original edge points
	HKCKDtree* kdtree = new HKCKDtree;
	kdtree->Build_Tree(&(el_pnts[0].x), el_pnts.size(), 2);

	/// find corresponding point of each approximated curve point in original points
	vector<int> idx_map(aprox_pnts.size(), -1);
	idx_map[0] = 0; idx_map[idx_map.size()-1] = el_pnts.size()-1;
	vector<int>		ann_idx;
	vector<double>	ann_dist;
	for(size_t i = 1; i < idx_map.size()-1; ++i)
	{
		Point2d query(aprox_pnts[i].x, aprox_pnts[i].y);
		kdtree->Find(&(query.x), 1, ann_idx, ann_dist);
		idx_map[i] = ann_idx[0];
	}

	/// project original edge link to approximated curve and down sampling
	el_pnts.clear();
	src_pnts[0] = aprox_pnts[0];
	el_pnts.push_back(src_pnts[0]);
	for(size_t i = 1; i < idx_map.size(); ++i)
	{
		int idx1 = idx_map[i-1];
		int idx2 = idx_map[i];
		HKCEdgeLink::PntT& p1 = aprox_pnts[i-1];
		HKCEdgeLink::PntT& p2 = aprox_pnts[i];

		double lnth_sum = 0.0;
		vector<double> ratios(idx2-idx1, 0);
		for(int j = idx1+1, r = 0; j <= idx2; ++j, ++r)
		{
			lnth_sum += CvPntDist(el_pnts[j-1], el_pnts[j]);
			ratios[r] = lnth_sum;
		}

		for(int j = idx1+1, r = 0, c = 0; j < idx2; ++j, ++r, ++c)
		{
			if(c >= _size)
			{
				double w = ratios[r]/lnth_sum;
				src_pnts[j] = p1 + (p2-p1)*w;
				el_pnts.push_back(src_pnts[j]);
				c = 0;
			}
		}
		src_pnts[idx2] = p2;
		el_pnts.push_back(p2);
	}

	delete kdtree;
}

/// Smooth edge link (take average of incident neighbors)
void HKCV::Edge_Smooth(HKCEdgeLink* _edge_link, int _iter)
{
	HKCEdgeLink::VecPnt& el_pnts = _edge_link->Points();
	int	pnt_num = el_pnts.size();
	HKCEdgeLink::VecPnt tmp_pnts(pnt_num);
	for(int i = 0; i < _iter; ++i)
	{
		tmp_pnts[0] = el_pnts[0];
		tmp_pnts[pnt_num-1] = el_pnts[pnt_num-1];
		for(int j = 1; j < pnt_num-1; ++j)
			tmp_pnts[j] = (el_pnts[j-1]+el_pnts[j+1]) * 0.5;
		el_pnts = tmp_pnts;
	}
}

/// Sharpen edge link
void HKCV::Edge_Sharpen(HKCEdgeLink* _edge_link, double _epslon, bool _replace)
{
	HKCEdgeLink::VecPnt& el_pnts = _edge_link->Points();
	HKCEdgeLink::VecPnt aprox_pnts;

	/// Approximates a polygonal curve(s) with the specified precision.
	approxPolyDP(el_pnts, aprox_pnts, _epslon, false);

	/// if replace the original edge link with approximated curve?
	if(_replace)
	{
		el_pnts.clear();
		el_pnts = aprox_pnts;
		return;
	}

	/// fit the original edge link to polygonal curve
	/// create a KD-tree for original edge points
	HKCKDtree* kdtree = new HKCKDtree;
	kdtree->Build_Tree(&(el_pnts[0].x), el_pnts.size(), 2);

	/// find corresponding point of each approximated curve point in original points
	vector<int> idx_map(aprox_pnts.size(), -1);
	idx_map[0] = 0; idx_map[idx_map.size()-1] = el_pnts.size()-1;
	vector<int>		ann_idx;
	vector<double>	ann_dist;
	for(size_t i = 1; i < idx_map.size()-1; ++i)
	{
		Point2d query(aprox_pnts[i].x, aprox_pnts[i].y);
		kdtree->Find(&(query.x), 1, ann_idx, ann_dist);
		idx_map[i] = ann_idx[0];
	}

	/// project original edge link to approximated curve
	el_pnts[0] = aprox_pnts[0];
	for(size_t i = 1; i < idx_map.size(); ++i)
	{
		int idx1 = idx_map[i-1];
		int idx2 = idx_map[i];
		HKCEdgeLink::PntT& p1 = aprox_pnts[i-1];
		HKCEdgeLink::PntT& p2 = aprox_pnts[i];

		double lnth_sum = 0.0;
		vector<double> ratios(idx2-idx1, 0);
		for(int j = idx1+1, r = 0; j <= idx2; ++j, ++r)
		{
			lnth_sum += CvPntDist(el_pnts[j-1], el_pnts[j]);
			ratios[r] = lnth_sum;
		}

		for(int j = idx1+1, r = 0; j < idx2; ++j, ++r)
		{
			double w = ratios[r]/lnth_sum;
			//el_pnts[j] = p1*(1.0-w)+p2*w;
			el_pnts[j] = p1 + (p2-p1)*w;
		}
		el_pnts[idx2] = p2;
	}

	delete kdtree;
}

/// Perturb edge link
void HKCV::Edge_Perturb(HKCEdgeLink* _edge_link, int _size, double _mag)
{
	HKCEdgeLink::VecPnt& el_pnts = _edge_link->Points();
	int	pnt_num = el_pnts.size();
	int h_size = _size / 2;
	int iter = pnt_num / _size;
	for(int i = 0; i < iter; ++i)
	{
		int mid_idx = i*_size+h_size-1;
		Vec3f pre_n = Vec3f(el_pnts[mid_idx-1].y-el_pnts[mid_idx].y, el_pnts[mid_idx].x-el_pnts[mid_idx-1].x);
		Vec3f nxt_n = Vec3f(el_pnts[mid_idx].y-el_pnts[mid_idx+1].y, el_pnts[mid_idx+1].x-el_pnts[mid_idx].x);
		Vec3f mid_n = (pre_n+nxt_n)*0.5;
		normalize(mid_n, mid_n, 1, 0, NORM_L2, CV_32F);
		double rand_mag = g_RNG.uniform(-_mag, _mag);
		double slope = rand_mag/h_size;

		Vec3f offset = mid_n*rand_mag;
		el_pnts[mid_idx] = el_pnts[mid_idx] + HKCEdgeLink::PntT(offset[0], offset[1]);
		for(int j = 1; j < h_size-1; ++j)
		{
			offset = mid_n*slope*(h_size-j);
			el_pnts[mid_idx+j] = el_pnts[mid_idx+j] + HKCEdgeLink::PntT(offset[0], offset[1]);
			el_pnts[mid_idx-j] = el_pnts[mid_idx-j] + HKCEdgeLink::PntT(offset[0], offset[1]);
		}
	}
}
*/