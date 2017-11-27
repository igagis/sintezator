#include "Path.hpp"

void Path::to(morda::Vec2r absPos) {
	this->path.emplace_back(absPos);
}



Path::Vertices Path::stroke(morda::real halfWidth, morda::real antiAliasWidth) {
	Vertices ret;

	if(this->path.size() <= 1){
		return ret;
	}
	
	decltype(this->path)::value_type *prev = nullptr, *cur = nullptr, *next = nullptr;
	
	std::uint16_t inIndex = 0;
	
	for(auto i = this->path.begin(); i != this->path.end(); ++i){
		prev = cur;
		cur = &(*i);
		{
			auto ii = i;
			++ii;
			next = ii == this->path.end() ? nullptr : &(*ii);
		}
		
		morda::Vec2r prevNormal, nextNormal;
		
		ASSERT(prev || next)
		
		if(!prev){
			ASSERT(next)
			nextNormal = (*next - *cur).normalize();
			std::swap(nextNormal.x, nextNormal.y);
			nextNormal.x = -nextNormal.x;
			prevNormal = nextNormal;
		}else{
			prevNormal = (*cur - *prev).normalize();
			std::swap(prevNormal.x, prevNormal.y);
			prevNormal.x = -prevNormal.x;
			
			if(!next){
				ASSERT(prev)
				nextNormal = prevNormal;
			}else{
				nextNormal = (*next - *cur).normalize();
				std::swap(nextNormal.x, nextNormal.y);
				nextNormal.x = -nextNormal.x;
			}
		}
		
		auto normal = (prevNormal + nextNormal).normalize();
		
		auto miter = halfWidth / (normal * prevNormal);
		
		ret.pos.push_back((*cur) + normal * miter);
		ret.pos.push_back((*cur) - normal * miter);
		
		ret.inIndices.push_back(inIndex);
		++inIndex;
		ret.inIndices.push_back(inIndex);
		++inIndex;
	}
	
	return ret;
}
