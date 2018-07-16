#include "SineSourceBlock.hpp"
#include "Socket.hpp"

namespace{
const char* layout_c = R"qwertyuiop(
	Column{
		Text{
			text{"Sine Wave"}
		}
		Right{
			OutSocket{
				name{output}
				outlet{right}
				text{output}
			}
		}
	}
)qwertyuiop";
}

SineSourceBlock::SineSourceBlock() :
		Widget(nullptr),
		Block(stob::parse(layout_c).get()),
		source(std::make_shared<SineSource>(440)),
		sourceVisitor(this->source)
{
	auto& outputSocket = this->getByName("output").getByNameAs<Socket>("ws");
	
	outputSocket.visitor = &this->sourceVisitor;
}
