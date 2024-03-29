#include "wire_socket.hpp"

#include "wire_area.hpp"

#include <ruis/util/util.hpp>

WireSocket::WireSocket(const utki::shared_ref<ruis::context>& c, const tml::forest& desc) :
		ruis::widget(std::move(c), desc)
{
	for(const auto& p : desc){
		if(!ruis::is_property(p)){
			continue;
		}

		if(p.value == "outlet"){
			auto v = ruis::get_property_value(p);
			if(v == "left"){
				this->outlet_v = Outlet_e::LEFT;
			}else if(v == "right"){
				this->outlet_v = Outlet_e::RIGHT;
			}else if(v == "top"){
				this->outlet_v = Outlet_e::TOP;
			}else if(v == "bottom"){
				this->outlet_v = Outlet_e::BOTTOM;
			}
		}
	}
}

void WireSocket::connect(const std::shared_ptr<WireSocket>& o) {
	// disconnect existing connection
	this->disconnect();
	
	if(!o || o.get() == this){
		return;
	}
	
	o->disconnect();
	
	this->slave = o;
	this->slave->primary = utki::make_shared_from(*this).to_shared_ptr();
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



std::array<ruis::vector2, 2> WireSocket::outletPos() const noexcept{
	ruis::vector2 dir;
	ruis::vector2 pos;
	switch(this->outlet_v){
		default:
			ASSERT(false)
		case Outlet_e::BOTTOM:
			pos = this->rect().p + this->rect().d.comp_mul(ruis::vector2(0.5, 1));
			dir = ruis::vector2(0, 1);
			break;
		case Outlet_e::LEFT:
			pos = this->rect().p + this->rect().d.comp_mul(ruis::vector2(0, 0.5));
			dir = ruis::vector2(-1, 0);
			break;
		case Outlet_e::RIGHT:
			pos = this->rect().p + this->rect().d.comp_mul(ruis::vector2(1, 0.5));
			dir = ruis::vector2(1, 0);
			break;
		case Outlet_e::TOP:
			pos = this->rect().p + this->rect().d.comp_mul(ruis::vector2(0.5, 0));
			dir = ruis::vector2(0, -1);
			break;
	}
	return {{pos, dir}};
}

bool WireSocket::on_mouse_button(const ruis::mouse_button_event& e) {
	if(e.button != ruis::mouse_button::left){
		return false;
	}
	
	if(auto wa = this->try_get_ancestor<WireArea>()){
		if(e.is_down){
			std::shared_ptr<WireSocket> grabbedSocket;
			if(auto p = this->getRemote()){
				p->disconnect();
				grabbedSocket = std::move(p);
			}else{
				grabbedSocket = utki::make_shared_from(*this).to_shared_ptr();
			}
			
			wa->grabbedSocket = std::move(grabbedSocket);
			wa->mousePos = this->pos_in_ancestor(e.pos, wa);
		}else{
			wa->grabbedSocket->connect(wa->hoveredSocket);
			wa->grabbedSocket.reset();
		}
		return true;
	}
	return false;
}

void WireSocket::on_hovered_change(unsigned pointerID) {
	// TRACE(<< "Hover changed: " << this->is_hovered() << " " << this << std::endl)
	if(auto wa = this->try_get_ancestor<WireArea>()){
		if(this->is_hovered()){
			wa->hoveredSocket = utki::make_shared_from(*this).to_shared_ptr();
		}else{
			if(wa->hoveredSocket.get() == this){
				wa->hoveredSocket.reset();
			}
		}
	}
}

std::shared_ptr<WireSocket> WireSocket::getRemote() {
	if(this->slave){
		return this->slave;
	}
	
	if(auto p = this->primary.lock()){
		return p;
	}
	
	return nullptr;
}
