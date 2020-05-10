/*
 * fireFightingGameThing
 * RootedObject.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the RootedObject class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "RootedObjectType.h"
//--------------------

// function definitions of the RootedObject class
//-------------------------------------------------------------------

RootedObjectData::RootedObjectData(const std::string& toml)
{
    std::istringstream stream(toml);
    auto parsedData = toml::parse(stream);
    auto& sprite = toml::find(parsedData,"Tile");

    displayName = toml::find<std::string>(sprite, "displayName");
    contentPack = toml::find<std::string>(sprite, "contentPack");
    spriteFilename = toml::find<std::string>(sprite, "sprite");
}

toml::value RootedObjectData::toToml()
{
    toml::value dn(displayName);
    toml::value cp(contentPack);
    toml::value sn(spriteFilename);

    toml::value table({{"sprite",sn},{"contentPack",cp},{"displayName",dn}});
    return toml::value( { {"Tile",table} } );
}
