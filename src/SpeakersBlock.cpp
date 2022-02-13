#include "SpeakersBlock.hpp"

#include "Socket.hpp"

namespace{
const auto layout_c = treeml::read(R"qwertyuiop(
	@column{
		@text{
			text{Speakers}
		}
		@left{
			@InSocket{
				id{input}
				outlet{left}
				text{input}
			}
		}
	}
)qwertyuiop");
}


SpeakersBlock::SpeakersBlock(std::shared_ptr<morda::context> c, const treeml::forest& desc):
		widget(std::move(c), desc),
		Block(this->context, layout_c),
		sink(std::make_unique<aumiks::speakers>(audout::rate::hz_44100)),
		inputVisitor(this->sink->input)
{
	auto& inputSocket = this->get_widget("input").get_widget_as<Socket>("ws");
	
	inputSocket.visitor = &this->inputVisitor;
	
	this->sink->start();
}