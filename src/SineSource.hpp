#pragma once

#include <aumiks/Source.hpp>

class SineSource : public aumiks::FramedSource<float, audout::Frame_e::MONO>{
	float t = 0;
	
	float freq;
public:
	SineSource(float freq);
	
	bool fillSampleBuffer(utki::Buf<aumiks::Frame<float, audout::Frame_e::MONO> > buf)noexcept override;
};
