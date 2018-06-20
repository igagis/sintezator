#include "Block.hpp"

#include <morda/widgets/label/NinePatch.hpp>

namespace{
const char* blockLayout_c = R"qwertyuiop(
	MouseProxy{
		name{mouseProxy}
	}
	NinePatch{
		name{ninePatch}

		layout{dx{fill} dy{fill}}

		image{morda_npt_window_bg}

		left{@{morda_window_border_size}}
		top{@{morda_window_border_size}}
		right{@{morda_window_border_size}}
		bottom{@{morda_window_border_size}}
	}
)qwertyuiop";
}


Block::Block(const stob::Node* chain) :
		morda::Widget(chain),
		morda::Pile(stob::parse(blockLayout_c).get()),
		content(this->getByNameAs<morda::NinePatch>("ninePatch").content())
{
	if(chain){
		this->content.add(*chain);
	}
}
