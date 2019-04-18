test_deque : test_deque.cc deque.h
	g++ -Wall -Werror -std=c++11 -o test_deque test_deque.cc -pthread -lgtest
