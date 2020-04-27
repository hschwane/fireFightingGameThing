/*
 * fireFightingGameThing
 * MouseController.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the MouseController class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_MOUSECONTROLLER_H
#define FIREFIGHTINGGAMETHING_MOUSECONTROLLER_H

// includes
//--------------------
#include <vector>
#include <functional>
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
//--------------------

//-------------------------------------------------------------------
/**
 * class MouseController
 *
 * handles mouse input like selection, mouse-over and scrolling
 * Raw mouse input is available from the window and "Input" class.
 *
 */
class MouseController
{
public:
    MouseController(mpu::gph::Window& wnd);

    void update();

    glm::vec2 getCameraMovement() {return m_thisFrameCameraMovement;} //!< returns camera movement based on mouse inputs from current frame

    void getTileUnderMouse()
    {

    }

//    int addSelectionCallback();
//    void removeSelectionCallback(int id);

private:
//    std::vector<std::function<void()>>
    glm::vec2 m_cameraDragVelocity{0,0}; //!< speed with which camera is dragged
    glm::vec2 m_thisFrameCameraMovement{0,0}; //!< camera movement based on mouse during current frame

    std::reference_wrapper<mpu::gph::Window> m_wnd;

    // settings
    float m_cameraDragSensitivity{0.3}; //!< sensitivity of camera dragging
    float m_cameraDragSpeedLimit{50.0}; //!< sensitivity of camera dragging
    float m_cameraEdgeScrollSpeed{20.0}; //!< how fast the camera will scroll when mouse is touching border of the screen
    bool m_trapCursor{false}; //!< trap cursor in window
};


#endif //FIREFIGHTINGGAMETHING_MOUSECONTROLLER_H
