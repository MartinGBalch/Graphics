#include "graphics\RenderObjects.h"
#include "glinc.h"
#include "..\include\graphics\draw.h"

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
