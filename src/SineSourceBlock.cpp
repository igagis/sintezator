#include "SineSourceBlock.hpp"
#include "Socket.hpp"

namespace{
const auto layout_c = puu::read(R"qwertyuiop(
	Column{
		Text{
			text{"Sine Wave"}
		}
		Right{
			OutSocket{
				id{output}
				outlet{right}
				text{output}
			}
		}
	}
)qwertyuiop");
}

SineSourceBlock::SineSourceBlock() :
		widget(puu::forest()),
		Block(layout_c),
		source(std::make_shared<SineSource>(440)),
		sourceVisitor(this->source)
{
	auto& outputSocket = this->getByName("output").getByNameAs<Socket>("ws");
	
	outputSocket.visitor = &this->sourceVisitor;
}
