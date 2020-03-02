#include "Block.hpp"

#include <morda/widgets/label/nine_patch.hpp>
#include <morda/widgets/proxy/mouse_proxy.hpp>

namespace{
const auto blockLayout_c = puu::read(R"qwertyuiop(
	@mouse_proxy{
		id{mouseProxy}
		layout{dx{fill} dy{fill}}
	}
	@nine_patch{
		id{ninePatch}

		image{morda_npt_window_bg}

		left{${morda_window_border_size}}
		top{${morda_window_border_size}}
		right{${morda_window_border_size}}
		bottom{${morda_window_border_size}}
	}
)qwertyuiop");
}


Block::Block(std::shared_ptr<morda::context> c, const puu::forest& desc) :
		morda::widget(std::move(c), desc),
		morda::pile(this->context, blockLayout_c),
		content(this->get_widget_as<morda::nine_patch>("ninePatch").content())
{
	this->content.inflate_push_back(desc);
	
	auto& mp = this->get_widget_as<morda::mouse_proxy>("mouseProxy");
	
	mp.mouse_button_handler = [this](widget& widget, bool isDown, const morda::vector2& pos, morda::mouse_button button, unsigned pointerId){
		if(button != morda::mouse_button::left){
			return false;
		}

		if(isDown){
			this->captured = true;
			this->capturePoint = pos;
			return true;
		}
		this->captured = false;
		return false;
	};
	
	mp.mouse_move_handler = [this](widget& widget, const morda::vector2& pos, unsigned pointerId){
		if(this->captured){
			this->move_by(pos - this->capturePoint);
			return true;
		}
		return false;
	};
}
