#include "game.hpp"
#include "advanced_enemy.hpp"
#include "super_enemy.hpp"
#include "define.hpp"
#include "spaceship.hpp"
#include "rsdl.hpp"
#include <iostream>
#include "easy_enemy.hpp"
#include <fstream>
#include <vector>

using namespace std;

Game::Game(string _file_address) : 
spaceship(SPACESHIP_COLUMN, SPACESHIP_ROW, SPACESHIP_WIDTH, SPACESHIP_HEIGHT , &window) , 
window(WINDOW_WIDTH , WINDOW_HEIGHT){
  file_address = _file_address;
}

void Game::run(){
  read_information();
  bool is_winner = true;
  window.play_music("Star Wars.mp3");
  for(int counter = 0; counter < round_number ; counter++){
    read_map(counter);
    make_first_view();
    bool is_game_started = true;
    int enemy_shoot_counter = 1;
    while (is_game_started){
      handle_events(is_game_started, enemy_shoot_counter);
      update_objects(is_game_started , is_winner);
      draw_screen();
      delay(50);
      enemy_shoot_counter++;
    }
    spaceship.delet_your_bullet();
    hostages.clear();
  }
  after_game(is_winner);
}

void Game::after_game(bool is_winner){
  while(true){
    window.clear();
    if(is_winner)
      window.draw_img("winner.jpg");
    else {
      window.stop_music();
      window.draw_img("gameover.jpg");
    }
    window.update_screen();
    Event event = window.poll_for_event();
    if (event.get_type() == Event::QUIT){
      exit(0);
    }
  }
}

void Game::make_first_view()
{
  block_height = WINDOW_HEIGHT / row_number;
  block_width = WINDOW_WIDTH / column_number;
  make_enemies(block_height, block_width);
  draw_screen();
}

void Game::handle_events(bool &is_game_started, int& enemy_shoot_counter){
  Spaceship *spaceship_ptr = &spaceship;
  while (window.has_pending_event()){
    Event event = window.poll_for_event();
    if (event.get_type() == Event::KEY_PRESS){
      char pressed_key = event.get_pressed_key();
      if (pressed_key == 'd')
        spaceship_ptr->move(RIGHT);
      else if (pressed_key == 'a')
        spaceship_ptr->move(LEFT);
      else if (pressed_key == 'w')
        spaceship_ptr->move(UP);
      else if (pressed_key == 's')
        spaceship_ptr->move(DOWN);
      else if (pressed_key == ' ')
        spaceship_ptr->shoot(&window);
    }
    if (event.get_type() == Event::KEY_RELEASE){
      spaceship.stop(event.get_pressed_key());
    }
    if (event.get_type() == Event::QUIT){
      exit(0);
    }
  }
  manage_enemy_shoot(enemy_shoot_counter);
}

void Game::manage_enemy_shoot(int& enemy_shoot_counter){
  if (enemy_shoot_counter % SECOND_ENEMY_SHOT == 0 || 
      enemy_shoot_counter % FIRST_ENEMY_SHOT == 0){
    for (int i = 0; i < all_enemies.size(); i++){
      all_enemies[i]->shoot(&window);
      if (enemy_shoot_counter % 60 == 0){
        enemy_shoot_counter = 0;
      }
    }
  }
}

void Game::draw_screen(){
  window.clear();
  window.draw_img("back.jpeg");
  spaceship.draw_yourself(&window);
  for (int i = 0; i < spaceship.get_bullets().size(); i++){
    spaceship.get_bullets()[i].draw_yourself(&window);
  }
  for (int i = 0; i < all_enemies.size(); i++){
    for (int j = 0; j < all_enemies[i]->get_bullets().size(); j++){
      all_enemies[i]->get_bullets()[j].draw_yourself(&window);
    }
  }
  for (int i = 0 ; i < hostages.size(); i++){
    hostages[i].draw_yourself(&window);
  }
  for (int i = 0; i < all_enemies.size(); i++){
    all_enemies[i]->draw_yourself(&window);
  }
  window.update_screen();
}

void Game::update_objects(bool &is_game_started , bool &is_winner){
  if(all_enemies.size() == 0)
    is_game_started = false;
  spaceship.update_yourself();
  spaceship.update_bullets();
  if (!spaceship.get_status()){
    is_game_started = false;
    is_winner = false;
  }
  for (int i = 0; i < all_enemies.size(); i++){
    all_enemies[i]->update_bullets();
  }
  for (int i = 0; i < all_enemies.size(); i++){
    all_enemies[i]->update(&window);
  }
  for (int i = 0; i < all_enemies.size(); i++){
    int bullet_index;
    if (all_enemies[i]->does_get_shot(spaceship.get_bullets(), bullet_index)){
      all_enemies.erase(all_enemies.begin() + i);
      spaceship.erase_used_bullet(bullet_index);
    }
  }
  for (int i = 0; i < hostages.size(); i++){
    int bullet_index;
    if (hostages[i].does_get_shot(spaceship.get_bullets())){
      spaceship.become_dead();
    }
  }
  for (int i = 0; i < all_enemies.size(); i++){
    if (spaceship.crashed(all_enemies[i])){
      spaceship.become_dead();
    }
  }
  for (int i = 0; i < hostages.size(); i++){
    if (spaceship.crashed_hostage(hostages[i])){
      spaceship.become_dead();
    }
  }
  for (int i = 0; i < all_enemies.size(); i++){
    if (spaceship.does_get_shot(all_enemies[i]->get_bullets())){
      spaceship.become_dead();
    }
  }
}

void Game::read_information(){
  ifstream file;
  file.open(file_address);
  file >> row_number >> column_number;
  file >> round_number;
  file.close();
}

void Game::read_map(int counter){
  ifstream file;
  map.clear();
  string line;
  file.open(file_address);
  getline(file, line);
  getline(file, line);
  for (int j = 0; j < counter * row_number ; j++)  {
    getline(file, line);
  }
  for(int i = 0; i < row_number; i++){
    getline(file, line);
    map.push_back(line);
  }
}

void Game::make_enemies(int block_height , int block_width){
  for(int i = 0; i < row_number; i++){
    for(int j = 0; j < column_number; j++){
      if(map[i][j] == 'E'){
        all_enemies.push_back(new Easy_enemy(j * block_width , i * block_height , SPACESHIP_WIDTH ,SPACESHIP_HEIGHT , &window));
      }
      if(map[i][j] == 'M'){
        all_enemies.push_back(new Advanced_enemy(j * block_width , i * block_height , SPACESHIP_WIDTH ,SPACESHIP_HEIGHT , &window));
      }
      if(map[i][j] == 'S'){
        hostages.push_back (Spaceship(j * block_width , i * block_height , SPACESHIP_WIDTH ,SPACESHIP_HEIGHT , &window));
      }
    }
  }
}