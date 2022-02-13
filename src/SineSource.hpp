#pragma once

#include <aumiks/source.hpp>

class SineSource : public aumiks::source{
	float t = 0;
	
	float freq;
public:
	SineSource(float freq);
	
	bool fill_sample_buffer(utki::span<aumiks::frame> buf)noexcept override;
};
