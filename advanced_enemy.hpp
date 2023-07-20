#ifndef ADVANCED_ENEMY_HPP
#define ADVANCED_ENEMY_HPP
#include "define.hpp"
#include "bullet.hpp"
#include <vector>
#include "super_enemy.hpp"

using namespace std;

class Advanced_enemy : public Super_enemy{
public:
    Advanced_enemy(int _column , int _row ,int _width ,int _height , Window* win);
    virtual void draw_yourself(Window* window);
    virtual void update(Window* window);
};

#endif
