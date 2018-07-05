#include "WireArea.hpp"
#include "Path.hpp"
#include "PathVba.hpp"

#include <morda/util/util.hpp>
#include <morda/Morda.hpp>

namespace{
const morda::real antialiasWidth_c = morda::real(0.55f);
const morda::real splineControlLength_c = morda::real(100);
const morda::real deafultWireHalfWidth_c = morda::real(0.25f);
const std::uint32_t defaultWireColor_c = 0xff0000ff;
const std::uint32_t defaultGrabbedColor_c = 0xff808080;
}

WireArea::WireArea(const stob::Node* chain) :
		Widget(chain),
		SizeContainer(chain)
{
	if(auto p = morda::getProperty(chain, "wireWidth")){
		this->wireHalfWidth = morda::real(p->asFloat()) / 2;
	}else{
		this->wireHalfWidth = deafultWireHalfWidth_c;
	}
	
	if(auto p = morda::getProperty(chain, "wireColor")){
		this->wireColor = p->asUint32();
	}else{
		this->wireColor = defaultWireColor_c;
	}
	
	if(auto p = morda::getProperty(chain, "grabbedColor")){
		this->grabbedColor = p->asUint32();
	}else{
		this->grabbedColor = defaultGrabbedColor_c;
	}
}


void WireArea::render(const morda::Matr4r& matrix) const {
	this->Container::render(matrix);
	
	for(auto& s : this->sockets){
		if(!s->slave){
			continue;
		}
		
		auto primOutletPos = s->outletPos();
		auto slaveOutletPos = s->slave->outletPos();
		auto p0 = s->calcPosInParent(primOutletPos[0], this);
		auto p = s->slave->calcPosInParent(slaveOutletPos[0], this) - p0;
		
		Path path;
		path.cubicTo(primOutletPos[1] * splineControlLength_c, p + slaveOutletPos[1] * splineControlLength_c, p);
		
		PathVba vba(path.stroke(this->wireHalfWidth, antialiasWidth_c, 1));
		
		vba.render(morda::Matr4r(matrix).translate(p0), this->wireColor);
	}
	
	if(this->grabbedSocket){
		auto outletPos = this->grabbedSocket->outletPos();
		auto p0 = this->grabbedSocket->calcPosInParent(outletPos[0], this);
		
		Path path;
		path.lineTo(mousePos - p0);
		
		PathVba vba(path.stroke(this->wireHalfWidth, antialiasWidth_c, 1));
		
		vba.render(morda::Matr4r(matrix).translate(p0), this->grabbedColor);
	}
}

bool WireArea::onMouseMove(const morda::Vec2r& pos, unsigned pointerID) {
	if(this->grabbedSocket){
		this->mousePos = pos;
	}
	return this->Container::onMouseMove(pos, pointerID);;
}


void WireArea::layOut() {
	this->SizeContainer::layOut();
	
	this->sockets = this->find<WireSocket>();
	TRACE(<< "this->sockets.size() = " << this->sockets.size() << std::endl)
}
