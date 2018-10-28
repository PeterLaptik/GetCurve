#ifndef CFUNCTIONNAME_H
#define CFUNCTIONNAME_H

//(*Headers(CFunctionName)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class CFunctionName: public wxDialog
{
	public:

		CFunctionName(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CFunctionName();
		wxString GetResult(void);

		//(*Declarations(CFunctionName)
		wxButton* Button1;
		wxButton* Button2;
		wxStaticText* StaticText1;
		wxTextCtrl* TextCtrl1;
		//*)

	protected:

		//(*Identifiers(CFunctionName)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(CFunctionName)
		void PressedCancel(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnOKPressed(wxCommandEvent& event);
		void OnCancelPressed(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

		wxString m_result;
};

#endif
