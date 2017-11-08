#include "Path.hpp"

Path::Path(morda::Vec2r firstPoint) {
	this->path.emplace_back(firstPoint);
}

void Path::lineTo(morda::Vec2r absPos) {
	this->path.emplace_back(absPos);
}



Path::Vertices Path::stroke(morda::real width, morda::real antiAliasWidth) {
	Vertices ret;
	
	//TODO:
	
	return ret;
}
