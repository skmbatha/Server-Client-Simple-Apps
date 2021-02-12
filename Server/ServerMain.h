/***************************************************************
 * Name:      ServerMain.h
 * Purpose:   Defines Application Frame
 * Author:    Success Katlego Mbatha (skatlego.mbatha@gmail.com)
 * Created:   2019-01-09
 * Copyright: Success Katlego Mbatha (www.katlego98523.waplux.com)
 * License:
 **************************************************************/

#ifndef SERVERMAIN_H
#define SERVERMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
    #include <wx/socket.h>
#endif

#include "ServerApp.h"

#include <wx/wfstream.h>
#include <wx/datstrm.h>
#include <wx/txtstrm.h>
#include <wx/sstream.h>
#include <wx/zstream.h>
#include <wx/mstream.h>
#include <wx/sckstrm.h>
#include <wx/textdlg.h>
#include <wx/zipstrm.h>
#include <wx/file.h>

class ServerFrame: public wxFrame
{
    public:
        ServerFrame(wxFrame *frame, const wxString& title);
        ~ServerFrame();

        void OnInitialize(wxCommandEvent &event);///Inilialise the server
        void Connected(wxSocketEvent & event);///Communicate with client
        void OnConnecting(wxSocketEvent & event);///Initialise socket with flags

        wxSocketServer *Temp=NULL;
        wxStatusBar *Status=NULL;

    private:
        enum IDs{OnServerStart,OnServer,OnSocket};

        DECLARE_EVENT_TABLE()///Declare wvwnt table
};


#endif // SERVERMAIN_H
