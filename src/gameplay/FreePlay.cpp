/*
 * fireFightingGameThing
 * InGame.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the InGame class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "FreePlay.h"
#include "resourceManagement.h"
//--------------------

// function definitions of the InGame class
//-------------------------------------------------------------------

FreePlay::FreePlay()
        : m_playerCamera({0,0},1.0,"FreeplayCamera")
{
    m_playerCamera.addInputs();
    addKeybindings();
}

void FreePlay::onActivation()
{
    // start a new game by launching a demo operation
    m_currentOperation = Operation::makeDemoOperation();

    // set camera to the center of the map
    glm::vec2 camPos = (m_currentOperation->getMap().getSize() - glm::ivec2(1)) * 0.5;
    m_playerCamera.setPosition(camPos);
    m_playerCamera.setZoom(0.18);
}

void FreePlay::onDeactivation()
{
    // cleanup
    m_currentOperation = nullptr;
    getRM().tryReleaseAll();
}

void FreePlay::handleImGui()
{
    if(m_currentlyHoveredObject)
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", m_currentlyHoveredObject->getType().getName().c_str());
        ImGui::EndTooltip();
    } else if(m_currentlyHoveredTileType)
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", m_currentlyHoveredTileType->getName().c_str());
        ImGui::EndTooltip();
    }
}

void FreePlay::update(MouseController& mc)
{
    // add mouse movement to camera and update
    m_playerCamera.moveX(mc.getCameraMovement().x);
    m_playerCamera.moveY(mc.getCameraMovement().y);
    m_playerCamera.update();

    // get some information on whatever is hovered
    const Map& currentMap = m_currentOperation->getMap();
    glm::uvec2 hoveredTile = Map::tileAtWorld(mc.getMousePosWorld());
    if(currentMap.isValid(hoveredTile))
    {
        m_currentlyHoveredObject = m_currentOperation->getMap().getRootedObject(hoveredTile);
        m_currentlyHoveredTileType = &m_currentOperation->getMap().getTileType(hoveredTile);
    } else
    {
        m_currentlyHoveredObject = nullptr;
        m_currentlyHoveredTileType = nullptr;
    }



//    const TileType* hoveredTileType = &m_currentOperation->getMap().getTileType(hoveredTile);
//    if()

    m_currentOperation->handlePlayerInput();
    m_currentOperation->update();
}

void FreePlay::draw(mpu::gph::Renderer2D& renderer, MouseController& mc)
{
    renderer.setView(m_playerCamera.viewMatrix());
    m_currentOperation->draw(renderer);
    renderer.render();
}

void FreePlay::addKeybindings()
{
    using namespace mpu::gph;
    namespace ip = mpu::gph::Input;

    ip::mapScrollToInput("FreeplayCameraZoom");
    ip::mapKeyToInput("FreeplayCameraMoveDownUp",GLFW_KEY_W,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("FreeplayCameraMoveDownUp",GLFW_KEY_S,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
    ip::mapKeyToInput("FreeplayCameraMoveLeftRight",GLFW_KEY_D,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("FreeplayCameraMoveLeftRight",GLFW_KEY_A,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
}

