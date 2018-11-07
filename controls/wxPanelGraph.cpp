#include "wxPanelGraph.h"

// Custom event. See description in the header file
wxDEFINE_EVENT(EVT_GOT_POINT, wxCommandEvent);

// Predefined settings
const int borderHShift = 40;                    // letters shift from horizontal border
const int borderVShift = 20;                    // letter shift from vertical border
const double borderStartX = 100;                // initial border values / initial picture scale
const double borderStartY = 100;                // initial border values / initial picture scale
const int zeroXYForLogarithmicDefault = -2;     // power for logarithmic edge points
const double zeroLineForLogarithmic = 1;        // zero line coordinate for logarithmic axises
const int minGridToShowCorners = 3;             // minimum grid number (sparse grid) to show additional coordinates
const int maxOrder = 10;                        // maximum order for numbers
const int minOrder = -10;                       // minimum order for numbers
const int maxBaseNumber = 20;                   // maximum base number for grid dividing
const double zeroValue = 9.4e-10;               // trim to zero

// Scaling
const double SCALE_ZOOM_COEFF = 1.25;
bool m_needToBeZoomedOut;

// Default palette settings
const wxColour DEFAULT_COLOUR_PANEL = wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK);
const wxColour DEFAULT_COLOUR_LINES_ZERO = *wxBLACK;
const wxColour DEFAULT_COLOUR_LINES_COORD = *wxBLUE;
const wxColour DEFAULT_COLOUR_LINES_COORD_ADDS = wxColour(200,200,200);
const wxColour DEFAULT_COLOUR_ERROR_TEXT = *wxRED;

wxPanelGraph::wxPanelGraph(wxPanel *parent,
                     int id,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style,
                     const wxString& name)
            : wxPanel(parent, id, pos, size, style, name)
{
    // Scale settings
    m_borderLeft = 0;
    m_borderRight = borderStartX;
    m_borderUp = borderStartY;
    m_borderDown = 0;
    m_isMousePressed = false;
    m_startX = 0;
    m_startY = 0;
    m_maxDelta = 150;
    m_isXscaleLocked = false;
    m_isYscaleLocked = false;
    // Appearance
    m_isXlogarithmic = false;
    m_isYlogarithmic = false;
    m_isDragLocked = false;
    m_showZeroLines = true;
    m_showHorNet = true;
    m_showVertNet = true;
    m_showHorAddNet = true;
    m_showVertAddNet = true;
    zeroXYLogPower = zeroXYForLogarithmicDefault;
    zeroXYForLogarithmic = pow(10, zeroXYLogPower);
    m_width = this->GetSize().GetWidth();
    m_height = this->GetSize().GetHeight();
    // Colors and brushes settings
    m_palette_zeroLines = DEFAULT_COLOUR_LINES_ZERO.GetRGB();
    m_palette_coordLines = DEFAULT_COLOUR_LINES_COORD.GetRGB();
    m_palette_coordAddLines = DEFAULT_COLOUR_LINES_COORD_ADDS.GetRGB();
    m_palette_myColor = DEFAULT_COLOUR_PANEL.GetRGB();
    m_palette_text = DEFAULT_COLOUR_LINES_ZERO.GetRGB();
    m_palette_text_error = DEFAULT_COLOUR_ERROR_TEXT.GetRGB();
    this->SetBackgroundColour(m_palette_myColor);
    // events
    Connect(wxEVT_PAINT, wxPaintEventHandler(wxPanelGraph::OnPaint));
    Connect(wxEVT_SIZE, wxSizeEventHandler(wxPanelGraph::OnSize));
    Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(wxPanelGraph::OnPanelGraphMouseWheel));
    Connect(wxEVT_MOTION, wxMouseEventHandler(wxPanelGraph::OnPanelGraphMouseMove));
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(wxPanelGraph::OnPanelGraphMouseDown));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(wxPanelGraph::OnPanelGraphMouseUp));
}

wxPanelGraph::~wxPanelGraph()
{

}

void wxPanelGraph::OnSize(wxSizeEvent& event)
{
    m_width = this->GetSize().GetWidth();
    m_height = this->GetSize().GetHeight();
    this->Refresh();
}

