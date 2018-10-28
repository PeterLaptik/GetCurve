#include "GetCurveMain.h"
#include "../dialogues/CFunctionName.h"
#include <wx/textfile.h>


const char* const CSV_del = "\t";               // CSV delimiter
const char* const NUMBER_PRECISION = "%.16e";   // precision for coefficients output
//const char* const PATH_SEPARATOR = "/";       @excluded
const char* const TMP_PIC_NAME = "tmp.png";

// Makes snapshot of the screen and saves a bitmap on disk
void GetCurveFrame::MakeScreenSnapshot(wxCommandEvent& event)
{
    bool isFileChosen;
    wxString filePath;
    wxMemoryDC memDC;
    wxBitmap bitmapToSave(PanelGraph->GetSize().x, PanelGraph->GetSize().y);
    memDC.SelectObject(bitmapToSave);

    isFileChosen = false;
    while(!isFileChosen)
    {
        wxFileDialog *dlg = new wxFileDialog
                            (this, ("Save snapshot"),
                             myLastDirectory,
                             wxEmptyString,
                             wxT("Image files (*.png)|*.png"),
                             wxFD_SAVE,
                             wxDefaultPosition,
                             wxDefaultSize,
                             wxT("Save snapshot"));

        if (dlg->ShowModal()==wxID_CANCEL)
        {
            delete dlg;
            return;
        }

        isFileChosen = true;
        filePath = dlg->GetPath();
        if (wxFileExists(filePath))
        {
            isFileChosen = false;
            bool dlgResult = AskUserDialogue("File exists! \nDo you want to overwrite current file?",
                                             "File rewrite");
            if (dlgResult)
                isFileChosen = true;
        }
        delete dlg;
    }

    PanelGraph->OnPaintMemoryDC(memDC);
    bitmapToSave.SaveFile(filePath, wxBITMAP_TYPE_PNG);
}

// Exports a function for polynomial calculation
void GetCurveFrame::ExportCFunction(wxCommandEvent& event)
{
    wxString functionName;
    wxString textOut;
    wxTextFile myFile;
    wxString filePath;
    bool isFileChosen;
    double *coefficients;

    CFunctionName *dlg = new CFunctionName(this);
    dlg->ShowModal();
    functionName = dlg->GetResult();
    delete dlg;

    if (functionName==wxEmptyString)
        return;

    while(!isFileChosen)
    {
        wxFileDialog *dlg = new wxFileDialog
                            (this, ("Save C function"),
                             myLastDirectory,
                             wxEmptyString,
                             wxT("C files (*.c)|*.c"),
                             wxFD_SAVE,
                             wxDefaultPosition,
                             wxDefaultSize,
                             wxT("Save function"));

        if (dlg->ShowModal()==wxID_CANCEL)
        {
            delete dlg;
            return;
        }

        isFileChosen = true;
        filePath = dlg->GetPath();
        if (wxFileExists(filePath))
        {
            isFileChosen = false;
            bool dlgResult = AskUserDialogue("File exists! \nDo you want to overwrite current file?",
                                             "File rewrite");
            if (dlgResult)
                isFileChosen = true;
        }
        delete dlg;
    }

    if (!wxFileExists(filePath))
        isFileChosen = myFile.Create(filePath);

    if (!isFileChosen)
    {
        wxMessageBox("An error occurred on file creating!");
        return;
    }

    // Write function
    myFile.Open(filePath);
    myFile.Clear();

    textOut.Clear();
    textOut<<"#include <math.h>";
    myFile.AddLine(textOut);
    textOut.Clear();

    textOut.Clear();
    textOut<<"\ndouble "<<functionName<<"(double x);\n\n";
    myFile.AddLine(textOut);
    textOut.Clear();

    textOut<<"double "<<functionName<<"(double x)\n{\t";
    myFile.AddLine(textOut);
    textOut.Clear();
    textOut<<"\t// Border point values for the calculated polynomial:";
    myFile.AddLine(textOut);
    textOut.Clear();
    textOut<<"\t// left border: x = "<<polynom.GetMinX();
    myFile.AddLine(textOut);
    textOut.Clear();
    textOut<<"\t// right border: x = "<<polynom.GetMaxX();
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\tint counter;\t// number of elements";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\tint i;\t\t\t// current element";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\tdouble result;\t// result of the calculation";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\tdouble a["<<polynom.GetCount()<<"] = {";
    myFile.AddLine(textOut);
    coefficients = polynom.GetPolynomialArray();
    for (int i=0; i<polynom.GetCount(); ++i)
    {
        textOut.Clear();
        textOut<<"\t\t\t\t"<<wxString::Format(NUMBER_PRECISION, coefficients[i]);
        if (i<polynom.GetCount()-1)
            textOut<<",";
        myFile.AddLine(textOut);
    }
    textOut.Clear();
    textOut<<"\t\t\t\t};";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\n\tcounter = "<<polynom.GetCount()<<";";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\tresult = 0;";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\tfor (i=0; i<counter; i++)\n{";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\t\tresult += a[i]*pow(x,i);";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\t}";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"\treturn result;";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"}";
    myFile.AddLine(textOut);

    myFile.Write();
    myFile.Close();
}

