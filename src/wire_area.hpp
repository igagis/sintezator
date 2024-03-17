#pragma once

#include "wire_socket.hpp"

class WireArea : public ruis::container{
	friend class WireSocket;
	
	const ruis::real deafultWireHalfWidth_c = ruis::real(0.25f);
	const uint32_t defaultWireColor_c = 0xff0000ff;
	const uint32_t defaultGrabbedColor_c = 0xff808080;

	ruis::real wireHalfWidth = deafultWireHalfWidth_c;
	uint32_t wireColor = defaultWireColor_c;
	uint32_t grabbedColor = defaultGrabbedColor_c;
public:
	WireArea(const WireArea&) = delete;
	WireArea& operator=(const WireArea&) = delete;
	
	WireArea(const utki::shared_ref<ruis::context>& c, const tml::forest& desc);
	
	void render(const ruis::matrix4& matrix)const override;

	void on_lay_out() override;
	
	bool on_mouse_move(const ruis::mouse_move_event& e)override;

private:
	ruis::vector2 mousePos;
	
	std::shared_ptr<WireSocket> grabbedSocket;
	std::shared_ptr<WireSocket> hoveredSocket;
	
	std::vector<utki::shared_ref<WireSocket>> sockets;

};

