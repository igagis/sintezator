#include "InputVisitor.hpp"
#include "SourceVisitor.hpp"


InputVisitor::InputVisitor(aumiks::Input<std::int32_t>& input) :
		input(input)
{
}

ConnectInputVisitor::ConnectInputVisitor(aumiks::Input<std::int32_t>& input) :
		InputVisitor(input)
{
}

void ConnectInputVisitor::accept(SocketVisitor& v) {
	v.visit(*this);
}

void ConnectInputVisitor::visit(SourceVisitor& v) {
	this->input.connect(v.source);
}

void ConnectInputVisitor::visit(InputVisitor& v){
	//do nothing
}
