#include "InputVisitor.hpp"
#include "SourceVisitor.hpp"


InputVisitor::InputVisitor(aumiks::Input<std::int32_t>& input) :
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

void InputVisitor::connectVisit(InputVisitor& v){
	//do nothing
}

void InputVisitor::disconnectVisit(SourceVisitor& v) {
	this->input.disconnect();
}

void InputVisitor::disconnectVisit(InputVisitor& v) {
	//do nothing
}
