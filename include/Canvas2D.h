#ifndef CANVAS2D_H
#define CANVAS2D_H

#include <vector>
#include <string>
#include "wx/dc.h"
#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/panel.h"
#include "wx/frame.h"
#include "structures.h"




class Canvas2D : public wxPanel
{
public:
    Canvas2D(wxFrame* parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition,
             const wxSize &size = wxSize(625,648), long style=wxTAB_TRAVERSAL, const wxString &name=wxPanelNameStr);
    virtual ~Canvas2D();
    void paint(wxPaintEvent &event);
    void leftClick(wxMouseEvent& event);
    void clearVertex();
    void setBond(int bondNumber);
    void setActiveElement(elem activeElement);
    wxBitmap getBitmap();
    std::vector<vertex2D> vertices;
private:
    void render(wxDC& dc);
    void getVertexLocation(int x0, int y0, int x, int y, int value, int &x1, int &y1);
    std::string getStringForVertex(atom active);
    bool isWithinSafeZone(int x0, int y0);
    char getPossibleBonds(elem activeElement);
    int counter;
    const int length = 30;
    int bond;
    elem active;

};

#endif // CANVAS2D_H
