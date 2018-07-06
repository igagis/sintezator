#include <cmath>

#include "Path.hpp"

void Path::lineTo(morda::Vec2r absPos) {
	this->path.emplace_back(absPos);
}

void Path::lineBy(morda::Vec2r relPos) {
	ASSERT(this->path.size() != 0)
	this->lineTo(this->path.back() + relPos);
}

void Path::cubicBy(morda::Vec2r relP1, morda::Vec2r relP2, morda::Vec2r relP3) {
	ASSERT(this->path.size() != 0)
	auto& d = this->path.back();
	this->cubicTo(d + relP1, d + relP2, d + relP3);
}




void Path::cubicTo(morda::Vec2r p1, morda::Vec2r p2, morda::Vec2r p3) {
	auto p0 = this->path.back();

	auto bezier = [p0, p1, p2, p3](morda::real t){
		using utki::pow3;
		using utki::pow2;
		return pow3(1 - t) * p0 + 3 * t * pow2(1 - t) * p1 + 3 * pow2(t) * (1 - t) * p2 + pow3(t) * p3;
	};
	
	auto lengthEst = (p1 - p0).magnitude() + (p2 - p1).magnitude() + (p3 - p2).magnitude();
	
	const morda::real minStep_c = 10.0f;
	
	auto numSteps = lengthEst / minStep_c;

	auto dt = 1 / numSteps;

	//NOTE: start from dt because 0th point is already there in the path
	for(morda::real t = dt; t < 1; t += dt){
		this->lineTo(bezier(t));
	}
	this->lineTo(bezier(1));
}


Path::Vertices Path::stroke(morda::real halfWidth, morda::real antialiasWidth, morda::real antialiasAlpha)const{
	Vertices ret;

	if(this->path.size() <= 1){
		return ret;
	}
	
	const decltype(this->path)::value_type *prev = nullptr, *cur = nullptr, *next = nullptr;
	
	std::uint16_t inIndex = 0;
	
	for(auto i = this->path.begin(); i != this->path.end(); ++i){
		prev = cur;
		cur = &(*i);
		{
			auto ii = i;
			++ii;
			if(ii == this->path.end()){
				next = nullptr;
			}else{
				next = &(*ii);
			}
		}
		
		morda::Vec2r prevNormal, nextNormal;
		
		ASSERT(prev || next)
		
		if(prev){
			prevNormal = (*cur - *prev).normalize();
			std::swap(prevNormal.x, prevNormal.y);
			prevNormal.x = -prevNormal.x;
		}
		if(next){
			nextNormal = (*next - *cur).normalize();
			std::swap(nextNormal.x, nextNormal.y);
			nextNormal.x = -nextNormal.x;
		}else{
			ASSERT(prev)
			nextNormal = prevNormal;
		}
		if(!prev){
			ASSERT(next)
			prevNormal = nextNormal;
		}
		
		auto normal = (prevNormal + nextNormal).normalize();
		
		auto miterCoeff = 1 / (normal * prevNormal);
		auto miter = miterCoeff * halfWidth;
		auto antialiasMiter = miterCoeff * (halfWidth + antialiasWidth);
		
		using std::sqrt;
		using utki::pi;
		
		if(!prev){
			ASSERT(next)
			ret.pos.push_back((*cur) - normal * miter - normal.rotation(-pi<morda::real>() / 4) * antialiasWidth * sqrt(2));
		}else if(!next){
			ASSERT(prev)
			ret.pos.push_back((*cur) - normal * miter - normal.rotation(pi<morda::real>() / 4) * antialiasWidth * sqrt(2));
		}else{
			ret.pos.push_back((*cur) - normal * antialiasMiter);
		}
		ret.alpha.push_back(0);
		++inIndex;
		
		ret.pos.push_back((*cur) - normal * miter);
		ret.alpha.push_back(antialiasAlpha);
		ret.inIndices.push_back(inIndex);
		++inIndex;
		
		ret.pos.push_back((*cur) + normal * miter);
		ret.alpha.push_back(antialiasAlpha);
		ret.inIndices.push_back(inIndex);
		++inIndex;
		
		if(!prev){
			ret.pos.push_back((*cur) + normal * miter + normal.rotation(utki::pi<morda::real>() / 4) * antialiasWidth * std::sqrt(2));
		}else if(!next){
			ret.pos.push_back((*cur) + normal * miter + normal.rotation(-utki::pi<morda::real>() / 4) * antialiasWidth * std::sqrt(2));
		}else{
			ret.pos.push_back((*cur) + normal * antialiasMiter);
		}
		ret.alpha.push_back(0);
		++inIndex;
	}
	
	ret.outIndices.push_back(3);
	ret.outIndices.push_back(2);
	
	for(unsigned i = 0; i != this->path.size(); ++i){
		ret.outIndices.push_back(4 * i);
		ret.outIndices.push_back(4 * i + 1);
	}
	
	for(unsigned i = this->path.size() - 1; i != 0; --i){
		ret.outIndices.push_back(4 * i + 3);
		ret.outIndices.push_back(4 * i + 2);
	}
	
	ret.outIndices.push_back(3);
	ret.outIndices.push_back(2);
	
	return ret;
}
