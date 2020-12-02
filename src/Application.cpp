#include "Application.h"
#include "MainFrame.h"

IMPLEMENT_APP(Application);

bool Application::OnInit()
{

    bool wxsOK = true;
    if ( wxsOK )
    {
    	MainFrame* Frame = new MainFrame(0);
    	Frame->Show(true);
    }

    return wxsOK;

}
