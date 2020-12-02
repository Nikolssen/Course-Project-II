#ifndef CANVAS3D_H
#define CANVAS3D_H

#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "structures.h"

class Canvas3D : public wxGLCanvas
{

public:
    Canvas3D(wxFrame* parent, wxWindowID id,int* attributes, const wxPoint&pos, const wxSize& size);
    virtual ~Canvas3D();
    void getTransformed();
    void save();

    wxString filePath;
    std::vector<vertex3D> vertices3D;

private:
    void render(wxPaintEvent& evt);
    void zoom(wxMouseEvent &evt);
    void sphere(vertex3D &vertex, int pos);
    void prepare();

    std::vector<GLUquadricObj*> reusableQuadrics;
    wxGLContext*	m_context;
    const GLfloat light_ambient[4]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    const GLfloat light_diffuse[4]  = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat light_position[4] = { 2.0f, 5.0f, 5.0f, 0.0f };

    const GLfloat mat_ambient[4]    = { 0.7f, 0.7f, 0.7f, 1.0f };
    const GLfloat mat_diffuse[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[1] = { 100.0f };
    bool shouldPaint;
    bool shouldSave;
    float dist;

    DECLARE_EVENT_TABLE()
};

#endif // CANVAS3D_H
