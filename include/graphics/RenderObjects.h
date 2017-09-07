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



struct Texture
{
	unsigned handle;
};

Geometry makeGeometry(const Vertex *vertices, size_t vsize, const unsigned *indices, size_t isize);
void freeGeometry(Geometry &g);

Shader makeShader(const char *vert_source, const char *frag_source);
void freeShader(Shader &s);

void solveTangent(Vertex *v, size_t vsize, const unsigned *idxs, size_t isize);

Texture makeTexture(unsigned w, unsigned h, unsigned c, const void  *pixels, bool isFloat = false);
void freeTexture(Texture &t);
struct FrameBuffer
{
	unsigned handle;
	unsigned width, height;
	unsigned nTargets;
	Texture depthTarget;
	Texture targets[8];
};
FrameBuffer MakeFrameBuffer(unsigned w, unsigned h, unsigned c, bool hasDepth, unsigned nTargets, unsigned nFloatTargets);
void freeFrameBuffer(FrameBuffer & fb);