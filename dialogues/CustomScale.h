#ifndef CUSTOMSCALE_H
#define CUSTOMSCALE_H

//(*Headers(CustomScale)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

#include "../controls/wxPanelGraph.h"

class CustomScale: public wxDialog
{
	public:

		CustomScale(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CustomScale();

		void SetPanel(wxPanelGraph *p)
		{
		    panelPt = p;
		}

		//(*Declarations(CustomScale)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxTextCtrl* TextCtrlXmax;
		wxTextCtrl* TextCtrlXmin;
		wxTextCtrl* TextCtrlYmax;
		wxTextCtrl* TextCtrlYmin;
		//*)

	protected:

		//(*Identifiers(CustomScale)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		static const long ID_STATICTEXT3;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT4;
		static const long ID_TEXTCTRL4;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(CustomScale)
		void OKClick(wxCommandEvent& event);
		void CancelClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

		// Scale data
		double m_Xmin;
		double m_Xmax;
		double m_Ymin;
		double m_Ymax;
		wxPanelGraph *panelPt;
};

#endif
