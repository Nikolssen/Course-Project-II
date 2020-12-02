#include "MainFrame.h"
#include "Canvas2D.h"
#include "xpm_icons.h"

const long MainFrame::ID_Canvas2D= wxNewId();
const long MainFrame::ID_ToolBar= wxNewId();
const long MainFrame::ID_ToolBarItem_Carbon = wxNewId();
const long MainFrame::ID_ToolBarItem_Nitrogen = wxNewId();
const long MainFrame::ID_ToolBarItem_Oxygen = wxNewId();
const long MainFrame::ID_ToolBarItem_Phosphorus = wxNewId();
const long MainFrame::ID_ToolBarItem_Sulfur = wxNewId();
const long MainFrame::ID_ToolBarItem_Fluorine = wxNewId();
const long MainFrame::ID_ToolBarItem_Chlorine = wxNewId();
const long MainFrame::ID_ToolBarItem_Bromine = wxNewId();
const long MainFrame::ID_ToolBarItem_Iodine = wxNewId();
const long MainFrame::ID_ToolBarItem_Single = wxNewId();
const long MainFrame::ID_ToolBarItem_Double = wxNewId();
const long MainFrame::ID_ToolBarItem_Triple = wxNewId();
const long MainFrame::ID_ToolBarItem_Eraser = wxNewId();
const long MainFrame::ID_ToolBarItem_Calotte = wxNewId();
const long MainFrame::ID_ToolBarItem_Save2D = wxNewId();
const long MainFrame::ID_ToolBarItem_Save3D = wxNewId();
const long MainFrame::ID_Canvas3D = wxNewId();

