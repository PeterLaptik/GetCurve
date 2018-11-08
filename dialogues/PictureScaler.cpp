#include "PictureScaler.h"
#include <wx/dcclient.h>
#include <wx/msgdlg.h>
#include "../res/iconsScaleDialog.h"
#include <wx/mstream.h>

#ifdef __WXGTK20__
#include <wx/settings.h>
#endif // __WXGTK20__

//(*InternalHeaders(PictureScaler)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(PictureScaler)
const long PictureScaler::ID_PANEL1 = wxNewId();
const long PictureScaler::ID_BITMAPBUTTON1 = wxNewId();
const long PictureScaler::ID_STATICTEXT1 = wxNewId();
const long PictureScaler::ID_TEXTCTRL1 = wxNewId();
const long PictureScaler::ID_STATICTEXT2 = wxNewId();
const long PictureScaler::ID_TEXTCTRL2 = wxNewId();
const long PictureScaler::ID_BITMAPBUTTON2 = wxNewId();
const long PictureScaler::ID_STATICTEXT3 = wxNewId();
const long PictureScaler::ID_TEXTCTRL3 = wxNewId();
const long PictureScaler::ID_BITMAPBUTTON3 = wxNewId();
const long PictureScaler::ID_STATICTEXT4 = wxNewId();
const long PictureScaler::ID_TEXTCTRL4 = wxNewId();
const long PictureScaler::ID_CHECKBOX1 = wxNewId();
const long PictureScaler::ID_CHECKBOX2 = wxNewId();
const long PictureScaler::ID_BUTTON1 = wxNewId();
const long PictureScaler::ID_BUTTON2 = wxNewId();
//*)

// Custom event: picture has got scale
wxDEFINE_EVENT(EVT_IMAGE_HAS_BEEN_SCALED, wxCommandEvent);

BEGIN_EVENT_TABLE(PictureScaler,wxFrame)
	//(*EventTable(PictureScaler)
	//*)
END_EVENT_TABLE()

// Pick point state enumerator
enum PointChoosing
{
    XYpoint,
    Xpoint,
    Ypoint,
    NOpoint
};

PointChoosing ptCurrent;    // current picking state

const double m_minScale = 0.25;
const double m_maxScale = 4;
const double scaleCoefficient = 1.1;
const int DRAG_IMAGE_DELAY = 10;
const int ORDER_BY_DEFAULT = 10;

