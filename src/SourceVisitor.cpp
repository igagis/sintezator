#include "SourceVisitor.hpp"
#include "InputVisitor.hpp"

SourceVisitor::SourceVisitor(std::shared_ptr<aumiks::Source<std::int32_t> > source) :
		source(std::move(source))
{
}

void SourceVisitor::connectAccept(SocketVisitor& v) {
	v.connectVisit(*this);
}

void SourceVisitor::disconnectAccept(SocketVisitor& v) {
	v.disconnectVisit(*this);
}

void SourceVisitor::connectVisit(InputVisitor& v) {
	v.input.connect(this->source);
}

void SourceVisitor::connectVisit(SourceVisitor& v) {
	//do nothing
}

void SourceVisitor::disconnectVisit(InputVisitor& v) {
	v.input.disconnect();
}

void SourceVisitor::disconnectVisit(SourceVisitor& v) {
	//do nothing
}
