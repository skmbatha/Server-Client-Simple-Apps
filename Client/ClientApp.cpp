/***************************************************************
 * Name:      ClientApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Success Katlego Mbatha (skatlego.mbatha@gmail.com)
 * Created:   2019-01-09
 * Copyright: Success Katlego Mbatha (www.katlego98523.waplux.com)
 * License:
 **************************************************************/


#include "ClientApp.h"
#include "ClientMain.h"

IMPLEMENT_APP(ClientApp);

bool ClientApp::OnInit()
{
    wxInitAllImageHandlers();///Initialise all image handlers

    ClientFrame* frame = new ClientFrame(0L, _("Client app (Katlego Mbatha)"));

    frame->SetPosition(wxPoint(600,130));

    wxImage Import(wxT("bitmaps/Client.jpg"),wxBITMAP_TYPE_JPEG);
    Import.Scale(48,48);
    wxBitmap bitm(Import);
    wxIcon ClientIcon;
    ClientIcon.CopyFromBitmap(bitm);

    frame->SetIcon(ClientIcon); // To Set App Icon
    frame->Show();

    return true;
}