void GetCurveFrame::ExportCSVTable(wxCommandEvent& event)
{
    wxString textOut;
    wxTextFile myFile;
    wxString filePath;
    bool isFileChosen;
    double *coefficients;

    while(!isFileChosen)
    {
        wxFileDialog *dlg = new wxFileDialog
                            (this, ("Save CSV table"),
                             myLastDirectory,
                             wxEmptyString,
                             wxT("CSV files (*.csv)|*.csv"),
                             wxFD_SAVE,
                             wxDefaultPosition,
                             wxDefaultSize,
                             wxT("Save table"));

        if (dlg->ShowModal()==wxID_CANCEL)
        {
            delete dlg;
            return;
        }

        isFileChosen = true;
        filePath = dlg->GetPath();
        if (wxFileExists(filePath))
        {
            isFileChosen = false;
            bool dlgResult = AskUserDialogue("File exists! \nDo you want to overwrite current file?",
                                             "File rewrite");
            if (dlgResult)
                isFileChosen = true;
        }
        delete dlg;
    }

    if (!wxFileExists(filePath))
        isFileChosen = myFile.Create(filePath);

    if (!isFileChosen)
    {
        wxMessageBox("An error occurred on file creating!");
        return;
    }

    myFile.Open(filePath);
    myFile.Clear();

    textOut.Clear();
    textOut<<" "<<CSV_del<<"coefficient";
    myFile.AddLine(textOut);

    textOut.Clear();
    textOut<<"index"<<CSV_del<<"value";
    myFile.AddLine(textOut);

    coefficients = polynom.GetPolynomialArray();
    for (int i=0; i<polynom.GetCount(); ++i)
    {
        textOut.Clear();
        textOut<<i<<CSV_del<<wxString::Format(NUMBER_PRECISION, coefficients[i]);
        myFile.AddLine(textOut);
    }

    myFile.Write();
    myFile.Close();
}

