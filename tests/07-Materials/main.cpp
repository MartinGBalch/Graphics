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
	context.Init();

	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }


	};

	unsigned quadidx[] = { 0,1,3,1,2,3 };
	solveTangent(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);

	Texture floor_normal = loadTexture("../../resources/textures/weird.jpg");
	Texture floor_diffuse = loadTexture("../../resources/textures/squig.jpg");

	Shader standard = loadShader("../../resources/shaders/standard.vert",
								 "../../resources/shaders/standard.frag");

	FrameBuffer screen = { 0,800,600 };

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

	glm::mat4 go_model;

	glm::vec3 light_direction = glm::normalize(glm::vec3(1, -1, 1));

	while (context.step())
	{
		int loc = 0, slot = 0;

		setUniforms(standard, loc, slot, cam_proj, cam_view, go_model, floor_normal,floor_diffuse, light_direction);

		s0_draw(screen, standard, quad);
 
	}
	context.Terminate();
	return 0;


}