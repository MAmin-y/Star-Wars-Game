CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
all: starwars.out

starwars.out: main.o game.o spaceship.o rsdl.o bullet.o super_enemy.o easy_enemy.o advanced_enemy.o 
	g++ --std=c++11 main.o game.o spaceship.o rsdl.o bullet.o super_enemy.o easy_enemy.o advanced_enemy.o $(CCFLAGS) -o a.out

main.o: main.cpp game.hpp
	g++ --std=c++11 -c main.cpp -o main.o

game.o: game.cpp game.hpp spaceship.hpp define.hpp rsdl.hpp advanced_enemy.hpp easy_enemy.hpp super_enemy.hpp
	g++ --std=c++11 -c game.cpp -o game.o

spaceship.o: spaceship.cpp spaceship.hpp define.hpp rsdl.hpp
	g++ --std=c++11 -c spaceship.cpp -o spaceship.o

rsdl.o: rsdl.cpp rsdl.hpp 
	g++ --std=c++11 -c rsdl.cpp -o rsdl.o

bullet.o: bullet.cpp bullet.hpp rsdl.hpp define.hpp
	g++ --std=c++11 -c bullet.cpp -o bullet.o

super_enemy.o: super_enemy.cpp super_enemy.hpp rsdl.hpp define.hpp bullet.hpp
	g++ --std=c++11 -c super_enemy.cpp -o super_enemy.o

easy_enemy.o: easy_enemy.cpp easy_enemy.hpp bullet.hpp rsdl.hpp define.hpp super_enemy.hpp
	g++ --std=c++11 -c easy_enemy.cpp -o easy_enemy.o

advanced_enemy.o: advanced_enemy.cpp advanced_enemy.hpp bullet.hpp rsdl.hpp define.hpp super_enemy.hpp
	g++ --std=c++11 -c advanced_enemy.cpp -o advanced_enemy.o

.PHONY: clean
clean:
		rm -r *.o