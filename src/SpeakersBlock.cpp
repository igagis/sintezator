#include "SpeakersBlock.hpp"

#include "Socket.hpp"

namespace{
const auto layout_c = puu::read(R"qwertyuiop(
	Column{
		Text{
			text{Speakers}
		}
		Left{
			InSocket{
				id{input}
				outlet{left}
				text{input}
			}
		}
	}
)qwertyuiop");
}


SpeakersBlock::SpeakersBlock():
		widget(puu::forest()),
		Block(layout_c),
		sink(utki::makeUnique<aumiks::Speakers>(audout::SamplingRate_e::HZ_44100)),
		inputVisitor(this->sink->input)
{
	auto& inputSocket = this->getByName("input").getByNameAs<Socket>("ws");
	
	inputSocket.visitor = &this->inputVisitor;
	
	this->sink->start();
}