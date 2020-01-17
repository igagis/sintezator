#pragma once

#include <morda/widgets/group/SizeContainer.hpp>

#include "WireSocket.hpp"

class WireArea : public morda::SizeContainer{
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
	
	WireArea(const puu::forest& desc);
	
	void render(const morda::Matr4r& matrix) const override;

	void layOut() override;
	
	bool onMouseMove(const morda::Vec2r& pos, unsigned pointerID) override;

private:
	morda::Vec2r mousePos;
	
	std::shared_ptr<WireSocket> grabbedSocket;
	std::shared_ptr<WireSocket> hoveredSocket;
	
	std::vector<std::shared_ptr<WireSocket>> sockets;

};

