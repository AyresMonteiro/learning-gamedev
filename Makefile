CXXFLAGS := $(shell pkg-config --cflags sfml-all)
LDLIBS := $(shell pkg-config --libs sfml-all)

main: main.cpp ./build/classes/GameScreen.class.o
	g++ $(CXXFLAGS) ./main.cpp ./build/classes/GameScreen.class.o -o main $(LDLIBS)

./build/classes/GameScreen.class.o: ./src/classes/GameScreen.class.cpp
	g++ $(CXXFLAGS) ./src/classes/GameScreen.class.cpp -c -o ./build/classes/GameScreen.class.o

clean:
	rm ./build/classes/* && rm ./main
