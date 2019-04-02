/**
* @file AppRenderDefault.cpp
*
* Implementation of the class methods for default application render
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppTool.h"
#include "AppToolManager.h"
#include "AppRender.h"

using namespace HKUtils;
using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCRenderDef

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                          Render Methods                             */
/// Render application item
void HKCRenderDef::Render(HKCAppItem^ _appItem, HKOGLPanelControl^ _glPanel)
{
	if(!_appItem) return;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_POLYGON_SMOOTH);	
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//   (0,0)--------->y (0,y)
	//      |
	//      |
	//      |
	//      V
	//      x
	//    (x,0) 
	/// Render media items
	
	for each(HKCMediaItem^ media in _appItem->Items)
	{
		if(media->glContext == _glPanel)
		{
			media->Render();

			if(System::String::Compare("Region", media->Label) == 0  && media->Prop->Render->Visible )
			{
				vector<cv::Mat>&  region_segs  = _appItem->Data->WordArtEvi.region_segs;
				int region = _appItem->Data->WordArtEdt.select_region;
				if (region!=-1)
				{
					int height = region_segs[region].rows;
					glColor3d(1.0,1.0,0.0);
					glBegin(GL_QUADS);
					for (int i=0;i<region_segs[region].rows;i++)
					{
						for (int j=0;j<region_segs[region].cols;j++)
						{
							int idx = region_segs[region].cols*i+j;
							if (region_segs[region].data[idx]!=0)
							{
								glVertex2d(j  ,height-i);
								glVertex2d(j+1,height-i);
								glVertex2d(j+1,height-i-1);
								glVertex2d(j  ,height-i-1);
							}
						}
					}
					glEnd();
				}
			}

// 			if(System::String::Compare("BoldWarpingTest", media->Label) == 0  && media->Prop->Render->Visible )
// 			{
// 				glEnable( GL_BLEND );
// 				HKCWordArtEvi& string_lines_data = _appItem->Data->WordArtEvi;
// 				QRWordArt::QRStringLines& splines = _appItem->Data->WordArtData[0].splines;
// 				HKCWordArtEdt& Edt_data = _appItem->Data->WordArtEdt;
// 				for(int i=0; i<Edt_data.boldwarpBG.size(); i++)
// 				{
// 					double alpha = 1;
// 					double r = Edt_data.boldwarpBG[i].scalar[1];
// 					double s = Edt_data.boldwarpBG[i].SplineID;
// 					double c = Edt_data.boldwarpBG[i].CharID;
// 					glColor4d(r,r,r,alpha);
// 					splines[s]->GetQRSamples()[c]->qr_char->DrawBoundingBox();
// 					glColor4d(0.0,0.0,1.0,1.0);
// 				}
// 			}

// 			if(System::String::Compare("Frame", media->Label) == 0  && media->Prop->Render->Visible )
// 			{
//  				glEnable( GL_BLEND );
//  				double x=210;
//  				double y=190;
//  				double w=70;
//  				double h=70;
//  				glColor4d(0.0,0.0,1.0,1);
//  				glLineWidth(3.0f);
//  				glBegin(GL_LINE_LOOP);
//  				glVertex2d(x,y);
//  				glVertex2d(x,y+h);
//  				glVertex2d(x+w,y+h);
//  				glVertex2d(x+w,y);
//  				glEnd();
//  				glDisable( GL_BLEND );
// 			}

			if(System::String::Compare("Editing", media->Label) == 0  && media->Prop->Render->Visible )
			{
				glEnable( GL_BLEND );
				if(_appItem->Data->WordArtEdt.OrdEditingMode==false&&_appItem->Data->WordArtEdt.TextbaseEditingMode==false)
				{
					//¼gmedia->RanderTexture
					HKCWordArtEvi& string_lines_data = _appItem->Data->WordArtEvi;
					QRWordArt::QRStringLines& splines = _appItem->Data->WordArtData[0].splines;
					for(int i=0; i<splines.size(); i++)
					{
						double alpha = 0.5;
						if (_appItem->Data->WordArtEdt.select==i)alpha = 0.9;
						glColor4d(1.0,1.0,1.0,alpha);
						splines[i]->DrawStroke();
						glColor4d(0.0,0.0,1.0,1.0);
						splines[i]->DrawLine();
						splines[i]->DrawCtrlPoint();
					}

					if (_appItem->Data->WordArtEdt.select!=-1)
					{
						HSSSpline::PathPoint<5> p = splines[_appItem->Data->WordArtEdt.select]->GetCtrlPoint(_appItem->Data->WordArtEdt.select_ctrlpoint);
						glColor3d(1.0,1.0,0);
						glBegin(GL_POINTS);
						glVertex2d(p[0],p[1]);
						glEnd();
					}
				}
				else if(_appItem->Data->WordArtEdt.TextbaseEditingMode==true||_appItem->Data->WordArtEdt.ScalingEditingMode==true)
				{
					//¼gmedia->RanderTexture
					HKCWordArtEvi& string_lines_data = _appItem->Data->WordArtEvi;
					QRWordArt::QRStringLines& splines = _appItem->Data->WordArtData[0].splines;
					
					QRWordArt::QRStringLine::QRSamples& c_samples=splines[_appItem->Data->WordArtEdt.select]->GetQRSamples();
					glPointSize(10);
					if (_appItem->Data->WordArtEdt.select_char!=-1)
					{
						HSSSpline::PathPoint<5> p = splines[_appItem->Data->WordArtEdt.select]->get_point(c_samples[_appItem->Data->WordArtEdt.select_char]->sample);
						glColor3d(1.0,1.0,0);
						glBegin(GL_POINTS);
						glVertex2d(p[0],p[1]);
						glEnd();
					}
					else if (_appItem->Data->WordArtEdt.select_word!=-1)
					{
						QRWordArt::QRStringLine::QRSamples w_sample =splines[_appItem->Data->WordArtEdt.select]->GetWordSamples()[_appItem->Data->WordArtEdt.select_word];
						
						glColor3d(1.0,1.0,0);
						glBegin(GL_POINTS);
						for(int i = 0 ; i <w_sample.size();i++)
						{
							HSSSpline::PathPoint<5> p =splines[_appItem->Data->WordArtEdt.select]->get_point(w_sample[i]->sample);
							glVertex2d(p[0],p[1]);
						}
						glEnd();
					}
					else if (_appItem->Data->WordArtEdt.select!=-1)
					{
						glColor3d(1.0,1.0,0);
						glBegin(GL_POINTS);
						for(int i = 0 ; i <c_samples.size();i++)
						{
							HSSSpline::PathPoint<5> p = splines[_appItem->Data->WordArtEdt.select]->get_point(c_samples[i]->sample);
							glVertex2d(p[0],p[1]);
						}
						glEnd();
					}
				}
				else if(_appItem->Data->WordArtEdt.OrdEditingMode==true)
				{
					//¼gmedia->RanderTexture
					HKCWordArtEvi& string_lines_data = _appItem->Data->WordArtEvi;
					QRWordArt::QRStringLines& splines = _appItem->Data->WordArtData[0].splines;
					for(int i=0; i<splines.size(); i++)
					{						
						
						if (i==_appItem->Data->WordArtEdt.select_record){glColor4d(1.0,0.0,0.0,1.0);}
						else if (i==_appItem->Data->WordArtEdt.select){glColor4d(0.0,0.0,1.0,1.0);}
						else{glColor4d(0.0,1.0,0.0,1.0);}

						splines[i]->DrawLine(HSSSpline::Sample(0,0),HSSSpline::Sample(splines[i]->n_segs()-1,1));
						//splines[i]->DrawMidPoint();
						glColor4d(1.0,1.0,1.0,0.5);
						if (i!=0)
						{
							glLineWidth(3.0);
							glBegin(GL_LINES);
							HSSSpline::PathPoint<5> p1 = splines[i]->get_midpoint();
							HSSSpline::PathPoint<5> p2 = splines[i-1]->get_midpoint();
							glVertex2d(p1[0],p1[1]);
							glVertex2d(p2[0],p2[1]);
							glEnd();
						}
					}

					if (_appItem->Data->WordArtEdt.select!=-1&&_appItem->Data->WordArtEdt.select_record!=-1)
					{
						HSSSpline::PathPoint<5> p1 = splines[_appItem->Data->WordArtEdt.select_record]->get_midpoint();
						HSSSpline::PathPoint<5> p2 = splines[_appItem->Data->WordArtEdt.select]->get_midpoint();
						GLint factor=4;// ­È¥i§ï¬°1~5
						GLushort pattern=0x5555;
						glEnable(GL_LINE_STIPPLE);
						glColor3d(1.0,1.0,0);
						glLineStipple( factor,pattern);
						glBegin(GL_LINES);
						glVertex2d(p1[0],p1[1]);
						glVertex2d(p2[0],p2[1]);		
						glEnd();
						glDisable(GL_LINE_STIPPLE);
					}
				}
				glDisable( GL_BLEND );
			}
			
			if(System::String::Compare("Word Art", media->Label) == 0  && media->Prop->Render->Visible &&_appItem->Data->WordArtEdt.OrdEditingMode==false)
			{
				int word_art_idx =  _appItem->Data->CurrentWordArtID;
				QRWordArt::QRStringLines& spline = _appItem->Data->WordArtData[word_art_idx].splines;
				for (int sp_id=0;sp_id<spline.size();sp_id++){spline[sp_id]->DrawWordArt(false);}
			}

			if(System::String::Compare("Pattern", media->Label) == 0 && media->Prop->Render->Visible )
			{
				glEnable( GL_BLEND );
				glEnable(GL_TEXTURE_2D);
				int word_art_idx =  _appItem->Data->CurrentWordArtID;
				QRWordArt::QRPatterns* patterns = patterns = &_appItem->Data->WordArtData[word_art_idx].pattern_blending;
				for (int i=0;i<patterns->size();i++){(*patterns)[i].Draw();}
				glDisable(GL_TEXTURE_2D);
				glDisable( GL_BLEND );
			}

			//*
				cv::Point   posn(151,150);
				int fsize =72;
				glColor3d(0.0,0.0,1.0);
				glLineWidth(2.0);
				glBegin(GL_LINE_STRIP);
				glVertex2d(posn.x-0.5*fsize+0.5,posn.y-0.5*fsize+0.5);
				glVertex2d(posn.x+0.5*fsize+0.5,posn.y-0.5*fsize+0.5);
				glVertex2d(posn.x+0.5*fsize+0.5,posn.y+0.5*fsize+0.5);
				glVertex2d(posn.x-0.5*fsize+0.5,posn.y+0.5*fsize+0.5);
				glVertex2d(posn.x-0.5*fsize+0.5,posn.y-0.5*fsize+0.5);
				glEnd();
			//*/
		}
	}	
	glPopAttrib();
}

/// Render application tool
void HKCRenderDef::Render(HKCAppToolMgr^ _toolMgr, HKOGLPanelControl^ _glPanel)
{
	if(!_toolMgr) return;

	/// Render tools
	for each(HKCAppTool^ tool in _toolMgr->Tools){tool->Render();}
}