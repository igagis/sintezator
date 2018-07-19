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
		sink(utki::makeUnique<aumiks::Speakers>(audout::SamplingRate_e::HZ_44100)),
		inputVisitor(this->sink->input)
{
	auto& inputSocket = this->getByName("input").getByNameAs<Socket>("ws");
	
	inputSocket.visitor = &this->inputVisitor;
	
	this->sink->start();
}