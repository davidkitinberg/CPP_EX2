FLAGS = g++ -std=c++11 -Wall -Wextra -pedantic

Main:
	$(FLAGS) Main.cpp SquareMat.cpp -o main
	./main

Test:
	$(FLAGS) Test.cpp SquareMat.cpp -o test
	./test

valgrind:
	$(FLAGS) -g Test.cpp SquareMat.cpp -o test_valgrind
	valgrind --leak-check=full ./test_valgrind

clean:
	rm -f main test test_valgrind
