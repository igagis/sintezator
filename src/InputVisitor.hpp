#pragma once

#include <aumiks/Input.hpp>

#include "SocketVisitor.hpp"


class InputVisitor : public SocketVisitor{
public:
	aumiks::Input<std::int32_t>& input;
	
	InputVisitor(aumiks::Input<std::int32_t>& input);
	
	InputVisitor(const InputVisitor&) = delete;
	InputVisitor& operator=(const InputVisitor&) = delete;

	void connectAccept(SocketVisitor& v) override;
	
	void disconnectAccept(SocketVisitor& v) override;
	
	void connectVisit(SourceVisitor& v) override;
	
	void disconnectVisit(SourceVisitor& v) override;
};
