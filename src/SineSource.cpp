#include "SineSource.hpp"

#include <cmath>
#include <utki/math.hpp>

SineSource::SineSource(float freq) :
		freq(freq)
{
}

bool SineSource::fillSampleBuffer(utki::Buf<aumiks::Frame<float, audout::Frame_e::MONO> > buf)noexcept{
	for (auto d = buf.begin(), e = buf.end(); d != e; ++d) {
		using std::sin;
		using utki::pi;
		
		d->channel[0] = 0xfff * sin(2 * pi<float>() * this->t * this->freq);
		this->t += 1 / 44100.0f;
	}
	
	return false;
}

