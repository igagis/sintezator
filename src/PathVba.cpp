#include "PathVba.hpp"

#include <morda/Morda.hpp>

#include "App.hpp"

PathVba::PathVba(const Path::Vertices& path){
	auto coreBuf = morda::inst().renderer().factory->createVertexBuffer(utki::wrapBuf(path.pos));
	
	this->core = morda::inst().renderer().factory->createVertexArray(
			{{
				coreBuf,
			}},
			morda::inst().renderer().factory->createIndexBuffer(utki::wrapBuf(path.inIndices)),
			morda::VertexArray::Mode_e::TRIANGLE_STRIP
		);
	
	
	this->border = morda::inst().renderer().factory->createVertexArray(
			{{
				coreBuf,
				morda::inst().renderer().factory->createVertexBuffer(utki::wrapBuf(path.alpha)),
			}},
			morda::inst().renderer().factory->createIndexBuffer(utki::wrapBuf(path.outIndices)),
			morda::VertexArray::Mode_e::TRIANGLE_STRIP
		);
}

void PathVba::render(const morda::Matr4r& matrix, std::uint32_t color){
	morda::inst().renderer().shader->colorPos->render(matrix, *this->core, 0xff00ff00);
	static_cast<::App&>(mordavokne::inst()).shaderColorPosLum.render(matrix, *this->border, 0xff00ff00);
}
