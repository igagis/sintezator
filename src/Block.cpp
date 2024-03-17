#include "Block.hpp"

#include <ruis/widgets/label/nine_patch.hpp>
#include <ruis/widgets/proxy/mouse_proxy.hpp>

namespace{
const auto blockLayout_c = tml::read(R"qwertyuiop(
	layout{pile}
	@mouse_proxy{
		id{mouseProxy}
		lp{dx{fill} dy{fill}}
	}
	@nine_patch{
		id{ninePatch}

		image{ruis_npt_window_bg}

		left{${ruis_window_border_size}}
		top{${ruis_window_border_size}}
		right{${ruis_window_border_size}}
		bottom{${ruis_window_border_size}}
	}
)qwertyuiop");
}


Block::Block(const utki::shared_ref<ruis::context>& c, const tml::forest& desc) :
		ruis::widget(std::move(c), desc),
		ruis::container(this->context, blockLayout_c),
		content(this->get_widget_as<ruis::nine_patch>("ninePatch").content())
{
	this->content.push_back_inflate(desc);
	
	auto& mp = this->get_widget_as<ruis::mouse_proxy>("mouseProxy");
	
	mp.mouse_button_handler = [this](ruis::mouse_proxy& widget, const ruis::mouse_button_event& e){
		if(e.button != ruis::mouse_button::left){
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
	
	mp.mouse_move_handler = [this](ruis::mouse_proxy& w, const ruis::mouse_move_event& e){
		if(this->captured){
			this->move_by(e.pos - this->capturePoint);
			return true;
		}
		return false;
	};
}
