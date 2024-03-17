#include "wire_area.hpp"

#include <ruis/paint/path_vao.hpp>

#include <ruis/context.hpp>
#include <ruis/util/util.hpp>

#include <ruis/layouts/layout.hpp>

namespace{
const ruis::real antialiasWidth_c = ruis::real(0.55f);
const ruis::real splineControlLength_c = ruis::real(100);
}

WireArea::WireArea(const utki::shared_ref<ruis::context>& c, const tml::forest& desc) :
		widget(std::move(c), desc),
		container(this->context, desc, ruis::layout::size)
{
	for(const auto& p : desc){
		if(!ruis::is_property(p)){
			continue;
		}

		if(p.value == "wireWidth"){
			this->wireHalfWidth = ruis::get_property_value(p).to_float() / 2;
		}else if(p.value == "wireColor"){
			this->wireColor = ruis::get_property_value(p).to_uint32();
		}else if(p.value == "grabbedColor"){
			this->grabbedColor = ruis::get_property_value(p).to_uint32();
		}
	}
}


void WireArea::render(const ruis::matrix4& matrix) const {
	this->container::render(matrix);
	
	for(auto& s : this->sockets){
		if(!s.get().slave){
			continue;
		}
		
		auto primOutletPos = s.get().outletPos();
		auto slaveOutletPos = s.get().slave->outletPos();
		auto p0 = s.get().pos_in_ancestor(primOutletPos[0], this);
		auto p = s.get().slave->pos_in_ancestor(slaveOutletPos[0], this) - p0;
		
		ruis::path path;
		path.cubic_to(primOutletPos[1] * splineControlLength_c, p + slaveOutletPos[1] * splineControlLength_c, p);
		
		ruis::path_vao vba(this->context.get().renderer);
		vba.set(path.stroke(this->wireHalfWidth, antialiasWidth_c, 1));
		
		vba.render(ruis::matrix4(matrix).translate(p0), this->wireColor);
	}
	
	if(this->grabbedSocket){
		auto outletPos = this->grabbedSocket->outletPos();
		auto p0 = this->grabbedSocket->pos_in_ancestor(outletPos[0], this);
		
		ruis::path path;
		path.line_to(mousePos - p0);
		
		ruis::path_vao vba(this->context.get().renderer);
		vba.set(path.stroke(this->wireHalfWidth, antialiasWidth_c, 1));
		
		vba.render(ruis::matrix4(matrix).translate(p0), this->grabbedColor);
	}
}

bool WireArea::on_mouse_move(const ruis::mouse_move_event& e) {
	if(this->grabbedSocket){
		this->mousePos = e.pos;
		return this->container::on_mouse_move(
				ruis::mouse_move_event{
					e.pos,
					e.pointer_id,
					true
				}
			);
	}
	return this->container::on_mouse_move(e);
}

void WireArea::on_lay_out() {
	this->container::on_lay_out();
	
	this->sockets = this->get_all_widgets<WireSocket>();
	// TRACE(<< "this->sockets.size() = " << this->sockets.size() << std::endl)
}
