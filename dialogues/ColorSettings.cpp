#include "ColorSettings.h"

//(*InternalHeaders(ColorSettings)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(ColorSettings)
const long ColorSettings::ID_STATICTEXT1 = wxNewId();
const long ColorSettings::ID_PANEL1 = wxNewId();
const long ColorSettings::ID_STATICTEXT2 = wxNewId();
const long ColorSettings::ID_PANEL2 = wxNewId();
const long ColorSettings::ID_STATICTEXT3 = wxNewId();
const long ColorSettings::ID_PANEL3 = wxNewId();
const long ColorSettings::ID_STATICTEXT4 = wxNewId();
const long ColorSettings::ID_PANEL4 = wxNewId();
const long ColorSettings::ID_STATICTEXT5 = wxNewId();
const long ColorSettings::ID_PANEL5 = wxNewId();
const long ColorSettings::ID_STATICTEXT6 = wxNewId();
const long ColorSettings::ID_PANEL6 = wxNewId();
const long ColorSettings::ID_STATICTEXT7 = wxNewId();
const long ColorSettings::ID_PANEL7 = wxNewId();
const long ColorSettings::ID_STATICTEXT8 = wxNewId();
const long ColorSettings::ID_PANEL8 = wxNewId();
const long ColorSettings::ID_STATICTEXT9 = wxNewId();
const long ColorSettings::ID_SPINCTRL1 = wxNewId();
const long ColorSettings::ID_STATICTEXT10 = wxNewId();
const long ColorSettings::ID_SPINCTRL2 = wxNewId();
const long ColorSettings::ID_BUTTON1 = wxNewId();
const long ColorSettings::ID_BUTTON3 = wxNewId();
const long ColorSettings::ID_BUTTON2 = wxNewId();
const long ColorSettings::ID_BUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ColorSettings,wxDialog)
	//(*EventTable(ColorSettings)
	//*)
END_EVENT_TABLE()

// Drafting settings for a target object
const int MINIMUM_LINE_THICKNESS = 1;
const int MIMIMUM_POINT_RADIUS = 0;

