/*
 * fireFightingGameThing
 * MapEditorScene.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the MapEditorScene class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "MapEditorScene.h"
#include "App.h"
#include "layer.h"
//--------------------


// function definitions of the MapEditorScene class
//-------------------------------------------------------------------
MapEditorScene::MapEditorScene()
    : m_camera({0,0},1.0,"EditorCamera"),
      ttGrass(TileType::loadFromFile(PROJECT_RESOURCE_PATH"data/core/tiles/grass.cfg")),
      ttConcrete(TileType::loadFromFile(PROJECT_RESOURCE_PATH"data/core/tiles/concrete.cfg"))

{
    // setup input handling
    m_camera.addInputs();
    addKeybindings();
}

void MapEditorScene::onActivation()
{
    activeMap = Map({100,100});

    namespace ip = mpu::gph::Input;
    mpu::gph::Input::addButton("BeginSelection","Begin a selection.",[&](const mpu::gph::Window& wnd)
    {
        selectionStart = mpu::gph::mouseToWorld2D(wnd.getCursorPos(),{0,0,800,800},App::getRenderer().getViewProjection());
        selecting = true;
    });

    mpu::gph::Input::addButton("EndSelection","End a selection.",[&](const mpu::gph::Window& wnd)
    {
        glm::vec2 selectionEnd = mpu::gph::mouseToWorld2D(wnd.getCursorPos(),{0,0,800,800},App::getRenderer().getViewProjection());
        activeMap.setTileType(glm::round(selectionEnd),ttConcrete);
        selecting = false;
    });

    mpu::gph::Input::mapMouseButtonToInput("BeginSelection",GLFW_MOUSE_BUTTON_1,ip::ButtonBehavior::onPress);
    mpu::gph::Input::mapMouseButtonToInput("EndSelection",GLFW_MOUSE_BUTTON_1,ip::ButtonBehavior::onRelease);
}

void MapEditorScene::onDeactivation()
{

}

void MapEditorScene::update()
{
    m_camera.update();
}

void MapEditorScene::draw()
{
    App::getRenderer().setView(m_camera.viewMatrix());

    glm::uvec2 id{0,0};
    for(id.y = 0; id.y<activeMap.getSize().y; id.y++)
        for(id.x = 0; id.x<activeMap.getSize().x; id.x++)
        {
            App::getRenderer().addSprite(activeMap.getTileType(id).getSprite(), glm::translate(glm::vec3({id, 0})), MAP_LAYER);
        }
}

void MapEditorScene::addKeybindings()
{
    using namespace mpu::gph;
    namespace ip = mpu::gph::Input;

    ip::mapScrollToInput("EditorCameraZoom");
    ip::mapKeyToInput("EditorCameraMoveDownUp",GLFW_KEY_W,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("EditorCameraMoveDownUp",GLFW_KEY_S,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
    ip::mapKeyToInput("EditorCameraMoveLeftRight",GLFW_KEY_D,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("EditorCameraMoveLeftRight",GLFW_KEY_A,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
}
