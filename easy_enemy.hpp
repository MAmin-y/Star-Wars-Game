#ifndef EASY_ENEMY_HPP
#define EASY_ENEMY_HPP
#include "define.hpp"
#include "bullet.hpp"
#include <vector>
#include "super_enemy.hpp"

using namespace std;

class Easy_enemy : public Super_enemy {
public:
    Easy_enemy(int _column , int _row ,int _width ,int _height , Window* win);
    virtual void draw_yourself(Window* window);
    virtual void update(Window* window);
};
#endif