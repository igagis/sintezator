#include "App.hpp"
#include "Block.hpp"
#include "SpeakersBlock.hpp"
#include "Socket.hpp"
#include "SineSourceBlock.hpp"


App::App() :
		mordavokne::application("sintezator", [](){
			return mordavokne::window_params(r4::vec2ui(320, 480));
		}())
{
	this->gui.initStandardWidgets(*this->get_res_file());

	//		morda::inst().resMan.mountResPack(*this->getResFile("res/"));

	this->gui.context->inflater.register_widget<Block>("Block");
	this->gui.context->inflater.register_widget<WireArea>("WiredArea");
	this->gui.context->inflater.register_widget<Socket>("Socket");

	auto c = this->gui.context->inflater.inflate(
			*this->get_res_file("res/main.gui")
		);

	{
		auto& wa = c->get_widget_as<WireArea>("wireArea");
		wa.push_back(std::make_shared<SpeakersBlock>(this->gui.context, puu::forest()));
		wa.push_back(std::make_shared<SineSourceBlock>(this->gui.context, puu::forest()));

		auto in11 = c->try_get_widget("in11")->try_get_widget_as<WireSocket>("ws");
		ASSERT(in11)
		auto in12 = c->try_get_widget("in12")->try_get_widget_as<WireSocket>("ws");
		ASSERT(in12)
		in11->connect(in12);
	}

	this->gui.set_root(std::move(c));
}
