#include "game.hpp"
#include <vector>
#include<iostream>
#include "rsdl.hpp"



using namespace std;

int main(int argc, char* argv[])
{
    Game game(argv[1]);
    game.run();
}