#include "graphics\RenderObjects.h"
#include "glinc.h"
#include "..\include\graphics\draw.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"

void s0_draw(const FrameBuffer & f, const Shader & s, const Geometry & g)
{
	glBindFramebuffer(GL_FRAMEBUFFER, f.handle);
	glUseProgram(s.handle);
	glBindVertexArray(g.handle);

	glViewport(0, 0, f.width, f.height);

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}

void setUniform(const Shader & shader, int location, float value)
{
	glProgramUniform1f(shader.handle, location, value);
}

void clearFramebuffer(const FrameBuffer & fb)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fb.handle);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void setUniform(const Shader & shader, int location, int value, int press)
{
	glProgramUniform1i(shader.handle, location, value);
}

void setUniform(const Shader & s, int location, const Texture & value, int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, value.handle);
	glProgramUniform1i(s.handle, location, slot);

}

namespace __internal
{
	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, float val)
	{
		glProgramUniform1f(s.handle, loc_io++, val);
	}

	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, int val)
	{
		glProgramUniform1i(s.handle, loc_io++, val);

	}

	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const Texture & val)
	{
		glActiveTexture(GL_TEXTURE0 + tex_io);
		glBindTexture(GL_TEXTURE_2D, val.handle);
		glProgramUniform1i(s.handle, loc_io++, tex_io++);
	}

	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::vec3 & val)
	{
		glProgramUniform3fv(s.handle, loc_io++, 1, glm::value_ptr(glm::vec3(0, 0, 1)));
	}

	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::vec4 & val)
	{
		glProgramUniform4fv(s.handle, loc_io++, 1, glm::value_ptr(val));
	}

	void t_setUniform(const Shader & s, int & loc_io, int & tex_io, const glm::mat4 & val)
	{
		glProgramUniformMatrix4fv(s.handle, loc_io++, 1, 0, glm::value_ptr(val));
	}


}
