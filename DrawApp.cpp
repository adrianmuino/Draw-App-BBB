/***************************************************************
 * Name:      DrawApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Adrian A. Muino ()
 * Created:   2021-02-20
 * Copyright: Adrian A. Muino ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "DrawApp.h"

//(*AppHeaders
#include "DrawMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DrawApp);

bool DrawApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	DrawFrame* Frame = new DrawFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
