#pragma once

struct Geometry;
struct FrameBuffer;
struct Shader;
struct Texture;


void s0_draw(const FrameBuffer &f, const Shader &s, const Geometry &g);

void setUniform(const Shader &shader, int location, float value);

void clearFramebuffer(const FrameBuffer &fb);

void setUniform(const Shader &shader, int location, int value, int press);

void setUniform(const Shader &s, int location, const Texture &value, int slot);