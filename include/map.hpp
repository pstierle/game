#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "field.hpp"
#include "item.hpp"

class Map
{
public:
    std::vector<std::vector<Field>> fieldGrid;
    std::vector<Item> items;
    double width;
    double height;

    Map();
    void initFields();
    void initItems();
    void render();
    void update();
    void removeItem(size_t index);
};

#endif