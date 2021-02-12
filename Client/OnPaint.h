#ifndef ONPAINT_H_INCLUDED
#define ONPAINT_H_INCLUDED

#include <wx/wx.h>
#include <wx/dragimag.h>
#include "ClientMain.h"

class Drawer:public ClientFrame
{
public : Drawer();
         ~Drawer();

         void PaintBackground(wxPaintEvent& paint);

private:DECLARE_EVENT_TABLE();
};



#endif // ONPAINT_H_INCLUDED
