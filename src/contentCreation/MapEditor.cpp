/*
 * fireFightingGameThing
 * MapEditor.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the MapEditor class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "MapEditor.h"
#include "rendering/mapRendering.h"
//--------------------


// function definitions of the MapEditor class
//-------------------------------------------------------------------
MapEditor::MapEditor()
    : m_camera({0, 0}, 1.0, "EditorCamera"),
      m_tileSelectionPreview(PROJECT_RESOURCE_PATH"data/default/tileSelection.png"),
      rng(mpu::getRanndomSeed()), dist(0, 1)

{
    // setup input handling
    m_camera.addInputs();
    addKeybindings();

    m_activeTiles.emplace_back( noneTile() );
    m_activeTiles.emplace_back( getRM().load<TileType>("core/tiles/water.tile") );

    activeMap = Map({100,100}, *m_activeTiles[0]);

    testTree = std::make_unique<RootedObject>( glm::uvec2(5,5), std::make_shared<RootedObjectType>("Tree", getRM().load<mpu::gph::Sprite2D>("core/sprites/tree.sprite")) );
    activeMap.setRootedObject({5,5},*testTree);
}

void MapEditor::onActivation()
{
}

void MapEditor::onDeactivation()
{
}

void MapEditor::handleImGui()
{
    glm::ivec2 wndSize = ImGui::getAttatchedWindow().getSize();

    ImGui::SetNextWindowPos({0,0},ImGuiCond_Always);
    ImGui::SetNextWindowSizeConstraints(ImVec2(128,wndSize.y),ImVec2(wndSize.x,wndSize.y) );

    if(ImGui::Begin("Terrain", nullptr,  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
    {
        float previewSize = glm::min(64.0f, ImGui::GetWindowContentRegionWidth() / 4);
        for(int i = 0; i < m_activeTiles.size(); i++)
        {
            ImGui::PushID(i);
            if(ImGui::Selectable("##", m_selectedTile == i, 0, ImVec2(0, previewSize)))
                m_selectedTile = i;
            ImGui::SameLine();
            ImGui::Image((void*)(intptr_t)static_cast<GLuint>(m_activeTiles[i].get()->getSprite(0).getTexture()),
                         ImVec2(previewSize, previewSize));
            ImGui::SameLine();
            ImGui::Text("%s", m_activeTiles[i].get()->getName().c_str());
            ImGui::PopID();
        }
    }
    ImGui::End();
}

void MapEditor::update(MouseController& mc)
{
    // handle tile selection
    if(mc.selectionState() == SelectionState::completed)
    {
        activeMap.forEachTileInRect(mc.selctionBeginPos(), mc.selectionEndPos(), [this](Map& map, const glm::uvec2& tile)
        {
            map.setTile(tile, *m_activeTiles[m_selectedTile], m_activeTiles[m_selectedTile]->selectVariant(dist(rng)));
        });
    }

    // add mouse movement to camera and update
    m_camera.moveX(mc.getCameraMovement().x);
    m_camera.moveY(mc.getCameraMovement().y);
    m_camera.update();
}

void MapEditor::draw(mpu::gph::Renderer2D& renderer, MouseController& mc)
{
    renderer.setView(m_camera.viewMatrix());

    // show selection preview
    if(mc.selectionState() == SelectionState::inProgress)
    {
        activeMap.forEachTileInRect(mc.selctionBeginPos(), mc.getMousePosWorld(), [this,&renderer](Map& map, const glm::uvec2& tile)
        {
            renderer.addSprite(m_tileSelectionPreview,glm::translate(glm::vec3(tile,0)),5,{1,1,1,.7});
        });
    }

    drawMap(renderer,activeMap);
    renderer.render();
}

void MapEditor::addKeybindings()
{
    using namespace mpu::gph;
    namespace ip = mpu::gph::Input;

    ip::mapScrollToInput("EditorCameraZoom");
    ip::mapKeyToInput("EditorCameraMoveDownUp",GLFW_KEY_W,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("EditorCameraMoveDownUp",GLFW_KEY_S,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
    ip::mapKeyToInput("EditorCameraMoveLeftRight",GLFW_KEY_D,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("EditorCameraMoveLeftRight",GLFW_KEY_A,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
}


