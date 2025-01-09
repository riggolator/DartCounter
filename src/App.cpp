#include "App.h"
#include "StartWindow.h"

//wxIMPLEMENT_APP(DartCounterApp);

bool DartCounterApp::OnInit() {
    StartWindow* startWindow = new StartWindow();
    startWindow->Show(true);
    return true;
}

