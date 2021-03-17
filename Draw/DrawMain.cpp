/***************************************************************
 * Name:      DrawMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Adrian A. Muino ()
 * Created:   2021-02-20
 * Copyright: Adrian A. Muino ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "DrawMain.h"
#include <wx/msgdlg.h>
#include "json.hpp"
#include <fstream>

//(*InternalHeaders(DrawFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

using json = nlohmann::json;

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

//(*IdInit(DrawFrame)
const long DrawFrame::ID_PANEL1 = wxNewId();
const long DrawFrame::ID_BUTTON1 = wxNewId();
const long DrawFrame::ID_BUTTON2 = wxNewId();
const long DrawFrame::ID_BUTTON3 = wxNewId();
const long DrawFrame::ID_BUTTON4 = wxNewId();
const long DrawFrame::ID_SPINCTRL1 = wxNewId();
const long DrawFrame::ID_STATICTEXT1 = wxNewId();
const long DrawFrame::ID_STATICLINE1 = wxNewId();
const long DrawFrame::ID_PANEL2 = wxNewId();
const long DrawFrame::idMenuQuit = wxNewId();
const long DrawFrame::idMenuAbout = wxNewId();
//*)

BEGIN_EVENT_TABLE(DrawFrame,wxFrame)
    //(*EventTable(DrawFrame)
    //*)
END_EVENT_TABLE()

DrawFrame::DrawFrame(wxWindow* parent,wxWindowID id) : psize(100), pointCnt(0)      // p size is 100 by default to get the last 100 clicks
{
    wxString iconDir;

    if(wxFileExists(_T("icon.xpm")))
        iconDir = wxGetCwd() + _T("/icon.xpm");
    else
        iconDir = wxGetCwd() + _T("/../../icon.xpm");

    //(*Initialize(DrawFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxMessageDialog* MessageDialog1;

    Create(parent, wxID_ANY, _("Draw"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL, _T("wxID_ANY"));
    SetClientSize(wxSize(480,216));
    SetFocus();
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(iconDir, wxBITMAP_DEFAULT_TYPE));
    	SetIcon(FrameIcon);
    }
    DrawPanel = new wxPanel(this, ID_PANEL1, wxPoint(8,8), wxSize(464,120), wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    DrawPanel->SetFocus();
    DrawPanel->SetForegroundColour(wxColour(176,176,176));
    DrawPanel->SetBackgroundColour(wxColour(247,247,247));
    ControlPanel = new wxPanel(this, ID_PANEL2, wxPoint(8,136), wxSize(464,32), wxBORDER_SIMPLE|wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    ControlPanel->SetForegroundColour(wxColour(176,176,176));
    Button1 = new wxButton(ControlPanel, ID_BUTTON1, _("Exit"), wxPoint(8,8), wxSize(38,17), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button2 = new wxButton(ControlPanel, ID_BUTTON2, _("Save"), wxPoint(64,8), wxSize(38,18), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button3 = new wxButton(ControlPanel, ID_BUTTON3, _("Load"), wxPoint(120,8), wxSize(39,17), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button4 = new wxButton(ControlPanel, ID_BUTTON4, _("Pen Color"), wxPoint(192,8), wxSize(71,17), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    SpinCtrl1 = new wxSpinCtrl(ControlPanel, ID_SPINCTRL1, _T("5"), wxPoint(344,8), wxSize(113,15), 0, 1, 50, 5, _T("ID_SPINCTRL1"));
    SpinCtrl1->SetValue(_T("5"));
    StaticText1 = new wxStaticText(ControlPanel, ID_STATICTEXT1, _("Pen Width"), wxPoint(272,8), wxSize(80,14), 0, _T("ID_STATICTEXT1"));
    StaticText1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
    StaticLine1 = new wxStaticLine(ControlPanel, ID_STATICLINE1, wxPoint(177,0), wxSize(286,31), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, wxID_ANY, wxST_SIZEGRIP|wxNO_FULL_REPAINT_ON_RESIZE|wxALWAYS_SHOW_SB, _T("wxID_ANY"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ColourDialog1 = new wxColourDialog(this);
    MessageDialog1 = new wxMessageDialog(this, wxEmptyString, _("Message"), wxOK|wxCANCEL, wxDefaultPosition);

    DrawPanel->Connect(wxEVT_ERASE_BACKGROUND,(wxObjectEventFunction)&DrawFrame::OnDrawPanelEraseBackground,0,this);
    DrawPanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&DrawFrame::OnDrawPanelLeftDown,0,this);
    DrawPanel->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&DrawFrame::OnDrawPanelLeftDClick,0,this);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DrawFrame::OnQuit);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DrawFrame::OnSave);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DrawFrame::OnLoad);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DrawFrame::OnPenColor);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&DrawFrame::OnPenWidth);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DrawFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DrawFrame::OnAbout);
    //*)

    points = new wxPoint[psize];
    mode = Click;
    color = *wxBLACK;
    width = 5;
    StatusBar1->SetStatusText(wxT("Click Mode"), 0);
}

DrawFrame::~DrawFrame()
{
    delete []points;
    //(*Destroy(DrawFrame)
    //*)
}

void DrawFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DrawFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(_("Welcome to the Draw program.\nThere are two main modes:\n 1. Click Mode\n 2. Draw Mode"));
}

void DrawFrame::OnDrawPanelEraseBackground(wxEraseEvent& event)
{
    // do nothing
    // this is done to disable the default wxEVT_ERASE_BACKGROUND event handler and reduce flickering
}

void DrawFrame::OnDrawPanelLeftDown(wxMouseEvent& event)
{
    if((mode == Click) && (pointCnt < psize)){
        wxClientDC dc(DrawPanel);
        wxPen pen(*color, width, wxSOLID); // black pen of width 1
        dc.SetPen(pen);
        dc.DrawPoint(event.GetPosition());
        dc.SetPen(wxNullPen);

        points[pointCnt++] = event.GetPosition();
    }
}

void DrawFrame::OnDrawPanelLeftDClick(wxMouseEvent& event)
{
    wxClientDC dc(DrawPanel);

    if(mode == Click && pointCnt > 1){
        mode = Draw;
        StatusBar1->SetStatusText(wxT("Draw Mode"), 0);
        dc.Clear();
        wxPen pen(*color, width, wxSOLID); // black pen of width 1
        dc.SetPen(pen);
        dc.DrawLines(pointCnt, points);
        dc.SetPen(wxNullPen);
    }else{
        mode = Click;
        StatusBar1->SetStatusText(wxT("Click Mode"), 0);
        dc.Clear();
        pointCnt = 0;
        memset(points, 0, pointCnt);   // reset the array of points
    }
}

void DrawFrame::OnSave(wxCommandEvent& event)
{
    wxString wildcard = wxT("JSON files (*.json)|*.json");
    wxString defaultDir = wxT("~/Documents");
    wxString defaultFilename = wxT("drawing.json");
    wxString path;

    wxFileDialog dialog(this, wxEmptyString, defaultDir, defaultFilename, wildcard, wxFD_SAVE);
    if(dialog.ShowModal() == wxID_OK){
         path = dialog.GetPath();          // path is a wxString. Need to convert it to str
    }

    std::ofstream ofs(path.mb_str(), std::ofstream::out);
    if(ofs.is_open()){
        // create an empty structure (null)
        json j;

        j["width"] = width;
        j["color"] = {color.Red(), color.Green(), color.Blue(), color.Alpha()};
        j["count"] = pointCnt;
        for(int i = 0; i < pointCnt; i++)
            j["points"].push_back({points[i].x,points[i].y});

        ofs << j.dump(1);   // serialize json object with indent of 1

        ofs.close();
    }else{
        std::cout << "Error opening file";
    }
}

void DrawFrame::OnLoad(wxCommandEvent& event)
{
    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("JSON files (*.json)|*.json");
    wxString defaultDir = wxT("~/Documents");
    wxString defaultFilename = wxEmptyString;
    wxString path;

    wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard, wxFD_OPEN);
    if(dialog.ShowModal() == wxID_OK){
         path = dialog.GetPath();          // path is a wxString. Need to convert it to str
    }
    std::ifstream ifs(path.mb_str(), std::ofstream::in);
    if(ifs.is_open()){

        mode = Draw;
        StatusBar1->SetStatusText(wxT("Draw Mode"), 0);
        memset(points, 0, pointCnt);   // reset the array of points

        // create an empty structure (null)
        json j;

        ifs >> j;   // deserialize json object from file

        width = j["width"];
        color = wxColor(j["color"][0], j["color"][1], j["color"][2], j["color"][3]);    // r,g,b,a
        pointCnt = j["count"];

        for(int i = 0; i < pointCnt; i++)
            points[i] = wxPoint(j["points"][i][0], j["points"][i][1]);    // x,y

        wxClientDC dc(DrawPanel);
        dc.Clear();
        wxPen pen(*color, width, wxSOLID); // black pen of width 1
        dc.SetPen(pen);
        if(pointCnt == 1)
            dc.DrawPoint(points[0]);
        else if(pointCnt > 1)
            dc.DrawLines(pointCnt, points);
        dc.SetPen(wxNullPen);

        ifs.close();
    }else{
        //std::cout << "Error opening file";
    }
}

void DrawFrame::OnPenColor(wxCommandEvent& event)
{
    if(ColourDialog1->ShowModal() == wxID_OK){
        wxColourData data = ColourDialog1->GetColourData();
        color = data.GetColour();
    }
}

void DrawFrame::OnPenWidth(wxSpinEvent& event)
{
    width = event.GetValue();
}
