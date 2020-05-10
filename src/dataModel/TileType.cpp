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
    auto& sprite = toml::find(parsedData,"Tile");

    displayName = toml::find<std::string>(sprite, "displayName");
    contentPack = toml::find<std::string>(sprite, "contentPack");
    spriteFilename = toml::find<std::string>(sprite, "sprite");
}

toml::value TileData::toToml()
{
    toml::value dn(displayName);
    toml::value cp(contentPack);
    toml::value sn(spriteFilename);

    toml::value table({{"sprite",sn},{"contentPack",cp},{"displayName",dn}});
    return toml::value( { {"Tile",table} } );
}
