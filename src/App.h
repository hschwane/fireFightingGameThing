/*
 * fireFightingGameThing
 * AppState.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the AppState class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_APP_H
#define FIREFIGHTINGGAMETHING_APP_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
//--------------------

// namespace
//--------------------
//-------------------------------------------------------------------
/**
 * encasulates the current global state of the application and provides facilities to all scenes
 */
namespace App {
//--------------------

inline mpu::gph::Window& getMainWnd()
{
    static mpu::gph::Window _mainWnd(10,10,"");
    return _mainWnd;
}

inline mpu::gph::Renderer2D& getRenderer()
{
    static mpu::gph::Renderer2D _renderer;
    return _renderer;
};

inline mpu::gph::SceneManager& getSceneManager()
{
    static mpu::gph::SceneManager _sceneManager;
    return _sceneManager;
}

}

#endif //FIREFIGHTINGGAMETHING_APP_H
