#ifndef SUPER_ENEMY_HPP
#define SUPER_ENEMY_HPP
#include "define.hpp"
#include "bullet.hpp"
#include <vector>
#include "rsdl.hpp"

class Super_enemy{
public:
    Super_enemy(int _column , int _row ,int _width ,int _height , Window* win);
    virtual void draw_yourself(Window* window) = 0;
    virtual void update(Window * window) = 0;
    bool does_get_shot(vector <Bullet> spaceship_bullets , int& index);
    void shoot(Window* window);
    void update_bullets();
    int get_row(){ return row; }
    int get_column(){ return column; }
    int get_width(){ return width; }
    int get_height(){ return height; }
    vector <Bullet> get_bullets(){ return bullets; }
protected:
    int row;
    int column;
    int width;
    int height;
    int vx;
    vector <Bullet> bullets;
    Window *window;
};

#endif