#pragma once

#include <mordavokne/App.hpp>

#include "WiredArea.hpp"

class App : public mordavokne::App{
public:
	
	OpenGL2ShaderColorPosLum shaderColorPosLum;
	
	App();
};
