/*
 * fireFightingGameThing
 * TileType.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the TileType class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_TILETYPE_H
#define FIREFIGHTINGGAMETHING_TILETYPE_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
//--------------------

//-------------------------------------------------------------------
/**
 * class TileType
 *
 * a type of tile used on the map
 *
 */
class TileType
{
public:
    //!< create a new tile type using textures
    TileType(std::string refName, std::vector<std::shared_ptr<mpu::gph::Sprite2D>> spriteVariants,
             std::vector<float> frequencies, std::vector<std::shared_ptr<mpu::gph::Sprite2D>> spriteTransitions,
             float precedence)
            : m_displayName(std::move(refName)), m_spriteVariants(spriteVariants),
              m_frequencies(frequencies), m_spriteTransitions(spriteTransitions),
              m_precedence(precedence)
    {
        for(const auto& ptr : m_spriteVariants)
            assert_critical(ptr, "TileType", "Constructing TileType" + refName + "from nullptr sprite!");
        for(const auto& ptr : m_spriteTransitions)
            assert_critical(ptr, "TileType", "Constructing TileType" + refName + " from nullptr sprite!");
    }

    //!< create a simple tile without variants or transitions
    TileType(std::string refName, std::shared_ptr<mpu::gph::Sprite2D> displaySprite)
            : m_displayName(std::move(refName)), m_precedence(0)
    {
        assert_critical(displaySprite, "TileType", "Constructing TileType from nullptr sprite!");
        m_spriteVariants.push_back(displaySprite);
        m_frequencies.push_back(1.0);
    }

    const std::string& getName() const { return m_displayName; } //!< the name of this tile type in the user interface
    int getNumVariants() const { return m_spriteVariants.size(); } //!< the number of different variants of this tile
    int selectVariant(float r) const; //!< pass random number to select a variant according to frequency
    const mpu::gph::Sprite2D&
    getSprite(int i) const { return *m_spriteVariants[i]; } //!< the sprite that this tile uses for rendering
    const mpu::gph::Sprite2D&
    getTransition(int i) const { *m_spriteTransitions[i]; } //!< returns the transitional sprite
    bool hasTransitions() const { return !m_spriteTransitions.empty(); } //!< chack if transitions are available
    float
    getPrecedence() const { return m_precedence; } //!< [0,1)tiles with higher precedence are displayed on top in transitions

private:
    std::string m_displayName; //!< the name of the tile as displayed in the ui
    std::vector<std::shared_ptr<mpu::gph::Sprite2D>> m_spriteVariants; //!< list of sprites for randomization
    std::vector<float> m_frequencies; //!< frequencies of the different tile variants
    std::vector<std::shared_ptr<mpu::gph::Sprite2D>> m_spriteTransitions; //!< transitional sprites#
    float m_precedence; //!< tiles with higher precedence are displayed on top in transitions
};

//-------------------------------------------------------------------
// helper functions to load and store tiles
/**
 * class TileData
 * @brief stores all data from a .tile file and can read from a string / store into a string
 *          errors during parsing will throw an exception
 */
class TileData
{
public:
    TileData() = default;
    explicit TileData(const std::string& toml);
    toml::value toToml();

    std::string displayName;
    std::string contentPack;
    std::vector<std::string> spriteFilenames;
    std::vector<float> frequencies;
    std::vector<std::string> transitionFilenames;
    float precedence;
};

#endif //FIREFIGHTINGGAMETHING_TILETYPE_H
