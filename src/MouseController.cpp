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
    // move camera by dragging middle mouse button
    m_thisFrameCameraMovement = glm::min(glm::vec2(m_cameraDragSpeedLimit),m_cameraDragSensitivity*m_cameraDragVelocity) * ip::deltaTime();

    // trap cursor in window
    if( ip::getHoveredWindow() == nullptr && m_trapCursor )
    {

    }
}
