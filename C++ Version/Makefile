CXX       := /usr/bin/g++
CXX_FLAGS := -std=c++17 -Wall -Wextra -Wpedantic -g

SRC     := src
INCLUDE := include

all: clean main.exe run

main.exe: main.cpp $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@

test.exe: test.cpp $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@

run: all
	./main.exe

clean:
	rm -f *.exe