PictureScaler::PictureScaler(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(PictureScaler)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer4;
	wxBoxSizer* BoxSizer5;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer7;
	wxBoxSizer* BoxSizer8;

	Create(parent, wxID_ANY, _("Image scale settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxFRAME_FLOAT_ON_PARENT, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	BoxSizer2->Add(Panel1, 1, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND, 5);
	BoxSizer3 = new wxBoxSizer(wxVERTICAL);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	BitmapButton1 = new wxBitmapButton(this, ID_BITMAPBUTTON1, GetIcon(calibrate_xy_png, calibrate_xy_png_size), wxDefaultPosition, wxSize(48,48), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	BoxSizer4->Add(BitmapButton1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("x0="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer4->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer4->Add(TextCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("y0="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer4->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer4->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer4, 1, wxALL|wxALIGN_LEFT, 5);
	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
	BitmapButton2 = new wxBitmapButton(this, ID_BITMAPBUTTON2, GetIcon(calibrate_x_png, calibrate_x_png_size), wxDefaultPosition, wxSize(48,48), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	BitmapButton2->Disable();
	BoxSizer5->Add(BitmapButton2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("y0; x="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer5->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL3, _("10"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	TextCtrl3->Disable();
	BoxSizer5->Add(TextCtrl3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer5, 1, wxALL|wxALIGN_LEFT, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	BitmapButton3 = new wxBitmapButton(this, ID_BITMAPBUTTON3, GetIcon(calibrate_y_png, calibrate_y_png_size), wxDefaultPosition, wxSize(48,48), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	BitmapButton3->Disable();
	BoxSizer6->Add(BitmapButton3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("x0; y="), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	BoxSizer6->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl4 = new wxTextCtrl(this, ID_TEXTCTRL4, _("10"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	TextCtrl4->Disable();
	BoxSizer6->Add(TextCtrl4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer6, 1, wxALL|wxALIGN_LEFT, 5);
	BoxSizer8 = new wxBoxSizer(wxVERTICAL);
	CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("Logarithmic X"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBox1->SetValue(false);
	BoxSizer8->Add(CheckBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, _("Logarithmic Y"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBox2->SetValue(false);
	BoxSizer8->Add(CheckBox2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer8, 1, wxALL|wxALIGN_LEFT, 5);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
	Button1 = new wxButton(this, ID_BUTTON1, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer7->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Button2->Disable();
	BoxSizer7->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 0, wxALL|wxALIGN_TOP, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	Center();

	Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&PictureScaler::OnImagePaint,0,this);
	Panel1->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&PictureScaler::StartDrag,0,this);
	Panel1->Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&PictureScaler::StopDrag,0,this);
	Panel1->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&PictureScaler::CancelByRightClick,0,this);
	Panel1->Connect(wxEVT_MOTION,(wxObjectEventFunction)&PictureScaler::OnDragging,0,this);
	Panel1->Connect(wxEVT_MOUSEWHEEL,(wxObjectEventFunction)&PictureScaler::OnMouseWheel,0,this);
	Panel1->Connect(wxEVT_SIZE,(wxObjectEventFunction)&PictureScaler::ImageResize,0,this);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PictureScaler::PickStartXY);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PictureScaler::PickX);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PictureScaler::PickY);
	Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PictureScaler::OnSetXLogarithmic);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PictureScaler::OnSetYLogarithmic);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PictureScaler::OnCancelClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PictureScaler::OnPressOK);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&PictureScaler::OnClose);
	//*)

    this->Maximize();
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
	m_scale = 1;
	m_startX = 0;
	m_startY = 0;
	m_isDragging = false;
	hasImage = false;
	ptCurrent = NOpoint;
	m_gotX = false;
	m_gotY = false;
	m_gotXY = false;
	m_isLogX = false;
	m_isLogY = false;
	isRescalingNow = false;
	m_minOrder = -ORDER_BY_DEFAULT;
	m_maxOrder = ORDER_BY_DEFAULT;
}

PictureScaler::~PictureScaler()
{
	//(*Destroy(PictureScaler)
	//*)
}

// Getting resource icons
wxBitmap PictureScaler::GetIcon(const unsigned char* myName, const long int mySize)
{
    wxMemoryInputStream inStream (myName, mySize);
    wxImage myImg (inStream, wxBITMAP_TYPE_PNG);
    wxBitmap myPic(myImg);
    return myPic;
}

// Set Image container
void PictureScaler::SetImageObject(ImageCurve *inImage,
                                   int minOrder,
                                   int maxOrder)
{
    image = inImage;

    if (image==NULL)
        Destroy();

    hasImage = inImage->HasImage();

    if (!hasImage)
        Destroy();

    m_imageH = image->GetImage()->GetHeight();
    m_imageW = image->GetImage()->GetWidth();
    m_image = image->GetImage();
    m_minOrder = minOrder;
    m_maxOrder = maxOrder;
}

void PictureScaler::OnImagePaint(wxPaintEvent& event)
{
    //wxBitmap myImage;
    wxString textToDraw;
    wxPen myPen(*wxRED, 1, wxSOLID);
    wxPaintDC dc(Panel1);

    if (!hasImage)
        return;

    wxBitmap myImage (m_image->Scale(m_imageW*m_scale, m_imageH*m_scale));
    dc.DrawBitmap(myImage, m_startX, m_startY);

    dc.SetPen(myPen);
    if (m_gotXY)
    {
        dc.DrawLine(m_startX + ptZeroXshift*m_scale, dc.GetSize().GetHeight(),
                    m_startX + ptZeroXshift*m_scale, 0);

        dc.DrawLine(dc.GetSize().GetWidth(), m_startY + ptZeroYshift*m_scale,
                    0, m_startY + ptZeroYshift*m_scale);

        textToDraw.Clear();
        textToDraw<<wxT("[")<<ptZeroXRealValue<<wxT(";")<<ptZeroYRealValue<<wxT("]");
        dc.DrawText(textToDraw, m_startX + ptZeroXshift*m_scale, m_startY + ptZeroYshift*m_scale);
    }

    if (m_gotX)
    {
        dc.DrawLine(m_startX + ptLineXshift*m_scale, m_startY + ptZeroYshift*m_scale,
                    m_startX + ptLineXshift*m_scale, 0);

        textToDraw.Clear();
        textToDraw<<wxT("[")<<ptLineXRealValue<<wxT(";")<<ptZeroYRealValue<<wxT("]");
        dc.DrawText(textToDraw, m_startX + ptLineXshift*m_scale, m_startY + ptZeroYshift*m_scale);
        textToDraw.Clear();
        textToDraw<<ptLineXRealValue;
        dc.DrawText(textToDraw, m_startX + ptLineXshift*m_scale, 0);
    }

    if (m_gotY)
    {
        dc.DrawLine(m_startX + ptZeroXshift*m_scale, m_startY + ptLineYshift*m_scale,
                    dc.GetSize().x, m_startY + ptLineYshift*m_scale);

        textToDraw.Clear();
        textToDraw<<wxT("[")<<ptZeroXRealValue<<wxT(";")<<ptLineYRealValue<<wxT("]");
        dc.DrawText(textToDraw, m_startX + ptZeroXshift*m_scale, m_startY + ptLineYshift*m_scale);
        textToDraw.Clear();
        textToDraw<<ptLineYRealValue;
        dc.DrawText(textToDraw, dc.GetSize().GetWidth()-(textToDraw.length()*10), m_startY + ptLineYshift*m_scale);
    }
}

void PictureScaler::ImageResize(wxSizeEvent& event)
{
    Panel1->Refresh();
}

// Changes image scale
void PictureScaler::OnMouseWheel(wxMouseEvent& event)
{
    if (event.GetWheelRotation()>0)
    {
        if (m_scale<m_maxScale)
        {
            m_scale *= scaleCoefficient;
        }
        else
        {
            m_scale /= scaleCoefficient;
        }
    }
    else
    {
        if (m_scale>m_minScale)
        {
            m_scale /= scaleCoefficient;
        }
        else
        {
            m_scale *= scaleCoefficient;
        }
    }
    Panel1->Refresh();
}

// Drag image or picking points:
// Mouse left button has been pressed
void PictureScaler::StartDrag(wxMouseEvent& event)
{
    wxString textToDraw;
    switch(ptCurrent)
    {
        // Dragging image
        case NOpoint:
            {
                m_isDragging = true;
                m_dragX = event.GetPosition().x;
                m_dragY = event.GetPosition().y;
                break;
            }

        // Choosing points
        case XYpoint:
            {
                ptZeroXshift = (event.GetPosition().x - m_startX)/m_scale;
                ptZeroYshift = (event.GetPosition().y - m_startY)/m_scale;
                TextCtrl1->GetValue().ToDouble(&ptZeroXRealValue);
                TextCtrl2->GetValue().ToDouble(&ptZeroYRealValue);
                Panel1->SetCursor(*wxSTANDARD_CURSOR);
                ptCurrent = NOpoint;
                if (((ptZeroXRealValue<image->GetMinOrder()) && (m_isLogX)) ||
                    ((ptZeroYRealValue<image->GetMinOrder()) && (m_isLogY)))
                {
                    wxMessageBox("Wrong point value for the logarithmic scale!");
                    Button2->Enable(false);
                    return;
                }
                m_gotXY = true;
                BitmapButton2->Enable();
                BitmapButton3->Enable();
                TextCtrl3->Enable();
                TextCtrl4->Enable();
                Panel1->Refresh();
                break;
            }
        case Xpoint:
            {
                ptLineXshift = (event.GetPosition().x - m_startX)/m_scale;
                TextCtrl3->GetValue().ToDouble(&ptLineXRealValue);
                Panel1->SetCursor(*wxSTANDARD_CURSOR);
                ptCurrent = NOpoint;
                if (((ptLineXshift<ptZeroXshift)&&(ptLineXRealValue>ptZeroXRealValue)) ||
                    ((ptLineXshift>ptZeroXshift)&&(ptLineXRealValue<ptZeroXRealValue)) ||
                    (ptLineXRealValue==ptZeroXRealValue) || (ptLineXshift==ptZeroXshift))
                {
                    wxMessageBox("Wrong x-point");
                    Button2->Enable(false);
                    return;
                }
                m_gotX = true;
                Panel1->Refresh();
                break;
            }
        case Ypoint:
            {
                ptLineYshift = (event.GetPosition().y - m_startY)/m_scale;
                TextCtrl4->GetValue().ToDouble(&ptLineYRealValue);
                Panel1->SetCursor(*wxSTANDARD_CURSOR);
                ptCurrent = NOpoint;
                if (((ptLineYshift<ptZeroYshift)&&(ptLineYRealValue<ptZeroYRealValue)) ||
                    ((ptLineYshift>ptZeroYshift)&&(ptLineYRealValue>ptZeroYRealValue)) ||
                    (ptLineYRealValue==ptZeroYRealValue) || (ptLineYshift==ptZeroYshift))
                {
                    wxMessageBox("Wrong y-point");
                    Button2->Enable(false);
                    return;
                }
                m_gotY = true;
                Panel1->Refresh();
                break;
            }
    }

    if (m_gotXY && m_gotX && m_gotY)
        Button2->Enable();
}

// Stop dragging:
// Mouse left button has been released
void PictureScaler::StopDrag(wxMouseEvent& event)
{
    m_isDragging = false;
}

// Drag image on mouse move
void PictureScaler::OnDragging(wxMouseEvent& event)
{
    int x, y;

    if (!m_isDragging)  // mouse left button is not pressed
        return;

    if ((fabs(m_dragX - x)<DRAG_IMAGE_DELAY) ||
        (fabs(m_dragY - y)<DRAG_IMAGE_DELAY))
        return;

    x = event.GetPosition().x;
    y = event.GetPosition().y;
    m_startX -= (m_dragX - x);
    m_startY -= (m_dragY - y);
    m_dragX = x;
    m_dragY = y;
    Panel1->Refresh();
}

// Button XY has been pressed
void PictureScaler::PickStartXY(wxCommandEvent& event)
{
    ptCurrent = XYpoint;
    Panel1->SetCursor(*wxCROSS_CURSOR);
    Panel1->SetFocus();
}

// Button line-X has been pressed
void PictureScaler::PickX(wxCommandEvent& event)
{
    ptCurrent = Xpoint;
    Panel1->SetCursor(*wxCROSS_CURSOR);
    Panel1->SetFocus();
}

// Button line-Y has been pressed
void PictureScaler::PickY(wxCommandEvent& event)
{
    ptCurrent = Ypoint;
    Panel1->SetCursor(*wxCROSS_CURSOR);
    Panel1->SetFocus();
}

void PictureScaler::OnSetXLogarithmic(wxCommandEvent& event)
{
    m_isLogX = CheckBox1->GetValue();
}

void PictureScaler::OnSetYLogarithmic(wxCommandEvent& event)
{
    m_isLogY = CheckBox2->GetValue();
}

// Button OK has been pressed
void PictureScaler::OnPressOK(wxCommandEvent& event)
{
    wxCommandEvent myEvent(EVT_IMAGE_HAS_BEEN_SCALED);
    // Overall check
    if ((m_isLogX) &&
        ((ptZeroXRealValue<image->GetMinOrder()) || (ptLineXRealValue<image->GetMinOrder())))
    {
        wxMessageBox("Wrong x-values for the logarithmic axis!");
        return;
    }

    if ((m_isLogY) && ((ptZeroYRealValue<image->GetMinOrder()) || (ptLineYRealValue<image->GetMinOrder())))
    {
        wxMessageBox("Wrong y-values for the logarithmic axis!");
        return;
    }

    if (((ptLineXshift<ptZeroXshift)&&(ptLineXRealValue>ptZeroXRealValue)) ||
        ((ptLineXshift>ptZeroXshift)&&(ptLineXRealValue<ptZeroXRealValue)) ||
        (ptLineXRealValue==ptZeroXRealValue) || (ptLineXshift==ptZeroXshift))
        {
            wxMessageBox("X-value does not match to zero point!");
            Button2->Enable(false);
            return;
        }

    if (((ptLineYshift<ptZeroYshift)&&(ptLineYRealValue<ptZeroYRealValue)) ||
        ((ptLineYshift>ptZeroYshift)&&(ptLineYRealValue>ptZeroYRealValue)) ||
        (ptLineYRealValue==ptZeroYRealValue) || (ptLineYshift==ptZeroYshift))
        {
            wxMessageBox("Y-value does not match to zero point!");
            Button2->Enable(false);
            return;
        }

    // Numeric check
    if ((m_isLogX) &&
        ((ptZeroXshift<pow(10, m_minOrder)) || (ptZeroXRealValue<pow(10, m_minOrder))))
    {
        wxMessageBox("Numbers are out of range!");
        Button2->Enable(false);
        return;
    }

    if ((m_isLogY) &&
        ((ptZeroYshift<pow(10, m_minOrder)) || (ptZeroYRealValue<pow(10, m_minOrder))))
    {
        wxMessageBox("Numbers are out of range!");
        Button2->Enable(false);
        return;
    }

    if ((ptZeroYshift>pow(10, m_maxOrder)) || (ptZeroYRealValue>pow(10, m_maxOrder)) ||
        (ptZeroXshift>pow(10, m_maxOrder)) || (ptZeroXRealValue>pow(10, m_maxOrder)))
    {
        wxMessageBox("Too high number values!");
        Button2->Enable(false);
        return;
    }

    if ((ptZeroYshift<-pow(10, m_maxOrder)) || (ptZeroYRealValue<-pow(10, m_maxOrder)) ||
        (ptZeroXshift<-pow(10, m_maxOrder)) || (ptZeroXRealValue<-pow(10, m_maxOrder)))
    {
        wxMessageBox("Too low number values!");
        Button2->Enable(false);
        return;
    }

    // Set data for an image container
    image->SetIsXLog(m_isLogX);
    image->SetIsYLog(m_isLogY);
    image->SetXYZeroShift(ptZeroXshift, ptZeroYshift, ptZeroXRealValue, ptZeroYRealValue);
    image->SetXLine(ptLineXshift, ptLineXRealValue);
    image->SetYLine(ptLineYshift, ptLineYRealValue);
    image->SetScaled(true);
    wxPostEvent(this, myEvent);
    Destroy();
}

void PictureScaler::SetIsRescaling(bool rescale)
{
    isRescalingNow = rescale;
}

void PictureScaler::OnCancelClick(wxCommandEvent& event)
{
    if (!isRescalingNow)
        image->DeletePicture();

    Destroy();
}

void PictureScaler::OnClose(wxCloseEvent& event)
{
    if (!isRescalingNow)
        image->DeletePicture();

    Destroy();
}

void PictureScaler::CancelByRightClick(wxMouseEvent& event)
{
    ptCurrent = NOpoint;
    Panel1->SetCursor(*wxSTANDARD_CURSOR);
}
