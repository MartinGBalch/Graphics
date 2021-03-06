#pragma once
#include "glm\fwd.hpp"
#include "graphics\RenderObjects.h"
void s0_draw(const FrameBuffer &f, const Shader &s, const Geometry &g);

void setUniform(const Shader &shader, int location, float value);


void setUniform(const Shader &s, int location, int value, int press);


void setUniform(const Shader &s, int location, const Texture &value, int slot);

namespace __internal
{
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, float val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, int val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const Texture &val);
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::vec3 & val);
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::vec4 & val);
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::mat4 & val);
	void t_setUniform(const Shader &s, int &loc_io, int &tex_io, const cubeTexture & val);

}

template<typename T, typename ...U>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val, U &&...uniforms)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);
	setUniforms(s, loc_io, tex_io, uniforms...);
}

template<typename T>
void setUniforms(const Shader &s, int &loc_io,int &tex_io, const T &val)
{
	__internal::t_setUniform(s, loc_io, tex_io, val);
}

enum RenderFlag {NONE = 0,  DEPTH = 1 , ADDITIVE = 2};

void setFlags(int flags);

void clearFramebuffer(const FrameBuffer & r, bool color = true, bool depth = true);


