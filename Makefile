CXXFLAGS =-ggdb -std=c++20 -Wall -Wextra -Werror -Wfatal-errors -pedantic
LDFLAGS = -pthread -lgtest -lgtest_main

all: dijkstras

dijkstras: src/dijkstras_main.cpp src/dijkstras.cpp
	$(CXX) $(CXXFLAGS) src/dijkstras_main.cpp src/dijkstras.cpp -o dijkstras
# ladder: src/ladder_main.cpp src/ladder.cpp
# 	$(CXX) $(CXXFLAGS) src/ladder_main.cpp src/ladder.cpp -o ladder

clean:
	rm -f dijkstras