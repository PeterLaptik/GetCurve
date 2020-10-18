#include "wxCurvePanel.h"

// Predefined settings
const int errorOutputX = 40;        // x-coordinate to output error messages
const int errorOutputY = 40;        // y-coordinate to output error messages
const double marginForTrim = 10;    // margin in percents. See TrimScale()
const double stepForOutCurve = 10;   // see DrawCurve method

// Default settings
const int MAX_POINT_RADIUS = 10;
const int MAX_MAINLINE_THICKNESS = 5;
const int POINT_LINE_WIDTH = 1;
const wxColour DEFAULT_COLOUR_MAINLINE = *wxBLACK;
const wxColour DEFAULT_COLOUR_POINTS = *wxBLACK;
const int DEFALUT_POINT_RADIUS = 5;
const int DEFAULT_LINE_THICKNESS = 2;

// Highlighting lines
const int DEFAULT_HIGHLIGHT_WITH_THIN = 1;
const int DEFAULT_HIGHLIGHT_WITH_THICK = 2;
const wxColour DEFAULT_HIGHLIGHT_COLOUR = *wxRED;

// Custom event
// See header file for the description
wxDEFINE_EVENT(EVT_CHANGED_XY, wxCommandEvent);

CurvePanel::CurvePanel(wxPanel *parent,
                     int id,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style,
                     const wxString& name)
            : wxPanelGraph(parent, id, pos, size, style, name)
{
    m_palette_pointRadius = DEFALUT_POINT_RADIUS;
    m_palette_mainLineThickness = DEFAULT_LINE_THICKNESS;
    m_palette_point_colour = DEFAULT_COLOUR_POINTS.GetRGB();
    m_palette_line_colour = DEFAULT_COLOUR_MAINLINE.GetRGB();
    m_counter = 0;
    m_coeff = 0;
    m_selected = NO_POINT_SELECTED;
    m_drawPointsOnly = false;
}

CurvePanel::~CurvePanel()
{

}

// Gets points from point array
void CurvePanel::SetPoints(Point *pt, size_t number)
{
    for (unsigned int i=0; i<number; ++i)
    {
        m_points[i].x = (*(pt + i)).x;
        m_points[i].y = (*(pt + i)).y;
        m_counter = number;
    }
    this->Refresh();
}

void CurvePanel::SetPolynomial(double *pt, size_t number)
{
    for (unsigned int i=0; i<number; ++i)
    {
        m_polynomial[i] = pt[i];
    }
    m_coeff = number;
}

// Receives number of point in a table has been picked
void CurvePanel::SelectPoint(int i)
{
    m_selected = i;
    this->Refresh();
}

int CurvePanel::GetSelectPoint()
{
    return m_selected;
}

// Draws entities on refresh event
void CurvePanel::DrawMe(wxDC &dc)
{
    if (m_counter<=0)
        return;

    wxPen pen(m_palette_point_colour, POINT_LINE_WIDTH, wxSOLID);

    if (!CheckPoints())
    {
        dc.SetTextForeground(wxColour(m_palette_text_error));
        if (m_error==DOUBLE_X_POINTS)
        {
            dc.DrawText(_T("Error: two points have the same x-coordinates"), errorOutputX, errorOutputY);
        }
        else if (m_error==LOG_SCALE_ERROR)
        {
            dc.DrawText(_T("Error: wrong coordinates for the logarithmic scale"), errorOutputX, errorOutputY);
        }
    }

    for (int i=0; i<m_counter; ++i)
    {
        DrawPoint(m_points[i].x, m_points[i].y, m_palette_pointRadius, dc, pen);
    }

    if (m_drawPointsOnly)
        return;

    // highlight the selected point is exists
    if ((m_selected<m_counter) && (m_selected>=0))
    {
        wxPen pen(DEFAULT_HIGHLIGHT_COLOUR, DEFAULT_HIGHLIGHT_WITH_THIN, wxSOLID);
        wxPen ptPen(DEFAULT_HIGHLIGHT_COLOUR, DEFAULT_HIGHLIGHT_WITH_THICK, wxSOLID);
        DrawLine(m_points[m_selected].x, m_points[m_selected].y,
                 m_points[m_selected].x, 0,
                 dc, pen);
        DrawLine(m_points[m_selected].x, m_points[m_selected].y,
                 0, m_points[m_selected].y,
                 dc, pen);
        DrawPoint(m_points[m_selected].x, m_points[m_selected].y, m_palette_pointRadius*1.5, dc, ptPen);
    }

    if (m_error!=NO_ERRORS)
        return;

    if (m_coeff>1)
        DrawCurve(dc);
}

