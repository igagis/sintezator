#pragma once

#include <vector>
#include <morda/config.hpp>

class Path {
	std::vector<morda::vector2> path = {{0, 0}};
	
public:
	Path() = default;
	
	Path(const Path&) = delete;
	Path& operator=(const Path&) = delete;
	
	void lineTo(morda::vector2 absPos);
	void lineTo(morda::real x, morda::real y){
		this->lineTo(morda::vector2(x, y));
	}
	
	void cubicTo(morda::vector2 absP1, morda::vector2 absP2, morda::vector2 absP3);
	void cubicBy(morda::vector2 relP1, morda::vector2 relP2, morda::vector2 relP3);
	
	void lineBy(morda::vector2 relPos);
	
	struct Vertices{
		std::vector<morda::vector2> pos;
		std::vector<morda::real> alpha;
		
		std::vector<std::uint16_t> inIndices;
		std::vector<std::uint16_t> outIndices;
	};
	
	Vertices stroke(morda::real halfWidth = morda::real(0.5f), morda::real antialiasWidth = morda::real(1.0f), morda::real antialiasAlpha = morda::real(0.35f))const;
};
