#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/file.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/filedlg.h>
#include "Canvas2D.h"
#include "Canvas3D.h"

#include "Converter.h"
class MainFrame : public wxFrame
{
public:
    MainFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~MainFrame();

private:
    Canvas2D* MainCanvas;
    Canvas3D* OtherCanvas;
    wxToolBar* MainToolBar;

    wxToolBarToolBase* ToolBarItem_Carbon;
    wxToolBarToolBase* ToolBarItem_Nitrogen;
    wxToolBarToolBase* ToolBarItem_Oxygen;
    wxToolBarToolBase* ToolBarItem_Phosphorus;
    wxToolBarToolBase* ToolBarItem_Sulfur;
    wxToolBarToolBase* ToolBarItem_Fluorine;
    wxToolBarToolBase* ToolBarItem_Chlorine;
    wxToolBarToolBase* ToolBarItem_Bromine;
    wxToolBarToolBase* ToolBarItem_Iodine;

    wxToolBarToolBase* ToolBarItem_Single;
    wxToolBarToolBase* ToolBarItem_Double;
    wxToolBarToolBase* ToolBarItem_Triple;

    wxToolBarToolBase* ToolBarItem_Eraser;
    wxToolBarToolBase* ToolBarItem_Calotte;
    wxToolBarToolBase* ToolBarItem_Save2D;
    wxToolBarToolBase* ToolBarItem_Save3D;


    static const long ID_Canvas2D;
    static const long ID_ToolBar;
    static const long ID_ToolBarItem_Carbon;
    static const long ID_ToolBarItem_Nitrogen;
    static const long ID_ToolBarItem_Oxygen;
    static const long ID_ToolBarItem_Phosphorus;
    static const long ID_ToolBarItem_Sulfur;
    static const long ID_ToolBarItem_Fluorine;
    static const long ID_ToolBarItem_Chlorine;
    static const long ID_ToolBarItem_Bromine;
    static const long ID_ToolBarItem_Iodine;

    static const long ID_ToolBarItem_Single;
    static const long ID_ToolBarItem_Double;
    static const long ID_ToolBarItem_Triple;

    static const long ID_ToolBarItem_Eraser;
    static const long ID_ToolBarItem_Calotte;
    static const long ID_ToolBarItem_Save2D;
    static const long ID_ToolBarItem_Save3D;
    static const long ID_Canvas3D;


    void CarbonClick(wxCommandEvent& event);
    void NitrogenClick(wxCommandEvent& event);
    void OxygenClick(wxCommandEvent& event);
    void PhosphorusClick(wxCommandEvent& event);
    void SulfurClick(wxCommandEvent& event);
    void FluorineClick(wxCommandEvent& event);
    void ChlorineClick(wxCommandEvent& event);
    void BromineClick(wxCommandEvent& event);
    void IodineClick(wxCommandEvent& event);
    void SingleClick(wxCommandEvent& event);
    void DoubleClick(wxCommandEvent& event);
    void TripleClick(wxCommandEvent& event);
    void EraseClick(wxCommandEvent& event);
    void CalotteClick(wxCommandEvent& event);
    void Save2DClick(wxCommandEvent&event);
    void Save3DClick(wxCommandEvent&event);
    DECLARE_EVENT_TABLE()
};

#endif // MAINFRAME_H
