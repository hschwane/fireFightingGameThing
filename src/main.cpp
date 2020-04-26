#include <iostream>
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>

void addGeneralKeys()
{
    using namespace mpu::gph;
    namespace ip = mpu::gph::Input;

    ip::addButton("Toggle Fullscreen","Switch between window and fullscreen.",[](Window& wnd){ wnd.toggleFullscreen();});
    ip::mapKeyToInput("Toggle Fullscreen",GLFW_KEY_F11);

    ip::addButton("Toggle GUI","Hides / shows GUI.",[](Window& wnd){ ImGui::toggleVisibility();});
    ip::mapKeyToInput("Toggle GUI",GLFW_KEY_F10);

    ip::addButton("Quit","Ends the game.",[](Window& wnd){ wnd.shouldClose();});
    ip::mapKeyToInput("Quit",GLFW_KEY_ESCAPE);
}


int main()
{
    mpu::Log myLog(mpu::LogLvl::ALL,mpu::ConsoleSink());
    myLog.printHeader("FireFightingGameThing",FFGT_VERSION,FFGT_VERSION_SHA);

    using namespace mpu::gph;

    // setup main window
    Window mainWnd(600,600,"FireFightingGameThing");

    // setup gui
    ImGui::create(mainWnd);

    // setup keybindings
    addGeneralKeys();

    // background color
    glClearColor(0.2,0.3,0.5,1.0);

    // start main loop
    while(mainWnd.frameEnd(), Input::update(), mainWnd.frameBegin())
    {

    }

}