#pragma once

#include <morda/widgets/group/Pile.hpp>

class Block : 
	private morda::Pile,
	virtual public morda::Widget
{
public:
	Block(const puu::forest& desc);
	
	Block(const Block&) = delete;
	Block& operator=(const Block&) = delete;
	
	morda::Pile& content;
	
private:
	bool captured = false;
	morda::Vec2r capturePoint;
	
};