void GetCurveFrame::SaveOdtReport(wxCommandEvent& event)
{
    OdtCreator myDoc;
    wxString textOut;
    wxTextFile myFile;
    wxString filePath;
    wxString fileName;
    bool isFileChosen;
    double *coefficients;

    while(!isFileChosen)
    {
        wxFileDialog *dlg = new wxFileDialog
                            (this, ("Save ODT text"),
                             myLastDirectory,
                             wxEmptyString,
                             wxT("CSV files (*.odt)|*.odt"),
                             wxFD_SAVE,
                             wxDefaultPosition,
                             wxDefaultSize,
                             wxT("Save text"));

        if (dlg->ShowModal()==wxID_CANCEL)
        {
            delete dlg;
            return;
        }

        isFileChosen = true;
        filePath = dlg->GetPath();
        fileName = dlg->GetFilename();

        if (wxFileExists(filePath))
        {
            isFileChosen = false;
            bool dlgResult = AskUserDialogue("File exists! \nDo you want to overwrite current file?",
                                             "File rewrite");
            if (dlgResult)
            {
                isFileChosen = true;
                wxRemoveFile(filePath);
            }

        }
        delete dlg;
    }

    if ((!isFileChosen) || (fileName.length()<=4))
    {
        wxMessageBox("There is no file to create!");
        return;
    }

    // Creating report
    myDoc.SetPath(filePath);
    myDoc.SetName(fileName.Mid(0, fileName.length()-4));
    if (!myDoc.Init())
    {
        wxMessageBox("An error occurred on file creating!");
        return;
    }

    myDoc.SetParagraphStyle(odtParaStandard);
    myDoc.Indent();
    myDoc.SetParagraphStyle(odtParaStandardRight);
    myDoc.AppendText(wxT("Point values. Table 1"));
    myDoc.SetParagraphStyle(odtParaStandard);

    // Points table
    myDoc.TableCreate(3, polynom.GetCount() + 1);
    myDoc.TableSetColumnWidth(0,3);
    myDoc.TableSetColumnWidth(1,5);
    myDoc.TableSetColumnWidth(2,5);
    textOut = "Point number";
    myDoc.TableAddCellValue(0,0, textOut, odtCellAlignCenter);
    textOut = "Value X";
    myDoc.TableAddCellValue(0,1, textOut, odtCellAlignCenter);
    textOut = "Value Y";
    myDoc.TableAddCellValue(0,2, textOut, odtCellAlignCenter);

    for (int i=0; i<polynom.GetCount(); ++i)
    {
        textOut.Clear();
        textOut<<i+1;
        myDoc.TableAddCellValue(i+1,0, textOut, odtCellAlignCenter);
        textOut.Clear();
        textOut<<polynom.GetPoint(i).x;
        myDoc.TableAddCellValue(i+1,1, textOut);
        textOut.Clear();
        textOut<<polynom.GetPoint(i).y;
        myDoc.TableAddCellValue(i+1,2, textOut);
    }
    myDoc.InsertTable();

    // Points picture
    myDoc.Indent();
    MakeSnapshotForOdt(myDoc, true);
    myDoc.SetParagraphStyle(odtParaStandardCenter);
    myDoc.AppendText("Fig.1 Set of points");
    myDoc.Indent();
    myDoc.Indent();

    // Table of coefficients
    myDoc.SetParagraphStyle(odtParaStandardRight);
    myDoc.AppendText(wxT("Coefficients for the polynomial expression "));
    textOut = "y( x ) =  sum from{i=0} to{";
    textOut<<polynom.GetCount() - 1<<"} a_i cdot x^i";
    myDoc.InsertFormula(textOut);
    myDoc.AppendText(wxT(". Table 2"));
    myDoc.TableCreate(2, polynom.GetCount() + 1);
    myDoc.TableSetColumnWidth(0,2);
    myDoc.TableSetColumnWidth(1,3);
    textOut = "Coefficient";
    myDoc.TableAddCellValue(0,0, textOut, odtCellAlignCenter);
    textOut = "Value";
    myDoc.TableAddCellValue(0,1, textOut, odtCellAlignCenter);
    coefficients = polynom.GetPolynomialArray();
    for (int i=0; i<polynom.GetCount(); ++i)
    {
        textOut.Clear();
        textOut<<"a_"<<i;
        myDoc.TableCellInsertFormula(i+1, 0, textOut, odtCellAlignCenter);
        textOut = wxString::Format(NUMBER_PRECISION, coefficients[i]);
        myDoc.TableAddCellValue(i+1,1, textOut);
    }
    myDoc.InsertTable();

    // Curve drawing
    myDoc.Indent();
    MakeSnapshotForOdt(myDoc, false);
    myDoc.SetParagraphStyle(odtParaStandardCenter);
    myDoc.AppendText("Fig.1 Set of points");
    myDoc.Indent();
    myDoc.SetParagraphStyle(odtParaStandard);
    myDoc.Write();
}

void GetCurveFrame::MakeSnapshotForOdt(OdtCreator &myDoc, bool onlyPoints)
{
    wxString filePath;
    wxMemoryDC memDC;
    wxBitmap bitmapToSave(PanelGraph->GetSize().x, PanelGraph->GetSize().y);
    memDC.SelectObject(bitmapToSave);
    wxDir *dir = new wxDir(wxGetCwd());
    filePath.Clear();
    filePath<<dir->GetName()<<wxFileName::GetPathSeparator()<<TMP_PIC_NAME;
    delete dir;
    PanelGraph->DrawPointsOnly(onlyPoints);
    PanelGraph->OnPaintMemoryDC(memDC);
    bitmapToSave.SaveFile(filePath, wxBITMAP_TYPE_PNG);
    myDoc.InsertPicture(filePath);
    wxRemoveFile(filePath);
    PanelGraph->DrawPointsOnly(false);
}
