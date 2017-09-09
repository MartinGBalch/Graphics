#pragma once
#include "RenderObjects.h"
#include <iostream>
#include <vector>


Texture loadTexture(const char *path);

Shader loadShader(const char *vert_path, const char *frag_path);
Geometry loadGeometry(const char *path);

cubeTexture loadSkybox(std::vector<std::string> faces);