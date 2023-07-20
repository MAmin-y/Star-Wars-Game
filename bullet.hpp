#ifndef Bullet_HPP
#define Bullet_HPP
#include "rsdl.hpp"

using namespace std;

class Bullet{
public:
    Bullet(int _x , int _y);
    void draw_yourself(Window* window);
    void update_spaceship();
    void update_enemy();
    bool is_out_of_screen(Window* window);
    int get_row();
    int get_column();
    int get_width();
private:
    int row;
    int column;
    int width;
    int height;
    int speed;
};
#endif