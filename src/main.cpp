#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>

#include "App.h"
#include "contentCreation/MapEditorScene.h"

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
    mpu::gph::Window& wnd = App::getMainWnd();
    wnd.setTitle("Fire Fighting Game Thingy");

    // add some keys valid everywhere
    addGeneralKeys();

    // setup imgui
    ImGui::create(wnd);

    // setup renderer
    mpu::gph::Renderer2D& renderer = App::getRenderer();
    renderer.setSamplingLinear(true,true);

    // handle window resizing
    wnd.addFBSizeCallback([&](int w, int h)
    {
      glViewport(0,0,w,h);
      float aspect = float(w)/h;
      renderer.setProjection(-1*aspect,1*aspect,-1,1);
    });
    wnd.setSize(800,800); // trigger resize callback to set projection

    // set grey background for startup
    glClearColor(0.2,0.2,0.2,1.0);

    // setup scenes and scene manager
    mpu::gph::SceneManager& scMngr = App::getSceneManager();
    unsigned int mapEditorScene = scMngr.addScene(std::make_unique<MapEditorScene>());
    scMngr.switchToScene(mapEditorScene);

    // start main loop
    while(wnd.frameEnd(), Input::update(), wnd.frameBegin())
    {
        scMngr.update();
        scMngr.draw();
        renderer.render();
    }
}