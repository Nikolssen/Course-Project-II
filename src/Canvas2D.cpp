#include "Canvas2D.h"



Canvas2D::Canvas2D(wxFrame* parent, wxWindowID id, const wxPoint &pos,
                   const wxSize &size, long style, const wxString &name):
    wxPanel(parent, id, pos, size, style, name)
{
    counter = -1;
    bond = 1;
    active = carbon;

}

Canvas2D::~Canvas2D()
{
}

bool Canvas2D::isWithinSafeZone(int x0, int y0)
{
    wxSize size = wxWindow::GetClientSize();
    int x = size.GetWidth();
    int y = size.GetHeight();
    return ((x0>50) && (x0<x -50) && (y0>50) && (y0<y-50));

}

void Canvas2D::paint(wxPaintEvent &event)
{
    wxPaintDC dc(this);
    dc.Clear();
    if (counter != -1)
        render(dc);
}

wxBitmap Canvas2D::getBitmap()
{
    if (counter ==1)
        return wxNullBitmap;
    wxMemoryDC memDC;
    wxBitmap bitmap(600, 600);
    memDC.SelectObject(bitmap);
    memDC.SetBrush(wxBrush(wxColor(255, 255, 255, 1),wxBRUSHSTYLE_SOLID));
    memDC.DrawRectangle(0,0,600, 600);
    render(memDC);
    memDC.SelectObject(wxNullBitmap);
    return bitmap;
}
void Canvas2D::leftClick(wxMouseEvent& event)
{
    vertex2D current;
    int x = event.GetX();
    int y = event.GetY();
    if (isWithinSafeZone(x,y))
    {
        switch (counter)
        {
        case -1:
            counter++;
            current.x = x;
            current.y = y;
            current.prevx = x+length*cos(pi/6);
            current.prevy = y-length*sin(pi/6);
            current.shortFront = (active != carbon);
            current.shortRear = false;
            current.element.atomName = active;
            current.element.freebonds = getPossibleBonds(current.element.atomName);
            current.element.bond = 0;
            vertices.push_back(current);
            break;
        case 0:
            if  ((vertices[0].x - 10 < x)  &&(vertices[0].x + 10 > x)  && (vertices[0].y - 10 < y) &&(vertices[0].y + 10 > y)&& (vertices[0].element.freebonds - bond >=0))
            {
                counter++;
                current.x = vertices[0].prevx;
                current.y = vertices[0].prevy;
                current.prevx = vertices[0].x;
                current.prevy = vertices[0].y;
                current.element.atomName = active;
                vertices[0].element.freebonds-=bond;
                vertices[0].element.bond = bond;
                current.element.freebonds = getPossibleBonds(active)-bond;
                current.element.bond = bond;
                current.shortFront = (active != carbon);
                current.shortRear = vertices[0].shortFront;
                vertices.push_back(current);
            }
            break;
        default:
            bool flag = false;
            int i;
            for (i = 0; i<=counter; i++)
            {
                if ((vertices[i].x - 10 < x)  &&(vertices[i].x + 10 > x)  && (vertices[i].y - 10 < y) &&(vertices[i].y + 10 > y) && (vertices[i].element.freebonds - bond >=0))
                {
                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                int x1;
                int y1;
                int exodus;
                if (bond == 3 || vertices[i].element.bond == 3|| (bond==2 && vertices[i].element.bond == 2))
                    exodus = 3;
                else
                {
                    if (vertices[i].element.bond == 2)
                        exodus = 2-vertices[i].element.freebonds;

                    else
                        exodus = (getPossibleBonds(vertices[i].element.atomName)-vertices[i].element.freebonds-1);

                }
                getVertexLocation(vertices[i].prevx,vertices[i].prevy, vertices[i].x, vertices[i].y,  exodus, x1, y1);
                counter++;
                current.x = x1;
                current.y = y1;
                current.prevx = vertices[i].x;
                current.prevy = vertices[i].y;
                current.element.atomName = active;
                vertices[i].element.freebonds -=bond;
                current.element.bond = bond;
                current.element.freebonds = getPossibleBonds(active)-bond;
                current.shortFront = (active != carbon);
                current.shortRear = vertices[i].shortFront;
                vertices.push_back(current);
            }
        }
        Refresh();
    }
}

void Canvas2D::render(wxDC& dc)
{
    dc.SetPen( wxPen( wxColor(0,0,0,1), 3));
    dc.SetTextForeground(wxColor(0,0,0,1));
    dc.SetFont(wxFont(15,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Arial"),wxFONTENCODING_DEFAULT));
    std::string str;
    if (counter == 0)
    {
        str = getStringForVertex(vertices[0].element);
        dc.DrawText(wxString(str), vertices[0].x, vertices[0].y-10);
    }
    else
    {
        if (vertices[0].element.atomName != carbon)
        {
            str = getStringForVertex(vertices[0].element);
            dc.DrawText(wxString(str), vertices.at(0).x-10, vertices.at(0).y-10);
        }
        int x0, x1, y0, y1;
        for (int i = 1; i<=counter; i++)
        {
            if (vertices[i].element.atomName != carbon)
            {
                str = getStringForVertex(vertices[i].element);
                dc.DrawText(wxString(str), vertices[i].x-5, vertices[i].y-10);
            }
            if (vertices[i].shortRear)
            {
                x0 = round(vertices[i].x/4.0 + vertices[i].prevx*3/4.0);
                y0 = round(vertices[i].y/4.0 + vertices[i].prevy*3/4.0);
            }
            else
            {
                x0 = vertices[i].prevx;
                y0 = vertices[i].prevy;
            }

            if (vertices[i].shortFront)
            {

                x1 = round(vertices[i].x/4.0*3 + vertices[i].prevx/4.0);
                y1 = round(vertices[i].y/4.0*3 + vertices[i].prevy/4.0);
            }
            else
            {
                x1 = vertices[i].x;
                y1 = vertices[i].y;
            }
            switch (vertices[i].element.bond)
            {


            case 2:
                if(vertices[i].prevx ==  vertices[i].x)
                {
                    dc.DrawLine(x0 - 2, y0, x1 -2, y1);
                    dc.DrawLine(x0 + 2, y0, x1 +2, y1);
                }
                else
                {
                    dc.DrawLine(x0, y0-3, x1, y1-3);
                    dc.DrawLine(x0, y0+3, x1, y1+3);
                }
                break;


            case 3:

                if(vertices[i].prevx ==  vertices[i].x)
                {
                    dc.DrawLine(x0 - 5, y0, x1 -5, y1);
                    dc.DrawLine(x0 + 5, y0, x1 +5, y1);
                }
                else
                {
                    dc.DrawLine(x0, y0-5, x1, y1-5);
                    dc.DrawLine(x0, y0+5, x1, y1+5);
                }
            case 1:
                dc.DrawLine(x0, y0, x1, y1);
                break;
            }
        }
    }
}
void Canvas2D::clearVertex()
{
    counter = -1;
    vertices.clear();
    Refresh();
}

char Canvas2D::getPossibleBonds(elem activeElement)
{
    switch (activeElement)
    {
    case carbon:
        return 4;
    case nitrogen:
    case phosphorus:
        return 3;
    case oxygen:
    case sulfur:
        return 2;
    default:
        return 1;
    }
}

void Canvas2D::getVertexLocation(int x0, int y0, int x, int y, int value, int &x1, int &y1)
{
    float alpha, c, s;
    int rx, ry;
    switch (value)
    {
    case 0:

        alpha = 2*pi/3;
        if (y0>=y)
            alpha = -alpha;
        break;
    case 1:

        alpha = 2*pi/3;
        if (y0<y)
            alpha = -alpha;
        break;
    case 2:
        alpha = pi/3;
        if (y0>=y)
            alpha = -alpha;
        break;
    case 3:
        alpha = pi;
        break;
    default:
        alpha = 2*pi/3;
    }

    rx = x0 - x;
    ry = y0 - y;
    c = cos(alpha);
    s = sin(alpha);
    x1 = round( x + rx * c - ry * s);
    y1 = round(y + rx * s + ry * c);
}

std::string Canvas2D::getStringForVertex(atom activeAtom)
{

    std::string vertex = "";
    if (activeAtom.freebonds >0)
    {
        vertex = "H";
        if (activeAtom.freebonds >1)
            vertex += std::to_string(activeAtom.freebonds);
    }
    switch (activeAtom.atomName)
    {
    case chlorine:
        vertex += "Cl";
        break;
    case bromine:
        vertex += "Br";
        break;
    case fluorine:
        vertex += " F";
        break;
    case iodine:
        vertex += " I";
        break;
    case sulfur:
        vertex += "S";
        break;
    case oxygen:
        if (activeAtom.freebonds != 1)
            vertex += "O";
        else
            vertex = "O" + vertex;
        break;
    case phosphorus:
        vertex = "P" + vertex;
        break;
    case nitrogen:
        vertex = "N" + vertex;
        break;
    case carbon:
        vertex = "C" + vertex;
        break;
    }
    return vertex;
}

void Canvas2D::setBond(int bondNumber)
{
    if (getPossibleBonds(active)>=bondNumber)
        bond = bondNumber;
}

void Canvas2D::setActiveElement(elem activeElement)
{
    active = activeElement;
    if (bond > getPossibleBonds(activeElement))
        bond = 1;
}


