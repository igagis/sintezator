#pragma once

#include <vector>
#include <morda/config.hpp>

class Path {
	std::vector<morda::Vec2r> path = {{0}};
	
public:
	Path() = default;
	
	Path(const Path&) = delete;
	Path& operator=(const Path&) = delete;
	
	void lineTo(morda::Vec2r absPos);
	void lineTo(morda::real x, morda::real y){
		this->lineTo(morda::Vec2r(x, y));
	}
	
	void cubicTo(morda::Vec2r absP1, morda::Vec2r absP2, morda::Vec2r absP3);
	void cubicBy(morda::Vec2r relP1, morda::Vec2r relP2, morda::Vec2r relP3);
	
	void lineBy(morda::Vec2r relPos);
	
	struct Vertices{
		std::vector<morda::Vec2r> pos;
		std::vector<morda::real> alpha;
		
		std::vector<std::uint16_t> inIndices;
		std::vector<std::uint16_t> outIndices;
	};
	
	Vertices stroke(morda::real halfWidth = morda::real(0.5f), morda::real antialiasWidth = morda::real(1.0f), morda::real antialiasAlpha = morda::real(0.35f))const;
};
