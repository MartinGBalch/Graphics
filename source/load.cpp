#include "graphics\load.h"
#include "graphics\RenderObjects.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb\stb_image.h"
#include <string>
#include <fstream>
#define TINYOBJLOADER_IMPLEMENTATION
#include "obj\tiny_obj_loader.h"
#include "graphics\Vertex.h"
#include "glinc.h"
using namespace std;

Texture loadTexture(const char * path)
{
	Texture retval = { 0 };

	stbi_set_flip_vertically_on_load(true);

	int w, h, c;
	unsigned char *pixels;
	pixels = stbi_load(path, &w, &h, &c, STBI_default);

	retval = makeTexture(w, h, c, pixels);
	stbi_image_free(pixels);
	return retval;
}

string fileToString(const char *path)
{
	ifstream file(path);
	string temp;
	string final;

	if (file.is_open())
	{
		while (getline(file, temp))
		{
			final += temp + "\n";
		}
		
	}

	return final;
}

Shader loadShader(const char * vert_path, const char * frag_path)
{
	Shader retval = { 0 };

	string v = fileToString(vert_path);
	string f = fileToString(frag_path);

	const char *vsource = v.c_str();
	const char *fsource = f.c_str();

	retval = makeShader(vsource, fsource);
	return retval;
}

Geometry loadGeometry(const char * path)
{
	Geometry retval = { 0,0,0,0 };


	tinyobj::attrib_t attrib;				// Vertex Data is stored.
	std::vector<tinyobj::shape_t> shapes;	// Triangular data, indices.
	std::vector<tinyobj::material_t> materials;
	std::string err;


	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	size_t isize = shapes[0].mesh.indices.size();
	size_t *indices = new unsigned[isize];

	size_t vsize = isize;
	Vertex *verts = new Vertex[vsize];

	for (int i = 0; i < isize; ++i)
	{
		indices[i] = i;

		int pi = shapes[0].mesh.indices[i].vertex_index;
		int ni = shapes[0].mesh.indices[i].normal_index;
		int ti = shapes[0].mesh.indices[i].texcoord_index;

		const float *p = &attrib.vertices[pi * 3];  // 3x
		const float *n = &attrib.normals[ni * 3];   // 3x
		const float *t = &attrib.texcoords[ti * 2]; // 2x

		verts[i].position = { p[0],p[1],p[2],1 };
		verts[i].uv = { t[0],t[1] };
		verts[i].norm = { n[0],n[1],n[2],1 };
	}

	solveTangent(verts, vsize, indices, isize);

	retval = makeGeometry(verts, vsize, indices, isize);

	delete[] verts;
	delete[] indices;
	return retval;

}

cubeTexture loadSkybox(std::vector<std::string> faces)
{
	cubeTexture textureID;
	glGenTextures(1, &textureID.handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID.handle);
	

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
