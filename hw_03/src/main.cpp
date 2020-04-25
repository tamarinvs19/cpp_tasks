#include "huffman.h"
#include "exceptions.h"
#include <iostream>
#include <map>

static void huffman(std::map<std::string, std::string> params) {
    huffman_archiver::HuffmanArchiver ha = huffman_archiver::HuffmanArchiver(params["file"], params["output"]);
    if (params["mode"] == "c") {
	ha.archivate();
	std::tuple<int, int, int> info = ha.get_info();
	std::cout <<
	    std::get<0>(info) << std::endl <<
	    std::get<1>(info) - std::get<2>(info) << std::endl <<
	    std::get<2>(info) << std::endl;
    }
    if (params["mode"] == "u") {
	ha.unarchivate();
	std::tuple<int, int, int> info = ha.get_info();
	std::cout <<
	    std::get<0>(info) - std::get<2>(info) << std::endl <<
	    std::get<1>(info) << std::endl <<
	    std::get<2>(info) << std::endl;
    }
}

static void interface(int argc, std::vector<std::string> argv) {
    std::map<std::string, std::string> cmds = {{"-c", ""}, {"-u", ""}, {"-f", ""}, {"--file", ""}, {"-o", ""}, {"--output", ""}};
    std::map<std::string, std::string> params = {{"mode", ""}, {"file", ""}, {"output", ""}};
    if (argc != 5) {
	throw my_exception::MyException("Error!\nUsage: ./hw_3 [-c / -u] [-f / --file <file_name>] [-o / --output <file_name>]");
    }

    for (int i=0; i<argc; i++) {
	if (cmds.find(argv[i]) == cmds.end())
	    throw my_exception::MyException("Error! Invalid key");
	if (argv[i] == "-c")
	    params["mode"] = "c";
	if (argv[i] == "-u")
	    params["mode"] = "u";
	if (argv[i] == "-f" || argv[i] == "--file") {
	    if (i < 5) {
		params["file"] = argv[i+1];
		i++;
	    }
	    else
		throw my_exception::MyException("Error! Incorrect order of args.");
	}
	if (argv[i] == "-o" || argv[i] == "--output") {
	    params["output"] = argv[i+1];
	    i++;
	}
    }

    huffman(params);
}
int main(int argc, char* argv[])
{
    std::vector<std::string> argv_v;
    for (int i=1; i<argc; ++i) {
	std::string str(argv[i]);
	argv_v.push_back(str);
    }
    try {
	interface(argc-1, argv_v);
    }
    catch (my_exception::MyException &e) {
	std::cout << e.what() << std::endl;
    }
    catch (std::bad_alloc &e) {
	std::cout << "Unable to allocate memory" << std::endl;
    }

    return 0;
}
