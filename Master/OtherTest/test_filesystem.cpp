#include "test_filesystem.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <streambuf>
#include <sstream>
#include <exception>
#include <filesystem>


void test_filesystem()
{
	std::filesystem::create_directories("sandbox/a/b");
	std::ofstream("sandbox/file1.txt");
	std::ofstream("sandbox/file2.txt");
	for (auto& p : std::filesystem::directory_iterator("sandbox"))
		std::cout << p.path() << '\n';
	std::filesystem::remove_all("sandbox");
}
