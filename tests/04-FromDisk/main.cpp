#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"
#include "graphics\genShape.h"
#include "graphics\load.h"

#include"glm/ext.hpp"
int main()
{
	Context context;
	context.Init(800, 1200);


	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 } },
		{ { -1, 1,0,1 },{},{ 0,1 } }
	};

	unsigned quadidx[] = { 0,1,3, 1,2,3 };

	

	FrameBuffer f = { 0,800,800 };

	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
	Texture tex = loadTexture("../../resources/textures/bigbear.png");
	Geometry model = loadGeometry("../../resources/models/cube.obj");
	Shader shade = loadShader("../../resources/shaders/test.vert", "../../resources/shaders/test.frag");

	
	double x = 0;
	double y = 0;
	while (context.step())
	{
		glm::mat4 rot = glm::rotate((float) context.getTime(),glm::vec3(1,1,1));

		clearFramebuffer(f);
		setFlags(RenderFlag::DEPTH);
		int loc = 0, tslot = 0;
		setUniforms(shade, loc, tslot, rot, tex);
		s0_draw(f, shade, model);


	}

	freeGeometry(model);
	freeShader(shade);
	freeTexture(tex);
	 
	context.Terminate();
	return 0;

}