#include "WiredArea.hpp"

#include <morda/util/util.hpp>

WiredArea::WiredArea(const stob::Node* chain) :
		Widget(chain),
		Container(chain)
{
	
}


WiredArea::WireSocket::WireSocket(const stob::Node* chain) :
		Widget(chain)
{
	if (auto p = morda::getProperty(chain, "outlet")) {
		if (std::string("left") == p->value()) {
			this->outlet_v = Outlet_e::LEFT;
		}else if (std::string("right") == p->value()) {
			this->outlet_v = Outlet_e::RIGHT;
		}else if (std::string("top") == p->value()) {
			this->outlet_v = Outlet_e::TOP;
		}else if (std::string("bottom") == p->value()) {
			this->outlet_v = Outlet_e::BOTTOM;
		}else{
			this->outlet_v = Outlet_e::CENTER;
		}
	}
}

void WiredArea::WireSocket::connect(const std::shared_ptr<WiredArea::WireSocket>& o) {
	this->setRelayoutNeeded();

	//disconnect existing connection
	if (auto c = this->connection.lock()) {
		c->connection.reset();
	}
	this->connection.reset();

	if (!o) {
		return;
	}

	this->connection = o;
	o->connection = this->sharedFromThis(this);
}
