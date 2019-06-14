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
}

int main()
{
    mpu::Log myLog(mpu::LogLvl::ALL,mpu::ConsoleSink());
    myLog.printHeader("FireFightingGameThing",FFGT_VERSION,FFGT_VERSION_SHA);

    using namespace mpu::gph;

    // setup main window
    Window mainWnd(800,600,"FireFightingGameThing");
    mainWnd.addSizeCallback([](int x,int y){ glViewport(0,0,x,y);});

    // setup gui
    ImGui::create(mainWnd);

    // start main loop
    while(mainWnd.frameEnd(), Input::update(), mainWnd.frameBegin())
    {


        // im gui debug window
        {
            using namespace ImGui;
            Begin("FFGT");
            End();
        }

        
    }
}