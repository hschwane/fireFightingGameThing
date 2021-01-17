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

int TileType::selectVariant(float r) const
{
    float p = 0;
    for(int i = 0; i < m_frequencies.size(); ++i)
    {
        p += m_frequencies[i];
        if(r <= p)
            return i;
    }
    return 0;
}

TileData::TileData(const std::string& toml)
{
    std::istringstream stream(toml);
    auto parsedData = toml::parse(stream);
    auto& tile = toml::find(parsedData, "Tile");

    displayName = toml::find<std::string>(tile, "displayName");
    contentPack = toml::find<std::string>(tile, "contentPack");
    spriteFilenames = toml::find<std::vector<std::string>>(tile, "sprites");
    transitionFilenames = toml::find_or<std::vector<std::string>>(tile, "transitions", std::vector<std::string>());

    for(const auto& item : transitionFilenames)
    {
        std::cout << item << std::endl;
    }

    frequencies = toml::find_or<std::vector<float>>(tile, "frequencies",
                                                    std::vector<float>(transitionFilenames.size(),
                                                                       1.0 / transitionFilenames.size()));
    precedence = toml::find<float>(tile, "precedence");
}

toml::value TileData::toToml()
{
    toml::value dn(displayName);
    toml::value cp(contentPack);
    toml::value sn(spriteFilenames);
    toml::value tn(transitionFilenames);
    toml::value fr(frequencies);
    toml::value pd(precedence);

    toml::value table({{"precedence",  pd},
                       {"transitions", sn},
                       {"frequencies", fr},
                       {"sprites",     sn},
                       {"contentPack", cp},
                       {"displayName", dn}});
    return toml::value({{"Tile", table}});
}
