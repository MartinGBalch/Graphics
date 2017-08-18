#include "graphics\Context.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"
#include "graphics\Vertex.h"
#include <iostream>

int main()
{
	Context context;
	context.Init(800,1200);

	Vertex verts[10] = {{{ -.5f, -.5f,0,1 },{1,0,0,1} },
					    {{   -1,  .6f,0,1 },{0,1,0,1} },
					    {{    0, 1,0,1 },{0,0,1,1} },
					    {{    1,  .6f,0,1 },{1,1,0,1} },
					    {{    0,    0,0,1 },{0,0,1,1} },
					    {{  .5f, -.5f,0,1 },{1,0,1,1} },
					    {{  .5f, .25f,0,1 },{0,1,1,1} },
						{{ -.5f, .25f,0,1 },{1,0,1,1} },
						{{  .4f,  .8f,0,1 },{1,0,1,1} },
						{{ -.4f,  .8f,0,1 },{0,1,1,1} }};

	unsigned idxs[18] = { 0,4,7,
						  7,1,9,
						  9,2,8,
						  8,3,6,
						  6,5,4};

	Geometry g = makeGeometry(verts, 10, idxs, 18);

	const char* vsource = "#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"out vec4 vPos;\n"
		"flat out vec4 vColr;\n"
		"void main () {gl_Position = position;\n"
		"vColr = color;\n"
		"vPos = position;}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"flat in vec4 vColr;\n"
		"in vec4 vPos;\n"
		"void main () {outColor = vColr;}\n";

	Shader s = makeShader(vsource, fsource);

	FrameBuffer f = { 0,800,600 };

	double x = 0;
	double y = 0;
	while (context.step())
	{
		s0_draw(f, s, g);

		///*std::cout << "You press the B key" << context.getKey('B') << std::endl;
		//std::cout << "You have left clicked" << context.getMouseButton(0) << std::endl;
		//context.getMousePosition(x, y);
		//std::cout << "x = " << x << std::endl;
		//std::cout << "y = " << y << std::endl;
		//std::cout << "Time:" << context.getTime() << std::end*/l;
	}
	
	freeGeometry(g);
	freeShader(s);

	context.Terminate();
	return 0;
}