void CurvePanel::DrawCurve(wxDC &dc)
{
    wxString tmp;
    double valueY;
    double valueX;
    Point xMinPt;        // unsorted case
    Point xMaxPt;        // unsorted case
    Point lastPoint;
    double step;        // pixel steps
    // borders
    double right;
    double left;
    double up;
    double down;
    wxPen pen(wxColour(m_palette_line_colour),
              m_palette_mainLineThickness,
              wxSOLID);

    left = this->GetBorderLeft();
    right = this->GetBorderRight();
    up = this->GetBorderUp();
    down = this->GetBorderDown();

    // find min/max x-values
    xMinPt.x = m_points[0].x;
    xMinPt.y = m_points[0].y;
    xMaxPt.x = m_points[0].x;
    xMaxPt.y = m_points[0].y;

    for (int i=1; i<m_counter; ++i)
    {
        if (xMinPt.x>m_points[i].x)
        {
            xMinPt.x = m_points[i].x;
            xMinPt.y = m_points[i].y;
        }
        if (xMaxPt.x<m_points[i].x)
        {
            xMaxPt.x = m_points[i].x;
            xMaxPt.y = m_points[i].y;
        }
    }

    step = (right - left)/m_width;
    lastPoint.x = xMinPt.x;
    lastPoint.y = xMinPt.y;
    valueX = lastPoint.x; // was +=

    if (GetIsLogarithmicX())
        step = RecalcStepForLogarithimc(valueX, left, right);

    while (valueX<=xMaxPt.x)
    {
        valueY = 0;
        if ((valueX<left) || (valueX>right))
        {
            valueX += step;
            continue;
        }

        for (int j=0; j<m_counter; ++j)
        {
            valueY += (m_polynomial[j]*pow(valueX,j));
        }

        if ((valueY<=GetLogZero()) && (GetIsLogarithmicY()))
            valueY = GetLogZero();

        this->DrawLine(lastPoint.x, lastPoint.y, valueX, valueY, dc, pen);
        lastPoint.x = valueX;
        lastPoint.y = valueY;

        if (GetIsLogarithmicX())
            step = RecalcStepForLogarithimc(valueX, left, right);

        valueX += step;
    }

    // Make curve out of points
    pen.SetColour(wxColour(m_palette_point_colour));
    dc.SetPen(pen);
    step *= stepForOutCurve;

    if (xMaxPt.x<right)
    {
        valueX = xMaxPt.x;
        while (valueX<right)
        {
            valueY = 0;
            if ((valueX<left) || (valueX>right))
            {
                valueX += step;
                continue;
            }
            for (int j=0; j<m_counter; ++j)
            {
                valueY += (m_polynomial[j]*pow(valueX,j));
            }
            if ((valueY<up) && (valueY>down))
            {
                if ((valueY<=GetLogZero()) && (GetIsLogarithmicY()))
                    valueY = GetLogZero();
                this->DrawPoint(valueX, valueY, 1, dc, pen);
            }

            if (GetIsLogarithmicX())
                step = stepForOutCurve*RecalcStepForLogarithimc(valueX, left, right);

            valueX += step;
        }
    }

    if (xMinPt.x>left)
    {
        valueX = left;
        while (valueX<xMinPt.x)
        {
            valueY = 0;
            if ((valueX<left) || (valueX>right))
            {
                valueX += step;
                continue;
            }
            for (int j=0; j<m_counter; ++j)
            {
                valueY += (m_polynomial[j]*pow(valueX,j));
            }

            if ((valueY<up) && (valueY>down))
            {
                if ((valueY<=GetLogZero()) && (GetIsLogarithmicY()))
                    valueY = GetLogZero();
                this->DrawPoint(valueX, valueY, 1, dc, pen);
            }

            if (GetIsLogarithmicX())
                step = stepForOutCurve*RecalcStepForLogarithimc(valueX, left, right);

            valueX += step;
        }
    }
}

// Corrects step value for the logarithmic axises for sharp curves avoiding
double CurvePanel::RecalcStepForLogarithimc(double currentXValue,
                                            double left,
                                            double right)
{
    double a, b;        // logarithmic borders
    double c;           // logarithmic position
    double pixel;       // next pixel position
    double nextXValue;  // next value of X that matches to the next pixel

    a = log10(left);
    b = log10(right);
    c = log10(currentXValue);
    pixel = m_width*(c - a)/(b - a) + 1;
    c = a + pixel/m_width*(b - a);
    nextXValue = pow(10, c);
    return fabs(nextXValue - currentXValue);    // result step
}

// Output current coordinates of mouse pointer
// Coordinates are transformed to global system
void CurvePanel::CoordinatesOutput()
{
    wxString textOut;
    wxCommandEvent m_event = wxCommandEvent(EVT_CHANGED_XY);
    textOut<<"x = "<<m_x<<"  y = "<<m_y;
    m_event.SetString(textOut);
    wxPostEvent(this, m_event);
}

