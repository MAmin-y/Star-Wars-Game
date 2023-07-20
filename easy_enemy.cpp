#include "easy_enemy.hpp"
#include "rsdl.hpp"
#include <vector>

Easy_enemy::Easy_enemy(int _column , int _row ,int _width ,int _height , Window* win) 
    : Super_enemy(_column , _row , _width ,_height ,win) {
        vx = 0;
    }


void Easy_enemy::draw_yourself(Window* window){
    window->draw_img("enemy.png" ,Rectangle(Point(column, row),width ,height));
}

void Easy_enemy::update(Window* window){
    if ((column + vx >= window->get_width()) || (column + vx + width >= window->get_width()))
        vx = -vx;
    if (column + vx <= 0)
        vx = -vx;
    column += vx;
}