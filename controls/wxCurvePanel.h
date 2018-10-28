#ifndef WXCURVEPANEL_H_INCLUDED
#define WXCURVEPANEL_H_INCLUDED

#include "../calc/entity.h"
#include "wxPanelGraph.h"

// Custom event
// Occurs when mouse pointer is moving over the panel
// Returns string-value of x,y-coordinates to be output in the main frame
BEGIN_DECLARE_EVENT_TYPES()
    wxDECLARE_EVENT(EVT_CHANGED_XY, wxCommandEvent);
END_DECLARE_EVENT_TYPES()

// Error state
enum CurveError
{
    NO_ERRORS,
    DOUBLE_X_POINTS,
    LOG_SCALE_ERROR
};

const int NO_POINT_SELECTED = -1;

class CurvePanel : public wxPanelGraph
{
    public:
        CurvePanel(wxPanel *parent,
                     int id,
                     const wxPoint& pos,
                     const wxSize& size,
                     long style,
                     const wxString& name);
        virtual ~CurvePanel();
        //void SetOutput(wxStatusBar *out);
        void SetPoints(Point *pt, size_t number);
        void SetPolynomial(double *pt, size_t number);
        void SelectPoint(int i);
        int GetSelectedPoint(void) const {return m_selected;}
        int GetSelectPoint(void);
        void DrawPointsOnly(bool pointsOnly = false) {m_drawPointsOnly = pointsOnly;}
        // Scaling
        void TrimScale(void);
        /* Excluded
        void TrimToZero(void);
        */
        void TrimProportionalRatioPerX(void);
        void TrimProportionalRatioPerY(void);
        // Calculations
        bool CheckPoints(void);         // check points for errors
        // Settings
        wxUint32 GetMainLineColour(void) const;
        wxUint32 GetPointColour(void) const;
        void SetMainLineColour(wxUint32 myColour);
        void SetPointColour(wxUint32 myColour);
        int GetMainLineThickness(void) const;
        int GetPointRadius(void) const;
        void SetMainLineThickness(int myThickness);
        void SetPointRadius(int myRadius);
        int GetMaxPointRadius(void);
        int GetMaxLineThickness(void);
        void RestoreDisplayDefaults(void);

    protected:

    private:
        void DrawMe(wxDC &DC);              // draws own entities
        void CoordinatesOutput(void);       // outputs coordinates at a statusbar
        void DrawCurve(wxDC &dc);
        inline double RecalcStepForLogarithimc(double currentXValue,
                                               double left,
                                               double right);
        // Predefined settings
        const int errorOutputX = 40;        // x-coordinate to output error messages
        const int errorOutputY = 40;        // y-coordinate to output error messages
        const double marginForTrim = 10;    // margin in percents. See TrimScale()
        const double stepForOutCurve = 10;   // see DrawCurve method

        // Errors
        CurveError m_error;
        // Settings
        int m_palette_pointRadius;          // radius of points
        int m_palette_mainLineThickness;    // thickness of the main curve
        wxUint32 m_palette_point_colour;    // color of points
        wxUint32 m_palette_line_colour;     // color of main line
        bool m_drawPointsOnly;
        //wxStatusBar *m_output;              // output coordinates
        // Data
        Point m_points[MAX_POINTS];         // array of points
        double m_polynomial[MAX_POINTS];    // polynomial coefficients
        int m_counter;                      // number of points
        int m_coeff;                        // number of coefficients
        int m_selected;                     // selected point to show
};

#endif // WXCURVEPANEL_H_INCLUDED
