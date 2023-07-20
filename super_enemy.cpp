#include "super_enemy.hpp"
#include "rsdl.hpp"

Super_enemy::Super_enemy(int _column , int _row ,int _width ,int _height , Window* win){
    width = _width;
    height = _height;
    column = _column;
    row = _row;
    window = win;
}

bool Super_enemy::does_get_shot(vector <Bullet> spaceship_bullets , int& index){
    for (int i = 0; i < spaceship_bullets.size(); i++){
        if( (spaceship_bullets[i].get_column() >= column &&
         spaceship_bullets[i].get_column() <= (column + width) &&
         spaceship_bullets[i].get_row() <= row + height &&
         spaceship_bullets[i].get_row() >= row)){
            index = i;
            return true;
        }
    }
    return false;
}

void Super_enemy::shoot(Window* window){
    Bullet new_bullet(column + width/2 , row + height);
    bullets.push_back(new_bullet);
    new_bullet.draw_yourself(window);
}

void Super_enemy::update_bullets(){
    for (int i = 0; i < bullets.size(); i++){
        bullets[i].update_enemy();
        if(bullets.size() > 0){
            if(bullets[i].is_out_of_screen(window))
                bullets.erase(bullets.begin() + i);
        }
    }
}