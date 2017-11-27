#include "Path.hpp"

void Path::to(morda::Vec2r absPos) {
	this->path.emplace_back(absPos);
}



Path::Vertices Path::stroke(morda::real halfWidth, morda::real antialiasWidth)const{
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
		
		ret.pos.push_back((*cur) + normal * antialiasMiter);
		ret.alpha.push_back(0);
		++inIndex;
		
		ret.pos.push_back((*cur) + normal * miter);
		ret.alpha.push_back(1);
		ret.inIndices.push_back(inIndex);
		++inIndex;
		
		ret.pos.push_back((*cur) - normal * miter);
		ret.alpha.push_back(1);
		ret.inIndices.push_back(inIndex);
		++inIndex;
		
		ret.pos.push_back((*cur) - normal * antialiasMiter);
		ret.alpha.push_back(0);
		++inIndex;
	}
	
	for(unsigned i = 0; i != this->path.size(); ++i){
		ret.outIndices.push_back(4 * i);
		ret.outIndices.push_back(4 * i + 1);
	}
	
	return ret;
}
