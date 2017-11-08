#pragma once

#include <vector>
#include <morda/config.hpp>

class Path {	
	std::vector<morda::Vec2r> path;
	
	bool isClosed = false;
	
public:
	Path(morda::Vec2r firstPoint = morda::Vec2r(morda::real(0)));
	
	Path(const Path&) = delete;
	Path& operator=(const Path&) = delete;
	
	void close(){
		this->isClosed = true;
	}
	
	void lineTo(morda::Vec2r absPos);
	
	struct Vertices{
		std::vector<morda::Vec2r> pos;
		std::vector<morda::real> alpha;
		
		std::vector<std::uint16_t> indices;
	};
	
	Vertices stroke(morda::real width = morda::real(1), morda::real antiAliasWidth = morda::real(1));
};
