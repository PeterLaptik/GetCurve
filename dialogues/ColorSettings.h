#ifndef COLORSETTINGS_H
#define COLORSETTINGS_H

#include "../controls/wxCurvePanel.h"

//(*Headers(ColorSettings)
#include <wx/button.h>
#include <wx/colordlg.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
//*)

class ColorSettings: public wxDialog
{
	public:

		ColorSettings(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ColorSettings();
		void SetTarget (CurvePanel *target);

		//(*Declarations(ColorSettings)
		wxButton* Button1;
		wxButton* Button2;
		wxButton* Button3;
		wxButton* Button4;
		wxColourDialog* ColourDialog1;
		wxPanel* clrCanvas;
		wxPanel* clrCoord;
		wxPanel* clrCoordAdds;
		wxPanel* clrMainLine;
		wxPanel* clrPoints;
		wxPanel* clrText;
		wxPanel* clrTextErr;
		wxPanel* clrZero;
		wxSpinCtrl* radPoint;
		wxSpinCtrl* thkLine;
		wxStaticText* StaticText10;
		wxStaticText* StaticText1;
		wxStaticText* StaticText2;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxStaticText* StaticText6;
		wxStaticText* StaticText7;
		wxStaticText* StaticText8;
		wxStaticText* StaticText9;
		//*)

	protected:

		//(*Identifiers(ColorSettings)
		static const long ID_STATICTEXT1;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT2;
		static const long ID_PANEL2;
		static const long ID_STATICTEXT3;
		static const long ID_PANEL3;
		static const long ID_STATICTEXT4;
		static const long ID_PANEL4;
		static const long ID_STATICTEXT5;
		static const long ID_PANEL5;
		static const long ID_STATICTEXT6;
		static const long ID_PANEL6;
		static const long ID_STATICTEXT7;
		static const long ID_PANEL7;
		static const long ID_STATICTEXT8;
		static const long ID_PANEL8;
		static const long ID_STATICTEXT9;
		static const long ID_SPINCTRL1;
		static const long ID_STATICTEXT10;
		static const long ID_SPINCTRL2;
		static const long ID_BUTTON1;
		static const long ID_BUTTON3;
		static const long ID_BUTTON2;
		static const long ID_BUTTON4;
		//*)

	private:

		//(*Handlers(ColorSettings)
		void ChangeBackground(wxMouseEvent& event);
		void ChangeZeroLineColour(wxMouseEvent& event);
		void ChangeCoordinateLineColour(wxMouseEvent& event);
		void ChangeCoordinateLineAddsColour(wxMouseEvent& event);
		void ApplyNewSettings(wxCommandEvent& event);
		void ClickCancel(wxCommandEvent& event);
		void ClickOK(wxCommandEvent& event);
		void SetDefault(wxCommandEvent& event);
		void OnclrZeroPaint(wxPaintEvent& event);
		void ChangeMainLineColor(wxMouseEvent& event);
		void ChangeMainLineColour(wxMouseEvent& event);
		void ChangePointsColour(wxMouseEvent& event);
		void ChangeTextColour(wxMouseEvent& event);
		void ChangeTextErrorColour(wxMouseEvent& event);
		void ChangeMainLineThickness(wxSpinEvent& event);
		void ChangePointRadius(wxSpinEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

		void RefreshColors(void);

		CurvePanel *targetPanel;
		wxUint32 colorCanvas;       // panel color
        wxUint32 colorZero;         // zero-lines color
        wxUint32 colorCoord;        // coordinate lines color
        wxUint32 colorCoordAdds;    // additional coordinate lines color
        wxUint32 colorLine;         // curve color
        wxUint32 colorPoint;        // point color
        wxUint32 colorText;         // normal text color
        wxUint32 colorTextErr;      // error text color
};

#endif