void wxPanelGraph::OnPanelGraphMouseUp(wxMouseEvent& event)
{
    m_isMousePressed = false;
    m_startX = 0;   // clear start position
    m_startY = 0;   // clear start position
    this->Refresh();
}

void wxPanelGraph::OnPanelGraphMouseDown(wxMouseEvent& event)
{
    if (m_isPicking)
    {
        m_x = event.GetX();
        m_y = event.GetY();
        CoordinatesTransform(m_x, m_y);
        wxCommandEvent m_event (EVT_GOT_POINT);
        wxPostEvent(this, m_event);
        return;                 // no dragging when on picking
    }
    m_isMousePressed = true;
    m_startX = event.GetX();    // start position for dragging picture
    m_startY = event.GetY();    // start position for dragging picture
}

// Transforms local coordinates into global coordinates
void wxPanelGraph::CoordinatesTransform(double &x, double &y)
{
    double a, b;    // logarithmic borders
    double c;       // logarithmic position

    if (!m_isXlogarithmic)
    {
        x = m_borderLeft + (m_borderRight - m_borderLeft)/m_width*x;

    }
    else
    {
        a = log10(m_borderLeft);
        b = log10(m_borderRight);
        c = a + x/m_width*(b - a);
        x = pow(10, c);
    }

    if (!m_isYlogarithmic)
    {
        y = m_borderUp - (m_borderUp - m_borderDown)/m_height*y;
    }
    else
    {
        a = log10(m_borderDown);
        b = log10(m_borderUp);
        c = a + (m_height - y)/m_height*(b - a);
        y = pow(10, c);
    }
}

// Transforms global coordinates into the local ones
void wxPanelGraph::CoordinatesReverseTransfrom(double &x, double &y)
{
    double a, b;    // logarithmic borders
    double c;       // logarithmic position

    if (!m_isXlogarithmic)
    {
        x = m_width*(x - m_borderLeft)/(m_borderRight - m_borderLeft);
    }
    else if (x!=0)
        {
            a = log10(m_borderLeft);
            b = log10(m_borderRight);
            c = log10(x);
            x = m_width*(c - a)/(b - a);
        }
    else {x = 0;}

    if (!m_isYlogarithmic)
    {
        y = m_height - m_height*(y - m_borderDown)/(m_borderUp - m_borderDown);
    }
    else if (y!=0)
        {
            a = log10(m_borderDown);
            b = log10(m_borderUp);
            c = log10(y);
            y = m_height - m_height*(c - a)/(b - a);
        }
    else {/*y = 0*/ y = m_height /* bottom border */;}
}

// Mouse move event
// Receive x/y-coordinates and send them into output
// if left-mouse button is pressed - drags picture
void wxPanelGraph::OnPanelGraphMouseMove(wxMouseEvent& event)
{
    double dx, dy;
    int x, y;

    x = m_x = event.GetX();
    y = m_y = event.GetY();
    CoordinatesTransform(m_x, m_y);
    this->CoordinatesOutput();

    if ((!m_isMousePressed) || (m_isDragLocked))
        return;

    if (m_isXlogarithmic && m_isYlogarithmic)
        return;

    dx = m_startX - x;
    dy = m_startY - y;
    dx /= m_width;
    dx *= (m_borderRight - m_borderLeft);
    dy /= m_height;
    dy *= (m_borderUp - m_borderDown);

    if (!m_isXlogarithmic)
    {
        m_borderLeft += dx;
        m_borderRight += dx;
        m_startX = x;
    }
    else { /****** Locked for shifting ******/ }

    if (!m_isYlogarithmic)
    {
        m_borderUp -= dy;
        m_borderDown -= dy;
        m_startY = y;
    }
    else { /****** Locked for shifting ******/ }

    /* excluded
    if ((!m_isXlogarithmic) && (!m_isYlogarithmic))
        this->Refresh();
    */
    this->Refresh();
}

// Changes a picture scale if mouse wheel moves
void wxPanelGraph::OnPanelGraphMouseWheel(wxMouseEvent& event)
{
    if (event.GetWheelRotation()<0)
        ZoomOut();

    if (event.GetWheelRotation()>0)
        ZoomIn();
}

