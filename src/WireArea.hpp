#pragma once

#include <morda/widgets/group/SizeContainer.hpp>

#include "WireSocket.hpp"

class WireArea : public morda::SizeContainer{
	friend class WireSocket;
	
	morda::real wireHalfWidth;
	std::uint32_t wireColor;
	std::uint32_t grabbedColor;
public:
	WireArea(const WireArea&) = delete;
	WireArea& operator=(const WireArea&) = delete;
	
	WireArea(const stob::Node* chain);
	
	void render(const morda::Matr4r& matrix) const override;

	void layOut() override;
	
	bool onMouseMove(const morda::Vec2r& pos, unsigned pointerID) override;

private:
	morda::Vec2r mousePos;
	
	std::shared_ptr<WireSocket> grabbedSocket;
	std::shared_ptr<WireSocket> hoveredSocket;
	
	std::list<std::shared_ptr<WireSocket>> sockets;

};

