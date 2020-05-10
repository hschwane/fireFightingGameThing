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
    // get the size of the window and make sure it is updated
    m_windowSize = m_wnd.get().getSize();
    m_viewport = {0,0,m_windowSize};
    m_wnd.get().addSizeCallback([this](int x, int y)
    {
        this->m_windowSize = {x,y};
        this->m_viewport = {0,0,m_windowSize};
    });

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

    // selection of things in the world
    ip::addButton("BeginSelection","Begin a selection.",[this](const mpu::gph::Window& wnd)
    {
        // handle beginning of drag selection
        glm::dvec2 cPos = m_wnd.get().getCursorPos();
        m_beginPosition = mpu::gph::mouseToWorld2D( cPos, m_viewport, m_viewProjection);
        this->m_selectionState = SelectionState::inProgress;
        m_singleClickSelecion = true;
    });

    ip::addButton("CancelDragSelection","Cancel a selection.",[this](const mpu::gph::Window& wnd)
    {
        this->m_selectionState = SelectionState::canceled;
        logDEBUG("MouseController") << "selection canceled";
    });

    ip::addButton("EndDragSelection","End a selection.",[this](const mpu::gph::Window& wnd)
    {
        if(this->m_selectionState == SelectionState::inProgress)
        {
            glm::dvec2 cPos = m_wnd.get().getCursorPos();
            m_endPosition = mpu::gph::mouseToWorld2D(cPos, m_viewport, m_viewProjection);
            this->m_selectionState = SelectionState::completed;
            logDEBUG("MouseController") << "selection complete " << glm::to_string(this->selctionBeginPos())
                                        << " -> " << glm::to_string(this->selectionEndPos());
        }
    });

    ip::mapMouseButtonToInput("BeginSelection",GLFW_MOUSE_BUTTON_1,ip::ButtonBehavior::onPress);
    ip::mapMouseButtonToInput("EndDragSelection",GLFW_MOUSE_BUTTON_1,ip::ButtonBehavior::onRelease);
    ip::mapMouseButtonToInput("CancelDragSelection",GLFW_MOUSE_BUTTON_2,ip::ButtonBehavior::onPress);

    // right click selection
    ip::addButton("RightClickSelection","Selection by right click.",[this](const mpu::gph::Window& wnd)
    {
        m_rightClickSelection = true;
    });
    ip::mapMouseButtonToInput("RightClickSelection",GLFW_MOUSE_BUTTON_2,ip::ButtonBehavior::onPress);

    // double click selection
    ip::addButton("DoubleClickSelection","Selection by double click.",[this](const mpu::gph::Window& wnd)
    {
        m_doubleClickSelection = true;
    });
    ip::mapMouseButtonToInput("DoubleClickSelection",GLFW_MOUSE_BUTTON_1,ip::ButtonBehavior::onDoubleClick);

}

void MouseController::setViewProjection(glm::mat4 viewProjection)
{
    m_viewProjection = viewProjection;
}

void MouseController::update()
{
    // get cursor position
    glm::dvec2 cPos = m_wnd.get().getCursorPos();
    m_mouseOverWindow = (ip::getActiveWindow() == &m_wnd.get());

    // trap cursor in window
    if( m_trapCursor )
    {
        cPos = glm::clamp(cPos, {0,0}, glm::dvec2(m_windowSize) );
        m_wnd.get().setCursorPos(cPos);
    }
    else
        m_mouseOverWindow = m_mouseOverWindow && (ip::getHoveredWindow() == &m_wnd.get());

    // scroll by moving mouse to edge of screen
    glm::vec2 edgeScrollMovement{0,0};
    if(m_mouseOverWindow || m_selectionState == SelectionState::inProgress)
    {
        if(cPos.x < 8)
            edgeScrollMovement.x = -m_cameraEdgeScrollSpeed;
        else if(cPos.x > m_windowSize.x - 8)
            edgeScrollMovement.x = m_cameraEdgeScrollSpeed;
        if(cPos.y < 8)
            edgeScrollMovement.y = m_cameraEdgeScrollSpeed;
        else if(cPos.y > m_windowSize.y - 8)
            edgeScrollMovement.y = -m_cameraEdgeScrollSpeed;
    }

    // move camera by dragging middle mouse button and edge scrolling
    m_thisFrameCameraMovement = glm::min( glm::vec2(m_cameraDragSpeedLimit),
            m_cameraDragSensitivity*m_cameraDragVelocity+edgeScrollMovement) * ip::deltaTime();

    // calculate mouse world position
    m_worldMousePos = mpu::gph::mouseToWorld2D( cPos, m_viewport, m_viewProjection);
}

void MouseController::lateUpdate()
{
    if(m_selectionState != SelectionState::inProgress)
        m_selectionState = SelectionState::none;

    m_singleClickSelecion = false;
    m_doubleClickSelection = false;
    m_rightClickSelection = false;
}
