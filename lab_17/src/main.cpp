#include <string>
#include <cstdlib>
#include <utility>
#include <iostream>
#include "sync_queue.hpp"


int main(int argc, char *argv[])
{
    // std::size_t worker_threads = argv[1];
    std::size_t queue_size = (std::size_t)atoi(argv[2]);
    lab_17::sync_queue<std::pair<int, int>> s_q(queue_size);

    std::string command = "";
    int id, start, end;
    while (command != "quit") {
	std::cin >> command;
	if (command == "submit") {
	    std::cin >> id >> start >> end;
	    std::pair<int, int> p(start, end);
	    s_q.push(p);
	}
	if (command == "show-done") {
	}
	if (command == "quit") {
	    s_q.shutdown();
	}
    }
    return 0;
}
