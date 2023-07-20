#include "advanced_enemy.hpp"
#include "rsdl.hpp"
#include "super_enemy.hpp"

void Advanced_enemy::draw_yourself(Window* window){
    window->draw_img(("advanced_enemy.png") ,Rectangle(Point(column, row),width ,height));
}

Advanced_enemy::Advanced_enemy(int _column , int _row ,int _width ,int _height , Window* win)
    : Super_enemy(_column , _row , _width ,_height ,win) {
        vx = ENEMY_SPEED;
    }

void Advanced_enemy::update(Window* window){
    if ((column + vx >= window->get_width()) || (column + vx + width >= window->get_width()))
        vx = -vx;
    if (column + vx <= 0)
        vx = -vx;
    column += vx;
}