MainFrame::MainFrame(wxWindow* parent,wxWindowID id)
{
    Create(parent, id, _("Molecular Editor"), wxDefaultPosition, wxSize(1280,720), (wxSYSTEM_MENU |wxCLOSE_BOX |wxCAPTION |wxCLIP_CHILDREN), _T("id"));
    SetForegroundColour(wxColour(0,0,0,1));
    SetBackgroundColour(wxColour(128, 128, 128, 1));
    SetIcon(wxIcon(ChemEditor));
    wxFont thisFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Bahnschrift"),wxFONTENCODING_DEFAULT);
    SetFont(thisFont);

    MainCanvas = new Canvas2D(this, ID_Canvas2D,wxPoint(0, 72), wxSize(625,648),wxTAB_TRAVERSAL,_T("ID_Canvas2D"));
    MainCanvas->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    MainCanvas->SetBackgroundColour(wxColor(252,244,199,1));

    int attributes[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    OtherCanvas = new Canvas3D((wxFrame*)this, ID_Canvas3D, attributes, wxPoint(625, 72), wxSize(655, 648));

    MainToolBar            = new wxToolBar(this, ID_ToolBar, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxTB_TEXT|wxTB_FLAT, _T("ID_ToolBar"));
    ToolBarItem_Carbon     = MainToolBar ->AddTool(ID_ToolBarItem_Carbon, _("Carbon"), wxBitmap(carbon_xpm), wxBitmap(carbon_xpm), wxITEM_NORMAL, _("Carbon"), _("Carbon"));
    ToolBarItem_Nitrogen   = MainToolBar ->AddTool(ID_ToolBarItem_Nitrogen, _("Nitrogen"), wxBitmap(nitrogen_xpm), wxBitmap(nitrogen_xpm), wxITEM_NORMAL,_("Nitrogen"), _("Nitrogen"));
    ToolBarItem_Oxygen     = MainToolBar ->AddTool(ID_ToolBarItem_Oxygen, _("Oxygen"), wxBitmap(oxygen_xpm), wxBitmap(oxygen_xpm), wxITEM_NORMAL, _("Oxygen"), _("Oxygen"));
    ToolBarItem_Phosphorus = MainToolBar ->AddTool(ID_ToolBarItem_Phosphorus, _("Phosphorus"),wxBitmap(phosphorus_xpm), wxBitmap(phosphorus_xpm), wxITEM_NORMAL, _("Phosphorus"), _("Phosphorus"));
    ToolBarItem_Sulfur     = MainToolBar ->AddTool(ID_ToolBarItem_Sulfur, _("Sulfur"), wxBitmap(sulfur_xpm), wxBitmap(sulfur_xpm), wxITEM_NORMAL, _("Sulfur"), _("Sulfur"));
    ToolBarItem_Fluorine   = MainToolBar ->AddTool(ID_ToolBarItem_Fluorine, _("Fluorine"), wxBitmap(fluorine_xpm), wxBitmap(fluorine_xpm), wxITEM_NORMAL, _("Fluorine"), _("Fluorine"));
    ToolBarItem_Chlorine   = MainToolBar ->AddTool(ID_ToolBarItem_Chlorine, _("Chlorine"), wxBitmap(chlorine_xpm), wxBitmap(chlorine_xpm), wxITEM_NORMAL,_("Chlorine"), _("Chlorine"));
    ToolBarItem_Bromine    = MainToolBar ->AddTool(ID_ToolBarItem_Bromine, _("Bromine"), wxBitmap(bromine_xpm), wxBitmap(bromine_xpm), wxITEM_NORMAL,_("Bromine"), _("Bromine"));
    ToolBarItem_Iodine     = MainToolBar ->AddTool(ID_ToolBarItem_Iodine, _("Iodine"), wxBitmap(iodine_xpm), wxBitmap(iodine_xpm), wxITEM_NORMAL, _("Iodine"), _("Iodine"));
    MainToolBar->AddSeparator();
    ToolBarItem_Single     = MainToolBar ->AddTool(ID_ToolBarItem_Single, _("Single Bond"), wxBitmap(single_xpm), wxBitmap(single_xpm), wxITEM_NORMAL, _("Single Bond"), _("Single Bond"));
    ToolBarItem_Double     = MainToolBar ->AddTool(ID_ToolBarItem_Double, _("Double Bond"), wxBitmap(double_xpm), wxBitmap(double_xpm), wxITEM_NORMAL, _("Double Bond"), _("Double Bond"));
    ToolBarItem_Triple     = MainToolBar ->AddTool(ID_ToolBarItem_Triple, _("Triple Bond"), wxBitmap(triple_xpm), wxBitmap(triple_xpm), wxITEM_NORMAL, _("Triple Bond"), _("Triple Bond"));
    MainToolBar->AddSeparator();
    ToolBarItem_Eraser     = MainToolBar ->AddTool(ID_ToolBarItem_Eraser, _("Clear"), wxBitmap(eraser_xpm), wxBitmap(eraser_xpm), wxITEM_NORMAL, _("Clear"), _("Clear"));
    ToolBarItem_Save2D     = MainToolBar ->AddTool(ID_ToolBarItem_Save2D, _("Save"), wxBitmap(save2d_xpm), wxBitmap(save2d_xpm),wxITEM_NORMAL, _("Save"), _("Save"));
    MainToolBar->AddSeparator();
    ToolBarItem_Calotte    = MainToolBar ->AddTool(ID_ToolBarItem_Calotte, _("Transform"), wxBitmap(calotte_xpm),wxBitmap(calotte_xpm), wxITEM_NORMAL, _("Transform"), _("Transform"));
    ToolBarItem_Save3D     = MainToolBar ->AddTool(ID_ToolBarItem_Save3D, _("Save"), wxBitmap(save3d_xpm), wxBitmap(save3d_xpm),wxITEM_NORMAL, _("Save"), _("Save"));
    MainToolBar->Realize();
    SetToolBar(MainToolBar);

    MainCanvas->Bind(wxEVT_LEFT_DOWN, &Canvas2D::leftClick, MainCanvas);
    MainCanvas->Bind(wxEVT_PAINT, &Canvas2D::paint, MainCanvas);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::CarbonClick, this, ID_ToolBarItem_Carbon);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::NitrogenClick, this, ID_ToolBarItem_Nitrogen);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::OxygenClick, this, ID_ToolBarItem_Oxygen);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::PhosphorusClick, this, ID_ToolBarItem_Phosphorus);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::SulfurClick, this, ID_ToolBarItem_Sulfur);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::FluorineClick, this, ID_ToolBarItem_Fluorine);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::ChlorineClick, this, ID_ToolBarItem_Chlorine);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::BromineClick, this, ID_ToolBarItem_Bromine);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::IodineClick, this, ID_ToolBarItem_Iodine);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::SingleClick, this, ID_ToolBarItem_Single);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::DoubleClick, this, ID_ToolBarItem_Double);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::TripleClick, this, ID_ToolBarItem_Triple);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::EraseClick, this, ID_ToolBarItem_Eraser);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::CalotteClick, this, ID_ToolBarItem_Calotte);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::Save2DClick, this, ID_ToolBarItem_Save2D);
    Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::Save3DClick, this, ID_ToolBarItem_Save3D);

}

