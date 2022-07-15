#pragma once

#include "Item.hpp"

#include <vector>


namespace GildedRose {


class GildedRose {
public:
    GildedRose(std::vector<Item>&& items);

    void update();

    bool empty() const;
    std::vector<Item>::const_iterator get_item(const std::string& name) const;

private:
    std::vector<Item> items;
};


} // end namespace GildedRose
