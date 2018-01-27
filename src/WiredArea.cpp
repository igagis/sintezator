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
	
	if(!o){
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
		path.cubicTo(primOutletPos[1] * 100, p + slaveOutletPos[1] * 100, p);
		
		PathVba vba(path.stroke(0.25, 0.55, 1));
		
		vba.render(morda::Matr4r(matrix).translate(p0), 0xff0000ff);
	}
	
	
	
	
	
	Path p;
	
	p.lineTo(100);
//	p.lineTo(10, 20);
//	p.lineTo(morda::Vec2r(50, 100));
//	p.lineTo(morda::Vec2r(100, 50));
	p.cubicBy(morda::Vec2r(50, -100), morda::Vec2r(200, 200), morda::Vec2r(200, 0));
	
	PathVba v(p.stroke(0.5, 1, 0.5));

//	glEnable(GL_CULL_FACE);
	v.render(matrix, 0xff00ff00);
}

void WiredArea::layOut() {
	this->Container::layOut();
	
	this->sockets = this->findChildren<WireSocket>();
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
			dir = morda::Vec2r(1, 0);
			break;
	}
	return {{this->rect().center(), dir}};
}
