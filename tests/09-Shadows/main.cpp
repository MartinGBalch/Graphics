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

	// Floor
	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangent(vquad, 4, quadidx, 6);
	Geometry floor_geo = makeGeometry(vquad, 4, quadidx, 6);
	glm::mat4 floor_model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
		* glm::scale(glm::vec3(5, 5, 1));

	// SoulSpear
	Geometry  ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model; // = glm::rotate(time, glm::vec3(0,1,0)) // on update.

						// Cube
	Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 cube_model = glm::translate(glm::vec3(2, 1, -1));

	

	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 5),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0));
	glm::mat4 cam_proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);

	// Light
	glm::vec3 light_dir = glm::normalize(glm::vec3(.8, -1, -1));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_dir, glm::vec3(0, 0, 0), glm::vec3(1, .5f, 0));
	glm::vec4 color = glm::vec4(1, 0, 0, 1);

	// Light2
	glm::vec3 light_dir2 = glm::normalize(glm::vec3(.3, -.5, -1));
	glm::mat4 light_proj2 = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view2 = glm::lookAt(-light_dir, glm::vec3(0, 0, 0), glm::vec3(.5f, 2, 0));
	glm::vec4 color2 = glm::vec4(0, 1, 0, 1);

	Shader shdr_shadow = loadShader("../../resources/shaders/shadow.vert",
		"../../resources/shaders/shadow.frag");
	Shader shdr_direct = loadShader("../../resources/shaders/direct.vert",
		"../../resources/shaders/direct.frag");

	// Buffers
	FrameBuffer fb_shadow = MakeFrameBuffer(2048, 2048, 0, true, 0, 0);
	FrameBuffer screen = { 0,1280, 720 };

	while (context.step())
	{
		float time = context.getTime();
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(fb_shadow, false, true);

		ss_model = glm::rotate(time + 5, glm::vec3(0, 1, 0));

		int loc = 0 , slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view,floor_model);
		s0_draw(fb_shadow, shdr_shadow, floor_geo);

		loc = slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view,ss_model);
		s0_draw(fb_shadow, shdr_shadow, ss_geo);
		
		loc = slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, cube_model);
		s0_draw(fb_shadow, shdr_shadow, cube_geo);

		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);

		loc = slot = 0;
		setUniforms(shdr_direct, loc, slot,
			cam_proj, cam_view,     // Camera Data
			floor_model,            // Geometry Data
			light_proj, light_view,
			light_proj2, light_view2,// Light Data          
			fb_shadow.depthTarget, color, color2); // Shadow Map
		s0_draw(screen, shdr_direct, floor_geo);

		loc = slot = 0;
		setUniforms(shdr_direct, loc, slot,
			cam_proj, cam_view,     // Camera Data
			ss_model,            // Geometry Data
			light_proj, light_view,
			light_proj2, light_view2,// Light Data
			fb_shadow.depthTarget, color, color2); // Shadow Map
		s0_draw(screen, shdr_direct, ss_geo);

		loc = slot = 0;
		setUniforms(shdr_direct, loc, slot,
			cam_proj, cam_view,     // Camera Data
			cube_model,            // Geometry Data
			light_proj, light_view,
			light_proj2, light_view2,// Light Data
			fb_shadow.depthTarget, color, color2); // Shadow Map
		s0_draw(screen, shdr_direct, cube_geo);


	}

}