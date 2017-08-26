#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"
#include "graphics\genShape.h"

int main()
{
	Context context;
	context.Init(800, 1200);



	Vertex verts[10] = { { { -.5f, -.5f,0,1 },{ 1,0,0,1 } },
	{ { -1,	  .6f,0,1 },{ 1,0,0,1 } },
	{ { 0,		1,0,1 },{ 1,1,0,1 } },
	{ { 1,    .6f,0,1 },{ 0,1,1,1 } },
	{ { 0,      0,0,1 },{ 0,1,0,1 } },
	{ { .5f, -.5f,0,1 },{ 1,0,1,1 } },
	{ { .5f, .25f,0,1 },{ 0,0,1,1 } },
	{ { -.5f,.25f,0,1 },{ 0,1,0,1 } },
	{ { .4f,  .8f,0,1 },{ 1,0,0,1 } },
	{ { -.4f, .8f,0,1 },{ 0,0,1,1 } } };

	unsigned idxs[18] = { 0,4,7,
		7,1,9,
		9,2,8,
		8,3,6,
		6,5,4 };

	//Geometry g = makeGeometry(verts, 10, idxs, 18);
	Geometry g = makeNGon(32, 1, .5f);

	const char* vsource = "#version 450\n"
		"layout(location = 0) uniform float time;\n"
		"layout(location = 1) uniform int press;\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 uv;\n"
		"out vec4 vPos;\n"
		"out vec4 vColr;\n"
		"out vec2 vUV;\n"
		"void main () {gl_Position = position; gl_Position.x += sin(time + position.x)/5.0;\n"
		"gl_Position.y *= cos(time + position.y)/1.0;\n"
		"vColr = color;\n"
		"vUV = uv;\n"
		"vPos = position;}\n";

	const char* fsource =
		"#version 450\n"
		"out vec4 outColor;\n"
		"layout(location = 0) uniform float time;\n"
		"layout(location = 2) uniform sampler2D map;\n"
		"in vec4 vColr;\n"
		"in vec2 vUV;\n"
		"in vec4 vPos;\n"
		"void main () {outColor = texture(map, vUV * sin(time * 2 + 5.0) + 5.0);}\n";
	// outColor = color;
	//outColor = texture(map, vUV * sin(time * 1 + 5.0) + 5.0);

	Shader s = makeShader(vsource, fsource);

	FrameBuffer f = { 0,800,1200 };

	unsigned char pixels[] = { 54,25,0,
							   27, 0 ,255,
							   236, 181, 32};
	Texture t_magyel = makeTexture(2, 1, 3, pixels);

	double x = 0;
	double y = 0;
	while (context.step())
	{
		clearFramebuffer(f);
		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 1, (int)context.getKey('R'));
		setUniform(s, 2, t_magyel, 0);
		s0_draw(f, s, g);

		
	}

	freeGeometry(g);
	freeShader(s);
	freeTexture(t_magyel);

	context.Terminate();
	return 0;

}