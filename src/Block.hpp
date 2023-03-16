#pragma once

#include <morda/container.hpp>

class Block : 
	private morda::container,
	virtual public morda::widget
{
public:
	Block(const utki::shared_ref<morda::context>& c, const treeml::forest& desc);
	
	Block(const Block&) = delete;
	Block& operator=(const Block&) = delete;
	
	morda::container& content;
	
private:
	bool captured = false;
	morda::vector2 capturePoint;
	
};
