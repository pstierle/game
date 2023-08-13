#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "field.hpp"

class Map
{
public:
    std::vector<std::vector<Field>> fieldGrid;

    Map();
    void render();
    void update();
};

#endif