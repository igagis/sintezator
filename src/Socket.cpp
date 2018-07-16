#include "Socket.hpp"


Socket::Socket(const stob::Node* chain) :
		morda::Widget(chain),
		WireSocket(chain)
{
}

void Socket::onConnected(WireSocket& to) {
	ASSERT(dynamic_cast<Socket*>(&to))
	auto& remote = dynamic_cast<Socket&>(to);
	
	if(!this->visitor || !remote.visitor){
		return;
	}
	this->visitor->connectAccept(*remote.visitor);
}

void Socket::onDisconnected(WireSocket& from) {
	ASSERT(dynamic_cast<Socket*>(&from))
	auto& remote = dynamic_cast<Socket&>(from);
	
	if(!this->visitor || !remote.visitor){
		return;
	}
	this->visitor->disconnectAccept(*remote.visitor);
}

