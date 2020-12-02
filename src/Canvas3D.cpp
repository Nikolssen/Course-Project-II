#include "Canvas3D.h"

Canvas3D::Canvas3D(wxFrame* parent, wxWindowID id,int* attributes,  const wxPoint&pos, const wxSize& size):
    wxGLCanvas((wxWindow*)parent, id, attributes, pos, size, 0, _T("GLCanvas"), wxNullPalette)
{
    m_context = new wxGLContext(this);
    SetBackgroundStyle(wxBG_STYLE_COLOUR);
    SetBackgroundColour(wxColor(0,0, 0, 1));
    shouldPaint = false;
    shouldSave = false;
    dist = 7.0;
}

Canvas3D::~Canvas3D()
{
    delete m_context;
    int j = reusableQuadrics.size();
    for ( int i = 0; i < j; i++ )
    {
        gluDeleteQuadric(reusableQuadrics[i]);
    }
}
void Canvas3D::zoom(wxMouseEvent &evt)
{
    int lines = evt.GetColumnsPerAction();
    int direction = ((evt.GetWheelRotation() > 0)? -1: 1) ;
    dist +=direction*lines*0.2;
    Refresh();
}
void Canvas3D::sphere(vertex3D &vertex, int pos)
{

    colour currentColour;
    float radius;

    switch (vertex.atomName)
    {
    case carbon:
        currentColour = {0.57, 0.57, 0.57};
        radius = 1.12;
        break;
    case oxygen:
        currentColour = {0.96, 0.07, 0.01};
        radius = 1;
        break;
    case nitrogen:
        currentColour = {0.2, 0.33, 0.9255};
        radius = 1.02;
        break;
    case phosphorus:
        currentColour = {0.98, 0.5, 0.02};
        radius = 1.18;
        break;
    case sulfur:
        currentColour = {1, 0.98, 0.267};
        radius = 1.18;
        break;
    case chlorine:
        currentColour = {0.094, 0.964, 0.09};
        radius = 1.15;
        break;
    case fluorine:
        currentColour = {0.54, 0.89, 0.325};
        radius = 0.97;
        break;
    case bromine:
        currentColour = {0.65, 0.16, 0.15};
        radius = 1.22;
        break;
    case iodine:
        currentColour = {0.58, 0, 0.58};
        radius = 1.3;
        break;
    default:
        currentColour = {1,1,1};
        radius = 0.79;
        break;
    }
    glPushMatrix();
    glColor3f(currentColour.red, currentColour.green, currentColour.blue);
    glTranslatef(vertex.point.x, vertex.point.y, vertex.point.z-dist);
    gluSphere(reusableQuadrics[pos], radius, 30, 30);
    glPopMatrix();

}

void Canvas3D::getTransformed()
{
    shouldPaint = true;
    Refresh();
}

void Canvas3D::prepare()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glClearDepth(1.0f);	// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float ratio_w_h = 1;
    gluPerspective(45 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 200 /*clip far*/);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
void Canvas3D::render(wxPaintEvent& evt)
{


    if(!IsShown())
        return;
    if (!shouldPaint)
        return;
    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC dc(this);
    prepare();
    while (reusableQuadrics.size()<vertices3D.size())
    {
        GLUquadricObj* quad = gluNewQuadric();
        reusableQuadrics.push_back(quad);
    }

    for (unsigned int i =0; i<vertices3D.size(); i++)
        sphere(vertices3D.at(i), i);


    glFlush();
    SwapBuffers();
    if (shouldSave)
    {

        wxBitmap bitmap(625, 620);
        wxMemoryDC dcDest;
        dcDest.SelectObject(bitmap);
        dcDest.Blit(0, 0,625, 620,&dc,0, 0,wxCOPY);
        dcDest.SelectObject(wxNullBitmap);
        wxImage image = bitmap.ConvertToImage();
        wxInitAllImageHandlers();
        wxString ext=filePath.AfterLast('.');
        if (ext == "bmp"||ext == "png"||ext == "jpg")
            image.SaveFile(filePath);
        shouldSave = false;
    }
}


void Canvas3D::save()
{

    shouldSave = true;
    Refresh();

}

