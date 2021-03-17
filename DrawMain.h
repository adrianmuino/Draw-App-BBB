/***************************************************************
 * Name:      DrawMain.h
 * Purpose:   Defines Application Frame
 * Author:    Adrian A. Muino ()
 * Created:   2021-02-20
 * Copyright: Adrian A. Muino ()
 * License:
 **************************************************************/

#ifndef DRAWMAIN_H
#define DRAWMAIN_H

//(*Headers(DrawFrame)
#include <wx/button.h>
#include <wx/colordlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
//*)

class DrawFrame: public wxFrame
{
    public:

        DrawFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DrawFrame();

    private:

        // Array of SIZE number of points
        wxPoint* points;
        unsigned int pointCnt;
        unsigned int psize;
        enum ModeType { Click, Draw };      // declaring Click mode and Draw mode
        ModeType mode;
        wxColour color;
        int width;

        //(*Handlers(DrawFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnDrawPanelEraseBackground(wxEraseEvent& event);
        void OnDrawPanelLeftDown(wxMouseEvent& event);
        void OnDrawPanelLeftDClick(wxMouseEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnLoad(wxCommandEvent& event);
        void OnPenColor(wxCommandEvent& event);
        void OnPenWidth(wxSpinEvent& event);
        void OnEraseBackground(wxEraseEvent& event);
        //*)

        //(*Identifiers(DrawFrame)
        static const long ID_PANEL1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_SPINCTRL1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICLINE1;
        static const long ID_PANEL2;
        static const long idMenuQuit;
        static const long idMenuAbout;
        //*)

        //(*Declarations(DrawFrame)
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxButton* Button4;
        wxColourDialog* ColourDialog1;
        wxPanel* ControlPanel;
        wxPanel* DrawPanel;
        wxSpinCtrl* SpinCtrl1;
        wxStaticLine* StaticLine1;
        wxStaticText* StaticText1;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DRAWMAIN_H
