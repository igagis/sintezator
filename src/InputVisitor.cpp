#include "InputVisitor.hpp"
#include "SourceVisitor.hpp"


InputVisitor::InputVisitor(aumiks::input& input) :
		input(input)
{
}

void InputVisitor::connectAccept(SocketVisitor& v) {
	v.connectVisit(*this);
}

void InputVisitor::disconnectAccept(SocketVisitor& v) {
	v.disconnectVisit(*this);
}


void InputVisitor::connectVisit(SourceVisitor& v) {
	this->input.connect(v.source);
}

void InputVisitor::disconnectVisit(SourceVisitor& v) {
	this->input.disconnect();
}
