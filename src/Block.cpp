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
	this->content.push_back_inflate(desc);
	
	auto& mp = this->get_widget_as<morda::mouse_proxy>("mouseProxy");
	
	mp.mouse_button_handler = [this](morda::mouse_proxy& widget, const morda::mouse_button_event& e){
		if(e.button != morda::mouse_button::left){
			return false;
		}

		if(e.is_down){
			this->captured = true;
			this->capturePoint = e.pos;
			return true;
		}
		this->captured = false;
		return false;
	};
	
	mp.mouse_move_handler = [this](morda::mouse_proxy& w, const morda::mouse_move_event& e){
		if(this->captured){
			this->move_by(e.pos - this->capturePoint);
			return true;
		}
		return false;
	};
}
