#include "WireArea.hpp"
#include "Path.hpp"
#include "PathVba.hpp"

#include <morda/util/util.hpp>
#include <morda/Morda.hpp>

namespace{
const morda::real antialiasWidth_c = morda::real(0.55f);
const morda::real splineControlLength_c = morda::real(100);
}

WireArea::WireArea(const puu::forest& desc) :
		widget(desc),
		SizeContainer(desc)
{
	for(const auto& p : desc){
		if(!morda::is_property(p)){
			continue;
		}

		if(p.value == "wireWidth"){
			this->wireHalfWidth = morda::get_property_value(p).to_float() / 2;
		}else if(p.value == "wireColor"){
			this->wireColor = morda::get_property_value(p).to_uint32();
		}else if(p.value == "grabbedColor"){
			this->grabbedColor = morda::get_property_value(p).to_uint32();
		}
	}
}


void WireArea::render(const morda::Matr4r& matrix) const {
	this->container::render(matrix);
	
	for(auto& s : this->sockets){
		if(!s->slave){
			continue;
		}
		
		auto primOutletPos = s->outletPos();
		auto slaveOutletPos = s->slave->outletPos();
		auto p0 = s->pos_in_ancestor(primOutletPos[0], this);
		auto p = s->slave->pos_in_ancestor(slaveOutletPos[0], this) - p0;
		
		Path path;
		path.cubicTo(primOutletPos[1] * splineControlLength_c, p + slaveOutletPos[1] * splineControlLength_c, p);
		
		PathVba vba(path.stroke(this->wireHalfWidth, antialiasWidth_c, 1));
		
		vba.render(morda::Matr4r(matrix).translate(p0), this->wireColor);
	}
	
	if(this->grabbedSocket){
		auto outletPos = this->grabbedSocket->outletPos();
		auto p0 = this->grabbedSocket->pos_in_ancestor(outletPos[0], this);
		
		Path path;
		path.lineTo(mousePos - p0);
		
		PathVba vba(path.stroke(this->wireHalfWidth, antialiasWidth_c, 1));
		
		vba.render(morda::Matr4r(matrix).translate(p0), this->grabbedColor);
	}
}

bool WireArea::on_mouse_move(const morda::Vec2r& pos, unsigned pointerID) {
	if(this->grabbedSocket){
		this->mousePos = pos;
	}
	return this->container::on_mouse_move(pos, pointerID);;
}


void WireArea::lay_out() {
	this->SizeContainer::lay_out();
	
	this->sockets = this->get_all_widgets<WireSocket>();
	// TRACE(<< "this->sockets.size() = " << this->sockets.size() << std::endl)
}
