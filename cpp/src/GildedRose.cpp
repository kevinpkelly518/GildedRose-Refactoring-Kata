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

    if (item.sellIn >= 0) {
        item.quality = item.quality < 50 ? item.quality + 1 : item.quality;
    } else {
        item.quality = item.quality < 50 ? item.quality + 2 : item.quality;
    }
}

ConjuredUpdater::ConjuredUpdater(const Item& item) : ItemUpdater(item) {}

void ConjuredUpdater::update() {
    item.sellIn = item.sellIn - 1;

    if (item.sellIn >= 0) {
        item.quality = item.quality > 1 ? item.quality - 2 : 0;
    } else {
        item.quality = item.quality > 3 ? item.quality - 4 : 0;
    }
}

LegendaryUpdater::LegendaryUpdater(const Item& item) : ItemUpdater(item) {}

void LegendaryUpdater::update() {}

StandardUpdater::StandardUpdater(const Item& item) : ItemUpdater(item) {}

void StandardUpdater::update() {
    item.sellIn = item.sellIn - 1;

    if (item.sellIn >= 0) {
        item.quality = item.quality > 0 ? item.quality - 1 : 0;
    } else {
        item.quality = item.quality > 1 ? item.quality - 2 : 0;
    }
}

TicketUpdater::TicketUpdater(const Item& item) : ItemUpdater(item) {}

void TicketUpdater::update() {
    item.sellIn = item.sellIn - 1;

    if (item.sellIn < 0) {
        item.quality = 0;
    } else if (item.sellIn < 5) {
        item.quality = item.quality < 48 ? item.quality + 3 : 50;
    } else if (item.sellIn < 10) {
        item.quality = item.quality < 49 ? item.quality + 2 : 50;
    } else {
        item.quality = item.quality < 50 ? item.quality + 1 : 50;
    }
}

std::unique_ptr<ItemUpdater> create_item_updater(const Item& item) {
    if (item.name == "Aged Brie") {
        return std::move(std::make_unique<CheeseUpdater>(item));
    }

    if (item.name.find("Conjured") != std::string::npos) {
        return std::move(std::make_unique<ConjuredUpdater>(item));
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
