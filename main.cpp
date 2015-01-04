#include <iostream>
#include "engine.h"

int main(int argc, char** argv)
{

    Engine engine;

    try
    {
       engine.run();
    }
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}




}
