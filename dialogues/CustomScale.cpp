#include "CustomScale.h"

//(*InternalHeaders(CustomScale)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(CustomScale)
const long CustomScale::ID_STATICTEXT1 = wxNewId();
const long CustomScale::ID_TEXTCTRL1 = wxNewId();
const long CustomScale::ID_STATICTEXT2 = wxNewId();
const long CustomScale::ID_TEXTCTRL2 = wxNewId();
const long CustomScale::ID_STATICTEXT3 = wxNewId();
const long CustomScale::ID_TEXTCTRL3 = wxNewId();
const long CustomScale::ID_STATICTEXT4 = wxNewId();
const long CustomScale::ID_TEXTCTRL4 = wxNewId();
const long CustomScale::ID_BUTTON1 = wxNewId();
const long CustomScale::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CustomScale,wxDialog)
	//(*EventTable(CustomScale)
	//*)
END_EVENT_TABLE()

CustomScale::CustomScale(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CustomScale)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;

	Create(parent, wxID_ANY, _("Scale graph panel"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Xmin="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlXmin = new wxTextCtrl(this, ID_TEXTCTRL1, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(TextCtrlXmin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Xmax="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer2->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlXmax = new wxTextCtrl(this, ID_TEXTCTRL2, _("100"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer2->Add(TextCtrlXmax, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Ymin="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlYmin = new wxTextCtrl(this, ID_TEXTCTRL3, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	BoxSizer3->Add(TextCtrlYmin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Ymax="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer3->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlYmax = new wxTextCtrl(this, ID_TEXTCTRL4, _("100"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	BoxSizer3->Add(TextCtrlYmax, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	Button1 = new wxButton(this, ID_BUTTON1, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer4->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer4->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CustomScale::CancelClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CustomScale::OKClick);
	//*)

	if (!TextCtrlXmin->GetValue().ToDouble(&m_Xmin))
        m_Xmin = 0;

	if (!TextCtrlXmax->GetValue().ToDouble(&m_Xmax))
        m_Xmax = 0;

	if (!TextCtrlYmin->GetValue().ToDouble(&m_Ymin))
        m_Ymin = 0;

	if (!TextCtrlYmax->GetValue().ToDouble(&m_Ymax))
        m_Ymax = 0;
}

CustomScale::~CustomScale()
{
	//(*Destroy(CustomScale)
	//*)
}

void CustomScale::OKClick(wxCommandEvent& event)
{
    if (!TextCtrlXmin->GetValue().ToDouble(&m_Xmin))
        m_Xmin = 0;

	if (!TextCtrlXmax->GetValue().ToDouble(&m_Xmax))
        m_Xmax = 0;

	if (!TextCtrlYmin->GetValue().ToDouble(&m_Ymin))
        m_Ymin = 0;

	if (!TextCtrlYmax->GetValue().ToDouble(&m_Ymax))
        m_Ymax = 0;

    if ((m_Xmin>m_Xmax) || (m_Ymin>m_Ymax))
    {
        wxMessageBox("Wrong borders!");
        return;
    }

    panelPt->ScaleSetFramePosition(m_Xmin, m_Xmax, m_Ymax, m_Ymin);
    Destroy();
}

void CustomScale::CancelClick(wxCommandEvent& event)
{
    Destroy();
}