// Zoom in
// Scales are limited by minOrder and maxOrder constants
// X or Y scales can be locked
void wxPanelGraph::ZoomIn()
{
    double deltaX;
    double deltaY;

    if ((!m_isXscaleLocked) &&
        (m_borderRight - m_borderLeft>pow(10,minOrder)))
    {
        deltaX = ((m_borderRight - m_borderLeft)/SCALE_ZOOM_COEFF);
        deltaX -= m_borderRight - m_borderLeft;
        deltaX /= 2;
        m_borderLeft -= deltaX;
        m_borderRight += deltaX;
    }
    if ((!m_isYscaleLocked) &&
        (m_borderUp - m_borderDown>pow(10,minOrder)))
    {
        deltaY = ((m_borderUp - m_borderDown)/SCALE_ZOOM_COEFF);
        deltaY -= m_borderUp - m_borderDown;
        deltaY /= 2;
        m_borderUp += deltaY;
        m_borderDown -= deltaY;
    }

    if (m_isYlogarithmic)
        m_borderDown = zeroXYForLogarithmic;

    if (m_isXlogarithmic)
        m_borderLeft = zeroXYForLogarithmic;

    this->Refresh();
}

// Zoom out
// Scales are limited by minOrder and maxOrder constants
// X or Y scales can be locked
void wxPanelGraph::ZoomOut()
{
    double deltaX;
    double deltaY;

    if ((!m_isXscaleLocked) &&
        (m_borderRight - m_borderLeft<pow(10,maxOrder)))
    {
        deltaX = ((m_borderRight - m_borderLeft)*SCALE_ZOOM_COEFF);
        deltaX -= m_borderRight - m_borderLeft;
        deltaX /= 2;
        m_borderLeft -= deltaX;
        m_borderRight += deltaX;
    }
    if ((!m_isYscaleLocked) &&
        (m_borderUp - m_borderDown<pow(10,maxOrder)))
    {
        deltaY = ((m_borderUp - m_borderDown)*SCALE_ZOOM_COEFF);
        deltaY -= m_borderUp - m_borderDown;
        deltaY /= 2;
        m_borderUp += deltaY;
        m_borderDown -= deltaY;
    }

    if (m_isYlogarithmic)
        m_borderDown = zeroXYForLogarithmic;

    if (m_isXlogarithmic)
        m_borderLeft = zeroXYForLogarithmic;

    this->Refresh();
}

// Paints on memory dc
void wxPanelGraph::OnPaintMemoryDC(wxDC &memDC)
{
    memDC.Clear();

    // Draw underlayer picture:
    m_underlayerPicture.DrawPicture(memDC, m_borderLeft, m_borderRight,
                                    m_borderUp, m_borderDown,
                                    m_width, m_height,
                                    m_isXlogarithmic, m_isYlogarithmic);

    if (!m_isXlogarithmic)
    {
        MakeVerticalNetLines(memDC);
    }
    else
    {
        MakeVerticalNetLinesLog(memDC);
    }

    if (!m_isYlogarithmic)
    {
        MakeHorizontalNetLines(memDC);
    }
    else
    {
        MakeHorizontalNetLinesLog(memDC);
    }

    MakeZeroLines(memDC);
    // Virtual function for subclasses output
    DrawMe(memDC); // drawing entities by subclasses
}

// On-paint event
// Draws line nets and calls a virtual method for subclasses
void wxPanelGraph::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    dc.Clear();

    // Draw underlayer picture:
    m_underlayerPicture.DrawPicture(dc, m_borderLeft, m_borderRight,
                                    m_borderUp, m_borderDown,
                                    m_width, m_height,
                                    m_isXlogarithmic, m_isYlogarithmic);

    //if (m_borderUp<m_borderDown)
        //wxMessageBox(_T("Hello error!"));

    // avoid errors
    if (m_borderLeft>m_borderRight)
        m_borderRight = m_borderLeft + pow(10, zeroXYLogPower + 1);
    if (m_borderDown>m_borderUp)
        m_borderUp = m_borderDown + pow(10, zeroXYLogPower + 1);

    m_needToBeZoomedOut = false;
    if (!m_isXlogarithmic)
    {
        MakeVerticalNetLines(dc);
    }
    else
    {
        MakeVerticalNetLinesLog(dc);
    }

    if (!m_isYlogarithmic)
    {
        MakeHorizontalNetLines(dc);
    }
    else
    {
        MakeHorizontalNetLinesLog(dc);
    }

    if (m_needToBeZoomedOut)
        ZoomOut();

    MakeZeroLines(dc);
    // Virtual function for subclasses output
    DrawMe(dc); // drawing entities by subclasses
}

