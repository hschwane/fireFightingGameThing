/*
 * fireFightingGameThing
 * InGame.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the InGame class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_FREEPLAY_H
#define FIREFIGHTINGGAMETHING_FREEPLAY_H

// includes
//--------------------
#include "gameState.h"
#include "Operation.h"
//--------------------

//-------------------------------------------------------------------
/**
 * class FreePlay
 *
 * Manages playing in free play mode.
 *
 */
class FreePlay : public GameStateBase
{
public:

    FreePlay();

    void onActivation() override;
    void onDeactivation() override;
    void handleImGui() override;
    void update(MouseController& mc) override;
    void draw(mpu::gph::Renderer2D& renderer, MouseController& mc) override;

private:
    void addKeybindings(); //!< add hotkeys and camera controles

    mpu::gph::Camera2D m_playerCamera; //!< camera with which the player looks at the world
    std::unique_ptr<Operation> m_currentOperation;

    const RootedObject* m_currentlyHoveredObject{nullptr};
    const TileType* m_currentlyHoveredTileType{nullptr};
};


#endif //FIREFIGHTINGGAMETHING_FREEPLAY_H
