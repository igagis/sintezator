#pragma once

#include "Block.hpp"

#include "SineSource.hpp"
#include "SourceVisitor.hpp"

class SineSourceBlock : public Block{
public:
	SineSourceBlock(const utki::shared_ref<ruis::context>& c, const tml::forest& desc);
	
	SineSourceBlock(const SineSourceBlock&) = delete;
	SineSourceBlock& operator=(const SineSourceBlock&) = delete;
private:

	std::shared_ptr<SineSource> source;
	SourceVisitor sourceVisitor;
	
};
