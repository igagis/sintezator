#include "App.hpp"
#include "Block.hpp"
#include "SpeakersBlock.hpp"
#include "Socket.hpp"
#include "SineSourceBlock.hpp"

App::App() :
		ruisapp::application("sintezator", [](){
			return ruisapp::window_params(r4::vector2<unsigned>(320, 480));
		}())
{
	this->gui.init_standard_widgets(*this->get_res_file());

	//		ruis::inst().resMan.mountResPack(*this->getResFile("res/"));

	this->gui.context.get().inflater.push_defs(R"(
		defs{
		@InSocket{ text outlet
			@pile{
				@text{
					text{${text}}
					color{0xff0000ff}
				}
				@Socket{
					id{ws}
					outlet{${outlet}}
					lp{dx{fill} dy{fill}}
				}
			}
		}

		@OutSocket{ text outlet
			@pile{
				@text{
					text{${text}}
					color{0xff00ff00}
				}
				@Socket{
					id{ws}
					outlet{${outlet}}
					lp{dx{fill} dy{fill}}
				}
			}
		}
	}
	)");

	this->gui.context.get().inflater.register_widget<Block>("Block");
	this->gui.context.get().inflater.register_widget<WireArea>("WiredArea");
	this->gui.context.get().inflater.register_widget<Socket>("Socket");

	auto c = this->gui.context.get().inflater.inflate(
			*this->get_res_file("res/main.gui")
		);

	{
		auto& wa = c.get().get_widget_as<WireArea>("wireArea");
		wa.push_back(utki::make_shared<SpeakersBlock>(this->gui.context, tml::forest()));
		wa.push_back(utki::make_shared<SineSourceBlock>(this->gui.context, tml::forest()));

		auto in11 = c.get().try_get_widget("in11")->try_get_widget_as<WireSocket>("ws");
		ASSERT(in11)
		auto in12 = c.get().try_get_widget("in12")->try_get_widget_as<WireSocket>("ws");
		ASSERT(in12)
		in11->connect(in12);
	}

	this->gui.set_root(c);
}
