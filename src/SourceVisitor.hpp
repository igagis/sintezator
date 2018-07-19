#pragma once

#include "SocketVisitor.hpp"

#include <aumiks/Source.hpp>

class SourceVisitor : public SocketVisitor{
public:
	std::shared_ptr<aumiks::Source> source;
	
	SourceVisitor(std::shared_ptr<aumiks::Source> source);
	
	SourceVisitor(const SourceVisitor&) = delete;
	SourceVisitor& operator=(const SourceVisitor&) = delete;
	
	void connectAccept(SocketVisitor& v) override;
	void disconnectAccept(SocketVisitor& v) override;
	
	void connectVisit(InputVisitor& v) override;
	
	void disconnectVisit(InputVisitor& v) override;
};
