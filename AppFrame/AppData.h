/**
* @file AppData.h
*
* Classes for application data
*
* @author James Hung-Kuo Chu
*/

#ifndef _APPDATA_H_
#define _APPDATA_H_

#include "AppWordArtData.h"
#include "AppQRCData.h"

namespace AppFrame
{	
	/**
	*	@brief Class for transformation
	*/
	class HKCXForm
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCXForm(void) { Clear(); }

		HKCXForm(const HKCXForm& _rhs)
		{
			Move	= _rhs.Move;
			Scale	= _rhs.Scale;
			Center	= _rhs.Center;
			Angle	= _rhs.Angle;
			Mirror	= _rhs.Mirror;		
			State	= _rhs.State;
			memcpy(XForm, _rhs.XForm, 16*sizeof(double));
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                   Initialization                             */
		/*! \{                                                                 */

		/// clear data
		void Clear(void)
		{
			Move  = cv::Vec2d(0.0,0.0);
			Scale = cv::Vec2d(1.0,1.0);
			//Center = cv::Point2d(0.0,0.0);
			Angle = 0.0;			
			Mirror = false;			
			memset(XForm, 0, 16*sizeof(double));
			XForm[0] = XForm[5] = XForm[10] = XForm[15] = 1.0;
			State = 0;
		}

		/*bool Changed(void)
		{
			return !(Move == cv::Vec2d(0.0,0.0) && Scale == cv::Vec2d(1.0,1.0) && 
				Angle == 0.0 && Mirror == false);
		}*/

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                      Operators                               */
		/*! \{                                                                 */

		/// operator=
		HKCXForm& operator=(const HKCXForm& _rhs)
		{
			if(this == &_rhs) return (*this);

			Move	= _rhs.Move;
			Scale	= _rhs.Scale;
			Center	= _rhs.Center;
			Angle	= _rhs.Angle;
			Mirror	= _rhs.Mirror;	
			State	= _rhs.State;
			memcpy(XForm, _rhs.XForm, 16*sizeof(double));

			return (*this);
		}
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                       Methods                                */
		/*! \{                                                                 */

		void Update(void)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslated(Move[0], Move[1], 0.0);
			glTranslated(Center.x, Center.y, 0.0);
			glRotated(Angle, 0.0, 0.0, 1.0);
			if(Mirror) glScaled(-Scale[0], Scale[1], 1.0);
			else glScaled(Scale[0], Scale[1], 1.0);
			glTranslated(-Center.x, -Center.y, 0.0);
			glGetDoublev(GL_MODELVIEW_MATRIX, XForm);
			glPopMatrix();
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                        Data                                  */
		/*! \{                                                                 */

		cv::Vec2d	Move;		///< Translation vector
		cv::Vec2d	Scale;		///< Scaling factors
		cv::Point2d Center;		///< Center of rotation
		cv::Point2d Mouse;		///< Mouse position
		double		Angle;		///< Angle of rotation	
		bool		Mirror;		///< Flag of mirror
		double		XForm[16];	///< Resultant affine transformation matrix
		int			State;		///< State of transformation

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the application data
	*/
	class IOHandle
	{
		/*==========================  PUBLIC  =================================*/
	public:		                                                               
		IOHandle(void) { Clear(); }		
		~IOHandle(void) { Clear(); }

		/// clear data
		void Clear(void) 
		{
			config_ver=1;
			vbf_filename = std::string("");
			seg_filename = std::string("");
			art_filename = std::string("");
			gap_filename = std::string("");
			wordart_filename = std::string("");
			flowfield_loaded= false;
			article_loaded =false;

			rs_control = true;
			sw_control = false;
			cw_control = true;
			im_control = true;

			rs_done = false;
		}

		/*! \}                                                                 */
		/*==========================  PUBLIC  =================================*/
	public:	
		int config_ver;
		std::string vbf_filename;
		std::string seg_filename;	
		std::string art_filename;
		std::string gap_filename;
		std::string wordart_filename;

		bool flowfield_loaded;
		bool article_loaded;

		bool rs_control;
		bool rs_done;
		bool sw_control;
		bool cw_control;
		bool im_control;
	};

	/**
	*	@brief Class for the application data
	*/
	class HKCAppData
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                    Constructors                              */
		/*! \{                                                                 */

		HKCAppData(void) { Clear(); }		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */

		~HKCAppData(void) { Clear(); }

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                      Methods                                 */
		/*! \{                                                                 */

		/// clear data
		void Clear(void) 
		{
			QRCData.Clear();
			WordArtEvi.Clear();
			WordArtEdt.Clear();
			IO_Handle.Clear();

			CurrentWordArtID = 0;
			WordArtData.resize(6);//預設6個: 0為初始WordArt,其餘1-5為Warping結果
		}

		/*! \}                                                                 */
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{     
		*/
		IOHandle IO_Handle;
		HKCQRCData	   QRCData;    //QR code
		HKCWordArtEvi  WordArtEvi; //Word Art Environment
		HKCWordArtEdt  WordArtEdt;

		int CurrentWordArtID;
		std::vector<HKCWordArtData> WordArtData;
		/*! \}                                                                 */
	};
}

#endif