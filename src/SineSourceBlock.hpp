#pragma once

#include "Block.hpp"

#include "SineSource.hpp"

class SineSourceBlock : public Block{
public:
	SineSourceBlock();
	
	SineSourceBlock(const SineSourceBlock&) = delete;
	SineSourceBlock& operator=(const SineSourceBlock&) = delete;
private:

	std::shared_ptr<SineSource> src;
	
};
