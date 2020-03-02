#pragma once

#include <morda/render/renderer.hpp>

#include "Path.hpp"

class PathVba{
	
	std::shared_ptr<morda::vertex_array> core;
	std::shared_ptr<morda::vertex_array> border;
	
	std::shared_ptr<morda::renderer> renderer;
public:
	PathVba(std::shared_ptr<morda::renderer> r, const Path::Vertices& path);
	
	PathVba(const PathVba&) = delete;
	PathVba& operator=(const PathVba&) = delete;
	
	void render(const morda::matrix4& matrix, std::uint32_t color);
	
private:

};
