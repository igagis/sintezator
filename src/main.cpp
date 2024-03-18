
#include "App.hpp"

ruisapp::application_factory app_fac([](auto executable, auto args){
	return std::make_unique<::App>();
});
