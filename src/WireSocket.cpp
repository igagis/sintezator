#include "WireSocket.hpp"

#include "WireArea.hpp"

#include <morda/util/util.hpp>

WireSocket::WireSocket(const stob::Node* chain) :
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

void WireSocket::connect(const std::shared_ptr<WireSocket>& o) {
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

void WireSocket::disconnect() {
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


std::array<morda::Vec2r, 2> WireSocket::outletPos() const noexcept{
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

bool WireSocket::onMouseButton(bool isDown, const morda::Vec2r& pos, morda::MouseButton_e button, unsigned pointerID) {
	if(button != morda::MouseButton_e::LEFT){
		return false;
	}
	
	if(auto wa = this->findAncestor<WireArea>()){
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

void WireSocket::onHoverChanged(unsigned pointerID) {
//	TRACE(<< "Hover changed: " << this->isHovered() << " " << this << std::endl)
	if(auto wa = this->findAncestor<WireArea>()){
		if(this->isHovered()){
			wa->hoveredSocket = this->sharedFromThis(this);
		}else{
			if(wa->hoveredSocket.get() == this){
				wa->hoveredSocket.reset();
			}
		}
	}
}