BEGIN_EVENT_TABLE(Canvas3D, wxGLCanvas)
    EVT_PAINT(Canvas3D::render)
    EVT_MOUSEWHEEL(Canvas3D::zoom)
END_EVENT_TABLE()

void MainFrame::CarbonClick(wxCommandEvent&event)
{
    MainCanvas->setActiveElement(carbon);
}

void MainFrame::NitrogenClick(wxCommandEvent&event)
{
    MainCanvas->setActiveElement(nitrogen);
}

void MainFrame::OxygenClick(wxCommandEvent&event)
{
    MainCanvas->setActiveElement(oxygen);
}

void MainFrame::PhosphorusClick(wxCommandEvent&event)
{
    MainCanvas->setActiveElement(phosphorus);
}

void MainFrame::SulfurClick(wxCommandEvent&event)
{
    MainCanvas->setActiveElement(sulfur);
}
void MainFrame::FluorineClick(wxCommandEvent&event)
{
    MainCanvas->setActiveElement(fluorine);
}
void MainFrame::ChlorineClick(wxCommandEvent&event)
{
    MainCanvas->setActiveElement(chlorine);
}
void MainFrame::BromineClick(wxCommandEvent&event)
{
    MainCanvas->setActiveElement(bromine);
}
void MainFrame::IodineClick(wxCommandEvent&event)
{
    MainCanvas->setActiveElement(iodine);
}
void MainFrame::SingleClick(wxCommandEvent&event)
{
    MainCanvas->setBond(1);
}
void MainFrame::DoubleClick(wxCommandEvent&event)
{
    MainCanvas->setBond(2);
}
void MainFrame::TripleClick(wxCommandEvent&event)
{
    MainCanvas->setBond(3);
}

void MainFrame::EraseClick(wxCommandEvent&event)
{
    MainCanvas->clearVertex();
}

void MainFrame::CalotteClick(wxCommandEvent&event)
{
    Converter* converter = new Converter();
    OtherCanvas->vertices3D = converter->convertToCalotte(MainCanvas->vertices);
    delete converter;
    OtherCanvas->getTransformed();
}

void MainFrame::Save2DClick(wxCommandEvent&event)
{
    wxString caption = _T("Choose a directory and filename");
    wxString wildcard =_T("BMP files (*.bmp)|*.bmp| PNG files (*.png)|*.png| JPG files (*.jpg)|*.jpg");
    wxString defaultDir = wxEmptyString;
    wxString defaultFilename = _T("Molecule.bmp");
    wxFileDialog dialog(this,caption, defaultDir, defaultFilename, wildcard, wxFD_SAVE);
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();
        wxString ext=path.AfterLast('.');
        wxImage image = MainCanvas->getBitmap().ConvertToImage();
        wxInitAllImageHandlers();

        if (ext == "bmp"||ext == "png"||ext == "jpg")
            image.SaveFile(path);
    }
}
void MainFrame::Save3DClick(wxCommandEvent&event)
{
    wxString caption = _T("Choose a directory and filename");
    wxString wildcard =_T("BMP files (*.bmp)|*.bmp| PNG files (*.png)|*.png| JPG files (*.jpg)|*.jpg");
    wxString defaultDir = wxEmptyString;
    wxString defaultFilename = _T("Molecule 3D.bmp");
    wxFileDialog *dialog = new wxFileDialog(this,caption, defaultDir, defaultFilename, wildcard, wxFD_SAVE);


    if (dialog->ShowModal() == wxID_OK)
    {

        OtherCanvas->filePath = dialog->GetPath();
        delete dialog;
        OtherCanvas->save();
    }
    else
    {
        delete dialog;

    }

}
BEGIN_EVENT_TABLE(MainFrame,wxFrame)

END_EVENT_TABLE()

MainFrame::~MainFrame()
{

}
