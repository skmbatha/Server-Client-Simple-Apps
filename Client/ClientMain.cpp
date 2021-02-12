/***************************************************************
 * Name:      ClientMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Success Katlego Mbatha (skatlego.mbatha@gmail.com)
 * Created:   2019-01-09
 * Copyright: Success Katlego Mbatha (www.katlego98523.waplux.com)
 * License:
 **************************************************************/

#include "ClientMain.h"
#include <string>
#include <string.h>


BEGIN_EVENT_TABLE(ClientFrame, wxFrame)

EVT_BUTTON(OnConnect,ClientFrame::OnInilialize)
EVT_SOCKET(OnConnection,ClientFrame::OnCommunicate)
EVT_BUTTON(OnCommand,ClientFrame::OnCommando)
EVT_PAINT(ClientFrame::Paint)

END_EVENT_TABLE()

ClientFrame::ClientFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{

    wxPanel *Main=new wxPanel(this,wxID_ANY);
    GlobalFramePtr=Main;
    wxButton *StartSesssion=new wxButton(Main,OnConnect,_("Connect to Server"),wxPoint(240,250));
    wxButton *SendCommand=new wxButton(Main,OnCommand,_("Enter Command"),wxPoint(370,250));

        ///set frame size

        this->SetSize(wxSize(700,550));

        ///setup status bar
        wxStatusBar *statusB=new wxStatusBar(this,wxID_ANY);
        Status=statusB;
        this->SetStatusBar(statusB);
        statusB->SetStatusText(wxT("Welcome to Client App!"));
}

ClientFrame::ClientFrame()///Doesn't have arguements
{
}

ClientFrame::~ClientFrame()///Destructor
{
}


void ClientFrame::OnCommando(wxCommandEvent& event)
{

    if(SocketBuf!=NULL)
    {
        wxTextEntryDialog *TextE=new wxTextEntryDialog(this,_("Commands"),_("Type the command prompt:"));
        if(TextE->ShowModal()==wxID_OK)
        {
           wxString data=TextE->GetValue();
           SocketBuf->Write(data,10);

        }
    }
    else
    {
            wxMessageBox(_("Not connected!"));
    }
}

void ClientFrame::OnInilialize(wxCommandEvent & WXUNUSED(event))
{
    wxIPV4address Ipv4addr;///Never make this a pointer
    Ipv4addr.Hostname(wxT("127.0.0.5"));///local
    Ipv4addr.Service(6575);///service or por number*/

    wxSocketClient *Socket=new wxSocketClient();///create the socket
    SocketBuf=Socket;

    ///configure events that should raise flags

    Socket->SetEventHandler(*this,OnConnection);///Coonect this socket settings to the event handler
    Socket->SetNotify(wxSOCKET_CONNECTION_FLAG |///set the flags that I want to receive eveents for
                      wxSOCKET_INPUT_FLAG |
                      wxSOCKET_LOST_FLAG);

    Socket->Notify(true);///activate the flags
    Socket->Connect(Ipv4addr,true);///initliaze the connection and don't wait for response


}

void ClientFrame::OnCommunicate(wxSocketEvent &event)
{
    wxSocketBase *socket=event.GetSocket();///Return the socket that the event is working on

    switch(event.GetSocketEvent())
    {
    case wxSOCKET_CONNECTION: {

                                 Status->SetStatusText(_("Connected!"));///DIplay connectced text on the status bar
                                 socket->SetFlags(wxSOCKET_WAITALL | wxSOCKET_BLOCK);///Block GUI while sending and wait until done

                                 wxFileInputStream file_import(wxT("hlogz.jpg"));///Import file into program

                                 wxSocketOutputStream Sock_file(*socket);///Validate the socket as obj
                                 wxZlibOutputStream *comp_file=new wxZlibOutputStream(Sock_file);///Transfer socket stream to zip

                                 comp_file->Write(file_import);///Write the file to the socket
                                 comp_file->Sync();///Send all the data

                                 delete comp_file;///This does EOF...Please include from
                                 socket->Destroy();///Terminate socket connectivity
                                 Status->SetStatusText(_("Data successfully sent."));
                                 break;
                              }

    case  wxSOCKET_INPUT:     {

                                char data2[11];

                                socket->Read(data2,sizeof(data2));
                                Status->SetStatusText(_("String received is:")+data2);
                               //socket->Close();//This disconnects
/*
//socket->SetTimeout(5);
// Wait for some data to come in, or for an error
// and block on the socket calls
socket->SetFlags(wxSOCKET_WAITALL | wxSOCKET_BLOCK);

                                char data[10];///for storing data
                                int cntr=0;

                                for(int u=0;u<10;u++)
                                {
                                    data[u]=0;///Clear trhe array
                                }

                                wxString Response;
                                wxSocketInputStream file(*socket);
                                wxTextInputStream input_buffer(file);

                              //  while(cntr<10)
                              //  {
                              //      input_buffer >> data[cntr];
                              //      cntr++;
                              //  }
                                input_buffer >> Response;
                                //wxMessageBox(Response);
                                Status->SetStatusText(Response);

                                ///clean up
                                //socket->Destroy();

                                socket->Destroy();
*/
                                break;
                              }

    case  wxSOCKET_LOST:      {
                                wxMessageBox(_("Connection lost"));
                                SocketBuf=NULL;
                                socket->Close();///Destroy the communication
                                break;
                              }
}
}

void ClientFrame::Paint(wxPaintEvent& paint)///PAINT EVENTS
{
    wxClientDC MainWindow(GlobalFramePtr);///Link the DC to the
    wxImage Image(_("bitmaps/BackgroundPicture.jpg"),wxBITMAP_TYPE_JPEG);

    Image.Scale(700,500);///Set window scale
    wxBitmap bitmap(Image);///Convert jpg to bitmap
    MainWindow.DrawBitmap(bitmap,wxPoint(0,0),false);
}