// Net lines for logarithmic axis
void wxPanelGraph::MakeHorizontalNetLinesLog(wxDC &dc)
{
    int order;
    wxString textOut;
    wxPen dashPen(m_palette_coordLines, 1, wxPENSTYLE_SHORT_DASH);

    order = log10(m_borderDown);
    dc.SetTextForeground(wxColour(m_palette_text));

    while(pow(10, order)<m_borderUp)
    {
        dashPen.SetColour(m_palette_coordLines);
        dc.SetPen(dashPen);

        if (m_showHorNet)
            DrawLine(m_borderLeft,pow(10, order), m_borderRight, pow(10, order), dc);

        textOut = wxT("10^");
        textOut<<order;
        dc.DrawText(textOut,
                    0,
                    m_height - m_height*(order - log10(m_borderDown))/(log10(m_borderUp) - log10(m_borderDown)));

        dashPen.SetColour(m_palette_coordAddLines);
        dc.SetPen(dashPen);
        for (int i=1; i<10; ++i)
        {
            if (pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i>m_borderUp)
                break;

            if (m_showHorAddNet)
            {
                DrawLine(m_borderLeft,
                         pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i,
                         m_borderRight,
                         pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i,
                         dc);
            }
        }

        order++;
    }
}

// Net lines for logarithmic axis
void wxPanelGraph::MakeVerticalNetLinesLog(wxDC &dc)
{
    int order;
    wxString textOut;
    wxPen dashPen(m_palette_coordLines, 1, wxPENSTYLE_SHORT_DASH);

    order = log10(m_borderLeft);
    dc.SetTextForeground(wxColour(m_palette_text));

    while(pow(10, order)<m_borderRight)
    {
        dashPen.SetColour(m_palette_coordLines);
        dc.SetPen(dashPen);

        if (m_showVertNet)
            DrawLine(pow(10, order),m_borderDown, pow(10, order), m_borderUp, dc);

        textOut = wxT("10^");
        textOut<<order;
        dc.DrawText(textOut,
                    m_width*(order - log10(m_borderLeft))/(log10(m_borderRight) - log10(m_borderLeft)),
                    m_height - borderVShift);

        dashPen.SetColour(m_palette_coordAddLines);
        dc.SetPen(dashPen);

        for (int i=1; i<10; ++i)
        {
            if (pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i>m_borderRight)
                break;

            if (m_showVertAddNet)
            {
                DrawLine(pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i,
                         m_borderUp,
                         pow(10, order) + (pow(10, order+1) - pow(10, order))/(10-1)*i,
                         m_borderDown,
                         dc);
            }
        }
        order++;
    }
}

