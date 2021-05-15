#include "SineSourceBlock.hpp"
#include "Socket.hpp"

namespace{
const auto layout_c = treeml::read(R"qwertyuiop(
	@column{
		@text{
			text{"Sine Wave"}
		}
		@right{
			@OutSocket{
				id{output}
				outlet{right}
				text{output}
			}
		}
	}
)qwertyuiop");
}

SineSourceBlock::SineSourceBlock(std::shared_ptr<morda::context> c, const treeml::forest& desc) :
		widget(std::move(c), desc),
		Block(this->context, layout_c),
		source(std::make_shared<SineSource>(440)),
		sourceVisitor(this->source)
{
	auto& outputSocket = this->get_widget("output").get_widget_as<Socket>("ws");
	
	outputSocket.visitor = &this->sourceVisitor;
}
