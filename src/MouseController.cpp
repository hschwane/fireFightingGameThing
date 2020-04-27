/*
 * fireFightingGameThing
 * MouseController.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the MouseController class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "MouseController.h"
//--------------------

// namespace
//--------------------
namespace ip = mpu::gph::Input;
//--------------------

// function definitions of the MouseController class
//-------------------------------------------------------------------
MouseController::MouseController(mpu::gph::Window& wnd)
    : m_wnd(wnd)
{
    // -------------------------------------------
    // use the input manager to define some input functions

    // move camera by dragging middle mouse button
    ip::addAxis("CameraDragHorizontal","Drags the camera with the mouse.",[this](mpu::gph::Window& wnd, double v)
    {
        this->m_cameraDragVelocity.x += v;
    });

    ip::addAxis("CameraDragVertical","Drags the camera with the mouse.",[this](mpu::gph::Window& wnd, double v)
    {
        this->m_cameraDragVelocity.y += v;
    });

    ip::mapCourserToInput("CameraDragHorizontal",ip::AxisOrientation::horizontal,ip::AxisBehavior::positive,0,"EnableMouseDrag");
    ip::mapCourserToInput("CameraDragVertical",ip::AxisOrientation::vertical,ip::AxisBehavior::negative,0,"EnableMouseDrag");
    ip::mapMouseButtonToInput("EnableMouseDrag",GLFW_MOUSE_BUTTON_3);

    ip::setModifierStateChangeCallback("EnableMouseDrag",[this](bool enable)
    {
        if(!enable)
            this->m_cameraDragVelocity = {0,0};
    });

    // selection

    ip::addButton("BeginSelection","Begin a selection.",[&](const mpu::gph::Window& wnd)
    {

    });

    ip::addButton("EndSelection","End a selection.",[&](const mpu::gph::Window& wnd)
    {

    });

}

void MouseController::update()
{
    // get cursor position
    glm::dvec2 cPos = m_wnd.get().getCursorPos();
    glm::vec2 wndSize = m_wnd.get().getSize();
    bool hovered = true; // will be set to false is mouse is not above the window

    // trap cursor in window
    if( m_trapCursor )
    {
        cPos = glm::clamp(cPos, {0,0}, glm::dvec2(wndSize) );
        m_wnd.get().setCursorPos(cPos);
    }
    else
        hovered = (ip::getHoveredWindow() == &m_wnd.get());

    // scroll by moving mouse to edge of screen
    glm::vec2 edgeScrollMovement{0,0};
    if(hovered)
    {
        if(cPos.x < 8)
            edgeScrollMovement.x = -m_cameraEdgeScrollSpeed;
        else if(cPos.x > wndSize.x - 8)
            edgeScrollMovement.x = m_cameraEdgeScrollSpeed;
        if(cPos.y < 8)
            edgeScrollMovement.y = m_cameraEdgeScrollSpeed;
        else if(cPos.y > wndSize.y - 8)
            edgeScrollMovement.y = -m_cameraEdgeScrollSpeed;
    }

    // move camera by dragging middle mouse button and edge scrolling
    m_thisFrameCameraMovement = glm::min( glm::vec2(m_cameraDragSpeedLimit),
            m_cameraDragSensitivity*m_cameraDragVelocity+edgeScrollMovement) * ip::deltaTime();
}
