
#include "graphics\RenderObjects.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
struct Camera
{
	glm::mat4 proj;
	glm::mat4 view;
};

struct SpecGloss
{
	Geometry geo;
	glm::mat4 model;

	Texture diffuse;
	Texture specular;
	Texture normal;
	float gloss;
};

struct StandardLight
{
	glm::vec3 directiion;
	glm::vec4 color;
	float intesity;
	glm::vec4 ambient;
	int type;
};

struct DirectionalLight
{
	glm::vec3 center; // location from which the shadow map is drawn.
	float size;		  // area that the shadow map covers.

	glm::vec3 direction;
	glm::vec4 color;
	float intensity;

	glm::mat4 getView() const { return glm::lookAt(direction + center, center, glm::vec3(0, 1, 0)); }
	glm::mat4 getProj() const { return glm::ortho<float>(-size, size, -size, size, -size, size); }
};

struct SimplePresetScene
{
	Camera cam;
	SpecGloss go[3];
	DirectionalLight dl[2];

	SimplePresetScene();
};


namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Camera &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const SpecGloss &val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const DirectionalLight &val);
}