// Check points
// Returns true if all is OK
bool CurvePanel::CheckPoints()
{
    m_error = NO_ERRORS;
    bool isXlogarithmic;
    bool isYlogarithmic;

    isXlogarithmic = GetIsLogarithmicX();
    isYlogarithmic = GetIsLogarithmicY();

    for (int i=0; i<m_counter; ++i)
    {
        for (int j=i+1; j<m_counter; ++j)
        {
            if (m_points[i].x==m_points[j].x)   // error: there are the same x-coordinates
            {
                m_error = DOUBLE_X_POINTS;
                return false;
            }

        }
    }

    for (int i=0; i<m_counter; ++i)
    {
        if (((isYlogarithmic) && m_points[i].y<pow(10, GetMinOrder())) ||
            ((isXlogarithmic) && m_points[i].x<pow(10,GetMinOrder())))
            {
                m_error = LOG_SCALE_ERROR;
                return false;
            }
    }

    return true;
}

// Shifts zero into the center of the panel
// Excluded
/*
void CurvePanel::TrimToZero()
{
    this->ScaleZeroToCenter();
}
*/

// Trims scale to show all the points
void CurvePanel::TrimScale()
{
    double maxX;
    double minX;
    double maxY;
    double minY;
    double xLength;
    double yLength;

    if (m_counter<2)
        return;

    maxX = minX = m_points[0].x;
    maxY = minY = m_points[0].y;
    for (int i=1; i<m_counter; ++i)
    {
        if (m_points[i].x>maxX)
            maxX = m_points[i].x;
        if (m_points[i].x<minX)
            minX = m_points[i].x;
        if (m_points[i].y>maxY)
            maxY = m_points[i].y;
        if (m_points[i].y<minY)
            minY = m_points[i].y;
    }
    xLength = (maxX - minX)*marginForTrim/100;
    yLength = (maxY - minY)*marginForTrim/100;
    maxX += xLength;
    minX -= xLength;
    maxY += yLength;
    minY -= yLength;

    if ((minX==maxX) || (minY==maxY))
        return;

    if (GetIsLogarithmicX())
        minX = GetLogZero();

    if (GetIsLogarithmicY())
        minY = GetLogZero();

    this->ScaleSetFramePosition(minX, maxX, maxY, minY);
}

// Makes x and y scales proportional to ratio of width/height of the panel
// Scale is based on the x axis values
void CurvePanel::TrimProportionalRatioPerX()
{
    double myPixRatio;
    double newBorderUp;
    myPixRatio = (this->GetBorderRight() - this->GetBorderLeft())/m_width;    // value per pixel
    newBorderUp = this->GetBorderDown() + myPixRatio*m_height;
    this->ScaleSetFramePosition(this->GetBorderLeft(),
                                this->GetBorderRight(),
                                newBorderUp,
                                this->GetBorderDown());
}

// Makes x and y scales proportional to ratio of width/height of the panel
// Scale is based on the y axis values
void CurvePanel::TrimProportionalRatioPerY()
{
    double myPixRatio;
    double newBorderRight;
    myPixRatio = (this->GetBorderUp() - this->GetBorderDown())/m_height;    // value per pixel
    newBorderRight = this->GetBorderLeft() + myPixRatio*m_width;
    this->ScaleSetFramePosition(this->GetBorderLeft(),
                                newBorderRight,
                                this->GetBorderUp(),
                                this->GetBorderDown());
}

/***************************** Settings ******************************************/
wxUint32 CurvePanel::GetMainLineColour() const
{
    return m_palette_line_colour;
}

wxUint32 CurvePanel::GetPointColour() const
{
    return m_palette_point_colour;
}

void CurvePanel::SetMainLineColour(wxUint32 myColour)
{
    m_palette_line_colour = myColour;
    this->Refresh();
}

void CurvePanel::SetPointColour(wxUint32 myColour)
{
    m_palette_point_colour = myColour;
    this->Refresh();
}

int CurvePanel::GetMainLineThickness() const
{
    return m_palette_mainLineThickness;
}

int CurvePanel::GetPointRadius() const
{
    return m_palette_pointRadius;
}

void CurvePanel::SetMainLineThickness(int myThickness)
{
    if ((myThickness<=0) || (myThickness>MAX_MAINLINE_THICKNESS))
        return;

    m_palette_mainLineThickness = myThickness;
    this->Refresh();
}

void CurvePanel::SetPointRadius(int myRadius)
{
    if ((myRadius<0) || (myRadius>MAX_POINT_RADIUS))
        return;

    m_palette_pointRadius = myRadius;
    this->Refresh();
}

int CurvePanel::GetMaxPointRadius()
{
    return MAX_POINT_RADIUS;
}

int CurvePanel::GetMaxLineThickness()
{
    return MAX_MAINLINE_THICKNESS;
}

void CurvePanel::RestoreDisplayDefaults()
{
    m_palette_pointRadius = DEFALUT_POINT_RADIUS;
    m_palette_mainLineThickness = DEFAULT_LINE_THICKNESS;
    m_palette_point_colour = DEFAULT_COLOUR_POINTS.GetRGB();
    m_palette_line_colour = DEFAULT_COLOUR_MAINLINE.GetRGB();
    RestoreColours();
}


