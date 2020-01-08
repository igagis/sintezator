#include "Block.hpp"

#include <morda/widgets/label/NinePatch.hpp>
#include <morda/widgets/proxy/MouseProxy.hpp>

namespace{
const char* blockLayout_c = R"qwertyuiop(
	MouseProxy{
		id{mouseProxy}
		layout{dx{fill} dy{fill}}
	}
	NinePatch{
		id{ninePatch}

		image{morda_npt_window_bg}

		left{${morda_window_border_size}}
		top{${morda_window_border_size}}
		right{${morda_window_border_size}}
		bottom{${morda_window_border_size}}
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
	
	auto& mp = this->getByNameAs<morda::MouseProxy>("mouseProxy");
	
	mp.mouseButton = decltype(morda::MouseProxy::mouseButton)([this](widget& widget, bool isDown, const morda::Vec2r& pos, morda::MouseButton_e button, unsigned pointerId){
		if(button != morda::MouseButton_e::LEFT){
			return false;
		}

		if(isDown){
			this->captured = true;
			this->capturePoint = pos;
			return true;
		}
		this->captured = false;
		return false;
	});
	
	mp.mouseMove = [this](widget& widget, const morda::Vec2r& pos, unsigned pointerId){
		if(this->captured){
			this->moveBy(pos - this->capturePoint);
			return true;
		}
		return false;
	};
}
