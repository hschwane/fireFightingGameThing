/*
 * fireFightingGameThing
 * TileType.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "TileType.h"
//--------------------

TileData::TileData(const std::string& toml)
{
    std::istringstream stream(toml);
    auto parsedData = toml::parse(stream);
    auto& tile = toml::find(parsedData, "Tile");

    displayName = toml::find<std::string>(tile, "displayName");
    contentPack = toml::find<std::string>(tile, "contentPack");
    spriteFilenames = toml::find<std::vector<std::string>>(tile, "sprites");
    transitionFilenames = toml::find_or<std::vector<std::string>>(tile, "transitions", std::vector<std::string>());
    precedence = toml::find<float>(tile, "precedence");
}

toml::value TileData::toToml()
{
    toml::value dn(displayName);
    toml::value cp(contentPack);
    toml::value sn(spriteFilenames);
    toml::value tn(transitionFilenames);
    toml::value pd(precedence);

    toml::value table({{"precedence",  pd},
                       {"transitions", sn},
                       {"sprites",     sn},
                       {"contentPack", cp},
                       {"displayName", dn}});
    return toml::value({{"Tile", table}});
}
