#include "GildedRose.hpp"

#include <algorithm>
#include <stdexcept>


namespace {





} // end namespace


namespace GildedRose {


ItemUpdater::ItemUpdater(const Item& item) : item(item) {}

std::string ItemUpdater::name() const {
    return item.name;
}

int ItemUpdater::sell_in() const {
    return item.sellIn;
}

int ItemUpdater::quality() const {
    return item.quality;
}

CheeseUpdater::CheeseUpdater(const Item& item) : ItemUpdater(item) {}

void CheeseUpdater::update() {
    item.sellIn = item.sellIn - 1;

    if (item.quality < 50) {
        item.quality = item.quality + 1;
    }

    if (item.sellIn < 0) {
        if (item.quality < 50) {
            item.quality = item.quality + 1;
        }
    }
}

LegendaryUpdater::LegendaryUpdater(const Item& item) : ItemUpdater(item) {}

void LegendaryUpdater::update() {}

StandardUpdater::StandardUpdater(const Item& item) : ItemUpdater(item) {}

void StandardUpdater::update() {
    item.sellIn = item.sellIn - 1;

    if (item.quality > 0) {
        item.quality = item.quality - 1;
    }

    if (item.sellIn < 0) {
        if (item.quality > 0) {
            item.quality = item.quality - 1;
        }
    }
}

TicketUpdater::TicketUpdater(const Item& item) : ItemUpdater(item) {}

void TicketUpdater::update() {
    item.sellIn = item.sellIn - 1;

    if (item.quality < 50) {
        item.quality = item.quality + 1;

        if (item.sellIn < 10) {
            if (item.quality < 50) {
                item.quality = item.quality + 1;
            }
        }

        if (item.sellIn < 5) {
            if (item.quality < 50) {
                item.quality = item.quality + 1;
            }
        }
    }

    if (item.sellIn < 0) {
        item.quality = 0;
    }
}

std::unique_ptr<ItemUpdater> create_item_updater(const Item& item) {
    if (item.name == "Aged Brie") {
        return std::move(std::make_unique<CheeseUpdater>(item));
    }

    if (item.name == "Sulfuras, Hand of Ragnaros") {
        return std::move(std::make_unique<LegendaryUpdater>(item));
    }

    if (item.name == "Backstage passes to a TAFKAL80ETC concert") {
        return std::move(std::make_unique<TicketUpdater>(item));
    }

    return std::move(std::make_unique<StandardUpdater>(item));
}

GildedRose::GildedRose(const std::vector<Item>& items) {
    for (const auto& item : items) {
        this->items.push_back(std::move(create_item_updater(item)));
    }
}

void GildedRose::update() {
    for (const auto& item : items) {
        item->update();
    }
}

bool GildedRose::empty() const {
    return items.empty();
}

int GildedRose::get_sell_in(const std::string& name) const {
    const auto item_it = std::find_if(
        items.begin(), items.end(), [&name](const std::unique_ptr<ItemUpdater>& item) { return item->name() == name; }
    );

    if (item_it == items.end()) {
        throw std::runtime_error{"Item not found"};
    }

    return (*item_it)->sell_in();
}

int GildedRose::get_quality(const std::string& name) const {
    const auto item_it = std::find_if(
        items.begin(), items.end(), [&name](const std::unique_ptr<ItemUpdater>& item) { return item->name() == name; }
    );

    if (item_it == items.end()) {
        throw std::runtime_error{"Item not found"};
    }

    return (*item_it)->quality();
}


} // end namespace GildedRose