// Draws horizontal lines
void wxPanelGraph::MakeHorizontalNetLines(wxDC &dc)
{
    int xNumber;        // number of lines. Preliminary
    int baseNumber;     // base for net points
    int order;          // base number's order
    double startPt;     // start point for grid
    wxString textOut;   // text for output
    wxString lastNumber;

    wxPen dashPen(m_palette_coordLines, 1, wxPENSTYLE_SHORT_DASH);

    // Smart net
    // Horizontal lines
    dc.SetPen(dashPen);
    dc.SetTextForeground(wxColour(m_palette_text));

    if (m_borderUp - m_borderDown>1)
    {
        order = 0;
        while (((int)(m_borderUp - m_borderDown))/(int)pow(10,order)!=0)
        {
            ++order;
            if (order>maxOrder)
                break;
        }
        order--;
    }
    else
    {
        order = 0;
        while (((m_borderUp - m_borderDown))/pow(10,order)<1)
        {
            --order;
            if (order<-minOrder)
                break;
        }
    }
    xNumber = m_height/m_maxDelta;
    baseNumber = 1;

    while(m_borderDown + (((double)baseNumber)*pow(10,order-1)*((double)xNumber))<m_borderUp)
    {
        baseNumber++;
        if (baseNumber>maxBaseNumber - 1)
            break;
    }

    if (baseNumber<maxBaseNumber)
    {
        startPt = 0;
        if (m_borderDown<=0)
        {
            while (startPt>m_borderDown)
                startPt -= ((double)baseNumber)*pow(10,order-1);
        }
        else
        {
            startPt = (int) (m_borderDown/((double)baseNumber*pow(10,order-1)));
            startPt *= ((double)baseNumber)*pow(10,order-1);
        }

        for (int i=1; i<=xNumber; i++)
        {
            if (m_showHorNet)
            {
                DrawLine(m_borderLeft,
                         startPt + i*(double)baseNumber*pow(10,order-1),
                         m_borderRight,
                         startPt + i*(double)baseNumber*pow(10,order-1),
                         dc);
            }

            textOut.Clear();
            textOut<<startPt + i*(double)baseNumber*pow(10,order-1);
            if (fabs(startPt + i*(double)baseNumber*pow(10,order-1))<zeroValue)
                textOut = _T("0");

            if (textOut==lastNumber)    // avoid incorrect scaling
                m_needToBeZoomedOut = true;
            lastNumber = textOut;

            dc.DrawText(textOut,
                        0,
                        m_height - m_height*(startPt + i*(double)baseNumber*pow(10,order-1) - m_borderDown)/(m_borderUp - m_borderDown));
        }
    }
    if ((m_borderUp - m_borderDown)/((double)baseNumber*pow(10,order-1))<=minGridToShowCorners)
    {
        textOut.Clear();
        textOut<<m_borderUp;
        dc.DrawText(textOut, 0,0);
    }
}

// Draws vertical net-lines
void wxPanelGraph::MakeVerticalNetLines(wxDC &dc)
{
    int xNumber;        // number of lines. Preliminary
    int baseNumber;     // base number for net points
    int order;          // base number's order
    double startPt;     // start point for grid
    wxString textOut;   // text for output
    wxString lastNumber;

    wxPen dashPen(m_palette_coordLines, 1, wxPENSTYLE_SHORT_DASH);

    // Smart net
    // Vertical lines
    dc.SetPen(dashPen);
    dc.SetTextForeground(wxColour(m_palette_text));

    if (m_borderRight - m_borderLeft>1)
    {
        order = 0;
        while (((int)(m_borderRight - m_borderLeft))/(int)pow(10,order)!=0)
        {
            ++order;
            if (order>maxOrder)
                break;
        }
        order--;
    }
    else
    {
        order = 0;
        while (((m_borderRight - m_borderLeft))/pow(10,order)<1)
        {
            --order;
            if (order<-minOrder)
                break;
        }
    }
    xNumber = m_width/m_maxDelta;
    baseNumber = 1;
    while(m_borderLeft + (((double)baseNumber)*pow(10,order-1)*((double)xNumber))<m_borderRight)
    {
        baseNumber++;
        if (baseNumber>maxBaseNumber - 1)
            break;
    }

    if (baseNumber<maxBaseNumber)
    {
        startPt = 0;
        if (m_borderLeft<=0)
        {
            while (startPt>m_borderLeft)
                startPt -= ((double)baseNumber)*pow(10,order-1);
        }
        else
        {
            startPt = (int) (m_borderLeft/((double)baseNumber*pow(10,order-1)));
            startPt *= ((double)baseNumber)*pow(10,order-1);
        }


        for (int i=1; i<=xNumber; i++)
        {
            if (m_showVertNet)
            {
                DrawLine(startPt + i*(double)baseNumber*pow(10,order-1),
                         m_borderUp,
                         startPt + i*(double)baseNumber*pow(10,order-1),
                         m_borderDown,
                         dc);
            }

            textOut.Clear();
            textOut<<startPt + i*(double)baseNumber*pow(10,order-1);

            if (textOut==lastNumber)    // avoid incorrect scaling
                m_needToBeZoomedOut = true;
            lastNumber = textOut;

            if (fabs(startPt + i*(double)baseNumber*pow(10,order-1))<zeroValue)
                textOut=_T("0");
            dc.DrawText(textOut,
                        m_width*(startPt + i*(double)baseNumber*pow(10,order-1) - m_borderLeft)/(m_borderRight - m_borderLeft),
                        m_height - borderVShift);
        }
    }

    if ((m_borderRight - m_borderLeft)/((double)baseNumber*pow(10,order-1))<=minGridToShowCorners)
    {
        textOut.Clear();
        textOut<<m_borderRight;
        dc.DrawText(textOut, m_width - borderHShift, m_height - borderVShift);
    }
}

