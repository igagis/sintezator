#include <mordavokne/AppFactory.hpp>


class Application : public mordavokne::App{
public:
	Application() :
			App([](){
					return mordavokne::App::WindowParams(kolme::Vec2ui(320, 480));
				}())
	{
		morda::inst().initStandardWidgets(*this->createResourceFileInterface());
		
//		morda::inst().resMan.mountResPack(*this->createResourceFileInterface("res/"));
		
//		auto c = morda::Morda::inst().inflater.inflate(
//				*this->createResourceFileInterface("res/main.gui.stob")
//			);
//		morda::Morda::inst().setRootWidget(c);
		
		
		morda::Morda::inst().setRootWidget(
				morda::inst().inflater.inflate(*stob::parse("PushButton{TextLabel{text{Hello}}}"))
			);
	}
};



std::unique_ptr<mordavokne::App> mordavokne::createApp(int argc, const char** argv, const utki::Buf<std::uint8_t> savedState){
	return utki::makeUnique<Application>();
}
