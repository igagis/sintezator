#pragma once

#include "Block.hpp"
#include "InputVisitor.hpp"

#include <aumiks/Speakers.hpp>

class SpeakersBlock : public Block{
	std::unique_ptr<aumiks::Sink> sink;
	InputVisitor inputVisitor;
public:
	SpeakersBlock();
	
	SpeakersBlock(const SpeakersBlock&) = delete;
	SpeakersBlock& operator=(const SpeakersBlock&) = delete;
	
private:

};
