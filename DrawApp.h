/***************************************************************
 * Name:      DrawApp.h
 * Purpose:   Defines Application Class
 * Author:    Adrian A. Muino ()
 * Created:   2021-02-20
 * Copyright: Adrian A. Muino ()
 * License:
 **************************************************************/

#ifndef DRAWAPP_H
#define DRAWAPP_H

#include <wx/app.h>

class DrawApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // DRAWAPP_H
