/***************************************************************
 * Name:      GetCurveMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Peter Laptik (Peter.Laptik@gmail.com)
 * Created:   2018-07-08
 * Copyright: Peter Laptik ()
 * License:   BSD
 **************************************************************/

#include "GetCurveMain.h"
#include "../res/icons.h"
#include <wx/msgdlg.h>
#include <wx/mstream.h>

//(*InternalHeaders(GetCurveFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

int comparator(const void *a, const void *b);   // comparator for points (compares per x-values)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(GetCurveFrame)
const long GetCurveFrame::ID_STATICTEXT2 = wxNewId();
const long GetCurveFrame::ID_GRID1 = wxNewId();
const long GetCurveFrame::ID_STATICTEXT1 = wxNewId();
const long GetCurveFrame::ID_SPINCTRL1 = wxNewId();
const long GetCurveFrame::ID_PANEL1 = wxNewId();
const long GetCurveFrame::ID_PANEL4 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON5 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON6 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON1 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON2 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON7 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON12 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON3 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON4 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON9 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON8 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON10 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON11 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON13 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON14 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON15 = wxNewId();
const long GetCurveFrame::ID_BITMAPBUTTON16 = wxNewId();
const long GetCurveFrame::ID_PANEL2 = wxNewId();
const long GetCurveFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long GetCurveFrame::idMenuFileNew = wxNewId();
const long GetCurveFrame::idMenuOpenFile = wxNewId();
const long GetCurveFrame::idMenuSaveFile = wxNewId();
const long GetCurveFrame::idMenuSaveFileAs = wxNewId();
const long GetCurveFrame::idMenuAddImage = wxNewId();
const long GetCurveFrame::idMenuExportPNG = wxNewId();
const long GetCurveFrame::idMenuExportC = wxNewId();
const long GetCurveFrame::idMenuExportCVS = wxNewId();
const long GetCurveFrame::idMenuExportOdt = wxNewId();
const long GetCurveFrame::idMenuExport = wxNewId();
const long GetCurveFrame::idMenuQuit = wxNewId();
const long GetCurveFrame::idMenuStop = wxNewId();
const long GetCurveFrame::idMenuPickPoint = wxNewId();
const long GetCurveFrame::idMenuPickPointSet = wxNewId();
const long GetCurveFrame::idMenuSortPoints = wxNewId();
const long GetCurveFrame::idMenuRescalePicture = wxNewId();
const long GetCurveFrame::idMenuRemoveImage = wxNewId();
const long GetCurveFrame::idMenuDeletePoint = wxNewId();
const long GetCurveFrame::idMenuRefresh = wxNewId();
const long GetCurveFrame::idShowHor = wxNewId();
const long GetCurveFrame::idShowVert = wxNewId();
const long GetCurveFrame::idShowZero = wxNewId();
const long GetCurveFrame::idShowHorAdds = wxNewId();
const long GetCurveFrame::idShowVertAdds = wxNewId();
const long GetCurveFrame::idMenuShowAll = wxNewId();
const long GetCurveFrame::idMenuShow = wxNewId();
const long GetCurveFrame::idMenuZoomIn = wxNewId();
const long GetCurveFrame::idMenuZoomOut = wxNewId();
const long GetCurveFrame::idMenuTrimScale = wxNewId();
const long GetCurveFrame::idMenuCenterZero = wxNewId();
const long GetCurveFrame::idMenuInitialScale = wxNewId();
const long GetCurveFrame::idTrimToImage = wxNewId();
const long GetCurveFrame::idMenuLogX = wxNewId();
const long GetCurveFrame::idMenuLogY = wxNewId();
const long GetCurveFrame::idMenuLockX = wxNewId();
const long GetCurveFrame::idMenuLockY = wxNewId();
const long GetCurveFrame::idLockDrag = wxNewId();
const long GetCurveFrame::idMenuPolynomialShow = wxNewId();
const long GetCurveFrame::idMenuSnapShot = wxNewId();
const long GetCurveFrame::idMenuExportFunction = wxNewId();
const long GetCurveFrame::idMenuExportCSV = wxNewId();
const long GetCurveFrame::idMenuMakeReport = wxNewId();
const long GetCurveFrame::idMenuColours = wxNewId();
const long GetCurveFrame::idMenuAbout = wxNewId();
const long GetCurveFrame::ID_STATUSBAR1 = wxNewId();
const long GetCurveFrame::ID_TOOLBAR1 = wxNewId();
const long GetCurveFrame::idUndo = wxNewId();
const long GetCurveFrame::idLockX = wxNewId();
const long GetCurveFrame::idLockY = wxNewId();
const long GetCurveFrame::idLogX = wxNewId();
const long GetCurveFrame::idLogY = wxNewId();
const long GetCurveFrame::idLockForDrag = wxNewId();
//*)

BEGIN_DECLARE_EVENT_TYPES()
    wxDECLARE_EVENT(EVT_CHANGED_XY, wxCommandEvent);
    wxDECLARE_EVENT(EVT_GOT_POINT, wxCommandEvent);
    wxDECLARE_EVENT(EVT_IMAGE_HAS_BEEN_SCALED, wxCommandEvent);
END_DECLARE_EVENT_TYPES()

BEGIN_EVENT_TABLE(GetCurveFrame,wxFrame)
    //(*EventTable(GetCurveFrame)
    //*)
    EVT_COMMAND(wxID_ANY, EVT_CHANGED_XY, GetCurveFrame::MouseCoordinatesHaveBeenChenged)
    EVT_COMMAND(wxID_ANY, EVT_GOT_POINT, GetCurveFrame::PointHasBeenPicked)
    EVT_COMMAND(wxID_ANY, EVT_IMAGE_HAS_BEEN_SCALED, GetCurveFrame::ImageHasBeenScaled)
    EVT_ICONIZE(GetCurveFrame::OnIconize)
END_EVENT_TABLE()

