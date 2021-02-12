#include "OnPaint.h"

BEGIN_EVENT_TABLE(Drawer,ClientFrame)///inherits from frame

EVT_PAINT(Drawer::PaintBackground)///paint the background on startup

END_EVENT_TABLE()


Drawer::Drawer():ClientFrame()
{
///do nothing
}

Drawer::~Drawer()
{
    this->Destroy();
}

void Drawer::PaintBackground(wxPaintEvent& paint)
{
   ClientFrame *temp=new ClientFrame();
   wxClientDC drawer(temp->GlobalFramePtr);

   wxMessageBox(_("Entered Paint event"));
}