ColorSettings::ColorSettings(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ColorSettings)
	wxBoxSizer* BoxSizer11;
	wxBoxSizer* BoxSizer12;
	wxBoxSizer* BoxSizer1;
	wxGridSizer* GridSizer1;

	Create(parent, wxID_ANY, _("Display settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	GridSizer1 = new wxGridSizer(10, 2, 0, 0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Canvas background color"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	GridSizer1->Add(StaticText1, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	clrCanvas = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(48,16), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	GridSizer1->Add(clrCanvas, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Zero axis lines color"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	GridSizer1->Add(StaticText2, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	clrZero = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxSize(48,16), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	GridSizer1->Add(clrZero, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Coordinate lines color"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	GridSizer1->Add(StaticText3, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	clrCoord = new wxPanel(this, ID_PANEL3, wxDefaultPosition, wxSize(48,16), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	GridSizer1->Add(clrCoord, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Coordinate extralines color"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	GridSizer1->Add(StaticText4, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	clrCoordAdds = new wxPanel(this, ID_PANEL4, wxDefaultPosition, wxSize(48,16), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	GridSizer1->Add(clrCoordAdds, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("Main line color"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	GridSizer1->Add(StaticText5, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	clrMainLine = new wxPanel(this, ID_PANEL5, wxDefaultPosition, wxSize(48,16), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	GridSizer1->Add(clrMainLine, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Points color"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	GridSizer1->Add(StaticText6, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	clrPoints = new wxPanel(this, ID_PANEL6, wxDefaultPosition, wxSize(48,16), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	GridSizer1->Add(clrPoints, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Normal text color"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	GridSizer1->Add(StaticText7, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	clrText = new wxPanel(this, ID_PANEL7, wxDefaultPosition, wxSize(48,16), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL7"));
	GridSizer1->Add(clrText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	StaticText8 = new wxStaticText(this, ID_STATICTEXT8, _("Error text color"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	GridSizer1->Add(StaticText8, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	clrTextErr = new wxPanel(this, ID_PANEL8, wxDefaultPosition, wxSize(48,16), wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL8"));
	GridSizer1->Add(clrTextErr, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	StaticText9 = new wxStaticText(this, ID_STATICTEXT9, _("Line thickness"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	GridSizer1->Add(StaticText9, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	thkLine = new wxSpinCtrl(this, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL1"));
	thkLine->SetValue(_T("0"));
	GridSizer1->Add(thkLine, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(this, ID_STATICTEXT10, _("Point radius"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	GridSizer1->Add(StaticText10, 1, wxLEFT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 32);
	radPoint = new wxSpinCtrl(this, ID_SPINCTRL2, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_SPINCTRL2"));
	radPoint->SetValue(_T("0"));
	GridSizer1->Add(radPoint, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(GridSizer1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxSHAPED|wxFIXED_MINSIZE, 5);
	BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
	Button1 = new wxButton(this, ID_BUTTON1, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer12->Add(Button1, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
	Button3 = new wxButton(this, ID_BUTTON3, _("Apply"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	Button3->Disable();
	BoxSizer12->Add(Button3, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer12->Add(Button2, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer12, 0, wxALL|wxALIGN_RIGHT, 16);
	BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
	Button4 = new wxButton(this, ID_BUTTON4, _("Reset to default"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer11->Add(Button4, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxSHAPED, 5);
	BoxSizer1->Add(BoxSizer11, 0, wxBOTTOM|wxLEFT|wxSHAPED, 16);
	SetSizer(BoxSizer1);
	ColourDialog1 = new wxColourDialog(this);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	clrCanvas->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&ColorSettings::ChangeBackground,0,this);
	clrZero->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&ColorSettings::ChangeZeroLineColour,0,this);
	clrCoord->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&ColorSettings::ChangeCoordinateLineColour,0,this);
	clrCoordAdds->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&ColorSettings::ChangeCoordinateLineAddsColour,0,this);
	clrMainLine->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&ColorSettings::ChangeMainLineColour,0,this);
	clrPoints->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&ColorSettings::ChangePointsColour,0,this);
	clrText->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&ColorSettings::ChangeTextColour,0,this);
	clrTextErr->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&ColorSettings::ChangeTextErrorColour,0,this);
	Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ColorSettings::ChangeMainLineThickness);
	Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&ColorSettings::ChangePointRadius);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ColorSettings::ClickCancel);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ColorSettings::ApplyNewSettings);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ColorSettings::ClickOK);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ColorSettings::SetDefault);
	//*)
	//this->SetSize(BoxSizer1->GetSize().GetWidth(),BoxSizer1->GetSize().GetHeight());
	//this->SetSize(800,800);
}

ColorSettings::~ColorSettings()
{
	//(*Destroy(ColorSettings)
	//*)
}

void ColorSettings::SetTarget (CurvePanel *target)
{
    targetPanel = target;
    thkLine->SetValue(targetPanel->GetMainLineThickness());
    thkLine->SetMin(MINIMUM_LINE_THICKNESS);
	thkLine->SetMax(targetPanel->GetMaxLineThickness());
	radPoint->SetValue(targetPanel->GetPointRadius());
	radPoint->SetMin(MIMIMUM_POINT_RADIUS);
	radPoint->SetMax(targetPanel->GetMaxPointRadius());
    RefreshColors();
}

// Gets panel colors data and refreshes rectangles
void ColorSettings::RefreshColors()
{
    colorCanvas = targetPanel->GetPanelColour();
    clrCanvas->SetBackgroundColour(wxColour(colorCanvas));
    colorZero = targetPanel->GetLinesZeroColour();
    clrZero->SetBackgroundColour(wxColour(colorZero));
    colorCoord = targetPanel->GetLinesCoordColour();
    clrCoord->SetBackgroundColour(wxColour(colorCoord));
    colorCoordAdds = targetPanel->GetLinesCoordAddsColour();
    clrCoordAdds->SetBackgroundColour(wxColour(colorCoordAdds));
    colorLine = targetPanel->GetMainLineColour();
    clrMainLine->SetBackgroundColour(wxColour(colorLine));
    colorPoint = targetPanel->GetPointColour();
    clrPoints->SetBackgroundColour(wxColour(colorPoint));
    colorText = targetPanel->GetTextColour();
    clrText->SetBackgroundColour(wxColour(colorText));
    colorTextErr = targetPanel->GetTextErrorColour();
    clrTextErr->SetBackgroundColour(wxColour(colorTextErr));
    radPoint->SetValue(targetPanel->GetPointRadius());
    thkLine->SetValue(targetPanel->GetMainLineThickness());
    this->Refresh();
}

// Canvas background
void ColorSettings::ChangeBackground(wxMouseEvent& event)
{
    wxColourDialog *dlg = new wxColourDialog(this);

    if(dlg->ShowModal()==wxID_OK)
    {
        colorCanvas = dlg->GetColourData().GetColour().GetRGB();
        clrCanvas->SetBackgroundColour(wxColour(colorCanvas));
        clrCanvas->Refresh();
        Button3->Enable(true);
    }
    delete dlg;
}

void ColorSettings::ChangeZeroLineColour(wxMouseEvent& event)
{
    wxColourDialog *dlg = new wxColourDialog(this);

    if(dlg->ShowModal()==wxID_OK)
    {
        colorZero = dlg->GetColourData().GetColour().GetRGB();
        clrZero->SetBackgroundColour(wxColour(colorZero));
        clrZero->Refresh();
        Button3->Enable(true);
    }
    delete dlg;
}

void ColorSettings::ChangeCoordinateLineColour(wxMouseEvent& event)
{
    wxColourDialog *dlg = new wxColourDialog(this);

    if(dlg->ShowModal()==wxID_OK)
    {
        colorCoord = dlg->GetColourData().GetColour().GetRGB();
        clrCoord->SetBackgroundColour(wxColour(colorCoord));
        clrCoord->Refresh();
        Button3->Enable(true);
    }
    delete dlg;
}

void ColorSettings::ChangeCoordinateLineAddsColour(wxMouseEvent& event)
{
    wxColourDialog *dlg = new wxColourDialog(this);

    if(dlg->ShowModal()==wxID_OK)
    {
        colorCoordAdds = dlg->GetColourData().GetColour().GetRGB();
        clrCoordAdds->SetBackgroundColour(wxColour(colorCoordAdds));
        clrCoordAdds->Refresh();
        Button3->Enable(true);
    }
    delete dlg;
}

void ColorSettings::SetDefault(wxCommandEvent& event)
{
    wxMessageDialog *dlg = new wxMessageDialog (this, wxT("Restore default settings?"),
                                                wxT("GetCurve message"), wxYES_NO|wxCENTRE,
                                                wxDefaultPosition);
    int dlgResult = dlg->ShowModal();

    switch (dlgResult)
    {
    case wxID_NO:
        {
            delete dlg;
            return;
        }
    }
    delete dlg;

    targetPanel->RestoreDisplayDefaults();
    RefreshColors();
}


void ColorSettings::ChangeMainLineColour(wxMouseEvent& event)
{
    wxColourDialog *dlg = new wxColourDialog(this);

    if(dlg->ShowModal()==wxID_OK)
    {
        colorLine = dlg->GetColourData().GetColour().GetRGB();
        clrMainLine->SetBackgroundColour(wxColour(colorLine));
        clrMainLine->Refresh();
        Button3->Enable(true);
    }
    delete dlg;
}

void ColorSettings::ChangePointsColour(wxMouseEvent& event)
{
    wxColourDialog *dlg = new wxColourDialog(this);

    if(dlg->ShowModal()==wxID_OK)
    {
        colorPoint = dlg->GetColourData().GetColour().GetRGB();
        clrPoints->SetBackgroundColour(wxColour(colorPoint));
        clrPoints->Refresh();
        Button3->Enable(true);
    }
    delete dlg;
}

void ColorSettings::ChangeTextColour(wxMouseEvent& event)
{
    wxColourDialog *dlg = new wxColourDialog(this);

    if(dlg->ShowModal()==wxID_OK)
    {
        colorText = dlg->GetColourData().GetColour().GetRGB();
        clrText->SetBackgroundColour(wxColour(colorText));
        clrText->Refresh();
        Button3->Enable(true);
    }
    delete dlg;
}

void ColorSettings::ChangeTextErrorColour(wxMouseEvent& event)
{
    wxColourDialog *dlg = new wxColourDialog(this);

    if(dlg->ShowModal()==wxID_OK)
    {
        colorTextErr = dlg->GetColourData().GetColour().GetRGB();
        clrTextErr->SetBackgroundColour(wxColour(colorTextErr));
        clrTextErr->Refresh();
        Button3->Enable(true);
    }
    delete dlg;
}

void ColorSettings::ChangeMainLineThickness(wxSpinEvent& event)
{
    targetPanel->SetMainLineThickness(thkLine->GetValue());
}

void ColorSettings::ChangePointRadius(wxSpinEvent& event)
{
    targetPanel->SetPointRadius(radPoint->GetValue());
}

void ColorSettings::ApplyNewSettings(wxCommandEvent& event)
{
    targetPanel->SetPanelColour(colorCanvas);
    targetPanel->SetLinesZeroColour(colorZero);
    targetPanel->SetLinesCoordColour(colorCoord);
    targetPanel->SetLinesCoordAddsColour(colorCoordAdds);
    targetPanel->SetMainLineColour(colorLine);
    targetPanel->SetPointColour(colorPoint);
    targetPanel->SetTextColour(colorText);
    targetPanel->SetTextErrorColour(colorTextErr);
    Button3->Enable(false);
}

void ColorSettings::ClickCancel(wxCommandEvent& event)
{
    Destroy();
}

void ColorSettings::ClickOK(wxCommandEvent& event)
{
    wxCommandEvent applyEvent;
    ApplyNewSettings(applyEvent);
    Destroy();
}
