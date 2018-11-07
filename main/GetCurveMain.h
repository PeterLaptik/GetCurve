/***************************************************************
 * Name:      GetCurveMain.h
 * Purpose:   Defines Application Frame
 * Author:    Peter Laptik (Peter.Laptik@gmail.com)
 * Created:   2018-07-08
 * Copyright: Peter Laptik ()
 * License:
 **************************************************************/

#ifndef GETCURVEMAIN_H
#define GETCURVEMAIN_H

#define TEST_MODE

#include "../dialogues/PictureScaler.h"
#include "../dialogues/CustomScale.h"
#include "../dialogues/ColorSettings.h"
#include "../dialogues/AboutWindow.h"
#include "../calc/polynom.h"
#include "../controls/wxCurvePanel.h"
#include "../toolboxes/PolynomialWindow.h"
#include "../odt_creator/include/OdtCreator.h"

const int NO_SELECTED_POINT = -1;
const char* const FRAME_LABEL = "GetCurve";

//(*Headers(GetCurveFrame)
#include <wx/bmpbuttn.h>
#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/splitter.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
//*)

const int INITIAL_POINT_NUMBER = 2;

enum PickingState
{
    NO_PICK, PICK_SINGLEPOINT, PICK_MULTIPOINT
};

class GetCurveFrame: public wxFrame
{
    public:

        GetCurveFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~GetCurveFrame();

    private:

