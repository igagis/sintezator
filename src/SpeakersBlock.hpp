#pragma once

#include "Block.hpp"
#include "InputVisitor.hpp"

#include <aumiks/speakers.hpp>

class SpeakersBlock : public Block{
	std::unique_ptr<aumiks::sink> sink;
	InputVisitor inputVisitor;
public:
	SpeakersBlock(const utki::shared_ref<ruis::context>& c, const tml::forest& desc);
	
	SpeakersBlock(const SpeakersBlock&) = delete;
	SpeakersBlock& operator=(const SpeakersBlock&) = delete;
	
private:

};
