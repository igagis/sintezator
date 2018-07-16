#include "SpeakersBlock.hpp"

#include "Socket.hpp"

namespace{
const char* layout_c = R"qwertyuiop(
	Column{
		Text{
			text{Speakers}
		}
		Left{
			InSocket{
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
		sink(utki::makeUnique<aumiks::StereoSink>(audout::SamplingRate_e::HZ_44100)),
		connectInputVisitor(this->sink->input())
{
	auto& inputSocket = this->getByName("input").getByNameAs<Socket>("ws");
	
	inputSocket.connectVisitor = &this->connectInputVisitor;
	
	this->sink->start();
}