#pragma once

#include "glm\glm.hpp"

struct Vertex;
struct Geometry
{
	unsigned handle, // Vertex Array object
			 vbo,	 // Vertex buffer object
			 ibo,	 // Index buffer object
			 size;   // How many indices make up this model
};

struct Shader
{
	unsigned handle;
};

struct FrameBuffer
{
	unsigned handle;
	unsigned width, height;
};

struct Texture
{
	unsigned handle;
};

Geometry makeGeometry(const Vertex *vertices, size_t vsize, const unsigned *indices, size_t isize);
void freeGeometry(Geometry &g);

Shader makeShader(const char *vert_source, const char *frag_source);
void freeShader(Shader &s);

Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char *pixels);
void freeTexture(Texture &t);

void solveTangent(Vertex *v, size_t vsize, const unsigned *idxs, size_t isize);