#include "GetCurveMain.h"
#include "../dialogues/PictureScaler.h"
#include<wx/filename.h>
#include <wx/wfstream.h>
#include <wx/datstrm.h>

const char* const FILE_SETTINGS_NAME = "settings.dat";
//const char* const FILE_DELIMITER = "\\"; @excluded
const char* const FILE_IDENT = "GetCurveFile_1.0";
const char* const FILE_IDENT_SETTINGS = "GetCurveFile_1.0_settings";

// Saves current settings: i.e. colors, tool window positions
void GetCurveFrame::SaveSettingsAtExit()
{
    wxString currentPath;
    currentPath = wxGetCwd();
    currentPath<<wxFileName::GetPathSeparator()<<FILE_SETTINGS_NAME;

    if (wxFileExists(currentPath))
    {
        // Create file and save
        wxFileInputStream file(currentPath);
        wxDataInputStream myFile(file);
        if (FILE_IDENT_SETTINGS!=myFile.ReadString())
        {
            currentPath.Clear();
            currentPath<<"Wrong settings file "<<FILE_SETTINGS_NAME<<"! \nDelete it and restart the program!";
            wxMessageBox(currentPath);
            return;
        }
        SaveSettings(currentPath);
    }
    else
    {
        // Sabe settings
        SaveSettings(currentPath);
    }
}

// Saves current settings (i.e. colors, positions) at program close
void GetCurveFrame::SaveSettings(const wxString &currentPath)
{
    wxFileOutputStream file(currentPath);
    wxDataOutputStream myFile(file);

    // First line for GetCurve settings files
    myFile.WriteString(FILE_IDENT_SETTINGS);

    // Save colors
    myFile.Write32(PanelGraph->GetPanelColour());
    myFile.Write32(PanelGraph->GetLinesZeroColour());
    myFile.Write32(PanelGraph->GetLinesCoordColour());
    myFile.Write32(PanelGraph->GetLinesCoordAddsColour());
    myFile.Write32(PanelGraph->GetMainLineColour());
    myFile.Write32(PanelGraph->GetPointColour());
    myFile.Write32(PanelGraph->GetTextColour());
    myFile.Write32(PanelGraph->GetTextErrorColour());

    // Thickness
    myFile.Write32(PanelGraph->GetPointRadius());
    myFile.Write32(PanelGraph->GetMainLineThickness());

    // Toolbars positions
    myFile.Write32(SplitterWindow1->GetSashPosition());
    myFile.Write32(coeffDlg->GetPosition().x);
    myFile.Write32(coeffDlg->GetPosition().y);

    // Opened toolbars
    myFile.Write32(coeffDlg->IsShown());

    // Close file
    file.Close();
}

// Loads settings on program load
void GetCurveFrame::LoadSettingsOnLoad()
{
    wxString currentPath;
    wxPoint point;          // position of toolbars
    currentPath = wxGetCwd();
    currentPath<<wxFileName::GetPathSeparator()<<FILE_SETTINGS_NAME;

    if (!wxFileExists(currentPath))
        return;

    wxFileInputStream file(currentPath);
    wxDataInputStream myFile(file);

    // First line for GetCurve settings files
    if (FILE_IDENT_SETTINGS!=myFile.ReadString())
        {
            currentPath.Clear();
            currentPath<<"Cannot read "<<FILE_SETTINGS_NAME<<"!";
            wxMessageBox(currentPath);
            return;
        }

    // Read colors
    PanelGraph->SetPanelColour(myFile.Read32());
    PanelGraph->SetLinesZeroColour(myFile.Read32());
    PanelGraph->SetLinesCoordColour(myFile.Read32());
    PanelGraph->SetLinesCoordAddsColour(myFile.Read32());
    PanelGraph->SetMainLineColour(myFile.Read32());
    PanelGraph->SetPointColour(myFile.Read32());
    PanelGraph->SetTextColour(myFile.Read32());
    PanelGraph->SetTextErrorColour(myFile.Read32());

    // Thickness
    PanelGraph->SetPointRadius(myFile.Read32());
    PanelGraph->SetMainLineThickness(myFile.Read32());

    // Toolbars positions
    SplitterWindow1->SetSashPosition(myFile.Read32());
    point.x = myFile.Read32();
    point.y = myFile.Read32();
    coeffDlg->SetPosition(point);

    // Show toolbars
    coeffDlg->Show(myFile.Read32());

    this->Refresh();
}

void GetCurveFrame::SaveFile(wxCommandEvent& event)
{
    if (currentFilePath!=wxEmptyString)
    {
        WriteFile(currentFilePath);
        return;
    }
    else
    {
        wxCommandEvent myEvent;
        SaveFileAs(myEvent);
    }
}

