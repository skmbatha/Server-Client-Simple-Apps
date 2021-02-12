/***************************************************************
 * Name:      ServerApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Success Katlego Mbatha (skatlego.mbatha@gmail.com)
 * Created:   2019-01-09
 * Copyright: Success Katlego Mbatha (www.katlego98523.waplux.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ServerApp.h"
#include "ServerMain.h"

IMPLEMENT_APP(ServerApp);

bool ServerApp::OnInit()
{
    wxInitAllImageHandlers();

    ServerFrame* frame = new ServerFrame(0L, _("Server app(by Katlego)"));

    wxImage Import(wxT("bitmaps/Server.jpg"),wxBITMAP_TYPE_JPEG);
    Import.Scale(48,48);
    wxBitmap bitm(Import);
    wxIcon ClientIcon;
    ClientIcon.CopyFromBitmap(bitm);

    frame->SetIcon(ClientIcon); // To Set App Icon
    frame->Show();

    frame->SetPosition(wxPoint(200,160));

    return true;
}
