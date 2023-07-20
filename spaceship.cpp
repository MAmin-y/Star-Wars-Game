#include "spaceship.hpp"
#include <math.h>
#include "define.hpp"
#include "super_enemy.hpp"
using namespace std;

Spaceship::Spaceship(int _x , int _y ,int _width , int _hight , Window *win){
    width = _width;
    height = _hight;
    row = _y;
    column = _x;
    vx = 0;
    vy = 0;
    is_alive = true;
    window = win;
}

Spaceship::Spaceship(){
    width = 0;
    height = 0;
    column = 0;
    row = 0;
    vx = 0;
    vy = 0;
    is_alive = true;
}

void Spaceship::move(string direction){
    if(direction == UP)
        vy = -SPACESHIP_SPEED;
    if(direction == DOWN)
        vy = SPACESHIP_SPEED;
    if(direction == LEFT)
        vx = -SPACESHIP_SPEED;
    if(direction == RIGHT)
        vx = SPACESHIP_SPEED;
}

void Spaceship::stop(char key){
    if (key == 'd' || key == 'a')
        vx = 0;
    if(key == 's' || key == 'w')
        vy = 0;
}

void Spaceship::draw_yourself(Window* window){
    window->draw_img("spaceship.jpg" ,Rectangle(Point(column, row), width , height));
}

void Spaceship::update_yourself(){
    column += vx;
    row += vy;
    if(column > WINDOW_WIDTH || column < 0 || column+ width > WINDOW_WIDTH){
        if(column > WINDOW_WIDTH || column+ width > WINDOW_WIDTH)
            column = WINDOW_WIDTH - width;
        else
            column -= vx;
    }
    if(row > WINDOW_HEIGHT || row < 0 || row+ width > WINDOW_HEIGHT){
        if(row > WINDOW_HEIGHT || row+ height > WINDOW_HEIGHT)
            row = WINDOW_HEIGHT - height;
        else
            row -= vy;
    }
}
void Spaceship::update_bullets(){
    for (int i = 0; i < bullets.size(); i++){
        bullets[i].update_spaceship();
        if(bullets.size() > 0){
            if(bullets[i].is_out_of_screen(window))
                bullets.erase(bullets.begin() + i);
        }
    }   
}

void Spaceship::shoot(Window* window){
    Bullet new_bullet(column + width/2 , row);
    bullets.push_back(new_bullet);
    new_bullet.draw_yourself(window);
}

void Spaceship::erase_used_bullet(int index){
    bullets.erase(bullets.begin() + index);
}

bool Spaceship::does_get_shot(vector <Bullet> enemy_bullets){
    for (int i = 0; i < enemy_bullets.size(); i++){
        if( enemy_bullets[i].get_column() >= column &&
         enemy_bullets[i].get_column() <= (column + width) &&
         enemy_bullets[i].get_row() <= row + height &&
         enemy_bullets[i].get_row() >= row){
            return true;
        }
    }
    return false;
}

void Spaceship::become_dead(){
    is_alive  = false;
}

bool Spaceship::crashed(Super_enemy* enemy){
    if(abs((column + width/2) - (enemy->get_column() + enemy->get_width() / 2)) <= width/2 + enemy->get_width()/2 &&
        abs((row + height/2) - (enemy->get_row() + enemy->get_height() / 2)) <= height/2 + enemy->get_height()/2)
            return true;
    return false;
}

void Spaceship::delet_your_bullet(){
    bullets.clear();
}

bool Spaceship::crashed_hostage(Spaceship hostage){
    if(abs((column + width/2) - (hostage.get_column() + hostage.get_width() / 2)) <= width/2 + hostage.get_width()/2 &&
        abs((row + height/2) - (hostage.get_row() + hostage.get_height() / 2)) <= height/2 + hostage.get_height()/2)
            return true;
    return false;
}