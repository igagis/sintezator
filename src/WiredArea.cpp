#include "WiredArea.hpp"

#include <morda/util/util.hpp>

WiredArea::WiredArea(const stob::Node* chain) :
		Widget(chain)
{
	
}


WiredArea::WireSocket::WireSocket(const stob::Node* chain) :
		Widget(chain)
{
	if (auto p = morda::getProperty(chain, "wireOut")) {
		if (std::string("left") == p->value()) {
			this->wireOut_v = WireOut_e::LEFT;
		}else if (std::string("right") == p->value()) {
			this->wireOut_v = WireOut_e::RIGHT;
		}else if (std::string("top") == p->value()) {
			this->wireOut_v = WireOut_e::TOP;
		}else if (std::string("bottom") == p->value()) {
			this->wireOut_v = WireOut_e::BOTTOM;
		}else{
			this->wireOut_v = WireOut_e::CENTER;
		}
	}
}