void GetCurveFrame::SaveFileAs(wxCommandEvent& event)
{
    bool dlgResult;
    bool isFileChosen;
    wxString pathToSave;
    wxString fileName;
    wxString chosenDirectory;

    isFileChosen = false;
    while (!isFileChosen)
    {
        wxFileDialog *dlg = new wxFileDialog
                                (this, ("Save file"),
                                 myLastDirectory,
                                 wxEmptyString,
                                 wxT("Data files (*.dat)|*.dat"),
                                 wxFD_SAVE,
                                 wxDefaultPosition,
                                 wxDefaultSize,
                                 wxT("Save file"));

        if (dlg->ShowModal()==wxID_CANCEL)
        {
            delete dlg;
            SaveCancelFlag = false;
            return;
        }

        pathToSave = dlg->GetPath();
        fileName = dlg->GetFilename();
        chosenDirectory = dlg->GetDirectory();  // set down

        isFileChosen = true;
        if (wxFileExists(pathToSave))
        {
            isFileChosen = false;
            dlgResult = AskUserDialogue("File exists! \nDo you want to overwrite current file?",
                                        "File rewrite");
            if (dlgResult)
                isFileChosen = true;
        }
        delete dlg;
    }

    if ((pathToSave==wxEmptyString) && (fileName==wxEmptyString))
        return;

    currentFilePath = pathToSave;
    currentFileName = fileName;
    myLastDirectory = chosenDirectory;
    WriteFile(currentFilePath);
    RefreshMyLabel();
}