GetCurveFrame::GetCurveFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(GetCurveFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("GetCurve"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(591,516));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(GetIcon(logo_png, logo_png_size));
    	SetIcon(FrameIcon);
    }
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    SplitterWindow1 = new wxSplitterWindow(this, ID_SPLITTERWINDOW1, wxDefaultPosition, wxSize(640,640), wxSP_3D, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinimumPaneSize(10);
    SplitterWindow1->SetSashGravity(0);
    Panel1 = new wxPanel(SplitterWindow1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Points\' coordinates:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer4->Add(StaticText2, 0, wxTOP|wxLEFT|wxRIGHT, 16);
    Grid1 = new wxGrid(Panel1, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
    Grid1->CreateGrid(20,2);
    Grid1->EnableEditing(true);
    Grid1->EnableGridLines(true);
    Grid1->SetColLabelValue(0, _("x"));
    Grid1->SetColLabelValue(1, _("y(x)"));
    Grid1->SetDefaultCellFont( Grid1->GetFont() );
    Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
    BoxSizer4->Add(Grid1, 0, wxLEFT|wxRIGHT|wxEXPAND, 16);
    BoxSizer2->Add(BoxSizer4, 0, wxALL|wxFIXED_MINSIZE, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Number of points:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer3->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl1 = new wxSpinCtrl(Panel1, ID_SPINCTRL1, _T("2"), wxDefaultPosition, wxSize(41,24), 0, 2, 20, 2, _T("ID_SPINCTRL1"));
    SpinCtrl1->SetValue(_T("2"));
    BoxSizer3->Add(SpinCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer3, 0, wxBOTTOM|wxLEFT|wxRIGHT, 16);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    Panel2 = new wxPanel(SplitterWindow1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    PanelGraph = new CurvePanel(Panel2, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    BoxSizer5->Add(PanelGraph, 1, wxALL|wxEXPAND, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    BitmapButton5 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON5, GetIcon(zoom_in_png, zoom_in_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON5"));
    BitmapButton5->SetToolTip(_("Zoom in"));
    BoxSizer7->Add(BitmapButton5, 0, wxALIGN_LEFT, 0);
    BitmapButton6 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON6, GetIcon(zoom_out_png, zoom_out_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON6"));
    BitmapButton6->SetToolTip(_("Zoom out"));
    BoxSizer7->Add(BitmapButton6, 0, wxALIGN_LEFT, 0);
    BitmapButton1 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON1, GetIcon(trim_to_1_png, trim_to_1_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW|wxRAISED_BORDER, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    BitmapButton1->SetToolTip(_("Trim to curve"));
    BoxSizer7->Add(BitmapButton1, 0, wxALIGN_LEFT, 0);
    BitmapButton2 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON2, GetIcon(center_zero_png, center_zero_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
    BitmapButton2->SetToolTip(_("Center zero"));
    BoxSizer7->Add(BitmapButton2, 0, wxALIGN_LEFT, 0);
    BitmapButton7 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON7, GetIcon(reset_scale_png, reset_scale_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON7"));
    BitmapButton7->SetToolTip(_("Reset scale"));
    BoxSizer7->Add(BitmapButton7, 0, wxALIGN_LEFT, 0);
    BitmapButton12 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON12, GetIcon(show_hide_image_png, show_hide_image_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON12"));
    BitmapButton12->SetToolTip(_("Show/hide image"));
    BoxSizer7->Add(BitmapButton12, 0, wxALIGN_LEFT, 0);
    BitmapButton3 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON3, GetIcon(pick_point_png, pick_point_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
    BitmapButton3->SetToolTip(_("Pick selected point"));
    BoxSizer7->Add(BitmapButton3, 0, wxTOP, 8);
    BitmapButton4 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON4, GetIcon(pick_multi_point_png, pick_multi_point_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
    BitmapButton4->SetToolTip(_("Pick point set"));
    BoxSizer7->Add(BitmapButton4, 0, wxALIGN_LEFT, 0);
    BoxSizer6->Add(BoxSizer7, 0, wxALL|wxALIGN_TOP, 5);
    BoxSizer8 = new wxBoxSizer(wxVERTICAL);
    BitmapButton9 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON9, GetIcon(y_ratio_png, y_ratio_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON9"));
    BitmapButton9->SetToolTip(_("Proportional scale: trim to y"));
    BoxSizer8->Add(BitmapButton9, 0, wxALIGN_LEFT, 0);
    BitmapButton8 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON8, GetIcon(x_ratio_png, x_ratio_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON8"));
    BitmapButton8->SetToolTip(_("Proportional scale: trim to x"));
    BoxSizer8->Add(BitmapButton8, 0, wxALIGN_LEFT, 0);
    BitmapButton10 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON10, GetIcon(log10Y_more_png, log10Y_more_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON10"));
    BitmapButton10->Disable();
    BitmapButton10->SetToolTip(_("Move up left border"));
    BoxSizer8->Add(BitmapButton10, 0, wxALIGN_LEFT, 0);
    BitmapButton11 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON11, GetIcon(log10_less_png, log10_less_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON11"));
    BitmapButton11->Disable();
    BitmapButton11->SetToolTip(_("Move down left border"));
    BoxSizer8->Add(BitmapButton11, 0, wxALIGN_LEFT, 0);
    BitmapButton13 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON13, GetIcon(logarithmic_png, logarithmic_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON13"));
    BitmapButton13->SetToolTip(_("Logarithmic coordinates"));
    BoxSizer8->Add(BitmapButton13, 0, wxALIGN_LEFT, 0);
    BitmapButton14 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON14, GetIcon(linear_png, linear_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON14"));
    BitmapButton14->SetToolTip(_("Linear coordinates"));
    BoxSizer8->Add(BitmapButton14, 0, wxALIGN_LEFT, 0);
    BitmapButton15 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON15, GetIcon(coefficients_png, coefficients_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON15"));
    BitmapButton15->SetToolTip(_("Show/hide coefficients"));
    BoxSizer8->Add(BitmapButton15, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 8);
    BitmapButton16 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON16, GetIcon(sort_png, sort_png_size), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON16"));
    BitmapButton16->SetToolTip(_("Sort points"));
    BoxSizer8->Add(BitmapButton16, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer6->Add(BoxSizer8, 0, wxALL|wxALIGN_TOP, 5);
    BoxSizer5->Add(BoxSizer6, 0, wxALL|wxALIGN_TOP, 5);
    Panel2->SetSizer(BoxSizer5);
    BoxSizer5->Fit(Panel2);
    BoxSizer5->SetSizeHints(Panel2);
    SplitterWindow1->SplitVertically(Panel1, Panel2);
    SplitterWindow1->SetSashPosition(100);
    BoxSizer1->Add(SplitterWindow1, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem27 = new wxMenuItem(Menu1, idMenuFileNew, _("New"), wxEmptyString, wxITEM_NORMAL);
    MenuItem27->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_OTHER));
    Menu1->Append(MenuItem27);
    MenuItem28 = new wxMenuItem(Menu1, idMenuOpenFile, _("Open"), wxEmptyString, wxITEM_NORMAL);
    MenuItem28->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_OTHER));
    Menu1->Append(MenuItem28);
    MenuItem29 = new wxMenuItem(Menu1, idMenuSaveFile, _("Save"), wxEmptyString, wxITEM_NORMAL);
    MenuItem29->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_OTHER));
    Menu1->Append(MenuItem29);
    MenuItem30 = new wxMenuItem(Menu1, idMenuSaveFileAs, _("Save as"), wxEmptyString, wxITEM_NORMAL);
    MenuItem30->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE_AS")),wxART_OTHER));
    Menu1->Append(MenuItem30);
    Menu1->AppendSeparator();
    MenuItem31 = new wxMenuItem(Menu1, idMenuAddImage, _("Import image"), wxEmptyString, wxITEM_NORMAL);
    MenuItem31->SetBitmap(GetIcon(toolbar_load_image_png, toolbar_load_image_png_size));
    Menu1->Append(MenuItem31);
    MenuItem32 = new wxMenu();
    MenuItem34 = new wxMenuItem(MenuItem32, idMenuExportPNG, _("PNG snapshot"), wxEmptyString, wxITEM_NORMAL);
    MenuItem34->SetBitmap(GetIcon(toolbar_export_image_png, toolbar_export_image_png_size));
    MenuItem32->Append(MenuItem34);
    MenuItem35 = new wxMenuItem(MenuItem32, idMenuExportC, _("C function"), wxEmptyString, wxITEM_NORMAL);
    MenuItem35->SetBitmap(GetIcon(toolbar_export_C_png, toolbar_export_C_png_size));
    MenuItem32->Append(MenuItem35);
    MenuItem36 = new wxMenuItem(MenuItem32, idMenuExportCVS, _("CVS table"), wxEmptyString, wxITEM_NORMAL);
    MenuItem36->SetBitmap(GetIcon(toolbar_export_CSV_png, toolbar_export_CSV_png_size));
    MenuItem32->Append(MenuItem36);
    MenuItem37 = new wxMenuItem(MenuItem32, idMenuExportOdt, _("ODT report"), wxEmptyString, wxITEM_NORMAL);
    MenuItem37->SetBitmap(GetIcon(toolbar_export_ODT_png, toolbar_export_ODT_png_size));
    MenuItem32->Append(MenuItem37);
    Menu1->Append(idMenuExport, _("Export data as"), MenuItem32, wxEmptyString);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    MenuItem1->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUIT")),wxART_OTHER));
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu4 = new wxMenu();
    MenuItem21 = new wxMenuItem(Menu4, idMenuStop, _("Stop command"), wxEmptyString, wxITEM_NORMAL);
    MenuItem21->SetBitmap(GetIcon(toolbar_stop_command_png, toolbar_stop_command_png_size));
    Menu4->Append(MenuItem21);
    Menu4->AppendSeparator();
    MenuItem18 = new wxMenuItem(Menu4, idMenuPickPoint, _("Pick point"), wxEmptyString, wxITEM_NORMAL);
    MenuItem18->SetBitmap(GetIcon(toolbar_pick_point_png, toolbar_pick_point_png_size));
    Menu4->Append(MenuItem18);
    MenuItem19 = new wxMenuItem(Menu4, idMenuPickPointSet, _("Pick set of points"), wxEmptyString, wxITEM_NORMAL);
    MenuItem19->SetBitmap(GetIcon(toolbar_pick_multi_point_png, toolbar_pick_multi_point_png_size));
    Menu4->Append(MenuItem19);
    MenuItem26 = new wxMenuItem(Menu4, idMenuSortPoints, _("Sort points"), wxEmptyString, wxITEM_NORMAL);
    MenuItem26->SetBitmap(GetIcon(toolbar_sort_png, toolbar_sort_png_size));
    Menu4->Append(MenuItem26);
    Menu4->AppendSeparator();
    MenuItem39 = new wxMenuItem(Menu4, idMenuRescalePicture, _("Rescale image"), wxEmptyString, wxITEM_NORMAL);
    MenuItem39->SetBitmap(GetIcon(toolbar_rescale_image_png, toolbar_rescale_image_png_size));
    Menu4->Append(MenuItem39);
    MenuItem40 = new wxMenuItem(Menu4, idMenuRemoveImage, _("Remove image"), wxEmptyString, wxITEM_NORMAL);
    MenuItem40->SetBitmap(GetIcon(toolbar_remove_image_png, toolbar_remove_image_png_size));
    Menu4->Append(MenuItem40);
    Menu4->AppendSeparator();
    MenuItem38 = new wxMenuItem(Menu4, idMenuDeletePoint, _("Delete point"), wxEmptyString, wxITEM_NORMAL);
    MenuItem38->SetBitmap(GetIcon(toolbar_delete_point_png, toolbar_delete_point_png_size));
    Menu4->Append(MenuItem38);
    MenuBar1->Append(Menu4, _("Edit"));
    Menu3 = new wxMenu();
    MenuItem8 = new wxMenuItem(Menu3, idMenuRefresh, _("Refresh"), wxEmptyString, wxITEM_NORMAL);
    MenuItem8->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_REDO")),wxART_OTHER));
    Menu3->Append(MenuItem8);
    MenuItem42 = new wxMenu();
    MenuItem43 = new wxMenuItem(MenuItem42, idShowHor, _("Show horizontal lines"), wxEmptyString, wxITEM_CHECK);
    MenuItem42->Append(MenuItem43);
    MenuItem43->Check(true);
    MenuItem44 = new wxMenuItem(MenuItem42, idShowVert, _("Show vertical lines"), wxEmptyString, wxITEM_CHECK);
    MenuItem42->Append(MenuItem44);
    MenuItem44->Check(true);
    MenuItem45 = new wxMenuItem(MenuItem42, idShowZero, _("Show zero lines"), wxEmptyString, wxITEM_CHECK);
    MenuItem42->Append(MenuItem45);
    MenuItem45->Check(true);
    MenuItem46 = new wxMenuItem(MenuItem42, idShowHorAdds, _("Show horizontal extralines"), wxEmptyString, wxITEM_CHECK);
    MenuItem42->Append(MenuItem46);
    MenuItem46->Check(true);
    MenuItem47 = new wxMenuItem(MenuItem42, idShowVertAdds, _("Show vertical extralines"), wxEmptyString, wxITEM_CHECK);
    MenuItem42->Append(MenuItem47);
    MenuItem47->Check(true);
    MenuItem49 = new wxMenuItem(MenuItem42, idMenuShowAll, _("Show all"), wxEmptyString, wxITEM_NORMAL);
    MenuItem42->Append(MenuItem49);
    Menu3->Append(idMenuShow, _("Show"), MenuItem42, wxEmptyString);
    Menu3->AppendSeparator();
    MenuItem11 = new wxMenuItem(Menu3, idMenuZoomIn, _("Zoom in"), wxEmptyString, wxITEM_NORMAL);
    MenuItem11->SetBitmap(GetIcon(toolbar_zoom_in_png, toolbar_zoom_in_png_size));
    Menu3->Append(MenuItem11);
    MenuItem12 = new wxMenuItem(Menu3, idMenuZoomOut, _("Zoom out"), wxEmptyString, wxITEM_NORMAL);
    MenuItem12->SetBitmap(GetIcon(toolbar_zoom_out_png, toolbar_zoom_out_png_size));
    Menu3->Append(MenuItem12);
    MenuItem14 = new wxMenuItem(Menu3, idMenuTrimScale, _("Trim to curve"), wxEmptyString, wxITEM_NORMAL);
    MenuItem14->SetBitmap(GetIcon(toolbar_trim_to_curve_png, toolbar_trim_to_curve_png_size));
    Menu3->Append(MenuItem14);
    MenuItem15 = new wxMenuItem(Menu3, idMenuCenterZero, _("Move zero to center"), wxEmptyString, wxITEM_NORMAL);
    MenuItem15->SetBitmap(GetIcon(toolbar_center_zero_png, toolbar_center_zero_png_size));
    Menu3->Append(MenuItem15);
    MenuItem13 = new wxMenuItem(Menu3, idMenuInitialScale, _("Reset scale"), wxEmptyString, wxITEM_NORMAL);
    MenuItem13->SetBitmap(GetIcon(toolbar_reset_scale_png, toolbar_reset_scale_png_size));
    Menu3->Append(MenuItem13);
    MenuItem41 = new wxMenuItem(Menu3, idTrimToImage, _("Trim to image"), wxEmptyString, wxITEM_NORMAL);
    MenuItem41->SetBitmap(GetIcon(toolbar_trim_to_image_png, toolbar_trim_to_image_png_size));
    Menu3->Append(MenuItem41);
    Menu3->AppendSeparator();
    MenuItem9 = new wxMenuItem(Menu3, idMenuLogX, _("Logarithmic X-axis"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(Menu3, idMenuLogY, _("Logarithmic Y-axis"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(MenuItem10);
    Menu3->AppendSeparator();
    MenuItem16 = new wxMenuItem(Menu3, idMenuLockX, _("Lock scale X"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(MenuItem16);
    MenuItem17 = new wxMenuItem(Menu3, idMenuLockY, _("Lock scale Y"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(MenuItem17);
    MenuItem48 = new wxMenuItem(Menu3, idLockDrag, _("Lock for drag"), wxEmptyString, wxITEM_CHECK);
    Menu3->Append(MenuItem48);
    MenuBar1->Append(Menu3, _("View"));
    Menu6 = new wxMenu();
    MenuItem22 = new wxMenuItem(Menu6, idMenuPolynomialShow, _("Show/hide coefficients"), wxEmptyString, wxITEM_NORMAL);
    MenuItem22->SetBitmap(GetIcon(toolbar_coefficients_png, toolbar_coefficients_png_size));
    Menu6->Append(MenuItem22);
    MenuItem23 = new wxMenuItem(Menu6, idMenuSnapShot, _("Make snaphot (.png)"), wxEmptyString, wxITEM_NORMAL);
    MenuItem23->SetBitmap(GetIcon(toolbar_export_image_png, toolbar_export_image_png_size));
    Menu6->Append(MenuItem23);
    MenuItem24 = new wxMenuItem(Menu6, idMenuExportFunction, _("Export function (.c)"), wxEmptyString, wxITEM_NORMAL);
    MenuItem24->SetBitmap(GetIcon(toolbar_export_C_png, toolbar_export_C_png_size));
    Menu6->Append(MenuItem24);
    MenuItem33 = new wxMenuItem(Menu6, idMenuExportCSV, _("Export table (.csv)"), wxEmptyString, wxITEM_NORMAL);
    MenuItem33->SetBitmap(GetIcon(toolbar_export_CSV_png, toolbar_export_CSV_png_size));
    Menu6->Append(MenuItem33);
    MenuItem25 = new wxMenuItem(Menu6, idMenuMakeReport, _("Create report (.odt)"), wxEmptyString, wxITEM_NORMAL);
    MenuItem25->SetBitmap(GetIcon(toolbar_export_ODT_png, toolbar_export_ODT_png_size));
    Menu6->Append(MenuItem25);
    MenuBar1->Append(Menu6, _("Results"));
    Menu5 = new wxMenu();
    MenuItem20 = new wxMenuItem(Menu5, idMenuColours, _("Appearance"), wxEmptyString, wxITEM_NORMAL);
    MenuItem20->SetBitmap(GetIcon(toolbar_settings_png, toolbar_settings_png_size));
    Menu5->Append(MenuItem20);
    MenuBar1->Append(Menu5, _("Settings"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    MenuItem2->SetBitmap(GetIcon(toolbar_about_png, toolbar_about_png_size));
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[4] = { -10, -10, -10, -10 };
    int __wxStatusBarStyles_1[4] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(4,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(4,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
    ToolBarItem1 = ToolBar1->AddTool(1100, _("New file"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("New file"), wxEmptyString);
    ToolBarItem2 = ToolBar1->AddTool(1101, _("Open file"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Open file"), wxEmptyString);
    ToolBarItem3 = ToolBar1->AddTool(1102, _("Save file"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Save file"), wxEmptyString);
    ToolBarItem5 = ToolBar1->AddTool(1103, _("Save As"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE_AS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("Save file as"), wxEmptyString);
    ToolBar1->AddSeparator();
    ToolBarItem6 = ToolBar1->AddTool(1104, _("Import image"), GetIcon(toolbar_load_image_png, toolbar_load_image_png_size), wxNullBitmap, wxITEM_NORMAL, _("Import image"), wxEmptyString);
    ToolBar1->AddSeparator();
    ToolBarItem18 = ToolBar1->AddTool(1401, _("Add point"), GetIcon(toolbar_pick_point_png, toolbar_pick_point_png_size), wxNullBitmap, wxITEM_NORMAL, _("Pick point"), wxEmptyString);
    ToolBarItem19 = ToolBar1->AddTool(1402, _("Add point set"), GetIcon(toolbar_pick_multi_point_png, toolbar_pick_multi_point_png_size), wxNullBitmap, wxITEM_NORMAL, _("Pick point set"), wxEmptyString);
    ToolBarItem20 = ToolBar1->AddTool(1403, _("Sort points"), GetIcon(toolbar_sort_png, toolbar_sort_png_size), wxNullBitmap, wxITEM_NORMAL, _("Sort points"), wxEmptyString);
    ToolBarItem21 = ToolBar1->AddTool(1404, _("Stop command"), GetIcon(toolbar_stop_command_png, toolbar_stop_command_png_size), wxNullBitmap, wxITEM_NORMAL, _("Stop command"), wxEmptyString);
    ToolBar1->AddSeparator();
    ToolBarItem8 = ToolBar1->AddTool(1201, _("Zoom In"), GetIcon(toolbar_zoom_in_png, toolbar_zoom_in_png_size), wxNullBitmap, wxITEM_NORMAL, _("Zoom in"), wxEmptyString);
    ToolBarItem7 = ToolBar1->AddTool(1202, _("Zoom Out"), GetIcon(toolbar_zoom_out_png, toolbar_zoom_out_png_size), wxNullBitmap, wxITEM_NORMAL, _("Zoom out"), wxEmptyString);
    ToolBarItem10 = ToolBar1->AddTool(1204, _("Trim to curve"), GetIcon(toolbar_trim_to_curve_png, toolbar_trim_to_curve_png_size), wxNullBitmap, wxITEM_NORMAL, _("Trim to curve"), wxEmptyString);
    ToolBarItem11 = ToolBar1->AddTool(1205, _("Trim to zero"), GetIcon(toolbar_center_zero_png, toolbar_center_zero_png_size), wxNullBitmap, wxITEM_NORMAL, _("Center zero"), wxEmptyString);
    ToolBarItem12 = ToolBar1->AddTool(1206, _("Reset scale"), GetIcon(toolbar_reset_scale_png, toolbar_reset_scale_png_size), wxNullBitmap, wxITEM_NORMAL, _("Reset scale"), wxEmptyString);
    ToolBarItem9 = ToolBar1->AddTool(1203, _("Hide image"), GetIcon(toolbar_show_hide_image_png, toolbar_show_hide_image_png_size), wxNullBitmap, wxITEM_NORMAL, _("Show/Hide image"), wxEmptyString);
    ToolBarItem13 = ToolBar1->AddTool(1207, _("Trim to image"), GetIcon(toolbar_trim_to_image_png, toolbar_trim_to_image_png_size), wxNullBitmap, wxITEM_NORMAL, _("Trim to image"), wxEmptyString);
    ToolBarItem23 = ToolBar1->AddTool(1208, _("Custom scale"), GetIcon(toolbar_custom_scale_png, toolbar_custom_scale_png_size), wxNullBitmap, wxITEM_NORMAL, _("Custom scale"), wxEmptyString);
    ToolBar1->AddSeparator();
    ToolBarItem22 = ToolBar1->AddTool(1505, _("Show coefficients"), GetIcon(toolbar_coefficients_png, toolbar_coefficients_png_size), wxNullBitmap, wxITEM_NORMAL, _("Show coefficients"), wxEmptyString);
    ToolBarItem14 = ToolBar1->AddTool(1501, _("Snapshot"), GetIcon(toolbar_export_image_png, toolbar_export_image_png_size), wxNullBitmap, wxITEM_NORMAL, _("Export PNG snapshot"), wxEmptyString);
    ToolBarItem15 = ToolBar1->AddTool(1502, _("Cfunction"), GetIcon(toolbar_export_C_png, toolbar_export_C_png_size), wxNullBitmap, wxITEM_NORMAL, _("Export C function"), wxEmptyString);
    ToolBarItem16 = ToolBar1->AddTool(1503, _("CsvTable"), GetIcon(toolbar_export_CSV_png, toolbar_export_CSV_png_size), wxNullBitmap, wxITEM_NORMAL, _("Export CSV table"), wxEmptyString);
    ToolBarItem17 = ToolBar1->AddTool(1504, _("OdtReport"), GetIcon(toolbar_export_ODT_png, toolbar_export_ODT_png_size), wxNullBitmap, wxITEM_NORMAL, _("Export ODT report"), wxEmptyString);
    ToolBar1->Realize();
    SetToolBar(ToolBar1);
    MenuItem5 = new wxMenuItem((&menuPanelGraph), idUndo, _("stop command"), wxEmptyString, wxITEM_NORMAL);
    MenuItem5->SetBitmap(GetIcon(toolbar_stop_command_png, toolbar_stop_command_png_size));
    menuPanelGraph.Append(MenuItem5);
    menuPanelGraph.AppendSeparator();
    MenuItem3 = new wxMenuItem((&menuPanelGraph), idLockX, _("Lock scale X"), wxEmptyString, wxITEM_CHECK);
    menuPanelGraph.Append(MenuItem3);
    MenuItem4 = new wxMenuItem((&menuPanelGraph), idLockY, _("Lock scale Y"), wxEmptyString, wxITEM_CHECK);
    menuPanelGraph.Append(MenuItem4);
    menuPanelGraph.AppendSeparator();
    MenuItem6 = new wxMenuItem((&menuPanelGraph), idLogX, _("Logarithmic X"), wxEmptyString, wxITEM_CHECK);
    menuPanelGraph.Append(MenuItem6);
    MenuItem7 = new wxMenuItem((&menuPanelGraph), idLogY, _("Logarithmic Y"), wxEmptyString, wxITEM_CHECK);
    menuPanelGraph.Append(MenuItem7);
    menuPanelGraph.AppendSeparator();
    MenuItem50 = new wxMenuItem((&menuPanelGraph), idLockForDrag, _("Lock for drag"), wxEmptyString, wxITEM_CHECK);
    menuPanelGraph.Append(MenuItem50);
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(ID_GRID1,wxEVT_GRID_CELL_CHANGED,(wxObjectEventFunction)&GetCurveFrame::InputPoint);
    Connect(ID_GRID1,wxEVT_GRID_SELECT_CELL,(wxObjectEventFunction)&GetCurveFrame::CellSelect);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&GetCurveFrame::PointChanged);
    PanelGraph->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&GetCurveFrame::ClearSelected,0,this);
    PanelGraph->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&GetCurveFrame::OnPanelGraphMenu,0,this);
    Connect(ID_BITMAPBUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ZoomIn);
    Connect(ID_BITMAPBUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ZoomOut);
    Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::TrimToCurve);
    Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::TrimToZero);
    Connect(ID_BITMAPBUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ScaleReset);
    Connect(ID_BITMAPBUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::HideShowImage);
    Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::PickPoint);
    Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::PickMultiPoint);
    Connect(ID_BITMAPBUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::TrimRatioPerY);
    Connect(ID_BITMAPBUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::TrimRatioPerX);
    Connect(ID_BITMAPBUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::IncrementLogLeftBorder);
    Connect(ID_BITMAPBUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::DecrementLogBorder);
    Connect(ID_BITMAPBUTTON13,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::MakeLogarithmicCoordinates);
    Connect(ID_BITMAPBUTTON14,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::MakeLinearCoordinates);
    Connect(ID_BITMAPBUTTON15,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ShowOrHideCoefficientWindow);
    Connect(ID_BITMAPBUTTON16,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&GetCurveFrame::SortPointsMenu);
    Connect(idMenuFileNew,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::FileNew);
    Connect(idMenuOpenFile,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::OpenFile);
    Connect(idMenuSaveFile,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::SaveFile);
    Connect(idMenuSaveFileAs,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::SaveFileAs);
    Connect(idMenuAddImage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::LoadUnderlayerPicture);
    Connect(idMenuExportPNG,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::MakeScreenSnapshot);
    Connect(idMenuExportC,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ExportCFunction);
    Connect(idMenuExportCVS,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ExportCSVTable);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::OnQuit);
    Connect(idMenuStop,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::StopCommandPopUpMenu);
    Connect(idMenuPickPoint,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::PickPoint);
    Connect(idMenuPickPointSet,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::PickMultiPoint);
    Connect(idMenuSortPoints,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::SortPointsMenu);
    Connect(idMenuRescalePicture,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::RescaleImage);
    Connect(idMenuRemoveImage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::RemoveUnderLayerImage);
    Connect(idMenuDeletePoint,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::DeletePoint);
    Connect(idMenuRefresh,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::RefreshPanel);
    Connect(idShowHor,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ShowHorizontalLines);
    Connect(idShowVert,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ShowVerticalLines);
    Connect(idShowZero,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ShowZeroLines);
    Connect(idShowHorAdds,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ShowHorizontalExtraLines);
    Connect(idShowVertAdds,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ShowVerticalExtraLines);
    Connect(idMenuShowAll,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ShowAllLines);
    Connect(idMenuZoomIn,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ZoomIn);
    Connect(idMenuZoomOut,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ZoomOut);
    Connect(idMenuTrimScale,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::TrimToCurve);
    Connect(idMenuCenterZero,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::TrimToZero);
    Connect(idMenuInitialScale,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ScaleReset);
    Connect(idTrimToImage,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::TrimToImage);
    Connect(idMenuLogX,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::SetLogarithmicX);
    Connect(idMenuLogY,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::SetLogarithmicY);
    Connect(idMenuLockX,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::LockXScale);
    Connect(idMenuLockY,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::LockYScale);
    Connect(idLockDrag,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::LockScreenDrag);
    Connect(idMenuPolynomialShow,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ShowOrHideCoefficientWindow);
    Connect(idMenuSnapShot,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::MakeScreenSnapshot);
    Connect(idMenuExportFunction,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ExportCFunction);
    Connect(idMenuExportCSV,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ExportCSVTable);
    Connect(idMenuMakeReport,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::SaveOdtReport);
    Connect(idMenuColours,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::ChangeColors);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::OnAbout);
    Connect(1100,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::FileNew);
    Connect(1101,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::OpenFile);
    Connect(1102,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::SaveFile);
    Connect(1103,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::SaveFileAs);
    Connect(1104,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::LoadUnderlayerPicture);
    Connect(1401,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::PickPoint);
    Connect(1402,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::PickMultiPoint);
    Connect(1403,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::SortPointsMenu);
    Connect(1404,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::StopCommandPopUpMenu);
    Connect(1201,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ZoomIn);
    Connect(1202,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ZoomOut);
    Connect(1204,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::TrimToCurve);
    Connect(1205,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::TrimToZero);
    Connect(1206,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ScaleReset);
    Connect(1203,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::HideShowImage);
    Connect(1207,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::TrimToImage);
    Connect(1208,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::SetCustomScale);
    Connect(1505,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ShowOrHideCoefficientWindow);
    Connect(1501,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::MakeScreenSnapshot);
    Connect(1502,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ExportCFunction);
    Connect(1503,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::ExportCSVTable);
    Connect(1504,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&GetCurveFrame::SaveOdtReport);
    Connect(idUndo,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::StopCommandPopUpMenu);
    Connect(idLockX,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::LockXScale);
    Connect(idLockY,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::LockYScale);
    Connect(idLogX,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::SetLogarithmicX);
    Connect(idLogY,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::SetLogarithmicY);
    Connect(idLockForDrag,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&GetCurveFrame::LockScreenDrag);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&GetCurveFrame::OnClose);
    //*)

    // Preliminary initializations
    SpinCtrl1->SetValue(INITIAL_POINT_NUMBER);
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
    for (int i=0; i<SpinCtrl1->GetValue(); i++)
    {
        Grid1->SetCellValue(i,0,wxString::Format("%lf", polynom.GetPoint(i).x));
        Grid1->SetCellValue(i,1,wxString::Format("%lf", polynom.GetPoint(i).y));
        Grid1->SetReadOnly(i,0,false);
        Grid1->SetReadOnly(i,1,false);
    }
    for (int i=SpinCtrl1->GetValue(); i<Grid1->GetNumberRows();i++)
    {
        Grid1->SetCellValue(i,0,wxT("-"));
        Grid1->SetCellValue(i,1,wxT("-"));
        Grid1->SetReadOnly(i,0,true);
        Grid1->SetReadOnly(i,1,true);
    }
    polynom.SetCount(INITIAL_POINT_NUMBER);
    PanelGraph->SetPoints(polynom.GetPointArray(), INITIAL_POINT_NUMBER);
    PanelGraph->Refresh();
    currentGridPosition = 0;
    isPick = NO_PICK;
    // IO options
    myLastDirectory = wxEmptyString;
    currentFilePath = wxEmptyString;
    currentFileName = wxEmptyString;
    hasFileNotSavedChanges = false;
    // Frame settings
    this->Maximize();
    isCoeffVisible = false;
    coeffDlg = new PolynomialWindow(this);
    coeffDlg->ShowError();
    // Load initial settings
    LoadSettingsOnLoad();
}

GetCurveFrame::~GetCurveFrame()
{
    //(*Destroy(GetCurveFrame)
    //*)
    delete coeffDlg;
}

// Extracts resources (icons) from a unsigned char array
wxBitmap GetCurveFrame::GetIcon(const unsigned char* myName, const long int mySize)
{
    wxMemoryInputStream inStream (myName, mySize);
    wxImage myImg (inStream, wxBITMAP_TYPE_PNG);
    wxBitmap myPic(myImg);
    return myPic;
}

void GetCurveFrame::OnQuit(wxCommandEvent& event)
{
    wxCommandEvent dummyEvent;
    int result = wxID_NO;
    SaveCancelFlag = true;

    if (hasFileNotSavedChanges)
    {
        result = OnCloseMessage();
    }

    switch (result)
        {
            case wxID_YES:
            {
                SaveFile(dummyEvent);
                break;
            }
            case wxID_NO:
            {
                break;
            }
            case wxID_CANCEL:
            {
                return;
            }
        }

    if (!SaveCancelFlag)
        return;

    SaveSettingsAtExit();
    Close();
}

void GetCurveFrame::OnClose(wxCloseEvent& event)
{
    wxCommandEvent dummyEvent;
    int result = wxID_NO;
    SaveCancelFlag = true;

    if (hasFileNotSavedChanges)
    {
        result = OnCloseMessage();
    }

    switch (result)
        {
            case wxID_YES:
            {
                SaveFile(dummyEvent);
                break;
            }
            case wxID_NO:
            {
                break;
            }
            case wxID_CANCEL:
            {
                return;
            }
        }

    if (!SaveCancelFlag)
        return;

    SaveSettingsAtExit();
    Destroy();
}

int GetCurveFrame::OnCloseMessage()
{
    int dlgResult;

    wxMessageDialog *msg = new wxMessageDialog
                            (this,
                             "The file has been changed. Do you want to save changes",
                             "Exit",
                             wxYES_NO| wxCANCEL|wxCENTRE,
                             wxDefaultPosition);

    dlgResult = msg->ShowModal();
    delete msg;
    return dlgResult;
}

void GetCurveFrame::OnAbout(wxCommandEvent& event)
{
    AboutWindow *dlg = new AboutWindow(this);
    dlg->ShowModal();
    delete dlg;
}

void GetCurveFrame::PointChanged(wxSpinEvent& event)
{
    int counter;
    Point a;
    wxString cell;
    counter = SpinCtrl1->GetValue();
    polynom.SetCount(counter);

    for (int i=0; i<counter; i++)
    {
        a = polynom.GetPoint(i);
        cell.Clear();
        cell<<a.x;
        Grid1->SetCellValue(i,0,cell);
        cell.Clear();
        cell<<a.y;
        Grid1->SetCellValue(i,1,cell);
        Grid1->SetReadOnly(i,0,false);
        Grid1->SetReadOnly(i,1,false);
    }

    // Disable cells
    for (int i=counter; i<Grid1->GetNumberRows();i++)
    {
        Grid1->SetCellValue(i,0,wxT("-"));
        Grid1->SetCellValue(i,1,wxT("-"));
        Grid1->SetReadOnly(i,0,true);
        Grid1->SetReadOnly(i,1,true);
    }

    PanelGraph->SetPoints(polynom.GetPointArray(), counter);

    if (polynom.CheckPoints())
    {
        polynom.Calculate();
        RefreshCoefficientToolwindow();
        PanelGraph->SetPolynomial(polynom.GetPolynomialArray(), counter);
    }
    else
    {
        RefreshCoefficientToolwindow(false);
        PanelGraph->SetPolynomial(polynom.GetPolynomialArray(), 0);
    }
    hasFileNotSavedChanges = true;
}

// Sorts points array and refreshes a grid table
void GetCurveFrame::SortPoints(int numberOfPoints)
{
    Point m_pt[MAX_POINTS];
    wxString myCell;

    for (int i=0; i<numberOfPoints; ++i)
    {
        Grid1->GetCellValue(i,0).ToDouble(&m_pt[i].x);
        Grid1->GetCellValue(i,1).ToDouble(&m_pt[i].y);
    }

    qsort(m_pt, numberOfPoints, sizeof(Point), &comparator);

    for (int i=0; i<numberOfPoints; ++i)
    {
        polynom.SetPoint(m_pt[i].x, m_pt[i].y, i);
        myCell.Clear();
        myCell<<m_pt[i].x;
        Grid1->SetCellValue(i,0,myCell);
        myCell.Clear();
        myCell<<m_pt[i].y;
        Grid1->SetCellValue(i,1,myCell);
    }
    PanelGraph->SetPoints(polynom.GetPointArray(), numberOfPoints);
    hasFileNotSavedChanges = true;
}

// Compares x-coordinates of two points
int comparator(const void *a, const void *b)
{
    if (((Point*)a)->x - ((Point*)b)->x>0)
    {
        return 1;
    }

    if (((Point*)a)->x - ((Point*)b)->x<0)
    {
        return -1;
    }

   return 0;
}

void GetCurveFrame::InputPoint(wxGridEvent& event)
{
    int row;
    int ptNumber;
    double x;
    double y;

    ptNumber = SpinCtrl1->GetValue();
    row = event.GetRow();

    if (!Grid1->GetCellValue(row,0).ToDouble(&x))
    {
        x = 0;  // not a number in the cell
        Grid1->SetCellValue(row, 0, wxT("0"));
    }

    if (!Grid1->GetCellValue(row,1).ToDouble(&y))
    {
        y = 0;  // not a number in the cell
        Grid1->SetCellValue(row, 1, wxT("0"));
    }

    polynom.SetPoint(x, y, row);
    PanelGraph->SetPoints(polynom.GetPointArray(), ptNumber);
    if (polynom.CheckPoints())
    {
        polynom.Calculate();
        RefreshCoefficientToolwindow();
        PanelGraph->SetPolynomial(polynom.GetPolynomialArray(), polynom.GetCount());

    }
    else
    {
        RefreshCoefficientToolwindow(false);
        PanelGraph->SetPolynomial(polynom.GetPolynomialArray(), 0);
    }
    hasFileNotSavedChanges = true;
}

// Deletes selected point
void GetCurveFrame::DeletePoint(wxCommandEvent& event)
{
    int point;
    int counter;
    wxSpinEvent myEvent;

    counter = SpinCtrl1->GetValue();
    point = PanelGraph->GetSelectedPoint();

    if (point==NO_POINT_SELECTED)
        return;

    if (point>counter)
        return;

    for (int i=point; i<counter - 1; ++i)
    {
        polynom.SetPoint(polynom.GetPoint(i+1).x,
                         polynom.GetPoint(i+1).y,
                         i);
    }

    polynom.SetPoint(0, 0, counter - 1);
    counter--;
    SpinCtrl1->SetValue(counter);
    PointChanged(myEvent);
}

void GetCurveFrame::CellSelect(wxGridEvent& event)
{
    wxString textOut;
    int selected = event.GetRow();
    PanelGraph->SelectPoint(selected);
    textOut.Clear();
    textOut<<"Selected point:"<<selected + 1;
    StatusBar1->SetStatusText(textOut, 0);
    currentGridPosition = selected;

}

void GetCurveFrame::ClearSelected(wxMouseEvent& event)
{
    PanelGraph->SelectPoint(NO_POINT_SELECTED);
    StatusBar1->SetStatusText("Selected point: no point", 0);
}

void GetCurveFrame::TrimToCurve(wxCommandEvent& event)
{
    PanelGraph->TrimScale();
    PanelGraph->SetFocus();
}

void GetCurveFrame::TrimToZero(wxCommandEvent& event)
{
    PanelGraph->ScaleZeroToCenter();
    //PanelGraph->TrimToZero();
    PanelGraph->SetFocus();
}

void GetCurveFrame::TrimRatioPerX(wxCommandEvent& event)
{
    PanelGraph->TrimProportionalRatioPerX();
    PanelGraph->SetFocus();
}

void GetCurveFrame::TrimRatioPerY(wxCommandEvent& event)
{
    PanelGraph->TrimProportionalRatioPerY();
    PanelGraph->SetFocus();
}

void GetCurveFrame::OnPanelGraphMenu(wxMouseEvent& event)
{
    wxPoint pt;
    pt.x = event.GetPosition().x;
    pt.y = event.GetPosition().y;
    pt.x += Panel1->GetSize().GetWidth();
    PopupMenu(&menuPanelGraph, pt);
}

void GetCurveFrame::LockXScale(wxCommandEvent& event)
{
    if (event.GetId()==MenuItem3->GetId())
    {
        PanelGraph->SetScaleXLocked(MenuItem3->IsChecked());
    }

    if (event.GetId()==MenuItem16->GetId())
    {
        PanelGraph->SetScaleXLocked(MenuItem16->IsChecked());
    }

    RefreshCheckBoxStates();
}

void GetCurveFrame::LockYScale(wxCommandEvent& event)
{
    if (event.GetId()==MenuItem4->GetId())
    {
        PanelGraph->SetScaleYLocked(MenuItem4->IsChecked());
    }

    if (event.GetId()==MenuItem17->GetId())
    {
        PanelGraph->SetScaleYLocked(MenuItem17->IsChecked());
    }

    RefreshCheckBoxStates();
}

void GetCurveFrame::SetLogarithmicX(wxCommandEvent& event)
{
    if (event.GetId()==MenuItem6->GetId())
    {
        PanelGraph->SetLogarithmicX(MenuItem6->IsChecked());
    }

    if (event.GetId()==MenuItem9->GetId())
    {
        PanelGraph->SetLogarithmicX(MenuItem9->IsChecked());
    }

    RefreshButtonStates();
    RefreshCheckBoxStates();
}

void GetCurveFrame::SetLogarithmicY(wxCommandEvent& event)
{
    if (event.GetId()==MenuItem7->GetId())
    {
        PanelGraph->SetLogarithmicY(MenuItem7->IsChecked());
    }

    if (event.GetId()==MenuItem10->GetId())
    {
        PanelGraph->SetLogarithmicY(MenuItem10->IsChecked());
    }

    RefreshButtonStates();
    RefreshCheckBoxStates();
}

void GetCurveFrame::MouseCoordinatesHaveBeenChenged(wxCommandEvent& event)
{
    StatusBar1->SetStatusText(event.GetString(),1);
}

void GetCurveFrame::PickPoint(wxCommandEvent& event)
{
    if (PanelGraph->GetSelectPoint()==NO_SELECTED_POINT)
        return;

    if (currentGridPosition>=polynom.GetCount())
    {
        PanelGraph->SetFocus();
        return;
    }
    PanelGraph->SetForPointPick(true);
    isPick = PICK_SINGLEPOINT;
    PanelGraph->SetFocus();
}

void GetCurveFrame::PickMultiPoint(wxCommandEvent& event)
{
    if (PanelGraph->GetSelectPoint()==NO_SELECTED_POINT)
        return;

    if (currentGridPosition>=MAX_POINTS)
    {
        PanelGraph->SetFocus();
        return;
    }

    if (currentGridPosition>=SpinCtrl1->GetValue())
        currentGridPosition = SpinCtrl1->GetValue();

    PanelGraph->SetForPointPick(true);
    isPick = PICK_MULTIPOINT;
    PanelGraph->SetFocus();
}

void GetCurveFrame::PointHasBeenPicked(wxCommandEvent& event)
{
    wxString cell;

    switch (isPick)
    {
    case NO_PICK:
        {
            PanelGraph->SetForPointPick(false);
            return;
        }
    case PICK_SINGLEPOINT:
        {
            hasFileNotSavedChanges = true;

            if (currentGridPosition>=polynom.GetCount())
                currentGridPosition = polynom.GetCount() - 1;
            polynom.SetPoint(PanelGraph->GetX(), PanelGraph->GetY(), currentGridPosition);
            cell.Clear();
            cell<<polynom.GetPoint(currentGridPosition).x;
            Grid1->SetCellValue(currentGridPosition, 0, cell);
            cell.Clear();
            cell<<polynom.GetPoint(currentGridPosition).y;
            Grid1->SetCellValue(currentGridPosition, 1, cell);
            PanelGraph->SetForPointPick(false);
            PanelGraph->SetPoints(polynom.GetPointArray(), polynom.GetCount());
            if (polynom.CheckPoints())
            {
                polynom.Calculate();
                RefreshCoefficientToolwindow();
                PanelGraph->SetPolynomial(polynom.GetPolynomialArray(), polynom.GetCount());
            }
            else
            {
                RefreshCoefficientToolwindow(false);
                PanelGraph->SetPolynomial(polynom.GetPolynomialArray(), 0);
            }
            break;
        }
    case PICK_MULTIPOINT:
        {
            hasFileNotSavedChanges = true;

            if (currentGridPosition>SpinCtrl1->GetValue())
                currentGridPosition = SpinCtrl1->GetValue();     // exclude void cells

            for (int i=0; i<=currentGridPosition; i++)
            {
                Grid1->SetReadOnly(i,0,false);
                Grid1->SetReadOnly(i,1,false);
            }
            for (int i=currentGridPosition+1; i<SpinCtrl1->GetValue() - 1; i++)
            {
                if (i>=SpinCtrl1->GetValue())
                {
                    Grid1->SetReadOnly(i,0,true);
                    Grid1->SetCellValue(i,0,wxT("-"));
                    Grid1->SetReadOnly(i,1,true);
                    Grid1->SetCellValue(i,1,wxT("-"));
                }
            }
            polynom.SetCount(currentGridPosition+1);
            polynom.SetPoint(PanelGraph->GetX(), PanelGraph->GetY(), currentGridPosition);
            cell.Clear();
            cell<<polynom.GetPoint(currentGridPosition).x;
            Grid1->SetCellValue(currentGridPosition, 0, cell);
            cell.Clear();
            cell<<polynom.GetPoint(currentGridPosition).y;
            Grid1->SetCellValue(currentGridPosition, 1, cell);

            PanelGraph->SetPoints(polynom.GetPointArray(), polynom.GetCount());
            if (polynom.CheckPoints())
            {
                polynom.Calculate();
                RefreshCoefficientToolwindow();
                PanelGraph->SetPolynomial(polynom.GetPolynomialArray(), polynom.GetCount());
            }
            else
            {
                RefreshCoefficientToolwindow(false);
                PanelGraph->SetPolynomial(polynom.GetPolynomialArray(), 0);
            }
            currentGridPosition++;
            SpinCtrl1->SetValue(currentGridPosition);
            if (currentGridPosition>=MAX_POINTS)
            {
                currentGridPosition--;
                PanelGraph->SetForPointPick(false);
                return;
            }
            PanelGraph->Refresh();
            break;
        }
    }
}

void GetCurveFrame::StopCommandPopUpMenu(wxCommandEvent& event)
{
    wxString textOut;
    PanelGraph->SelectPoint(-1);
    PanelGraph->SetForPointPick(false);
    isPick = NO_PICK;
    textOut.Clear();
    textOut<<"Selected point: no point";
    StatusBar1->SetStatusText(textOut, 1);
    PanelGraph->Refresh();
}

void GetCurveFrame::ZoomIn(wxCommandEvent& event)
{
    PanelGraph->ZoomIn();
    if (event.GetId()==BitmapButton5->GetId())
        PanelGraph->SetFocus();
}

void GetCurveFrame::ZoomOut(wxCommandEvent& event)
{
    PanelGraph->ZoomOut();
    if (event.GetId()==BitmapButton6->GetId())
        PanelGraph->SetFocus();
}


void GetCurveFrame::ScaleReset(wxCommandEvent& event)
{
    PanelGraph->ScaleResetFramePosition();
    PanelGraph->SetFocus();
}

void GetCurveFrame::IncrementLogLeftBorder(wxCommandEvent& event)
{
    PanelGraph->IncrementZeroLog();
    PanelGraph->SetFocus();
}

void GetCurveFrame::DecrementLogBorder(wxCommandEvent& event)
{
    PanelGraph->DecrementZeroLog();
    PanelGraph->SetFocus();
}

// Hides or shows image on GraphPanel
void GetCurveFrame::HideShowImage(wxCommandEvent& event)
{
    PanelGraph->HideImage(!PanelGraph->IsImageHidden());
    PanelGraph->SetFocus();
    PanelGraph->Refresh();
}

void GetCurveFrame::MakeLogarithmicCoordinates(wxCommandEvent& event)
{
    PanelGraph->SetLogarithmicX(true);
    PanelGraph->SetLogarithmicY(true);
    RefreshButtonStates();
    MenuItem6->Check(true);
    MenuItem7->Check(true);
    MenuItem9->Check(true);
    MenuItem10->Check(true);
    PanelGraph->SetFocus();
    PanelGraph->TrimScale();
}

void GetCurveFrame::MakeLinearCoordinates(wxCommandEvent& event)
{
    PanelGraph->SetLogarithmicX(false);
    PanelGraph->SetLogarithmicY(false);
    RefreshButtonStates();
    MenuItem6->Check(false);
    MenuItem7->Check(false);
    MenuItem9->Check(false);
    MenuItem10->Check(false);
    PanelGraph->SetFocus();
    PanelGraph->TrimScale();
}

void GetCurveFrame::RefreshPanel(wxCommandEvent& event)
{
    wxCommandEvent stopAll;
    StopCommandPopUpMenu(stopAll);
    PanelGraph->Refresh();
}

void GetCurveFrame::ChangeColors(wxCommandEvent& event)
{
    ColorSettings *dlg = new ColorSettings(this);
    dlg->SetTarget(PanelGraph);
    dlg->ShowModal();
    delete dlg;
}

void GetCurveFrame::SortPointsMenu(wxCommandEvent& event)
{
    wxCommandEvent stopEvent;
    StopCommandPopUpMenu(stopEvent);
    SortPoints(SpinCtrl1->GetValue());
    PanelGraph->Refresh();
}

void GetCurveFrame::ShowOrHideCoefficientWindow(wxCommandEvent& event)
{
    if (coeffDlg->IsShown())
    {
        coeffDlg->Hide();
    }
    else
    {
        coeffDlg->Show();
    }
}

void GetCurveFrame::RefreshCoefficientToolwindow(bool isOK)
{
    double *p;
    int counter;
    wxString textOut;

    if (!isOK)
    {
        coeffDlg->ShowError();
        return;
    }

    counter = polynom.GetCount();

    p = polynom.GetPolynomialArray();
    for (int i=0; i<counter; ++i)
    {
        textOut.Clear();
        textOut<<p[i];
        coeffDlg->coeffGrid->SetCellValue(i, 0, textOut);
    }

    textOut = wxT("-");
    for (int i=counter; i<MAX_POINTS; ++i)
    {
        coeffDlg->coeffGrid->SetCellValue(i, 0, textOut);
    }
}

void GetCurveFrame::RefreshMyLabel()
{
    wxString myLabel;
    myLabel.Clear();
    myLabel<<FRAME_LABEL;
    if (currentFileName!=wxEmptyString)
        myLabel<<" - "<<currentFileName;
    this->SetLabel(myLabel);
}

// Iconizes child windows if the main frame has been iconized
// @Excluded
void GetCurveFrame::OnIconize(wxIconizeEvent& event)
{
    // @excluded
    // coeffDlg->Iconize(this->IsIconized());
}

void GetCurveFrame::RescaleImage(wxCommandEvent& event)
{
    PanelGraph->HideImage(false);
    if (!PanelGraph->GetHasImage())
        return;

    PictureScaler *scaler = new PictureScaler(this);
    scaler->SetImageObject(PanelGraph->GetImage(),
                           PanelGraph->GetMinOrder(),
                           PanelGraph->GetMaxOrder());
    scaler->SetIsRescaling(true);
    scaler->Show();
}

void GetCurveFrame::ImageHasBeenScaled(wxCommandEvent& event)
{
    PanelGraph->ScaleTrimToImage();
    //PanelGraph->Refresh();
}

void GetCurveFrame::RemoveUnderLayerImage(wxCommandEvent& event)
{
    PanelGraph->DeleteImage();
    PanelGraph->Refresh();
}

void GetCurveFrame::TrimToImage(wxCommandEvent& event)
{
    PanelGraph->ScaleTrimToImage();
    RefreshButtonStates();
}

// Refreshes enable states of the buttons
void GetCurveFrame::RefreshButtonStates()
{
    if ((PanelGraph->GetIsLogarithmicX()) ||
        (PanelGraph->GetIsLogarithmicY()))
    {
        BitmapButton10->Enable(true);
        BitmapButton11->Enable(true);
    }
    else
    {
        BitmapButton10->Enable(false);
        BitmapButton11->Enable(false);
    }
}

// Refreshes enable states of the checkboxes
void GetCurveFrame::RefreshCheckBoxStates()
{
    MenuItem3->Check(PanelGraph->GetIsScaleLockedX());
    MenuItem4->Check(PanelGraph->GetIsScaleLockedY());
    MenuItem6->Check(PanelGraph->GetIsLogarithmicX());
    MenuItem9->Check(PanelGraph->GetIsLogarithmicX());
    MenuItem7->Check(PanelGraph->GetIsLogarithmicY());
    MenuItem10->Check(PanelGraph->GetIsLogarithmicY());
    MenuItem16->Check(PanelGraph->GetIsScaleLockedX());
    MenuItem17->Check(PanelGraph->GetIsScaleLockedY());

    MenuItem43->Check(PanelGraph->GetShowHorizontalNetwork());
    MenuItem44->Check(PanelGraph->GetShowVerticalNetwork());
    MenuItem45->Check(PanelGraph->GetShowZeroLines());
    MenuItem46->Check(PanelGraph->GetShowHorizontalNetworkAdds());
    MenuItem47->Check(PanelGraph->GetShowVerticalNetworkAdds());
    MenuItem48->Check(PanelGraph->GetIsDragLocked());
    MenuItem50->Check(PanelGraph->GetIsDragLocked());
}

void GetCurveFrame::ShowHorizontalLines(wxCommandEvent& event)
{
    PanelGraph->SetShowHorizontalNetwork(MenuItem43->IsChecked());
    RefreshCheckBoxStates();
    PanelGraph->Refresh();
}

void GetCurveFrame::ShowVerticalLines(wxCommandEvent& event)
{
    PanelGraph->SetShowVerticalNetwork(MenuItem44->IsChecked());
    RefreshCheckBoxStates();
    PanelGraph->Refresh();
}

void GetCurveFrame::ShowZeroLines(wxCommandEvent& event)
{
    PanelGraph->SetShowZeroLines(MenuItem45->IsChecked());
    RefreshCheckBoxStates();
    PanelGraph->Refresh();
}

void GetCurveFrame::ShowHorizontalExtraLines(wxCommandEvent& event)
{
    PanelGraph->SetShowHorizontalNetworkAdds(MenuItem46->IsChecked());
    RefreshCheckBoxStates();
    PanelGraph->Refresh();
}

void GetCurveFrame::ShowVerticalExtraLines(wxCommandEvent& event)
{
    PanelGraph->SetShowVerticalNetworkAdds(MenuItem47->IsChecked());
    RefreshCheckBoxStates();
    PanelGraph->Refresh();
}

void GetCurveFrame::LockScreenDrag(wxCommandEvent& event)
{
    if (event.GetId()==MenuItem48->GetId())
    {
        PanelGraph->LockDrag(MenuItem48->IsChecked());
    }

    if (event.GetId()==MenuItem50->GetId())
    {
        PanelGraph->LockDrag(MenuItem50->IsChecked());
    }

    RefreshCheckBoxStates();
}

void GetCurveFrame::ShowAllLines(wxCommandEvent& event)
{
    PanelGraph->RestoreNetworkDefault();
    RefreshCheckBoxStates();
}

void GetCurveFrame::SetCustomScale(wxCommandEvent& event)
{
    CustomScale *dlg = new CustomScale(this);
    dlg->SetPanel(PanelGraph);
    dlg->ShowModal();
    delete dlg;
}
