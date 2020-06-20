#include "PathVba.hpp"

#include "App.hpp"

PathVba::PathVba(std::shared_ptr<morda::renderer> r, const Path::Vertices& path) :
		renderer(std::move(r))
{
	auto coreBuf = this->renderer->factory->create_vertex_buffer(utki::make_span(path.pos));
	
	this->core = this->renderer->factory->create_vertex_array(
			{{
				coreBuf,
			}},
			this->renderer->factory->create_index_buffer(utki::make_span(path.inIndices)),
			morda::vertex_array::mode::triangle_strip
		);
	
	
	this->border = this->renderer->factory->create_vertex_array(
			{{
				coreBuf,
				this->renderer->factory->create_vertex_buffer(utki::make_span(path.alpha)),
			}},
			this->renderer->factory->create_index_buffer(utki::make_span(path.outIndices)),
			morda::vertex_array::mode::triangle_strip
		);
}

void PathVba::render(const morda::matrix4& matrix, std::uint32_t color){
	this->renderer->shader->color_pos->render(matrix, *this->core, color);
	this->renderer->shader->color_pos_lum->render(matrix, *this->border, color);
}