void GetCurveFrame::OpenFile(wxCommandEvent& event)
{
    int dlgResult;
    wxString pathToLoad;
    wxString fileName;
    wxCommandEvent toSaveEvent;

    if (hasFileNotSavedChanges)
    {
        // Ask for save
        /*
        dlgResult = AskUserDialogue("Current file has been changed!\n Do you want to save changes?",
                                    "File rewrite");
        if (dlgResult)
            SaveFile(toSaveEvent);
        */

        wxMessageDialog *msg = new wxMessageDialog
                            (this,
                             "Current file has been changed!\n Do you want to save changes?",
                             "File rewrite",
                             wxYES_NO| wxCANCEL|wxCENTRE,
                             wxDefaultPosition);

        dlgResult = msg->ShowModal();
        delete msg;

        switch (dlgResult)
        {
            case wxID_YES:
            {
                SaveFile(toSaveEvent);

                if (hasFileNotSavedChanges)
                    return;

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
    }

    wxFileDialog *dlg = new wxFileDialog
                            (this, ("Load file"),
                             myLastDirectory,
                             wxEmptyString,
                             wxT("Data files (*.dat)|*.dat"),
                             wxFD_OPEN|wxFD_FILE_MUST_EXIST,
                             wxDefaultPosition,
                             wxDefaultSize,
                             wxT("Save file"));

    if (dlg->ShowModal()==wxID_CANCEL)
    {
        delete dlg;
        return;
    }

    pathToLoad = dlg->GetPath();
    LoadFile(pathToLoad);   // current file path initializes here
    currentFileName = dlg->GetFilename();
    myLastDirectory = dlg->GetDirectory();
    RefreshMyLabel();
    delete dlg;
}

/**
File format:
    1 - identification
    2 - point counter
    3 - points (20 points)
**/
// Writes file
void GetCurveFrame::WriteFile(const wxString &path)
{
    Point *pt;
    int counter;
    counter = polynom.GetCount();
    pt = polynom.GetPointArray();

    wxFileOutputStream file(path);
    wxDataOutputStream myFile(file);

    myFile.WriteString(FILE_IDENT);
    myFile.Write32(counter);
    for (int i=0; i<counter; ++i)
    {
        myFile.WriteDouble(pt[i].x);
        myFile.WriteDouble(pt[i].y);
    }

    for (int i=counter; i<MAX_POINTS; ++i)
    {
        myFile.WriteDouble(0);
        myFile.WriteDouble(0);
    }

    file.Close();
    hasFileNotSavedChanges = false;
}

// Reads file
void GetCurveFrame::LoadFile(const wxString &path)
{
    int counter;
    double x, y;            // polynomial points
    wxString cellValue;
    wxSpinEvent myEvent;    // event to change points

    if (!wxFileExists(path))
        return;

    wxFileInputStream file(path);
    wxDataInputStream myFile(file);

    if (myFile.ReadString()!=FILE_IDENT)
    {
        wxMessageBox("The file is corrupted");
        return;
    }

    counter = myFile.Read32();
    for (int i=0; i<counter; ++i)
    {
        x = myFile.ReadDouble();
        y = myFile.ReadDouble();
        polynom.SetPoint(x, y, i);
    }

    x = y = 0;  // void points
    for (int i=counter; i<MAX_POINTS; ++i)
    {
        polynom.SetPoint(x, y, i);
    }

    // Filling forms
    SpinCtrl1->SetValue(counter);
    PointChanged(myEvent);
    currentFilePath = path;
    RefreshMyLabel();
    hasFileNotSavedChanges = false;
    PanelGraph->TrimScale();
}

void GetCurveFrame::FileNew(wxCommandEvent& event)
{
    int dlgResult;
    wxCommandEvent toSaveEvent;

    if (hasFileNotSavedChanges)
    {
        // Ask for save
        /*
        dlgResult = AskUserDialogue("Current file has been changed!\n Do you want to save changes?",
                                    "File rewrite");
        if (dlgResult)
            SaveFile(toSaveEvent);
        */

        wxMessageDialog *msg = new wxMessageDialog
                            (this,
                             "Current file has been changed!\n Do you want to save changes?",
                             "File rewrite",
                             wxYES_NO| wxCANCEL|wxCENTRE,
                             wxDefaultPosition);

        dlgResult = msg->ShowModal();
        delete msg;

        switch (dlgResult)
        {
            case wxID_YES:
            {
                SaveFile(toSaveEvent);

                if (hasFileNotSavedChanges)
                    return;

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
    }

    // Clear polynomial
    for (int i=0; i<MAX_POINTS; ++i)
    {
        polynom.SetPoint(0, 0, i);
    }

    // New data is being created:
    // Preliminary initializations
    SpinCtrl1->SetValue(INITIAL_POINT_NUMBER);
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
    coeffDlg->ShowError();
    PanelGraph->SetPoints(polynom.GetPointArray(), INITIAL_POINT_NUMBER);
    PanelGraph->Refresh();
    currentGridPosition = 0;
    isPick = NO_PICK;
    // IO options
    currentFilePath = wxEmptyString;
    currentFileName = wxEmptyString;
    hasFileNotSavedChanges = false;
    PanelGraph->RestoreNetworkDefault();
    RefreshMyLabel();
}

void GetCurveFrame::LoadUnderlayerPicture(wxCommandEvent& event)
{
    bool dlgResult;
    wxString pathToLoad;
    wxBitmapType myType;

    wxFileDialog *dlg = new wxFileDialog
                            (this, ("Load picture"),
                             myLastDirectory,
                             wxEmptyString,
                             wxT("Image files (*.png; *.bmp; .jpeg)|*.png; *.bmp; *.jpeg"),
                             wxFD_OPEN|wxFD_FILE_MUST_EXIST,
                             wxDefaultPosition,
                             wxDefaultSize,
                             wxT("Load file"));
    if (dlg->ShowModal()==wxID_CANCEL)
    {
        delete dlg;
        return;
    }
    pathToLoad = dlg->GetPath();
    delete dlg;

    wxFileName fullName(pathToLoad);
    wxString myExt = fullName.GetExt();
    if (myExt == "png")
    {
        myType = wxBITMAP_TYPE_PNG;
    }
    else if (myExt == "bmp")
    {
        myType = wxBITMAP_TYPE_BMP;
    }
    else if (myExt == "jpeg")
    {
        myType = wxBITMAP_TYPE_JPEG;
    } else {myType = wxBITMAP_TYPE_PNG;}

    // Scale picture
    PanelGraph->LoadPicture(pathToLoad, myType);
    PictureScaler *scaler = new PictureScaler(this);
    scaler->SetImageObject(PanelGraph->GetImage(),
                           PanelGraph->GetMinOrder(),
                           PanelGraph->GetMaxOrder());
    scaler->Show();
}

// Returns:
// @true - if OK has been pressed
// @false - if NO has been pressed
bool GetCurveFrame::AskUserDialogue(const wxString &question, const wxString &header)
{
    int dlgResult;

    wxMessageDialog *msg = new wxMessageDialog
                            (this,
                             question,
                             header,
                             wxYES_NO|wxCENTRE,
                             wxDefaultPosition);

    dlgResult = msg->ShowModal();
    switch(dlgResult)
    {
        case wxID_YES:
        {
            return true;
            break;
        }
        case wxID_NO:
        {
            return false;
            break;
        }
    }
    delete msg;
    return false;   // if something is wrong
}
