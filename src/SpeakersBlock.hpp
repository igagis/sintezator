#pragma once

#include "Block.hpp"
#include "InputVisitor.hpp"

#include <aumiks/speakers.hpp>

class SpeakersBlock : public Block{
	std::unique_ptr<aumiks::sink> sink;
	InputVisitor inputVisitor;
public:
	SpeakersBlock(const utki::shared_ref<morda::context>& c, const treeml::forest& desc);
	
	SpeakersBlock(const SpeakersBlock&) = delete;
	SpeakersBlock& operator=(const SpeakersBlock&) = delete;
	
private:

};
