#include "PolynomialWindow.h"

//(*InternalHeaders(PolynomialWindow)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PolynomialWindow)
const long PolynomialWindow::ID_GRID1 = wxNewId();
const long PolynomialWindow::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PolynomialWindow,wxFrame)
	//(*EventTable(PolynomialWindow)
	//*)
END_EVENT_TABLE()

const int MAX_POINTS = 20;

PolynomialWindow::PolynomialWindow(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(PolynomialWindow)
	wxBoxSizer* BoxSizer1;

	Create(parent, id, _("Polynomial coefficients"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxFRAME_TOOL_WINDOW|wxFRAME_FLOAT_ON_PARENT|wxCLIP_CHILDREN, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	coeffGrid = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
	coeffGrid->CreateGrid(20,1);
	coeffGrid->EnableEditing(true);
	coeffGrid->EnableGridLines(true);
	coeffGrid->SetRowLabelSize(64);
	coeffGrid->SetDefaultColSize(128, true);
	coeffGrid->SetColLabelValue(0, _("value"));
	coeffGrid->SetDefaultCellFont( coeffGrid->GetFont() );
	coeffGrid->SetDefaultCellTextColour( coeffGrid->GetForegroundColour() );
	BoxSizer1->Add(coeffGrid, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 32);
	Button1 = new wxButton(this, ID_BUTTON1, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(Button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PolynomialWindow::CloseHasBeenPressed);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&PolynomialWindow::OnClose);
	Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&PolynomialWindow::OnMaximize);
	//*)

	#ifndef __WXGTK20__
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
	coeffGrid->SetDefaultCellBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
	#endif // __WXGTK20__

	for (int i=0; i<MAX_POINTS; ++i)
    {
        m_textOut = wxT("a");
        m_textOut<<i;
        coeffGrid->SetRowLabelValue(i, m_textOut);
        coeffGrid->SetCellBackgroundColour(i, 0, *wxWHITE);
        coeffGrid->SetReadOnly(i, 0, true);
    }
    this->SetMaxSize(wxSize(GetSize().x*1.25, GetSize().y*1.25));
}

PolynomialWindow::~PolynomialWindow()
{
	//(*Destroy(PolynomialWindow)
	//*)
}


void PolynomialWindow::CloseHasBeenPressed(wxCommandEvent& event)
{
    Hide();
}

void PolynomialWindow::OnClose(wxCloseEvent& event)
{
    Hide();
}

void PolynomialWindow::OnMaximize(wxMouseEvent& event)
{
    return;
}

void PolynomialWindow::ShowError()
{
    for (int i=0; i<MAX_POINTS; ++i)
    {
        coeffGrid->SetCellValue(i,0,wxT("-"));
    }
    coeffGrid->SetCellValue(0,0,wxT("Error"));
}
