CXXFLAGS = -O -Wall -pedantic 
LDLIBS = -lncursesw
LINK.o = $(LINK.cpp)

snake: main.o	coordinates.o	snake.o	tick.o	food.o	direction.o

main.o: main.hpp	main.cpp	snake.o	food.o	tick.o	direction.o

snake.o: snake.cpp	snake.hpp	coordinates.o	direction.o

coordinates.o: coordinates.cpp	coordinates.hpp	direction.o

tick.o: tick.cpp	tick.hpp

food.o: food.cpp	food.hpp	coordinates.o

direction.o: direction.hpp	direction.cpp

run: snake
	./snake

clean:
	rm -f *.o
	rm -f *.gch
	
cclean: snake	clean
