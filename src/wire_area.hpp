#pragma once

#include "wire_socket.hpp"

class WireArea : public morda::container{
	friend class WireSocket;
	
	const morda::real deafultWireHalfWidth_c = morda::real(0.25f);
	const uint32_t defaultWireColor_c = 0xff0000ff;
	const uint32_t defaultGrabbedColor_c = 0xff808080;

	morda::real wireHalfWidth = deafultWireHalfWidth_c;
	uint32_t wireColor = defaultWireColor_c;
	uint32_t grabbedColor = defaultGrabbedColor_c;
public:
	WireArea(const WireArea&) = delete;
	WireArea& operator=(const WireArea&) = delete;
	
	WireArea(const utki::shared_ref<morda::context>& c, const treeml::forest& desc);
	
	void render(const morda::matrix4& matrix)const override;

	void on_lay_out() override;
	
	bool on_mouse_move(const morda::mouse_move_event& e)override;

private:
	morda::vector2 mousePos;
	
	std::shared_ptr<WireSocket> grabbedSocket;
	std::shared_ptr<WireSocket> hoveredSocket;
	
	std::vector<utki::shared_ref<WireSocket>> sockets;

};

