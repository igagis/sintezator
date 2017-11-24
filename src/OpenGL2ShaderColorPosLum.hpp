#pragma once

#include <morda/render/ShaderColor.hpp>
#include <mordaren/OpenGL2ShaderBase.hpp>

class OpenGL2ShaderColorPosLum :
		public morda::ShaderColor,
		private mordaren::OpenGL2ShaderBase
{
	GLint colorUniform;
public:
	OpenGL2ShaderColorPosLum();
	
	OpenGL2ShaderColorPosLum(const OpenGL2ShaderColorPosLum&) = delete;
	OpenGL2ShaderColorPosLum& operator=(const OpenGL2ShaderColorPosLum&) = delete;
	
	void render(const kolme::Matr4f& m, const morda::VertexArray& va, kolme::Vec4f color) override;
};

