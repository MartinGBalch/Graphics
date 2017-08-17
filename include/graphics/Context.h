#pragma once

class GLFWwindow;


class Context
{
private:
	GLFWwindow *handle;

public:
	bool getKey(int key);
	bool getMouseButton(int button);
	void getMousePosition(double &x_out, double &y_out);
	double getTime();


	bool Init(size_t w = 800, size_t h = 600, const char *title = "Graphics");

	bool step();

	bool Terminate();
};