#pragma once

#include <ruis/widgets/container.hpp>

class Block : 
	private ruis::container,
	virtual public ruis::widget
{
public:
	Block(const utki::shared_ref<ruis::context>& c, const tml::forest& desc);
	
	Block(const Block&) = delete;
	Block& operator=(const Block&) = delete;
	
	ruis::container& content;
	
private:
	bool captured = false;
	ruis::vector2 capturePoint;
	
};
