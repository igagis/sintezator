#pragma once

#include <vector>
#include <morda/config.hpp>

class Path {	
	std::vector<morda::Vec2r> path;
	
public:
	Path() = default;
	
	Path(const Path&) = delete;
	Path& operator=(const Path&) = delete;
	
	void to(morda::Vec2r absPos);
	
	struct Vertices{
		std::vector<morda::Vec2r> pos;
		std::vector<morda::real> alpha;
		
		std::vector<std::uint16_t> indices;
	};
	
	Vertices stroke(morda::real width = morda::real(1), morda::real antiAliasWidth = morda::real(1));
};
