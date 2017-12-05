#pragma once

#include <morda/render/VertexArray.hpp>

#include "Path.hpp"

class PathVba {
	
	std::shared_ptr<morda::VertexArray> core;
	std::shared_ptr<morda::VertexArray> border;
	
public:
	PathVba(const Path::Vertices& path);
	
	PathVba(const PathVba&) = delete;
	PathVba& operator=(const PathVba&) = delete;
	
	void render(const morda::Matr4r& matrix, std::uint32_t color);
	
private:

};
