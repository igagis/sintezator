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
	//disconnect existing connection
	this->disconnect();
	
	if(!o || o.get() == this){
		return;
	}
	
	o->disconnect();
	
	this->slave = o;
	this->slave->primary = this->sharedFromThis(this);
	this->onConnected(*this->slave);
}

void WireSocket::disconnect() {
	if(this->slave){
		ASSERT(!this->primary.lock())
		ASSERT(this->slave->primary.lock().get() == this)
		ASSERT(!this->slave->slave)
		this->slave->primary.reset();
		auto oldSlave = std::move(this->slave);
		this->slave.reset();
		this->onDisconnected(*oldSlave);
	}else if(auto p = this->primary.lock()){
		ASSERT(!p->primary.lock())
		ASSERT(p->slave.get() == this)
		p->disconnect();
	}
}



std::array<morda::Vec2r, 2> WireSocket::outletPos() const noexcept{
	morda::Vec2r dir;
	morda::Vec2r pos;
	switch(this->outlet_v){
		default:
			ASSERT(false)
		case Outlet_e::BOTTOM:
			pos = this->rect().p + this->rect().d.compMul(morda::Vec2r(0.5, 1));
			dir = morda::Vec2r(0, 1);
			break;
		case Outlet_e::LEFT:
			pos = this->rect().p + this->rect().d.compMul(morda::Vec2r(0, 0.5));
			dir = morda::Vec2r(-1, 0);
			break;
		case Outlet_e::RIGHT:
			pos = this->rect().p + this->rect().d.compMul(morda::Vec2r(1, 0.5));
			dir = morda::Vec2r(1, 0);
			break;
		case Outlet_e::TOP:
			pos = this->rect().p + this->rect().d.compMul(morda::Vec2r(0.5, 0));
			dir = morda::Vec2r(0, -1);
			break;
	}
	return {{pos, dir}};
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

void WireSocket::onConnected(WireSocket& to) {
	if (this->connected) {
		this->connected(*this, to);
	}
}

void WireSocket::onDisconnected(WireSocket& from) {
	if(this->disconnected){
		this->disconnected(*this, from);
	}
}

