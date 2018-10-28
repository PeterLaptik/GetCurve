#ifndef POLYNOMIALWINDOW_H
#define POLYNOMIALWINDOW_H

//(*Headers(PolynomialWindow)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/sizer.h>
//*)

class PolynomialWindow: public wxFrame
{
	public:

		PolynomialWindow(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~PolynomialWindow();
		void ShowError(void);

		//(*Declarations(PolynomialWindow)
		wxButton* Button1;
		wxGrid* coeffGrid;
		//*)

	protected:

		//(*Identifiers(PolynomialWindow)
		static const long ID_GRID1;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(PolynomialWindow)
		void CloseHasBeenPressed(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnMaximize(wxMouseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()

		wxString m_textOut; // test for output
};

#endif
