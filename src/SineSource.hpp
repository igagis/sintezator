#pragma once

#include <aumiks/Source.hpp>

class SineSource : public aumiks::FramedSource<std::int32_t, audout::Frame_e::MONO>{
	float t = 0;
	
	float freq;
public:
	SineSource(float freq);
	
	bool fillSampleBuffer(utki::Buf<aumiks::Frame<std::int32_t, audout::Frame_e::MONO> > buf)noexcept override;
};
