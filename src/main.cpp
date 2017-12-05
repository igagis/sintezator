#include <mordavokne/AppFactory.hpp>

#include "App.hpp"



std::unique_ptr<mordavokne::App> mordavokne::createApp(int argc, const char** argv, const utki::Buf<std::uint8_t> savedState){
	return utki::makeUnique<::App>();
}
