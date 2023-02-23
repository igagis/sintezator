#pragma once

#include <morda/widgets/group/pile.hpp>

class Block : 
	private morda::pile,
	virtual public morda::widget
{
public:
	Block(const utki::shared_ref<morda::context>& c, const treeml::forest& desc);
	
	Block(const Block&) = delete;
	Block& operator=(const Block&) = delete;
	
	morda::pile& content;
	
private:
	bool captured = false;
	morda::vector2 capturePoint;
	
};
