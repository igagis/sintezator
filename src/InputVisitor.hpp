#pragma once

#include <aumiks/Input.hpp>

#include "SocketVisitor.hpp"


class InputVisitor : public SocketVisitor{
public:
	aumiks::Input<std::int32_t>& input;
	
	InputVisitor(aumiks::Input<std::int32_t>& input);
	
	InputVisitor(const InputVisitor&) = delete;
	InputVisitor& operator=(const InputVisitor&) = delete;
	
private:

};

class ConnectInputVisitor : public InputVisitor{
public:
	ConnectInputVisitor(aumiks::Input<std::int32_t>& input);
	
	void accept(SocketVisitor& v) override;

	void visit(SourceVisitor& v) override;
	void visit(InputVisitor& v) override;
};