// Draws zero axises
void wxPanelGraph::MakeZeroLines(wxDC &dc)
{
    wxPen mainPen(m_palette_zeroLines, 2, wxSOLID);

    if (!m_showZeroLines)
        return;

    dc.SetPen(mainPen);

    if ((!m_isYlogarithmic)&&(m_borderLeft<0)&&(m_borderRight>0))
    {
        DrawLine(0, m_borderUp, 0, m_borderDown, dc, mainPen);
    }
    if ((!m_isYlogarithmic)&&(m_borderUp>0)&&(m_borderDown<0))
    {
        DrawLine(m_borderLeft, 0, m_borderRight, 0, dc, mainPen);
    }

    if (m_isXlogarithmic)
        DrawLine(zeroLineForLogarithmic, m_borderUp, zeroLineForLogarithmic, m_borderDown, dc, mainPen);

    if (m_isYlogarithmic)
        DrawLine(m_borderLeft, zeroLineForLogarithmic, m_borderRight, zeroLineForLogarithmic, dc, mainPen);
}

// Draws line on the panel
void wxPanelGraph::DrawLine (double x1, double y1, double x2, double y2, wxDC &dc)
{
    CoordinatesReverseTransfrom(x1, y1);
    CoordinatesReverseTransfrom(x2, y2);
    dc.DrawLine(x1, y1, x2, y2);
}

// Draws point / circle
void wxPanelGraph::DrawPoint(double x, double y, int radius, wxDC &dc, wxPen pen)
{
    dc.SetPen(pen);
    CoordinatesReverseTransfrom(x, y);
    dc.DrawCircle(x, y, radius);
}

// Plots point
void wxPanelGraph::PlotPoint(double x, double y, wxDC &dc, wxPen pen)
{
    CoordinatesReverseTransfrom(x, y);
    dc.DrawPoint(x, y);
}

// Draws line
// Marked as protected: for using by a subclasses
void wxPanelGraph::DrawLine (double x1, double y1, double x2, double y2, wxDC &dc, wxPen pen)
{
    dc.SetPen(pen);
    CoordinatesReverseTransfrom(x1, y1);
    CoordinatesReverseTransfrom(x2, y2);
    dc.DrawLine(x1, y1, x2, y2);
}

// Moves zero-coordinates to the center of the panel
void wxPanelGraph::ScaleZeroToCenter()
{
    if ((m_isXlogarithmic) || (m_isYlogarithmic))
        return;
    m_borderRight -= m_borderLeft;
    m_borderRight /= 2;
    m_borderLeft = - m_borderRight;
    m_borderUp -= m_borderDown;
    m_borderUp /= 2;
    m_borderDown = - m_borderUp;
    this->Refresh();
}

// Sets the frame position to defined borders coordinates
void wxPanelGraph::ScaleSetFramePosition(double left, double right, double up, double down)
{
    if ((left<=-pow(10,maxOrder)) || (down<=-pow(10,maxOrder)))
        return;

    if ((right>=pow(10,maxOrder)) || (up>=pow(10,maxOrder)))
        return;

    if ((left>=right) || (up<=down))
        return;

    if (!m_isXlogarithmic)
        m_borderLeft = left;

    if (!m_isYlogarithmic)
        m_borderDown = down;

    m_borderRight = right;
    m_borderUp = up;
    this->Refresh();
}

