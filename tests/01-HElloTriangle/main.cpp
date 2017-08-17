#include "graphics\Context.h"
#include <iostream>

int main()
{
	Context context;
	context.Init();

	

	double x = 0;
	double y = 0;
	while (context.step())
	{
		std::cout << "You press the B key" << context.getKey('B') << std::endl;
		std::cout << "You have left clicked" << context.getMouseButton(0) << std::endl;
		context.getMousePosition(x, y);
		std::cout << "x = " << x << std::endl;
		std::cout << "y = " << y << std::endl;
		std::cout << "Time:" << context.getTime() << std::endl;
	}
	

	context.Terminate();
	return 0;
}