#include <iostream>
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>

#include "engine/SpriteRenderer.h"

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
    mainWnd.addSizeCallback([](int x,int y){ glViewport(0,0,x,y);});

    // setup gui
    ImGui::create(mainWnd);

    // setup keybindings
    addGeneralKeys();

    // have a vao active because we have to have one
    VertexArray vao;
    vao.bind();

    // glsettings
    glClearColor(0.2,0.3,0.5,1.0);

    SpriteRenderer::setView(glm::mat4(1));
    SpriteRenderer::setProjection(glm::mat4(1));

    // load a texture
    Texture test(TextureFileType::eU8, PROJECT_RESOURCE_PATH "car_test01.png");
    Sampler sampler;
    sampler.set(GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    sampler.set(GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    // varables
    glm::vec2 size{0.1,0.28};
    glm::vec2 pos{0,0};
    float rot =0;

    // start main loop
    while(mainWnd.frameEnd(), Input::update(), mainWnd.frameBegin())
    {
        SpriteRenderer::drawSprite(test,size,pos,glm::radians(rot));

        // im gui debug window
        {
            using namespace ImGui;
            Begin("FFGT");

                SliderFloat2("position",&pos.x,1,0);
                SliderFloat("rotation",&rot,0,360);
                SliderFloat2("size",&size.x,0,1);
            End();
        }
    }

}