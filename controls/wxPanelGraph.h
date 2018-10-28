#ifndef WXPANELGRAPH_H_INCLUDED
#define WXPANELGRAPH_H_INCLUDED

#include <wx/wx.h>
#include "ImageCurve.h"

// Custom wxCommand event.
// Occurs when mouse left button is clicked on a panel
// and the panel is set to a picking mode. (See variable m_isPicking)
// The event is being handled in GetCurveMain.cpp
BEGIN_DECLARE_EVENT_TYPES()
    wxDECLARE_EVENT(EVT_GOT_POINT, wxCommandEvent);
END_DECLARE_EVENT_TYPES()


class wxPanelGraph : public wxPanel
{
    public:
        wxPanelGraph(wxPanel *parent,
                     int id,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style,
                     const wxString& name);
        virtual ~wxPanelGraph();
        double GetBorderLeft(void) const {return m_borderLeft;}
        double GetBorderRight(void) const {return m_borderRight;}
        double GetBorderUp(void) const {return m_borderUp;}
        double GetBorderDown(void) const {return m_borderDown;}

        // Scaling
        void ZoomIn(void);
        void ZoomOut(void);
        void ScaleResetFramePosition(void);
        void ScaleZeroToCenter(void);
        void ScaleSetFramePosition(double left, double right,
                                   double up, double down);
        void ScaleTrimToImage(void);
        void LockDrag(bool lock = false);
        bool GetIsDragLocked(void) const {return m_isDragLocked;}

        // Settings
        void SetScaleXLocked(bool isLocked);
        void SetScaleYLocked(bool isLocked);
        void SetLogarithmicX(bool isLog);
        void SetLogarithmicY(bool isLog);
        void IncrementZeroLog(void);        // increment left/down border for logarithmic axis
        void DecrementZeroLog(void);        // decrement left/down border for logarithmic axis
        bool GetIsLogarithmicX(void) const;
        bool GetIsLogarithmicY(void) const;
        bool GetIsScaleLockedX(void) const {return m_isXscaleLocked;}
        bool GetIsScaleLockedY(void) const {return m_isYscaleLocked;}
        void SetForPointPick(bool pick);    // pick points on panel
        double GetX(void) const;
        double GetY(void) const;
        int GetMinOrder(void) const {return minOrder;}
        int GetMaxOrder(void) const {return maxOrder;}
        int GetLogZero(void) const {return zeroXYForLogarithmic;}   // get left border for logarithmic axises

        // Panel appearance
        void RestoreNetworkDefault(void);

        void SetShowZeroLines(bool show = true) {m_showZeroLines = show;}
        bool GetShowZeroLines(void) const {return m_showZeroLines;}

        void SetShowHorizontalNetwork(bool show = true) {m_showHorNet = show;}
        bool GetShowHorizontalNetwork(void) const {return m_showHorNet;}

        void SetShowVerticalNetwork(bool show = true) {m_showVertNet = show;}
        bool GetShowVerticalNetwork(void) const {return m_showVertNet;}

        void SetShowHorizontalNetworkAdds(bool show = true) {m_showHorAddNet = show;}
        bool GetShowHorizontalNetworkAdds(void) const {return m_showHorAddNet;}

        void SetShowVerticalNetworkAdds(bool show = true) {m_showVertAddNet = show;}
        bool GetShowVerticalNetworkAdds(void) const {return m_showVertAddNet;}

        // Color settings
        wxUint32 GetLinesCoordColour(void) const;
        wxUint32 GetLinesCoordAddsColour(void) const;
        wxUint32 GetLinesZeroColour(void) const;
        wxUint32 GetPanelColour(void) const;
        wxUint32 GetTextErrorColour(void) const;
        wxUint32 GetTextColour(void) const;
        void SetLinesCoordColour(wxUint32 myColor);
        void SetLinesCoordAddsColour(wxUint32 myColor);
        void SetLinesZeroColour(wxUint32 myColor);
        void SetPanelColour(wxUint32 myColor);
        void SetTextErrorColour(wxUint32 myColor);
        void SetTextColour(wxUint32 myColor);
        void RestoreColours(void);

