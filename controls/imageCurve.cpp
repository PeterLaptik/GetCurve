#include "ImageCurve.h"

// Scale limits for a drafting image
// Be aware: too small or too big values can cause unhanled exceptions
const double m_minScale = 0.1;
const double m_maxScale = 5;
// Accessible number values
const int DEFAULT_ORDER_LIMIT = 10;
// Min and max number values
int m_minOrder = -10;
int m_maxOrder = 10;

ImageCurve::ImageCurve()
{
    m_hasImage = false;
    m_hiddenImage = false;
    m_minOrder = 0 - DEFAULT_ORDER_LIMIT;
    m_maxOrder = 0 + DEFAULT_ORDER_LIMIT;
    m_isScaled = false;
}

ImageCurve::~ImageCurve()
{

}

bool ImageCurve::LoadPicture(const wxString &path, wxBitmapType type)
{
    if (m_hasImage)
        DeletePicture();

    m_hasImage = m_image.LoadFile(path, type);
    if (m_hasImage)
    {
        m_width = m_image.GetWidth();
        m_height = m_image.GetHeight();
    }
    return m_hasImage;
}

void ImageCurve::DeletePicture()
{
    if (m_hasImage)
        m_image.Clear();

    m_hasImage = false;
    m_hiddenImage = false;
    m_isScaled = false;
}

bool ImageCurve::HasImage() const
{
    return m_hasImage;
}

wxImage* ImageCurve::GetImage()
{
    if (m_hasImage)
        return &m_image;

    return NULL;
}

void ImageCurve::HideImage(bool hide)
{
    m_hiddenImage = hide;
}

bool ImageCurve::IsHiddenImage() const
{
    return m_hiddenImage;
}

// Outputs picture according to current scale
void ImageCurve::DrawPicture(wxDC &dc,
                             double borderLeft, double borderRight,
                             double borderUp, double borderDown,
                             int width, int height,
                             bool isLogX, bool isLogY)
{
    wxBitmap myImage;
    double scaleX = 1;
    double scaleY = 1;
    double m_picScaleX;
    double m_picScaleY;
    double ptX;             // point to output image
    double ptY;             // point to output image
    double a, b, c;         // temporary variables for coordinates transformation

    if ((!m_hasImage) || (m_hiddenImage))
        return;

    if ((isLogX != m_isLogX) || (isLogY != m_isLogY))   // axis types do not match to each other
        return;

    if (!m_isScaled)
        return;

    if (!m_isLogX)
    {
        scaleX = width/(borderRight - borderLeft);
        m_picScaleX = fabs(m_ptLineXshift - m_ptZeroXshift)/fabs(m_ptLineXRealValue - m_ptZeroXRealValue);
        m_picXRealScale = scaleX/m_picScaleX;
        ptX = (m_ptZeroXRealValue - borderLeft)*scaleX - m_ptZeroXshift*m_picXRealScale;
    }
    else
    {
        scaleX = width/(log10(borderRight) - log10(borderLeft));
        m_picScaleX = fabs(m_ptLineXshift - m_ptZeroXshift)/fabs(log10(m_ptLineXRealValue) - log10(m_ptZeroXRealValue));
        m_picXRealScale = scaleX/m_picScaleX;
        a = log10(borderLeft);
        b = log10(borderRight);
        c = log10(m_ptZeroXRealValue);
        ptX = width*(c - a)/(b - a) - m_ptZeroXshift*m_picXRealScale;
    }

    if (!m_isLogY)
    {
        scaleY = height/(borderUp - borderDown);
        m_picScaleY = fabs(m_ptLineYshift - m_ptZeroYshift)/fabs(m_ptLineYRealValue - m_ptZeroYRealValue);
        m_picYRealScale = scaleY/m_picScaleY;
        ptY = height - ((m_ptZeroYRealValue - borderDown)*scaleY + m_ptZeroYshift*m_picYRealScale);
    }
    else
    {
        scaleY = height/(log10(borderUp) - log10(borderDown));
        m_picScaleY = fabs(m_ptLineYshift - m_ptZeroYshift)/fabs(log10(m_ptLineYRealValue) - log10(m_ptZeroYRealValue));
        m_picYRealScale = scaleY/m_picScaleY;
        a = log10(borderUp);
        b = log10(borderDown);
        c = log10(m_ptZeroYRealValue);
        ptY = (height*(c - a)/(b - a) - m_ptZeroYshift*m_picYRealScale);
    }

    if ((m_picXRealScale<m_minScale) || (m_picXRealScale>m_maxScale))
        return;

    if ((m_picYRealScale<m_minScale) || (m_picYRealScale>m_maxScale))
        return;

    myImage = wxBitmap(m_image.Scale(m_width*m_picXRealScale,
                                     m_height*m_picYRealScale));

    dc.DrawBitmap(myImage, ptX, ptY);
}

/***** Scale settings *****/
void ImageCurve::SetIsXLog(bool isLog)
{
    m_isLogX = isLog;
}

void ImageCurve::SetIsYLog(bool isLog)
{
    m_isLogY = isLog;
}

void ImageCurve::SetXYZeroShift(int shiftX, int shiftY, double valueX, double valueY)
{
    m_ptZeroXshift = shiftX;
    m_ptZeroYshift = shiftY;
    m_ptZeroXRealValue = valueX;
    m_ptZeroYRealValue = valueY;
}

void ImageCurve::SetXLine(int shiftX, double valueX)
{
    m_ptLineXshift = shiftX;
    m_ptLineXRealValue = valueX;
}

void ImageCurve::SetYLine(int shiftY, double valueY)
{
    m_ptLineYshift = shiftY;
    m_ptLineYRealValue = valueY;
}

void ImageCurve::SetScaled(bool isScaled)
{
    m_isScaled = isScaled;
}

int ImageCurve::GetMinOrder() const
{
    return m_minOrder;
}

int ImageCurve::GetMaxOrder() const
{
    return m_maxOrder;
}

double ImageCurve::GetRealBorderLeft()
{
    if (m_ptZeroXRealValue<m_ptLineXRealValue)
    {
        return m_ptZeroXRealValue;
    }
    else
    {
        return m_ptLineXRealValue;
    }
}

double ImageCurve::GetRealBorderRight()
{
    if (m_ptLineXRealValue>m_ptZeroXRealValue)
    {
        return m_ptLineXRealValue;
    }
    else
    {
        return m_ptZeroXRealValue;
    }
}

double ImageCurve::GetRealBorderUp()
{
    if (m_ptLineYRealValue>m_ptZeroYRealValue)
    {
        return m_ptLineYRealValue;
    }
    else
    {
        return m_ptZeroYRealValue;
    }
}

double ImageCurve::GetRealBorderDown()
{
    if (m_ptZeroYRealValue<m_ptLineYRealValue)
    {
        return m_ptZeroYRealValue;
    }
    else
    {
        return m_ptLineYRealValue;
    }
}

bool ImageCurve::GetIsLogX()
{
    return m_isLogX;
}

bool ImageCurve::GetIsLogY()
{
    return m_isLogY;
}
