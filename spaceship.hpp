#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP
#include "rsdl.hpp"
#include "bullet.hpp"
#include <vector>
#include "easy_enemy.hpp"
#include "super_enemy.hpp"

using namespace std;

class Spaceship{
public:
    Spaceship(int _x , int _y ,int _width ,int _height ,Window* win);
    Spaceship();
    void move(string direction);
    void update_yourself();
    void update_bullets();
    void stop(char key);
    void draw_yourself(Window* window);
    void shoot(Window* window);
    bool does_get_shot(vector <Bullet> enemy_bullets);
    void erase_used_bullet(int index);
    void become_dead();
    bool get_status(){ return is_alive; }
    bool crashed(Super_enemy* enemy);
    bool crashed_hostage(Spaceship hostage);
    void delet_your_bullet();
    vector <Bullet>* get_bullets_ptr(){return &bullets;}
    vector <Bullet> get_bullets(){return bullets;}
    int get_row(){return row;}
    int get_column(){return column;}
    int get_width(){return width;}
    int get_height(){return height;}
private:
    int vx;
    int vy;
    int column;
    int row;
    int width;
    int height;
    bool is_alive;
    vector <Bullet> bullets;
    Window *window;
};
#endif