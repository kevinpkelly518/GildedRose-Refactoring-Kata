#pragma once

#include "Item.hpp"

#include <vector>


namespace GildedRose {


class GildedRose {
public:
    GildedRose(std::vector<Item>&& items);

    void update();

    std::vector<Item> items;
};


} // end namespace GildedRose
