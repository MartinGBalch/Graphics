#include "graphics\Context.h"
#include "graphics\draw.h"
#include "graphics\GameObjects.h"
#include "graphics\RenderObjects.h"
#include "graphics\Load.h"
#include "graphics\Vertex.h"
#include <vector>
#include"glm/ext.hpp"
	

void main()
{
	Context context;
	context.Init(1280, 720);

	std::vector<std::string>faces;

	faces =
	{
		"../../resources/textures/stormydays_ft.tga",
		"../../resources/textures/stormydays_bk.tga",

		"../../resources/textures/stormydays_up.tga",
		"../../resources/textures/stormydays_dn.tga",

		"../../resources/textures/stormydays_rt.tga",
		"../../resources/textures/stormydays_lf.tga"
	};

	Geometry    sky_geo;
	cubeTexture sky_map;
	glm::mat4   sky_model;
	Shader      sky_shader;
	glm::mat4   cam_view;
	glm::mat4   cam_proj;

	Camera cam;
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);
	sky_geo = loadGeometry("../../resources/models/cube.obj");
	sky_model = glm::scale(glm::vec3(20, 20, 20));

	sky_map = loadSkybox(faces);

	sky_shader = loadShader("../../resources/shaders/skyBox.vert", "../../resources/shaders/skyBox.frag");

	FrameBuffer screen = { 0,1280,720 };

	int loc = 0, slot = 0;
	while (context.step())
	{
		loc = slot = 0;
		float time = context.getTime();
		setFlags(RenderFlag::DEPTH);
		clearFramebuffer(screen);

		sky_model = glm::rotate(time, glm::vec3(0, 1, 0));

		setUniforms(sky_shader, loc, slot, cam.proj, cam.view, sky_model, sky_map);
		s0_draw(screen, sky_shader, sky_geo);
	}
	context.Terminate();
}