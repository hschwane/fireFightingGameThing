#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>

#include "TileType.h"
#include "Map.h"

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

void addDebugCameraKeys()
{
    using namespace mpu::gph;
    namespace ip = mpu::gph::Input;

    ip::mapScrollToInput("DebugCameraZoom");
    ip::mapKeyToInput("DebugCameraMoveDownUp",GLFW_KEY_W,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("DebugCameraMoveDownUp",GLFW_KEY_S,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
    ip::mapKeyToInput("DebugCameraMoveLeftRight",GLFW_KEY_D,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("DebugCameraMoveLeftRight",GLFW_KEY_A,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
}

int main()
{
    mpu::Log myLog(mpu::LogLvl::ALL,mpu::ConsoleSink());
    myLog.printHeader("FireFightingGameThing",FFGT_VERSION,FFGT_VERSION_SHA);

    using namespace mpu::gph;

    // setup main window
    Window mainWnd(10,10,"FireFightingGameThing");
    addGeneralKeys();

    // setup imgui
    ImGui::create(mainWnd);

    // setup camera
    Camera2D debugCamera({0,0},1.0,"DebugCamera");
    debugCamera.addInputs();
    addDebugCameraKeys();

    // setup 2d renderer
    Renderer2D renderer;
    renderer.setSamplingLinear(true,true);

    // handle window resizing
    mainWnd.addFBSizeCallback([&](int w, int h)
    {
        glViewport(0,0,w,h);
        float aspect = float(w)/h;
        renderer.setProjection(-1*aspect,1*aspect,-1,1);
    });
    mainWnd.setSize(800,800); // trigger resize callback to set projection

    // background color
    glClearColor(0.2,0.3,0.5,1.0);

    // create some tile types
    constexpr unsigned char transparent[] = {0,0,0,0};
    constexpr unsigned char green[] = {60,200,30,255};
    constexpr unsigned char grey[] = {200,200,200,255};
    TileType ttGrass = TileType::loadFromFile(PROJECT_RESOURCE_PATH"data/core/tiles/grass.cfg");
    TileType ttConcrete = TileType::loadFromFile(PROJECT_RESOURCE_PATH"data/core/tiles/concrete.cfg");

    // create a map
    Map mainMap({100,100});


    // start main loop
    while(mainWnd.frameEnd(), Input::update(), mainWnd.frameBegin())
    {
        debugCamera.update();
        renderer.setView(debugCamera.viewMatrix());

        mainMap.addTilesForRendering(renderer);
        renderer.render();
    }
}