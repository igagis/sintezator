#include "WiredArea.hpp"
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

WiredArea::WiredArea(const stob::Node* chain) :
		Widget(chain),
		Container(chain)
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


WiredArea::WireSocket::WireSocket(const stob::Node* chain) :
		Widget(chain)
{
	this->outlet_v = Outlet_e::BOTTOM;
	
	if (auto p = morda::getProperty(chain, "outlet")) {
		if (std::string("left") == p->value()) {
			this->outlet_v = Outlet_e::LEFT;
		}else if (std::string("right") == p->value()) {
			this->outlet_v = Outlet_e::RIGHT;
		}else if (std::string("top") == p->value()) {
			this->outlet_v = Outlet_e::TOP;
		}else if (std::string("bottom") == p->value()) {
			this->outlet_v = Outlet_e::BOTTOM;
		}
	}
}

void WiredArea::WireSocket::connect(const std::shared_ptr<WiredArea::WireSocket>& o) {
	this->setRelayoutNeeded();

	//disconnect existing connection
	this->disconnect();
	
	if(!o || o.get() == this){
		return;
	}
	
	o->disconnect();
	
	this->slave = o;
	this->slave->primary = this->sharedFromThis(this);
}

void WiredArea::WireSocket::disconnect() {
	if(this->slave){
		ASSERT(!this->primary.lock())
		ASSERT(this->slave->primary.lock().get() == this)
		ASSERT(!this->slave->slave)
		this->slave->primary.reset();
		this->slave.reset();
	}else if(auto p = this->primary.lock()){
		ASSERT(!p->primary.lock())
		ASSERT(p->slave.get() == this)
		p->slave.reset();
		this->primary.reset();
	}
}


void WiredArea::render(const morda::Matr4r& matrix) const {
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

bool WiredArea::onMouseMove(const morda::Vec2r& pos, unsigned pointerID) {
	if(this->grabbedSocket){
		this->mousePos = pos;
	}
	return this->Container::onMouseMove(pos, pointerID);;
}


void WiredArea::layOut() {
	this->Container::layOut();
	
	this->sockets = this->find<WireSocket>();
	TRACE(<< "this->sockets.size() = " << this->sockets.size() << std::endl)
}

std::array<morda::Vec2r, 2> WiredArea::WireSocket::outletPos() const noexcept{
	morda::Vec2r dir;
	switch(this->outlet_v){
		default:
			ASSERT(false)
		case Outlet_e::BOTTOM:
			dir = morda::Vec2r(0, 1);
			break;
		case Outlet_e::LEFT:
			dir = morda::Vec2r(-1, 0);
			break;
		case Outlet_e::RIGHT:
			dir = morda::Vec2r(1, 0);
			break;
		case Outlet_e::TOP:
			dir = morda::Vec2r(0, -1);
			break;
	}
	return {{this->rect().center(), dir}};
}

bool WiredArea::WireSocket::onMouseButton(bool isDown, const morda::Vec2r& pos, morda::MouseButton_e button, unsigned pointerID) {
	if(button != morda::MouseButton_e::LEFT){
		return false;
	}
	
	if(auto wa = this->findAncestor<WiredArea>()){
		if(isDown){
			wa->grabbedSocket = this->sharedFromThis(this);
			wa->mousePos = this->calcPosInParent(pos, wa);
		}else{
			this->connect(wa->hoveredSocket);
			wa->grabbedSocket.reset();
		}
		return true;
	}
	return false;
}

void WiredArea::WireSocket::onHoverChanged(unsigned pointerID) {
	if(auto wa = this->findAncestor<WiredArea>()){
		if(this->isHovered()){
			wa->hoveredSocket = this->sharedFromThis(this);
		}else{
			wa->hoveredSocket.reset();
		}
	}
}
