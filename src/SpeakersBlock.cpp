#include "SpeakersBlock.hpp"
#include "WireSocket.hpp"


namespace{
const char* layout_c = R"qwertyuiop(
	Column{
		Text{
			text{Speakers}
			color{0xff00ff00}
		}
		Left{
			Socket{
				name{input}
				outlet{left}
				text{input}
			}
		}
	}
)qwertyuiop";
}


SpeakersBlock::SpeakersBlock():
		Widget(nullptr),
		Block(stob::parse(layout_c).get()),
		sink(utki::makeUnique<aumiks::StereoSink>(audout::SamplingRate_e::HZ_44100))
{
	auto& inputSocket = this->getByName("input").getByNameAs<WireSocket>("ws");
	
	inputSocket.userData = &this->sink->input();
	
	
}