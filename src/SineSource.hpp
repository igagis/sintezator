#pragma once

#include <aumiks/Source.hpp>

class SineSource : public aumiks::Source{
	float t = 0;
	
	float freq;
public:
	SineSource(float freq);
	
	bool fillSampleBuffer(utki::span<aumiks::Frame> buf)noexcept override;
};
