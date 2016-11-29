FLAGS := -std=c++11 -Wall -Wextra -pedantic
OBJ := City.o File.o Graph.o

pro: main.cpp $(OBJ)
	g++ $(FLAGS) $^ -o $@

%.o: %.cpp %.h
	g++ $(FLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm *.o pro
