#include "bullet.hpp"
#include "rsdl.hpp"
#include "define.hpp"
using namespace std;

Bullet::Bullet(int _x , int _y){
    column = _x;
    row = _y;
    width = BULLET_WIDTH;
    height = BULLET_HEIGHT;
}

void Bullet::draw_yourself(Window* window){
    window->draw_rect(Rectangle(Point(column , row) , width , height));
}

void Bullet::update_spaceship(){
    row -= BULLET_SPEED;
}

void Bullet::update_enemy(){
    row += BULLET_SPEED;
}

int Bullet::get_column(){
    return column;
}

int Bullet::get_row(){
    return row;
}

int Bullet::get_width(){
    return width;
}

bool Bullet::is_out_of_screen(Window* window){
    if(row < 0 || row >= window->get_height() || column < 0 || column >= window->get_width())
        return true;
    return false;
}