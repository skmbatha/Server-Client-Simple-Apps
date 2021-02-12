/***************************************************************
 * Name:      ServerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Success Katlego Mbatha (skatlego.mbatha@gmail.com)
 * Created:   2019-01-09
 * Copyright: Success Katlego Mbatha (www.katlego98523.waplux.com)
 * License:
 **************************************************************/

#include "ServerMain.h"


BEGIN_EVENT_TABLE(ServerFrame, wxFrame)

EVT_BUTTON(OnServerStart,ServerFrame::OnInitialize)
EVT_SOCKET(OnServer,ServerFrame::OnConnecting)
EVT_SOCKET(OnSocket,ServerFrame::Connected)

END_EVENT_TABLE()

ServerFrame::ServerFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    wxPanel *main= new wxPanel(this,wxID_ANY);
    wxButton *StartServer=new wxButton(main,OnServerStart,wxT("Start Server"),wxPoint(100,150));

        ///setup status bar
        wxStatusBar *statusB=new wxStatusBar(this,wxID_ANY);
        Status=statusB;
        this->SetStatusBar(statusB);
        statusB->SetStatusText(wxT("Welcome to server!"));
}


ServerFrame::~ServerFrame()
{
}

void ServerFrame::OnInitialize(wxCommandEvent &event)
{
    wxIPV4address addr;///create an IPV4 object
    addr.Hostname(_("127.0.0.5"));
    addr.Service(6575);///Service port

    wxSocketServer *Server=new wxSocketServer(addr);
    if(Server->Ok())
    Status->SetStatusText(_("Socket and address port linked\nServer is listening."));
    else
    Status->SetStatusText(_("Not linked"));

    Server->SetEventHandler(*this,OnServer);///Link this to connecting and the accepting function
    Server->SetNotify(wxSOCKET_CONNECTION_FLAG);///When connected call this and accept
    Server->Notify(true);///Acticate the flag

    Temp=Server;//save this to route the pointer to the OnConnecting functions
}

void ServerFrame::OnConnecting(wxSocketEvent & event)
{
    wxSocketBase *Serv=Temp->Accept(false);///Accept and dont await
    Serv->SetEventHandler(*this,OnSocket);///Set event flagson connection
    Serv->SetNotify(wxSOCKET_LOST_FLAG|wxSOCKET_INPUT_FLAG);///Specify flags
    Serv->Notify(true);///Activete flags
}

void ServerFrame::Connected(wxSocketEvent & event)
{
  wxSocketBase *Server=event.GetSocket();///Get the ptr addre of the evoking object

  switch(event.GetSocketEvent())
  {
  case wxSOCKET_INPUT:{
                        Server->SetFlags(wxSOCKET_WAITALL | wxSOCKET_BLOCK);///WAIT TILL data is finished but will cann wxYield

                        wxString name="Out.jpg";
                        wxFileOutputStream file(name);

                        wxSocketInputStream sock_read(*Server);
                        wxZlibInputStream *comp_read=new wxZlibInputStream(sock_read);

                        file.Write(*comp_read);///copy the file in the compressed file to the file
                        delete comp_read;

                        ///TRYING TO DO ZIP OPERATIONS

                        //wxFileOutputStream *FileSave=new wxFileOutputStream(_("ZipFile.zip"));
                        //wxZipOutputStream zipsave(FileSave);
                        //zipsave.PutNextEntry(wxT("James.txt"));
                        //zipsave.Close();
                        //wxZlibOutputStream *Save=new wxZlibOutputStream(zipsave);
                        //Save->Write(*comp_read);

                        //delete FileSave;
                       // delete Save;

                        /*wxMemoryOutputStream memOut;///Create memory saving object
                        wxZlibOutputStream comp_write(memOut);///Create zip saving object

                        comp_write.Write(comp_read);///Saved in memory

                        char data[100];
                        memOut.CopyTo(data,strlen(data));
                        wxMessageBox(data);*/
        break;}
  case wxSOCKET_LOST:{
                        wxMessageBox(_("Connection lost!!"));
                        Server->Destroy();
        break;}
  }
}




