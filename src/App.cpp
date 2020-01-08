#include "App.hpp"
#include "Block.hpp"
#include "SpeakersBlock.hpp"
#include "Socket.hpp"
#include "SineSourceBlock.hpp"


App::App() :
		mordavokne::App("sintezator", [](){
			return mordavokne::App::WindowParams(r4::vec2ui(320, 480));
		}())
{
	morda::inst().initStandardWidgets(*this->getResFile());

	//		morda::inst().resMan.mountResPack(*this->getResFile("res/"));

	morda::inst().inflater.register_widget<Block>("Block");
	morda::inst().inflater.register_widget<WireArea>("WiredArea");
	morda::inst().inflater.register_widget<Socket>("Socket");

	auto c = morda::Morda::inst().inflater.inflate(
			*this->getResFile("res/main.gui")
		);

	{
		auto& wa = c->getByNameAs<WireArea>("wireArea");
		wa.push_back(std::make_shared<SpeakersBlock>());
		wa.push_back(std::make_shared<SineSourceBlock>());

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
