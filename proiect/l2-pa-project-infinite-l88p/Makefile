FLAGS = -std=c++17 -O3

build: MyBot.o constants.o game_map.o log.o
	g++ $(FLAGS) $^ -o MyBot

MyBot.o: MyBot.cpp
	g++ $(FLAGS) $^ -c

constants.o: ./hlt/constants.cpp
	g++ $(FLAGS) $^ -c

game_map.o: ./hlt/game_map.cpp
	g++ $(FLAGS) $^ -c

log.o: ./hlt/log.cpp
	g++ $(FLAGS) $^ -c

.PHONY: clean
clean:
	rm -rf *.o MyBot
