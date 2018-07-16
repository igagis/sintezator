#pragma once

#include "SocketVisitor.hpp"

#include <aumiks/Source.hpp>

class SourceVisitor : public SocketVisitor{
public:
	std::shared_ptr<aumiks::Source<std::int32_t>> source;
	
	SourceVisitor(aumiks::Source<std::int32_t>& source);
	
	SourceVisitor(const SourceVisitor&) = delete;
	SourceVisitor& operator=(const SourceVisitor&) = delete;
	
private:

};