// Reset frame position (scale) to default
void wxPanelGraph::ScaleResetFramePosition()
{
    m_borderLeft = 0;
    m_borderRight = borderStartX;
    m_borderUp = borderStartY;
    m_borderDown = 0;

    if (m_isXlogarithmic)
    {
        zeroXYLogPower = zeroXYForLogarithmicDefault;
        zeroXYForLogarithmic = pow(10, zeroXYLogPower);
        m_borderLeft = zeroXYForLogarithmic;
    }

    if (m_isYlogarithmic)
    {
        zeroXYLogPower = zeroXYForLogarithmicDefault;
        zeroXYForLogarithmic = pow(10, zeroXYLogPower);
        m_borderDown = zeroXYForLogarithmic;
    }

    this->Refresh();
}

// Trim scale to the image size
void wxPanelGraph::ScaleTrimToImage()
{
    if (!m_underlayerPicture.HasImage())
        return;

    if (m_underlayerPicture.IsHiddenImage())
        m_underlayerPicture.HideImage(true);

    SetLogarithmicX(m_underlayerPicture.GetIsLogX());
    SetLogarithmicY(m_underlayerPicture.GetIsLogY());


    // exclude void image on image scaling
    if ((m_isYlogarithmic) && (m_underlayerPicture.GetRealBorderDown()<m_borderDown))
        {
            while((m_underlayerPicture.GetRealBorderDown()<m_borderDown) &&
                  (zeroXYLogPower > minOrder))
            DecrementZeroLog();
        }

    if ((m_isYlogarithmic) && (m_underlayerPicture.GetRealBorderDown()>m_borderDown))
        {
            while((m_underlayerPicture.GetRealBorderDown()>m_borderDown) &&
                  (zeroXYLogPower < maxOrder))
            IncrementZeroLog();
        }

    if ((m_isXlogarithmic) && (m_underlayerPicture.GetRealBorderLeft()<m_borderLeft))
        {
            while((m_underlayerPicture.GetRealBorderLeft()<m_borderLeft) &&
                  (zeroXYLogPower > minOrder))
            DecrementZeroLog();
        }

    if ((m_isXlogarithmic) && (m_underlayerPicture.GetRealBorderLeft()>m_borderLeft))
        {
            while((m_underlayerPicture.GetRealBorderLeft()>m_borderLeft) &&
                  (zeroXYLogPower < maxOrder))
            IncrementZeroLog();
        }
    // ^ exclude void image on image scaling

    ScaleSetFramePosition (m_underlayerPicture.GetRealBorderLeft(),
                           m_underlayerPicture.GetRealBorderRight(),
                           m_underlayerPicture.GetRealBorderUp(),
                           m_underlayerPicture.GetRealBorderDown());
}
// Picture set
bool wxPanelGraph::LoadPicture(const wxString &path, wxBitmapType type)
{
    return m_underlayerPicture.LoadPicture(path, type);
}

bool wxPanelGraph::IsImageHidden() const
{
    return m_underlayerPicture.IsHiddenImage();
}

void wxPanelGraph::HideImage(bool hide)
{
    m_underlayerPicture.HideImage(hide);
}

bool wxPanelGraph::GetHasImage()
{
    return m_underlayerPicture.HasImage();
}

void wxPanelGraph::DeleteImage()
{
    m_underlayerPicture.DeletePicture();
}

/******************** Panel graph settings ********************************************************/

int wxPanelGraph::GetMinOrder() const
{
    return minOrder;
}

int wxPanelGraph::GetMaxOrder() const
{
    return maxOrder;
}


void wxPanelGraph::SetScaleXLocked(bool isLocked)
{
    m_isXscaleLocked = isLocked;
}

void wxPanelGraph::SetScaleYLocked(bool isLocked)
{
    m_isYscaleLocked = isLocked;
}

void wxPanelGraph::SetLogarithmicX(bool isLog)
{
    m_isXlogarithmic = isLog;
    if (m_isXlogarithmic)
    {
        m_borderLeft = zeroXYForLogarithmic;
        m_borderRight = borderStartX;
    }
    this->Refresh();
}

void wxPanelGraph::SetLogarithmicY(bool isLog)
{
    m_isYlogarithmic = isLog;
    if (m_isYlogarithmic)
    {
        m_borderDown = zeroXYForLogarithmic;
        m_borderUp = borderStartY;
    }
    this->Refresh();
}

