#ifndef PICTURESCALER_H
#define PICTURESCALER_H

#include "../controls/imageCurve.h"

//(*Headers(PictureScaler)
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

// Custom event
// Occurs when image has been scaled
// Has to be catch in GetCurveMain
BEGIN_DECLARE_EVENT_TYPES()
    wxDECLARE_EVENT(EVT_IMAGE_HAS_BEEN_SCALED, wxCommandEvent);
END_DECLARE_EVENT_TYPES()

class PictureScaler: public wxFrame
{
	public:

		PictureScaler(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PictureScaler();

		void SetImageObject(ImageCurve *inImage,
                            int minOrder,
                            int maxOrder);

		void SetIsRescaling(bool rescale);

		//(*Declarations(PictureScaler)
		wxBitmapButton* BitmapButton1;
		wxBitmapButton* BitmapButton2;
		wxBitmapButton* BitmapButton3;
		wxButton* Button1;
		wxButton* Button2;
		wxCheckBox* CheckBox1;
		wxCheckBox* CheckBox2;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxTextCtrl* TextCtrl1;
		wxTextCtrl* TextCtrl2;
		wxTextCtrl* TextCtrl3;
		wxTextCtrl* TextCtrl4;
		//*)

	protected:

		//(*Identifiers(PictureScaler)
		static const long ID_PANEL1;
		static const long ID_BITMAPBUTTON1;
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_BITMAPBUTTON2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_BITMAPBUTTON3;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(PictureScaler)
		void OnImagePaint(wxPaintEvent& event);
		void ImageResize(wxSizeEvent& event);
		void OnMouseWheel(wxMouseEvent& event);
		void StartDrag(wxMouseEvent& event);
		void StopDrag(wxMouseEvent& event);
		void OnDragging(wxMouseEvent& event);
		void PickStartXY(wxCommandEvent& event);
		void PickX(wxCommandEvent& event);
		void PickY(wxCommandEvent& event);
		void OnSetXLogarithmic(wxCommandEvent& event);
		void OnSetYLogarithmic(wxCommandEvent& event);
		void OnPressOK(wxCommandEvent& event);
		void OnCancelClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void CancelByRightClick(wxMouseEvent& event);
		//*)

		wxBitmap GetIcon(const unsigned char* myName, const long int mySize); // icon from resources

		DECLARE_EVENT_TABLE()

		ImageCurve *image;
		wxImage *m_image;
		bool isRescalingNow;
		bool hasImage;
		int m_imageW;   // image width
		int m_imageH;   // image height
		double m_scale;
		int m_startX;
		int m_startY;
		bool m_isDragging;
		int m_dragX;
		int m_dragY;

		// Defined points / scaling
		bool m_gotX;
		bool m_gotY;
		bool m_gotXY;
		bool m_isLogX;
		bool m_isLogY;
		int ptZeroXshift;
		int ptZeroYshift;
		double ptZeroXRealValue;
		double ptZeroYRealValue;
		int ptLineXshift;
		double ptLineXRealValue;
		int ptLineYshift;
		double ptLineYRealValue;

		// Limits
		int m_minOrder;
		int m_maxOrder;
};

#endif