        //(*Handlers(GetCurveFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void PointChanged(wxSpinEvent& event);
        void TestRoutine(wxCommandEvent& event);
        void OnPanelGraphPaint(wxPaintEvent& event);
        void OnPanelGraphMouseWheel(wxMouseEvent& event);
        void OnRightDownMouse(wxMouseEvent& event);
        void OnPanelGraphLeftDown(wxMouseEvent& event);
        void OnPanelGraphLeftUp(wxMouseEvent& event);
        void OnPanelGraphMouseMove(wxMouseEvent& event);
        void CalibrateSpace(wxCommandEvent& event);
        void XAxisOn(wxCommandEvent& event);
        void YAxisOn(wxCommandEvent& event);
        void LineNumberX(wxSpinEvent& event);
        void LineNumberY(wxSpinEvent& event);
        void OnPanelGraphMouseMove1(wxMouseEvent& event);
        void InputPoint(wxGridEvent& event);
        void CellSelect(wxGridEvent& event);
        void ClearSelected(wxMouseEvent& event);
        void TrimToCurve(wxCommandEvent& event);
        void TrimToZero(wxCommandEvent& event);
        void OnButton1Click1(wxCommandEvent& event);
        void OnPanelGraphMenu(wxMouseEvent& event);
        void LockXScale(wxCommandEvent& event);
        void LockYScale(wxCommandEvent& event);
        void SetLogarithmicC(wxCommandEvent& event);
        void OnPanelGraphPaint1(wxPaintEvent& event);
        void SetLogarithmicX(wxCommandEvent& event);
        void SetLogarithmicY(wxCommandEvent& event);
        void PickPoint(wxCommandEvent& event);
        void PickMultiPoint(wxCommandEvent& event);
        void StopCommandPopUpMenu(wxCommandEvent& event);
        void ZoomIn(wxCommandEvent& event);
        void ZoomOut(wxCommandEvent& event);
        void ZoomPanel(wxCommandEvent& event);
        void TrimRatioPerX(wxCommandEvent& event);
        void TrimRatioPerY(wxCommandEvent& event);
        void ScaleReset(wxCommandEvent& event);
        void IncrementLogLeftBorder(wxCommandEvent& event);
        void DecrementLogBorder(wxCommandEvent& event);
        void HideShowImage(wxCommandEvent& event);
        void MakeLogarithmicCoordinates(wxCommandEvent& event);
        void MakeLinearCoordinates(wxCommandEvent& event);
        void RefreshPanel(wxCommandEvent& event);
        void ChangeColors(wxCommandEvent& event);
        void SortPointsMenu(wxCommandEvent& event);
        void ShowOrHideCoefficientWindow(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void SaveFile(wxCommandEvent& event);
        void SaveFileAs(wxCommandEvent& event);
        void OpenFile(wxCommandEvent& event);
        void FileNew(wxCommandEvent& event);
        void OnResize(wxSizeEvent& event);
        void MakeScreenSnapshot(wxCommandEvent& event);
        void ExportCFunction(wxCommandEvent& event);
        void ExportCSVTable(wxCommandEvent& event);
        void LoadUnderlayerPicture(wxCommandEvent& event);
        void RescaleImage(wxCommandEvent& event);
        void RemoveUnderLayerImage(wxCommandEvent& event);
        void TrimToImage(wxCommandEvent& event);
        void DeletePoint(wxCommandEvent& event);
        void ShowHorizontalLines(wxCommandEvent& event);
        void ShowVerticalLines(wxCommandEvent& event);
        void ShowZeroLines(wxCommandEvent& event);
        void ShowHorizontalExtraLines(wxCommandEvent& event);
        void ShowVerticalExtraLines(wxCommandEvent& event);
        void LockScreenDrag(wxCommandEvent& event);
        void ShowAllLines(wxCommandEvent& event);
        void SaveOdtReport(wxCommandEvent& event);
        void SetCustomScale(wxCommandEvent& event);
        //*)

        //(*Identifiers(GetCurveFrame)
        static const long ID_STATICTEXT2;
        static const long ID_GRID1;
        static const long ID_STATICTEXT1;
        static const long ID_SPINCTRL1;
        static const long ID_PANEL1;
        static const long ID_PANEL4;
        static const long ID_BITMAPBUTTON5;
        static const long ID_BITMAPBUTTON6;
        static const long ID_BITMAPBUTTON1;
        static const long ID_BITMAPBUTTON2;
        static const long ID_BITMAPBUTTON7;
        static const long ID_BITMAPBUTTON12;
        static const long ID_BITMAPBUTTON3;
        static const long ID_BITMAPBUTTON4;
        static const long ID_BITMAPBUTTON9;
        static const long ID_BITMAPBUTTON8;
        static const long ID_BITMAPBUTTON10;
        static const long ID_BITMAPBUTTON11;
        static const long ID_BITMAPBUTTON13;
        static const long ID_BITMAPBUTTON14;
        static const long ID_BITMAPBUTTON15;
        static const long ID_BITMAPBUTTON16;
        static const long ID_PANEL2;
        static const long ID_SPLITTERWINDOW1;
        static const long idMenuFileNew;
        static const long idMenuOpenFile;
        static const long idMenuSaveFile;
        static const long idMenuSaveFileAs;
        static const long idMenuAddImage;
        static const long idMenuExportPNG;
        static const long idMenuExportC;
        static const long idMenuExportCVS;
        static const long idMenuExportOdt;
        static const long idMenuExport;
        static const long idMenuQuit;
        static const long idMenuStop;
        static const long idMenuPickPoint;
        static const long idMenuPickPointSet;
        static const long idMenuSortPoints;
        static const long idMenuRescalePicture;
        static const long idMenuRemoveImage;
        static const long idMenuDeletePoint;
        static const long idMenuRefresh;
        static const long idShowHor;
        static const long idShowVert;
        static const long idShowZero;
        static const long idShowHorAdds;
        static const long idShowVertAdds;
        static const long idMenuShowAll;
        static const long idMenuShow;
        static const long idMenuZoomIn;
        static const long idMenuZoomOut;
        static const long idMenuTrimScale;
        static const long idMenuCenterZero;
        static const long idMenuInitialScale;
        static const long idTrimToImage;
        static const long idMenuLogX;
        static const long idMenuLogY;
        static const long idMenuLockX;
        static const long idMenuLockY;
        static const long idLockDrag;
        static const long idMenuPolynomialShow;
        static const long idMenuSnapShot;
        static const long idMenuExportFunction;
        static const long idMenuExportCSV;
        static const long idMenuMakeReport;
        static const long idMenuColours;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TOOLBAR1;
        static const long idUndo;
        static const long idLockX;
        static const long idLockY;
        static const long idLogX;
        static const long idLogY;
        static const long idLockForDrag;
        //*)

        //(*Declarations(GetCurveFrame)
        CurvePanel* PanelGraph;
        wxBitmapButton* BitmapButton10;
        wxBitmapButton* BitmapButton11;
        wxBitmapButton* BitmapButton12;
        wxBitmapButton* BitmapButton13;
        wxBitmapButton* BitmapButton14;
        wxBitmapButton* BitmapButton15;
        wxBitmapButton* BitmapButton16;
        wxBitmapButton* BitmapButton1;
        wxBitmapButton* BitmapButton2;
        wxBitmapButton* BitmapButton3;
        wxBitmapButton* BitmapButton4;
        wxBitmapButton* BitmapButton5;
        wxBitmapButton* BitmapButton6;
        wxBitmapButton* BitmapButton7;
        wxBitmapButton* BitmapButton8;
        wxBitmapButton* BitmapButton9;
        wxGrid* Grid1;
        wxMenu menuPanelGraph;
        wxMenu* Menu3;
        wxMenu* Menu4;
        wxMenu* Menu5;
        wxMenu* Menu6;
        wxMenu* MenuItem32;
        wxMenu* MenuItem42;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItem12;
        wxMenuItem* MenuItem13;
        wxMenuItem* MenuItem14;
        wxMenuItem* MenuItem15;
        wxMenuItem* MenuItem16;
        wxMenuItem* MenuItem17;
        wxMenuItem* MenuItem18;
        wxMenuItem* MenuItem19;
        wxMenuItem* MenuItem20;
        wxMenuItem* MenuItem21;
        wxMenuItem* MenuItem22;
        wxMenuItem* MenuItem23;
        wxMenuItem* MenuItem24;
        wxMenuItem* MenuItem25;
        wxMenuItem* MenuItem26;
        wxMenuItem* MenuItem27;
        wxMenuItem* MenuItem28;
        wxMenuItem* MenuItem29;
        wxMenuItem* MenuItem30;
        wxMenuItem* MenuItem31;
        wxMenuItem* MenuItem33;
        wxMenuItem* MenuItem34;
        wxMenuItem* MenuItem35;
        wxMenuItem* MenuItem36;
        wxMenuItem* MenuItem37;
        wxMenuItem* MenuItem38;
        wxMenuItem* MenuItem39;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem40;
        wxMenuItem* MenuItem41;
        wxMenuItem* MenuItem43;
        wxMenuItem* MenuItem44;
        wxMenuItem* MenuItem45;
        wxMenuItem* MenuItem46;
        wxMenuItem* MenuItem47;
        wxMenuItem* MenuItem48;
        wxMenuItem* MenuItem49;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem50;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem6;
        wxMenuItem* MenuItem7;
        wxMenuItem* MenuItem8;
        wxMenuItem* MenuItem9;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxSpinCtrl* SpinCtrl1;
        wxSplitterWindow* SplitterWindow1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStatusBar* StatusBar1;
        wxToolBar* ToolBar1;
        wxToolBarToolBase* ToolBarItem10;
        wxToolBarToolBase* ToolBarItem11;
        wxToolBarToolBase* ToolBarItem12;
        wxToolBarToolBase* ToolBarItem13;
        wxToolBarToolBase* ToolBarItem14;
        wxToolBarToolBase* ToolBarItem15;
        wxToolBarToolBase* ToolBarItem16;
        wxToolBarToolBase* ToolBarItem17;
        wxToolBarToolBase* ToolBarItem18;
        wxToolBarToolBase* ToolBarItem19;
        wxToolBarToolBase* ToolBarItem1;
        wxToolBarToolBase* ToolBarItem20;
        wxToolBarToolBase* ToolBarItem21;
        wxToolBarToolBase* ToolBarItem22;
        wxToolBarToolBase* ToolBarItem23;
        wxToolBarToolBase* ToolBarItem2;
        wxToolBarToolBase* ToolBarItem3;
        wxToolBarToolBase* ToolBarItem5;
        wxToolBarToolBase* ToolBarItem6;
        wxToolBarToolBase* ToolBarItem7;
        wxToolBarToolBase* ToolBarItem8;
        wxToolBarToolBase* ToolBarItem9;
        //*)

        DECLARE_EVENT_TABLE()

        // Custom events handlers
        void OnIconize(wxIconizeEvent& event);
        void MouseCoordinatesHaveBeenChenged(wxCommandEvent& event);
        void PointHasBeenPicked(wxCommandEvent& event);
        void ImageHasBeenScaled(wxCommandEvent& event);

        void SortPoints(int i);
        void RefreshCoefficientToolwindow(bool isOK = true);
        void SaveSettingsAtExit(void);
        void SaveSettings(const wxString &currentPath);
        void LoadSettingsOnLoad(void);
        void LoadFile(const wxString &path);
        void WriteFile(const wxString &path);
        void RefreshMyLabel(void);
        void RefreshButtonStates(void);
        void RefreshCheckBoxStates(void);
        bool AskUserDialogue(const wxString &question, const wxString &header);
        void MakeSnapshotForOdt(OdtCreator &myDoc, bool onlyPoints);
        int OnCloseMessage(void);
        wxBitmap GetIcon(const unsigned char* myName, const long int mySize);

        PolynomialWindow *coeffDlg;
        bool isCoeffVisible;
        int currentGridPosition;
        PickingState isPick;
        Polynom polynom;
        bool SaveCancelFlag;

        // Settings
        wxString myLastDirectory;
        wxString currentFilePath;
        wxString currentFileName;
        bool hasFileNotSavedChanges;
};

#endif // GETCURVEMAIN_H
