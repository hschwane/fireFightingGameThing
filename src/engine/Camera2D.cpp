/*
 * fireFightingGameThing
 * Camera2D.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the Camera2D class
 *
 * Copyright (c) 2019 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "Camera2D.h"
#include <random>
//--------------------

// namespace
//--------------------

//--------------------

// function definitions of the Camera2D class
//-------------------------------------------------------------------

int Camera2D::id = 0;

Camera2D::Camera2D(float aspectRatio,float moveSpeed,float zoomSpeed)
                : m_pos(0,0), m_zoom(1), m_aspect(aspectRatio), m_zoomSpeed(zoomSpeed), m_moveSpeed(moveSpeed),
                m_zoomBoundry(0.2,10), m_moveBoundary(0,0,0,0)
{
    int myId = id++;

    using namespace mpu::gph;

    // configure inputs
    Input::addAxis("Horizontal Camera Move ##"+mpu::toString(id), "Moves the camera along x axis.", [this](Window& wnd, double v)
    {
       this->m_pos.x += m_moveSpeed * v;

       if(m_moveBoundary.x != m_moveBoundary.z)
       {
           this->m_pos.x = std::fmax(m_moveBoundary.x, std::fmin(m_moveBoundary.z, this->m_pos.x));
       }
    });

    Input::addAxis("Vertical Camera Move ##"+mpu::toString(id), "Moves the camera along y axis.", [this](Window& wnd, double v)
    {
        this->m_pos.y += m_moveSpeed * v;
        if(m_moveBoundary.y != m_moveBoundary.w)
            this->m_pos.y = std::fmax(m_moveBoundary.y, std::fmin(m_moveBoundary.w, this->m_pos.y));
    });

    Input::addAxis("Camera Zoom ##"+mpu::toString(id), "Moves the camera closer.", [this](Window& wnd, double v)
    {
        this->m_zoom -= std::sqrt(std::abs(this->m_zoom)) * m_zoomSpeed * v;
        this->m_zoom = std::fmin( m_zoomBoundry.y, std::fmax( m_zoomBoundry.x, this->m_zoom));
    });

    Input::mapKeyToInput("Horizontal Camera Move ##"+mpu::toString(id),GLFW_KEY_D,0, Input::ButtonBehavior::defaultBehavior, Input::AxisBehavior::positive);
    Input::mapKeyToInput("Horizontal Camera Move ##"+mpu::toString(id),GLFW_KEY_A,0, Input::ButtonBehavior::defaultBehavior, Input::AxisBehavior::negative);
    Input::mapKeyToInput("Vertical Camera Move ##"+mpu::toString(id),GLFW_KEY_W,0, Input::ButtonBehavior::defaultBehavior, Input::AxisBehavior::positive);
    Input::mapKeyToInput("Vertical Camera Move ##"+mpu::toString(id),GLFW_KEY_S,0, Input::ButtonBehavior::defaultBehavior, Input::AxisBehavior::negative);
    Input::mapScrollToInput("Camera Zoom ##"+mpu::toString(id));
}

glm::mat4 Camera2D::getProj()
{
    return glm::ortho(-m_zoom + m_pos.x, m_zoom + m_pos.x, -m_zoom/m_aspect + m_pos.y, m_zoom/m_aspect + m_pos.y);
}

void Camera2D::update()
{


}

void Camera2D::drawGui()
{
    ImGui::Begin("Camera");

    ImGui::Text("Position: %s", glm::to_string(m_pos).c_str());
    ImGui::Text("Zoom Level: %f", m_zoom);
    ImGui::Text("Aspect Ratio: %f", m_aspect);
    ImGui::Text("Zoom Bounds: %s", glm::to_string(m_zoomBoundry).c_str());
    ImGui::Text("Move Bounds: %s", glm::to_string(m_moveBoundary).c_str());

    ImGui::SliderFloat("ZoomSpeed",&m_zoomSpeed,0.01,2);
    ImGui::SliderFloat("MoveSpeed",&m_moveSpeed,0.001,1.5);

    ImGui::End();
}