bool wxPanelGraph::GetIsLogarithmicX() const
{
    return m_isXlogarithmic;
}

bool wxPanelGraph::GetIsLogarithmicY() const
{
    return m_isYlogarithmic;
}

void wxPanelGraph::SetForPointPick(bool pick)
{
    m_isPicking = pick;
    if (pick)
    {
        this->SetCursor(*wxCROSS_CURSOR);
    }
    else
    {
        this->SetCursor(*wxSTANDARD_CURSOR);
    }
}

double wxPanelGraph::GetX() const
{
    return m_x;
}

double wxPanelGraph::GetY() const
{
    return m_y;
}

void wxPanelGraph::IncrementZeroLog()
{
    if ((zeroXYLogPower>=maxOrder) || (zeroXYLogPower>=log10(m_borderRight)-2))
        return;

    zeroXYLogPower++;
    zeroXYForLogarithmic = pow(10, zeroXYLogPower);
    m_borderLeft = m_borderDown = zeroXYForLogarithmic;
    Refresh();
}

void wxPanelGraph::DecrementZeroLog()
{
    if (zeroXYLogPower<=minOrder)
        return;

    zeroXYLogPower--;
    zeroXYForLogarithmic = pow(10, zeroXYLogPower);
    m_borderLeft = m_borderDown = zeroXYForLogarithmic;
    Refresh();
}

void wxPanelGraph::LockDrag(bool lock)
{
    m_isDragLocked = lock;
}

/******************** Panel graph colors ********************************************************/
wxUint32 wxPanelGraph::GetLinesCoordColour() const
{
    return m_palette_coordLines;
}

wxUint32 wxPanelGraph::GetLinesCoordAddsColour() const
{
    return m_palette_coordAddLines;
}

wxUint32 wxPanelGraph::GetLinesZeroColour() const
{
    return m_palette_zeroLines;
}

wxUint32 wxPanelGraph::GetTextColour() const
{
    return m_palette_text;
}

wxUint32 wxPanelGraph::GetTextErrorColour() const
{
    return m_palette_text_error;
}

wxUint32 wxPanelGraph::GetPanelColour() const
{
    return m_palette_myColor;
}

void wxPanelGraph::SetLinesCoordColour(wxUint32 myColor)
{
    m_palette_coordLines = myColor;
    this->Refresh();
}

void wxPanelGraph::SetLinesCoordAddsColour(wxUint32 myColor)
{
    m_palette_coordAddLines = myColor;
    this->Refresh();
}

void wxPanelGraph::SetLinesZeroColour(wxUint32 myColor)
{
    m_palette_zeroLines = myColor;
    this->Refresh();
}

void wxPanelGraph::SetPanelColour(wxUint32 myColor)
{
    m_palette_myColor = myColor;
    this->SetBackgroundColour(wxColour(m_palette_myColor));
    this->Refresh();
}

void wxPanelGraph::SetTextColour(wxUint32 myColor)
{
    m_palette_text = myColor;
    this->Refresh();
}

void wxPanelGraph::SetTextErrorColour(wxUint32 myColor)
{
    m_palette_text_error = myColor;
    this->Refresh();
}

// Sets default colors for the panel
void wxPanelGraph::RestoreColours()
{
    m_palette_myColor = DEFAULT_COLOUR_PANEL.GetRGB();
    m_palette_zeroLines = DEFAULT_COLOUR_LINES_ZERO.GetRGB();
    m_palette_coordLines = DEFAULT_COLOUR_LINES_COORD.GetRGB();
    m_palette_coordAddLines = DEFAULT_COLOUR_LINES_COORD_ADDS.GetRGB();
    m_palette_text = DEFAULT_COLOUR_LINES_ZERO.GetRGB();
    m_palette_text_error = DEFAULT_COLOUR_ERROR_TEXT.GetRGB();
    this->SetBackgroundColour(wxColour(m_palette_myColor));
    this->Refresh();
}

void wxPanelGraph::RestoreNetworkDefault()
{
    m_showZeroLines = true;
    m_showHorNet = true;
    m_showVertNet = true;
    m_showHorAddNet = true;
    m_showVertAddNet = true;
    this->Refresh();
}
