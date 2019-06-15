/*
 * fireFightingGameThing
 * Camera2D.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the Camera2D class
 *
 * Copyright (c) 2019 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_CAMERA2D_H
#define FIREFIGHTINGGAMETHING_CAMERA2D_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
//--------------------

//-------------------------------------------------------------------
/**
 * class Camera2D
 *
 * usage:
 *
 */
class Camera2D
{
public:
    Camera2D(float aspectRatio,float moveSpeed,float zoomSpeed);
    glm::mat4 getProj();
    void update();
    void drawGui();

    void setAspect(float aspect) {m_aspect = aspect;}
    void setPosition(glm::vec2 pos) {m_pos = pos;}
    void setZoom(float zoom) {m_zoom=zoom;}
    void setMoveSpeed(float moveSpeed) {m_moveSpeed = moveSpeed;}
    void setZoomSpeed(float zoomSpeed) {m_zoomSpeed = zoomSpeed;}
    void setMoveBoundary(const glm::vec4 &moveBoundary) {m_moveBoundary = moveBoundary;}
    void setZoomBoundry(const glm::vec2 &zoomBoundry) {m_zoomBoundry = zoomBoundry;}

    float getMoveSpeed() const {return m_moveSpeed;}
    float getZoomSpeed() const {return m_zoomSpeed;}
    const glm::vec2& getPosition() const { return m_pos;}
    float getZoom() const { return m_zoom;}
    const glm::vec4 &getMoveBoundary() const { return m_moveBoundary;}
    const glm::vec2 &getZoomBoundry() const { return m_zoomBoundry;}

private:
    static int id;
    glm::vec2 m_pos;
    float m_zoom;
    float m_moveSpeed;
    float m_zoomSpeed;

    glm::vec4 m_moveBoundary;
    glm::vec2 m_zoomBoundry;


    float m_aspect;
};


#endif //FIREFIGHTINGGAMETHING_CAMERA2D_H
