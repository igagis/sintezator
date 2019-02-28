#include <mordavokne/AppFactory.hpp>

#include "App.hpp"



std::unique_ptr<mordavokne::App> mordavokne::createApp(int argc, const char** argv){
	return utki::makeUnique<::App>();
}
