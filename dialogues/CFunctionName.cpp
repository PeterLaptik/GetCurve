#include "CFunctionName.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(CFunctionName)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(CFunctionName)
const long CFunctionName::ID_STATICTEXT1 = wxNewId();
const long CFunctionName::ID_TEXTCTRL1 = wxNewId();
const long CFunctionName::ID_BUTTON1 = wxNewId();
const long CFunctionName::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CFunctionName,wxDialog)
	//(*EventTable(CFunctionName)
	//*)
END_EVENT_TABLE()

CFunctionName::CFunctionName(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CFunctionName)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;

	Create(parent, wxID_ANY, _("Enter function name"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Function name:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer3->Add(StaticText1, 1, wxALL|wxALIGN_LEFT, 5);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("GetValue"), wxDefaultPosition, wxSize(277,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer3->Add(TextCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	Button1 = new wxButton(this, ID_BUTTON1, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer2->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CFunctionName::OnCancelPressed);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CFunctionName::OnOKPressed);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&CFunctionName::OnClose);
	//*)
	m_result = wxEmptyString;
	Button2->SetFocus();
}

CFunctionName::~CFunctionName()
{
	//(*Destroy(CFunctionName)
	//*)
}


void CFunctionName::OnCancelPressed(wxCommandEvent& event)
{
    this->Hide();
}

void CFunctionName::OnClose(wxCloseEvent& event)
{
    this->Hide();
}

void CFunctionName::OnOKPressed(wxCommandEvent& event)
{
    m_result = TextCtrl1->GetValue();
    this->Hide();
}

wxString CFunctionName::GetResult()
{
    return m_result;
}
