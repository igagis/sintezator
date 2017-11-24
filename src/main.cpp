#include <mordavokne/AppFactory.hpp>

#include "WiredArea.hpp"

class Application : public mordavokne::App{
public:
	Application() :
			App([](){
					return mordavokne::App::WindowParams(kolme::Vec2ui(320, 480));
				}())
	{
		morda::inst().initStandardWidgets(*this->getResFile());
		
//		morda::inst().resMan.mountResPack(*this->getResFile("res/"));
		
		morda::inst().inflater.addWidget<WiredArea>("WiredArea");
		morda::inst().inflater.addWidget<WiredArea::WireSocket>("WireSocket");
		
		auto c = morda::Morda::inst().inflater.inflate(
				*this->getResFile("res/main.gui")
			);		
		
		morda::Morda::inst().setRootWidget(
				std::move(c)
			);
	}
};



std::unique_ptr<mordavokne::App> mordavokne::createApp(int argc, const char** argv, const utki::Buf<std::uint8_t> savedState){
	return utki::makeUnique<Application>();
}
