#pragma once

#include <aumiks/input.hpp>

#include "SocketVisitor.hpp"


class InputVisitor : public SocketVisitor{
public:
	aumiks::input& input;
	
	InputVisitor(aumiks::input& input);
	
	InputVisitor(const InputVisitor&) = delete;
	InputVisitor& operator=(const InputVisitor&) = delete;

	void connectAccept(SocketVisitor& v) override;
	
	void disconnectAccept(SocketVisitor& v) override;
	
	void connectVisit(SourceVisitor& v) override;
	
	void disconnectVisit(SourceVisitor& v) override;
};
