#ifndef GAME_HPP
#define GAME_HPP
#include <iostream>
#include <vector>
#include "rsdl.hpp"
#include "spaceship.hpp"
#include "easy_enemy.hpp"
#include "advanced_enemy.hpp"
#include "super_enemy.hpp"

using namespace std;

class Game {
public:
    Game(string file_address);
    void read_information();
    void read_map(int counter);
    void run();
    void make_first_view();
    void handle_events(bool& is_game_started , int& enemy_shoot_counter);
    void draw_screen();
    void update_objects(bool& is_game_started , bool& is_winner);
    void make_enemies(int block_height , int block_width);
    void after_game(bool is_winner);
    void manage_enemy_shoot(int& enemy_shoot_counter);
private:
    Window window;
    Spaceship spaceship;
    vector <Spaceship> hostages;
    vector<Super_enemy *> all_enemies;
    string file_address;
    vector<string> map;
    int round_number;
    int column_number;
    int row_number;
    int block_width;
    int block_height;
};

#endif