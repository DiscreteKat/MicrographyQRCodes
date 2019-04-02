#ifndef _HKEDGELINKING_H_
#define _HKEDGELINKING_H_

namespace HKCV
{
	/**
	*	@brief Class for Edge Link
	*/
	class HKCEdgeLink
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                     Typedef                                  */
		/*! \{                                                                 */

		typedef cv::Point2f			PntT;
		typedef PntT::value_type	ValT;
		typedef std::vector<PntT>		VecPnt;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCEdgeLink(void) { Clear(); }
		HKCEdgeLink(VecPnt pnts) { m_Pnts=pnts; }
		HKCEdgeLink(const HKCEdgeLink& _rhs) { (*this) = _rhs; }

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		
		
		~HKCEdgeLink(void) { Clear(); }

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                   Initialization                             */
		/*! \{                                                                 */

		void Clear(void)
		{
			m_Pnts.clear();
			m_Lnth = 0.0;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                      Operators                               */
		/*! \{                                                                 */

		HKCEdgeLink& operator=(const HKCEdgeLink& _rhs)
		{
			if(this == &_rhs) return (*this);

			m_Pnts	= _rhs.m_Pnts;
			m_Lnth	= _rhs.m_Lnth;

			return (*this);
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		/// Edge points
		VecPnt& Points(void) { return m_Pnts; }
		const VecPnt& Points(void) const { return m_Pnts; }

		/// Number of pixels
		int Pix_Num(void) { return m_Pnts.size(); }

		/// Euclidean distance
		double& Length(void) { return m_Lnth; }
		const double& Length(void) const { return m_Lnth; }

		cv::Point2f get_tangent(int id)
		{
			if (id!=0)
			{
				return cv::Point2f((m_Pnts[id].x-m_Pnts[id-1].x),(m_Pnts[id].y-m_Pnts[id-1].y));
			}
			else
			{
				return cv::Point2f((m_Pnts[id+1].x-m_Pnts[id].x),(m_Pnts[id+1].y-m_Pnts[id].y));
			}			
		}

		bool find_tangent(cv::Point2f& pnt,cv::Point2f& tangent)
		{
			VecPnt::iterator it;
			it=find(m_Pnts.begin(),m_Pnts.end(),pnt);
			int index = std::distance(m_Pnts.begin(), it);
			if (it != m_Pnts.end())
			{
				tangent=get_tangent(index);
					return true;
			}
			else
			{
				return false;
			}
			
		}

		/*! \}                                                                 */
		/*===========================  PRIVATE  ===============================*/
	private:		
		/*---------------------------------------------------------------------*/		
		/*! \name                        Data                                  */
		/*! \{                                                                 */

		VecPnt	m_Pnts;
		double	m_Lnth;

		/*! \}                                                                 */
	};

	/// type define for the vector of edge links
	typedef std::vector<HKCEdgeLink*> VecEdgeLink;

	/// Convert the edge map into edge links and 
	/// remove edges with short length (in terms of pixel count)
	void Edge_Linking(cv::Mat&, VecEdgeLink&, HKCEdgeLink::PntT, int);	

	bool Thinning(cv::Mat& _img);
	/*
	/// Down sample edge link (in terms of pixel count)
	void Edge_DownSample(HKCEdgeLink*, int);

	/// Smooth edge link (take average of incident neighbors)
	void Edge_Smooth(HKCEdgeLink*, int);

	/// Sharpen edge link
	void Edge_Sharpen(HKCEdgeLink*, double, bool);

	/// Perturb edge link
	void Edge_Perturb(HKCEdgeLink*, int, double);
	*/
}

#endif