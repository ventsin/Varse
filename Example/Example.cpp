#include <iostream>
#include <functional>
#include <Varse/Varse.hpp>

int main(int argc, char* argv[])
{
	int width = 800, height = 600;

	va::Parser parser;

	parser.setToken("-w", std::function<void(int)>([&](int next)
		{width = next; }));

	parser.setToken("-h", std::function<void(int)>([&](int next)
		{height = next; }));

	parser.parse(argc, argv);

	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;

	getchar();

	return 0;
}

