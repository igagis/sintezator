#include "WiredArea.hpp"
#include "Path.hpp"
#include "PathVba.hpp"

#include <morda/util/util.hpp>
#include <morda/Morda.hpp>

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

void WiredArea::render(const morda::Matr4r& matrix) const {
	this->Container::render(matrix);
	
	Path p;
	
	p.lineTo(100);
//	p.lineTo(10, 20);
//	p.lineTo(morda::Vec2r(50, 100));
//	p.lineTo(morda::Vec2r(100, 50));
	p.cubicBy(morda::Vec2r(50, -100), morda::Vec2r(200, 200), morda::Vec2r(200, 0));
	
	PathVba v(p.stroke(0.5, 1, 0.5));

	glEnable(GL_CULL_FACE);	
	v.render(matrix, 0xff00ff00);
}
