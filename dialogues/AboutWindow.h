#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

//(*Headers(AboutWindow)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class AboutWindow: public wxDialog
{
	public:

		AboutWindow(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AboutWindow();

		//(*Declarations(AboutWindow)
		wxButton* Button1;
		wxStaticBitmap* StaticBitmap1;
		wxStaticText* StaticText1;
		wxTextCtrl* TextCtrl1;
		//*)

	protected:

		//(*Identifiers(AboutWindow)
		static const long ID_STATICTEXT1;
		static const long ID_STATICBITMAP1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(AboutWindow)
		void OnButton1Click(wxCommandEvent& event);
		//*)

		wxBitmap GetIcon(const unsigned char* myName, const long int mySize); // icon from resources

		DECLARE_EVENT_TABLE()
};

#endif
