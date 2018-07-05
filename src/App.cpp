#include "App.hpp"
#include "Block.hpp"



App::App() :
		mordavokne::App([](){
			return mordavokne::App::WindowParams(kolme::Vec2ui(320, 480));
		}())
{
	morda::inst().initStandardWidgets(*this->getResFile());

	//		morda::inst().resMan.mountResPack(*this->getResFile("res/"));

	morda::inst().inflater.registerType<Block>("Block");
	morda::inst().inflater.registerType<WireArea>("WiredArea");
	morda::inst().inflater.registerType<WireSocket>("WireSocket");

	auto c = morda::Morda::inst().inflater.inflate(
			*this->getResFile("res/main.gui")
		);
	
	{
		auto in11 = c->findByName("in11")->findByNameAs<WireSocket>("ws");
		ASSERT(in11)
		auto in12 = c->findByName("in12")->findByNameAs<WireSocket>("ws");
		ASSERT(in12)
		in11->connect(in12);
	}

	morda::Morda::inst().setRootWidget(
			std::move(c)
		);
}
