/*
 * fireFightingGameThing
 * Sprite.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the Sprite class
 *
 * Copyright (c) 2019 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "SpriteRenderer.h"
//--------------------

// namespace
//--------------------
namespace SpriteRenderer {
//--------------------

// function definitions of the Sprite class
//-------------------------------------------------------------------

namespace {
    mpu::gph::ShaderProgram& shader()
    {
        static mpu::gph::ShaderProgram m_shader({{PROJECT_SHADER_PATH "sprite.vert"},
                                                 {PROJECT_SHADER_PATH "sprite.frag"}});
        return m_shader;
    };
}

void setProjection(const glm::mat4& proj)
{
    shader().uniformMat4("proj",proj);
}

void drawSprite(mpu::gph::Texture& tex, const glm::vec2& size, const glm::vec2& pos, float rotation)
{
    // build model matrix
    glm::mat4 model(1);
    model =  glm::translate(model, glm::vec3(pos,0.0f));
    model =  glm::rotate(model, rotation,glm::vec3{0.0f,0.0f,1.0f});
    model = glm::scale(model, glm::vec3(size,0.0f));
//
    // setup shader
    shader().use();
    tex.bind(GL_TEXTURE0,GL_TEXTURE_2D);
    shader().uniformMat4("model",model);

    // draw (positions are calculated in the shader)
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
}

}