        // Image processing
        ImageCurve* GetImage(void) {return &m_underlayerPicture;}
        bool LoadPicture(const wxString &path, wxBitmapType type);
        bool IsImageHidden() const;
        void HideImage(bool hide);
        bool GetHasImage(void);
        void DeleteImage(void);

        // Output to memory dc
        void OnPaintMemoryDC(wxDC &dc);

    protected:
        void DrawPoint(double x, double y,
                       int radius, wxDC &dc, wxPen pen);

        void DrawLine (double x1, double y1,
                       double x2, double y2,
                       wxDC &dc, wxPen Pen);

        void PlotPoint(double x, double y,
                       wxDC &dc, wxPen pen);
        // Coordinates
        double m_x;                     // x-coordinate of mouse pointer (global)
        double m_y;                     // y-coordinate of mouse pointer (global)
        int m_width;                    // current panel width
        int m_height;                   // current panel width
        wxUint32 m_palette_text;        // normal text color
        wxUint32 m_palette_text_error;  // error text color

    private:
        // Pure virtual functions
        virtual void DrawMe(wxDC &dc) = 0;          // Subclass paints its own entities via DrawPoint/DrawLine methods
        virtual void CoordinatesOutput(void) = 0;   // Subclass outputs coordinates
        // Events handling
        void OnPaint(wxPaintEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnPanelGraphMouseWheel(wxMouseEvent& event);
        void OnPanelGraphMouseMove(wxMouseEvent& event);
        void OnPanelGraphMouseUp(wxMouseEvent& event);
        void OnPanelGraphMouseDown(wxMouseEvent& event);
        // Coordinates transformation
        void CoordinatesTransform(double &x, double &y);            // local coordinates to global coordinates conversion
        void CoordinatesReverseTransfrom(double &x, double &y);     // global coordinates to local coordinates conversion
        // Net lines drawing
        void MakeVerticalNetLines(wxDC &dc);
        void MakeVerticalNetLinesLog(wxDC &dc);        // logarithmic
        void MakeHorizontalNetLines(wxDC &dc);
        void MakeHorizontalNetLinesLog(wxDC &dc);      // logarithmic
        void MakeZeroLines(wxDC &dc);
        // Drawing
        inline void DrawLine (double x1, double y1, double x2, double y2, wxDC &dc);
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
        // Graph scale and position
        double m_borderLeft;        // left border global coordinates
        double m_borderRight;       // right border global coordinates
        double m_borderUp;          // top border global coordinates
        double m_borderDown;        // bottom border global coordinates
        double m_scaleX;            // x-axis scale
        double m_scaleY;            // y-axis scale
        // Mouse moving
        bool m_isDragLocked;        // can the canvas to be dragged
        bool m_isMousePressed;      // is mouse left button pressed
        bool m_isPicking;           // is panel waiting for mouse pick
        int m_startX;               // previous mouse x-position during dragging
        int m_startY;               // previous mouse y-position during dragging
        // Settings
        int m_maxDelta;             // maximum margin between net lines (in pixels)
        bool m_isXscaleLocked;      // lock scaling
        bool m_isYscaleLocked;      // lock scaling
        bool m_isXlogarithmic;      // log-coordinates for x-axis
        bool m_isYlogarithmic;          // log-coordinates for y-axis
        double zeroXYForLogarithmic;    // edge point for logarithmic axis
        int zeroXYLogPower;             // power for edge point coordinate
        bool m_showZeroLines;   // panel drawing features
        bool m_showHorNet;      // panel drawing features
        bool m_showVertNet;     // panel drawing features
        bool m_showHorAddNet;   // panel drawing features
        bool m_showVertAddNet;  // panel drawing features
        // External image for graph
        ImageCurve m_underlayerPicture;
        // Pens and brushes for output:
        wxUint32 m_palette_zeroLines;       // pen for zero lines
        wxUint32 m_palette_coordLines;      // pen for coordinates lines
        wxUint32 m_palette_coordAddLines;   // pen for additional lines (logarithmic axises)
        wxUint32 m_palette_myColor;         // color of the panel
};

#endif // WXPANELGRAPH_H_INCLUDED
