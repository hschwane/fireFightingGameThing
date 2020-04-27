/*
 * fireFightingGameThing
 * GameStateBase.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the GameStateBase class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_GAMESTATE_H
#define FIREFIGHTINGGAMETHING_GAMESTATE_H

// includes
//--------------------
#include "mpUtils/mpUtils.h"
#include "mpUtils/mpGraphics.h"
#include "MouseController.h"
//--------------------

enum class GameState
{
//    splash,
//    mainMenue,
    mapEditor
};

// create alias for game state machine
class GameStateBase;
using GameStateManager = mpu::StateMachine<GameState,GameStateBase>;

//-------------------------------------------------------------------
/**
 * class GameStateBase
 *
 * base class for game states
 *
 */
class GameStateBase
{
public:
    virtual ~GameStateBase()=default;
    virtual void onActivation()=0;
    virtual void onDeactivation()=0;
    virtual void handleImGui()=0;
    virtual void update(MouseController& mouseController)=0;
    virtual void draw(mpu::gph::Renderer2D& renderer)=0;

    void setStateMachine(GameStateManager* sm) {m_gameStateManager = sm;}

protected:
    GameStateManager* m_gameStateManager{nullptr}; //!< this will be set to a valid value before onActivate is called
};


#endif //FIREFIGHTINGGAMETHING_GAMESTATE_H
