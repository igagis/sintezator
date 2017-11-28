#include "WiredArea.hpp"
#include "Path.hpp"

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
	Path p;
	
	p.to(10);
	p.to(10, 20);
//	p.to(10);
	p.to(morda::Vec2r(50, 100));
	p.to(morda::Vec2r(100, 50));
	
	auto v = p.stroke(2);
	
	glEnable(GL_CULL_FACE);
	{
		auto vba = morda::inst().renderer().factory->createVertexArray(
				{{
					morda::inst().renderer().factory->createVertexBuffer(utki::wrapBuf(v.pos)),
				}},
				morda::inst().renderer().factory->createIndexBuffer(utki::wrapBuf(v.inIndices)),
				morda::VertexArray::Mode_e::TRIANGLE_STRIP
			);

		morda::inst().renderer().shader->colorPos->render(matrix, *vba, 0xff00ff00);
	}
	
	{
		auto vba = morda::inst().renderer().factory->createVertexArray(
				{{
					morda::inst().renderer().factory->createVertexBuffer(utki::wrapBuf(v.pos)),
					morda::inst().renderer().factory->createVertexBuffer(utki::wrapBuf(v.alpha)),
				}},
				morda::inst().renderer().factory->createIndexBuffer(utki::wrapBuf(v.outIndices)),
				morda::VertexArray::Mode_e::TRIANGLE_STRIP
			);

		this->shaderColorPosLum.render(matrix, *vba, 0xff00ff00);
	}
	
	this->Container::render(matrix);
}
