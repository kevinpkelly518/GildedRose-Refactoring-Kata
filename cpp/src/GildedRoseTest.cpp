#include "doctest.h"

#include "GildedRose.hpp"


namespace {


void check_update(const Item& item, int expect_sell_in, int expect_quality) {
  GildedRose::GildedRose gilded_rose{{item}};

  gilded_rose.updateQuality();

  CHECK(gilded_rose.get_item(item.name)->sellIn == expect_sell_in);
  CHECK(gilded_rose.get_item(item.name)->quality == expect_quality);
}


} // end namespace


TEST_CASE("Update Does Nothing") {
  GildedRose::GildedRose gilded_rose{{}};

  gilded_rose.updateQuality();

  CHECK(gilded_rose.empty());
}

TEST_CASE("Unclear Behavior") {
  check_update({"Sulfuras, Hand of Ragnaros", 0, 0}, 0, 0);
  check_update({"Aged Brie", 1, 51}, 0, 51);
  check_update({"Backstage passes to a TAFKAL80ETC concert", 1, 51}, 0, 51);
  check_update({"Item", 1, 52}, 0, 51);
  check_update({"Backstage passes to a Jon Bellion concert", 1, 50}, 0, 49);
  check_update({"Aged Brie", 0, 0}, -1, 2);
}

TEST_CASE("Update") {
  check_update({"Item", 1, 1}, 0, 0);
  check_update({"Item", 1, 0}, 0, 0);
  check_update({"Item", 0, 2}, -1, 0);

  check_update({"Aged Brie", 1, 50}, 0, 50);
  check_update({"Aged Brie", 1, 0}, 0, 1);
  check_update({"Aged Brie", 0, 50}, -1, 50);
  
  check_update({"Backstage passes to a TAFKAL80ETC concert", 1, 50}, 0, 50);
  check_update({"Backstage passes to a TAFKAL80ETC concert", 11, 0}, 10, 1);
  check_update({"Backstage passes to a TAFKAL80ETC concert", 10, 0}, 9, 2);
  check_update({"Backstage passes to a TAFKAL80ETC concert", 6, 0}, 5, 2);
  check_update({"Backstage passes to a TAFKAL80ETC concert", 10, 49}, 9, 50);
  check_update({"Backstage passes to a TAFKAL80ETC concert", 5, 0}, 4, 3);
  check_update({"Backstage passes to a TAFKAL80ETC concert", 5, 48}, 4, 50);
  check_update({"Backstage passes to a TAFKAL80ETC concert", 0, 20}, -1, 0);

  check_update({"Sulfuras, Hand of Ragnaros", 1, 80}, 1, 80);
  check_update({"Sulfuras, Hand of Ragnaros", -1, 80}, -1, 80);
}

TEST_CASE("Integration") {
  GildedRose::GildedRose gilded_rose{
    {
      {"Item", 10, 10},
      {"Aged Brie", 5, 0},
      {"Backstage passes to a TAFKAL80ETC concert", 7, 20},
      {"Sulfuras, Hand of Ragnaros", 0, 80}
    }
  };

  gilded_rose.updateQuality();
  gilded_rose.updateQuality();
  gilded_rose.updateQuality();
  gilded_rose.updateQuality();
  gilded_rose.updateQuality();

  CHECK(gilded_rose.get_item("Item")->sellIn == 5);
  CHECK(gilded_rose.get_item("Item")->quality == 5);

  CHECK(gilded_rose.get_item("Aged Brie")->sellIn == 0);
  CHECK(gilded_rose.get_item("Aged Brie")->quality == 5);

  CHECK(gilded_rose.get_item("Backstage passes to a TAFKAL80ETC concert")->sellIn == 2);
  CHECK(gilded_rose.get_item("Backstage passes to a TAFKAL80ETC concert")->quality == 33);

  CHECK(gilded_rose.get_item("Sulfuras, Hand of Ragnaros")->sellIn == 0);
  CHECK(gilded_rose.get_item("Sulfuras, Hand of Ragnaros")->quality == 80);
}