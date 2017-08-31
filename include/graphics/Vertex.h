#pragma once

#include "..\glm\glm.hpp"

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
	glm::vec2 uv;
	glm::vec4 norm;

	glm::vec4 tan;
	glm::vec4 bitan;
};