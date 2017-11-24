#include "Path.hpp"

void Path::to(morda::Vec2r absPos) {
	this->path.emplace_back(absPos);
}



Path::Vertices Path::stroke(morda::real width, morda::real antiAliasWidth) {
	Vertices ret;
	
	//TODO:
	
	return ret;
}
