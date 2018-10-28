/***************************************************************
 * Name:      GetCurveApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Peter Laptik (Peter.Laptik@gmail.com)
 * Created:   2018-07-08
 * Copyright: Peter Laptik ()
 * License:
 **************************************************************/

#include "GetCurveApp.h"

//(*AppHeaders
#include "GetCurveMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(GetCurveApp);

bool GetCurveApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	GetCurveFrame* Frame = new GetCurveFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
