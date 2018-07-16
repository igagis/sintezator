#include "SineSourceBlock.hpp"

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
		src(std::make_shared<SineSource>(440))
{
}
