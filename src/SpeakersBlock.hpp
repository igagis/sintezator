#pragma once

#include "Block.hpp"

#include <aumiks/SpeakersSink.hpp>

class SpeakersBlock : public Block{
	std::unique_ptr<aumiks::Sink<std::int32_t>> sink;
public:
	SpeakersBlock();
	
	SpeakersBlock(const SpeakersBlock&) = delete;
	SpeakersBlock& operator=(const SpeakersBlock&) = delete;
	
private:

};
