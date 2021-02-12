/***************************************************************
 * Name:      ClientMain.h
 * Purpose:   Defines Application Frame
 * Author:    Success Katlego Mbatha (skatlego.mbatha@gmail.com)
 * Created:   2019-01-09
 * Copyright: Success Katlego Mbatha (www.katlego98523.waplux.com)
 * License:
 **************************************************************/

#ifndef CLIENTMAIN_H
#define CLIENTMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/socket.h>
    #include <iostream>
#endif

#include "ClientApp.h"
#include <wx/sckstrm.h>
#include <wx/textdlg.h>

#include <wx/wfstream.h>
#include <wx/datstrm.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>
#include <wx/zstream.h>
#include <wx/file.h>


class ClientFrame: public wxFrame
{
    public:
        ClientFrame(wxFrame *frame, const wxString& title);
        ClientFrame();///1st overload of constructor
        ~ClientFrame();

        void OnInilialize(wxCommandEvent & WXUNUSED(event));
        void OnCommunicate(wxSocketEvent &event);
        void OnCommando(wxCommandEvent& event);
        void Paint(wxPaintEvent& paint);

        wxStatusBar *Status=NULL;
        wxTextEntryDialog *Text=NULL;
        wxSocketClient *SocketBuf=NULL;
        wxSocketBase *EventBuf=NULL;
        wxPanel *GlobalFramePtr=NULL;

    private:
        enum IDs{OnConnect=1000,OnConnection,OnCommand};
        DECLARE_EVENT_TABLE()
};


#endif // CLIENTMAIN_H
