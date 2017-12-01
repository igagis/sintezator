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

namespace kolme{
template <class T> Vector2<T> sqrt(const Vector2<T>& v){
	using std::sqrt;
	return Vector2<T>(sqrt(v.x), sqrt(v.y));
}

template <class T> Vector2<T> min(const Vector2<T>& v1, const Vector2<T>& v2){
	using std::min;
	return Vector2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
}

template <class T> Vector2<T> max(const Vector2<T>& v1, const Vector2<T>& v2){
	using std::max;
	return Vector2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
}

template <class T> Vector2<T> abs(const Vector2<T>& v){
	using std::abs;
	return Vector2<T>(abs(v.x), abs(v.y));
}
}

void Path::cubicTo(morda::Vec2r p1, morda::Vec2r p2, morda::Vec2r p3) {
	auto p0 = this->path.back();

	auto bezier = [p0, p1, p2, p3](morda::real t){
		using utki::pow3;
		using utki::pow2;
		return pow3(1 - t) * p0 + 3 * t * pow2(1 - t) * p1 + 3 * pow2(t) * (1 - t) * p2 + pow3(t) * p3;
	};
	
	auto a = -3 * p0 + 9 * p1 - 9 * p2 + 3 * p3;
	auto b = 6 * p0 - 12 * p1 + 6 * p2;
	auto c = -3 * p0 + 3 * p1;
	
	TRACE(<< "a = " << a << ", b = " << b << ", c = " << c << std::endl)
	
	auto diffBezier = [a, b ,c](morda::Vec2r t){
		return a.compMul(t).compMul(t) + b.compMul(t) + c;
	};
	
	auto D = b.compMul(b) - 4 * a.compMul(c);
	
	using std::sqrt;
	using std::min;
	using std::max;
	
	//dBezier roots
	auto t1 = (-b + sqrt(D)).compDiv(2 * a);
	auto t2 = (-b - sqrt(D)).compDiv(2 * a);
	
	TRACE(<< "t1 = " << t1 << ", t2 = " << t2 << std::endl)
	
	for(unsigned i = 0; i != t1.size(); ++i){
		using std::isnan;
		if(isnan(t1[i])){
			t1[i] = 0;
		}
	}
	t1 = max(morda::Vec2r(0), min(t1, morda::Vec2r(1)));
	
	for(unsigned i = 0; i != t2.size(); ++i){
		using std::isnan;
		if(isnan(t2[i])){
			t2[i] = 0;
		}
	}
	t2 = max(morda::Vec2r(0), min(t2, morda::Vec2r(1)));
	
	auto tExt = -b.compDiv(2 * a); //extremum position
	tExt = max(morda::Vec2r(0), min(tExt, morda::Vec2r(1)));
	
	using std::abs;
	
	auto absDiffBezierMin = abs(diffBezier(tExt)); //extremum value
	
	absDiffBezierMin = min(absDiffBezierMin, abs(diffBezier(t1)));
	absDiffBezierMin = min(absDiffBezierMin, abs(diffBezier(t2)));
	absDiffBezierMin = min(absDiffBezierMin, abs(diffBezier(0)));
	absDiffBezierMin = min(absDiffBezierMin, abs(diffBezier(1)));
	
	morda::real minVel = max(absDiffBezierMin.x, absDiffBezierMin.y);
	
	if(minVel > 0){
		const morda::real minStep_c = 1.4f;
		auto dt = minStep_c / minVel;
		
		for(morda::real t = 0; t < 1; t += dt){
			this->lineTo(bezier(t));
		}
		this->lineTo(bezier(1));
	}else{
		this->lineTo(bezier(min(tExt.x, tExt.y)));
		this->lineTo(bezier(max(tExt.x, tExt.y)));
		this->lineTo(bezier(1));
	}
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
		
		if(!prev){
			ret.pos.push_back((*cur) + normal * miter + normal.rotation(utki::pi<morda::real>() / 4) * antialiasWidth * std::sqrt(2));
		}else if(!next){
			ret.pos.push_back((*cur) + normal * miter + normal.rotation(-utki::pi<morda::real>() / 4) * antialiasWidth * std::sqrt(2));
		}else{
			ret.pos.push_back((*cur) + normal * antialiasMiter);
		}
		
		ret.alpha.push_back(0);
		++inIndex;
		
		ret.pos.push_back((*cur) + normal * miter);
		ret.alpha.push_back(antialiasAlpha);
		ret.inIndices.push_back(inIndex);
		++inIndex;
		
		ret.pos.push_back((*cur) - normal * miter);
		ret.alpha.push_back(antialiasAlpha);
		ret.inIndices.push_back(inIndex);
		++inIndex;
		
		if(!prev){
			ASSERT(next)
			ret.pos.push_back((*cur) - normal * miter - normal.rotation(-utki::pi<morda::real>() / 4) * antialiasWidth * std::sqrt(2));
		}else if(!next){
			ASSERT(prev)
			ret.pos.push_back((*cur) - normal * miter - normal.rotation(utki::pi<morda::real>() / 4) * antialiasWidth * std::sqrt(2));
		}else{
			ret.pos.push_back((*cur) - normal * antialiasMiter);
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
