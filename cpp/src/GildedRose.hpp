#pragma once

#include "Item.hpp"

#include <memory>
#include <vector>


namespace GildedRose {


class ItemUpdater {
public:
    ItemUpdater(const Item& item);
    ~ItemUpdater() = default;

    virtual void update() = 0;

    std::string name() const;
    int sell_in() const;
    int quality() const;

protected:
    Item item;
};

class CheeseUpdater : public ItemUpdater {
public:
  CheeseUpdater(const Item& item);

  void update() override;
};

class ConjuredUpdater : public ItemUpdater {
public:
  ConjuredUpdater(const Item& item);

  void update() override;
};

class LegendaryUpdater : public ItemUpdater {
public:
  LegendaryUpdater(const Item& item);

  void update() override;
};

class StandardUpdater : public ItemUpdater {
public:
  StandardUpdater(const Item& item);

  void update() override;
};

class TicketUpdater : public ItemUpdater {
public:
  TicketUpdater(const Item& item);

  void update() override;
};

std::unique_ptr<ItemUpdater> create_item_updater(const Item& name);

class GildedRose {
public:
    GildedRose(const std::vector<Item>& items);

    void update();

    bool empty() const;
    int get_sell_in(const std::string& name) const;
    int get_quality(const std::string& name) const;

private:
    std::vector<std::unique_ptr<ItemUpdater>> items;
};


} // end namespace GildedRose
