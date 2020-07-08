#pragma once

#include <morda/widgets/group/size_container.hpp>

#include "WireSocket.hpp"

class WireArea : public morda::size_container{
	friend class WireSocket;
	
	const morda::real deafultWireHalfWidth_c = morda::real(0.25f);
	const std::uint32_t defaultWireColor_c = 0xff0000ff;
	const std::uint32_t defaultGrabbedColor_c = 0xff808080;

	morda::real wireHalfWidth = deafultWireHalfWidth_c;
	std::uint32_t wireColor = defaultWireColor_c;
	std::uint32_t grabbedColor = defaultGrabbedColor_c;
public:
	WireArea(const WireArea&) = delete;
	WireArea& operator=(const WireArea&) = delete;
	
	WireArea(std::shared_ptr<morda::context> c, const puu::forest& desc);
	
	void render(const morda::matrix4& matrix)const override;

	void lay_out() override;
	
	bool on_mouse_move(const morda::mouse_move_event& e)override;

private:
	morda::vector2 mousePos;
	
	std::shared_ptr<WireSocket> grabbedSocket;
	std::shared_ptr<WireSocket> hoveredSocket;
	
	std::vector<std::shared_ptr<WireSocket>> sockets;

};

