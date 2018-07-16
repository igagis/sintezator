#include "Socket.hpp"


Socket::Socket(const stob::Node* chain) :
		morda::Widget(chain),
		WireSocket(chain)
{
}

void Socket::onConnected(WireSocket& to) {
	ASSERT(dynamic_cast<Socket*>(&to))
	auto& remote = dynamic_cast<Socket&>(to);
	
	if(!this->connectVisitor || !remote.connectVisitor){
		return;
	}
	this->connectVisitor->accept(*remote.connectVisitor);
}

void Socket::onDisconnected(WireSocket& from) {
	ASSERT(dynamic_cast<Socket*>(&from))
}

