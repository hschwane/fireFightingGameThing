/*
 * fireFightingGameThing
 * GameObject.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the GameObject class
 *
 * Copyright (c) 2019 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_GAMEOBJECT_H
#define FIREFIGHTINGGAMETHING_GAMEOBJECT_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
//--------------------

//-------------------------------------------------------------------
/**
 * class GameObject
 *
 * usage:
 *
 */
class GameObject
{
public:
    GameObject(std::string texFile, const glm::vec2& size);
    virtual ~GameObject() = default;


    virtual void update(){}
    virtual void draw();

protected:
    glm::vec2 m_pos;
    glm::vec2 m_size;
    float m_rotation;

private:
    mpu::gph::Texture m_tex;
};


#endif //FIREFIGHTINGGAMETHING_GAMEOBJECT_H
