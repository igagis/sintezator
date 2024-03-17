#include "SineSourceBlock.hpp"
#include "Socket.hpp"

namespace{
const auto layout_c = tml::read(R"qwertyuiop(
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

SineSourceBlock::SineSourceBlock(const utki::shared_ref<ruis::context>& c, const tml::forest& desc) :
		widget(std::move(c), desc),
		Block(this->context, layout_c),
		source(std::make_shared<SineSource>(440)),
		sourceVisitor(this->source)
{
	auto& outputSocket = this->get_widget("output").get_widget_as<Socket>("ws");
	
	outputSocket.visitor = &this->sourceVisitor;
}
