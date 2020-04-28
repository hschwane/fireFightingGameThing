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

//!< state of a mouse selection
enum class SelectionState
{
    none,
    inProgress,
    completed,
    canceled
};

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

    void setViewProjection(glm::mat4 viewProjection); //!<  pass viewProjection of the world currently visible
    void update(); //!< perform regular work and update values (call before everything else)
    void lateUpdate(); //!< performs regular work after (call after everything else)
//    void draw(mpu::gph::Renderer2D& renderer); //!< draws mouse cursor and selection overlays

    // camera movement
    glm::vec2 getCameraMovement() {return m_thisFrameCameraMovement;} //!< returns camera movement based on mouse inputs from current frame

    // mouse position
    bool isMouseOverWorld() const {return m_mouseOverWindow;} //!< is mouse above the world (is above window and no user interface is inbetween)?
    glm::vec2 getMousePosWorld() const {return m_worldMousePos;} //!< get cursor position in world coordinates

    // dragging selection
    SelectionState selectionState() const {return m_selectionState;} //!< is a selection currently in progress?
    glm::vec2 selctionBeginPos() const {return m_beginPosition;} //!< position where last drag started
    glm::vec2 selectionEndPos() const {return m_endPosition;} //!< on completed drags the end position is available here

    // single click selection
    bool singleClickSelection() const {return m_singleClickSelecion;} //!< if true user performed single click into world (could also be beginning of drag)

    // right click selection
    bool rightClickSelection() const {return m_rightClickSelection;} //!< if true user performed right click into the world

    // double click selection
    bool doubleClickSelection() const {return m_doubleClickSelection;} // if true user performed double click into the world

private:

    // main data
    std::reference_wrapper<mpu::gph::Window> m_wnd; //!< the main window
    glm::mat4 m_viewProjection; //!< matrix used to project the current image
    glm::ivec2 m_windowSize; //!< size of the main window
    glm::ivec4 m_viewport; //!< the currently active viewport

    // mouse position handling
    glm::vec2 m_worldMousePos; //!< mouse position in world coordinates
    bool m_mouseOverWindow; //!< is the mouse over our window and the window is active?

    // selection handling
    SelectionState m_selectionState{SelectionState::none}; //!< is player currently dragging a selection
    glm::vec2 m_beginPosition; //!< position where last drag began
    glm::vec2 m_endPosition; //!< end position of a completed selection
    bool m_singleClickSelecion{false};
    bool m_doubleClickSelection{false};
    bool m_rightClickSelection{false};

    // camera movement using mouse
    glm::vec2 m_cameraDragVelocity{0,0}; //!< speed with which camera is dragged
    glm::vec2 m_thisFrameCameraMovement{0,0}; //!< camera movement based on mouse during current frame

    // settings
    float m_cameraDragSensitivity{0.3}; //!< sensitivity of camera dragging
    float m_cameraDragSpeedLimit{50.0}; //!< sensitivity of camera dragging
    float m_cameraEdgeScrollSpeed{20.0}; //!< how fast the camera will scroll when mouse is touching border of the screen
    bool m_trapCursor{false}; //!< trap cursor in window
};


#endif //FIREFIGHTINGGAMETHING_MOUSECONTROLLER_H
