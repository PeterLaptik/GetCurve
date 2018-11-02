#ifndef IMAGECURVE_H_INCLUDED
#define IMAGECURVE_H_INCLUDED

#include <wx/bitmap.h>
#include <wx/imagbmp.h>
#include<wx/dcclient.h>

class ImageCurve
{
    public:
        ImageCurve();
        ~ImageCurve();
        bool LoadPicture(const wxString &path, wxBitmapType type);
        bool HasImage(void) const;
        wxImage* GetImage(void);
        void HideImage(bool hide);
        bool IsHiddenImage(void) const;
        void DeletePicture(void);
		int GetMinOrder(void) const;
		int GetMaxOrder(void) const;
        // Scale settings
        void SetIsXLog(bool isLog);
		void SetIsYLog(bool isLog);
		void SetXYZeroShift(int shiftX, int shiftY, double valueX, double valueY);
		void SetXLine(int shiftX, double valueX);
		void SetYLine(int shiftY, double valueY);
		void SetScaled(bool);
		// Get scaled values
		double GetRealBorderLeft(void);
        double GetRealBorderRight(void);
        double GetRealBorderUp(void);
        double GetRealBorderDown(void);
        bool GetIsLogX(void);
        bool GetIsLogY(void);
		// Picture output
		void DrawPicture(wxDC &dc,
                             double borderLeft, double borderRight,
                             double borderUp, double borderDown,
                             int width, int height,
                             bool isLogX, bool isLogY);

    protected:

    private:
        wxImage m_image;                // image
        int m_width;                    // picture width
        int m_height;                   // picture height
        bool m_hasImage;                // is the image loaded
        bool m_hiddenImage;             // is the image hidden
        bool m_isScaled;                // is image scaled
        // Picture scaling data:
        bool m_isLogX;                  // is picture x-axis logarithmic
		bool m_isLogY;                  // is picture y-axis logarithmic
		int m_ptZeroXshift;             // shift to start calibrated point per x-axis
		int m_ptZeroYshift;             // shift to start calibrated point per y-axis
		double m_ptZeroXRealValue;      // real value of the first calibrated point per x-axis
		double m_ptZeroYRealValue;      // real value of the first calibrated point per y-axis
		int m_ptLineXshift;             // shift to x-axis calibrated point
		double m_ptLineXRealValue;      // real value of the second calibrated point per x-axis
		int m_ptLineYshift;             // shift to y-axis calibrated point
		double m_ptLineYRealValue;      // real value of the second calibrated point per y-axis
		double m_picXRealScale;         // real picture scale to output
        double m_picYRealScale;         // real picture scale to output
};

#endif // IMAGECURVE_H_INCLUDED
