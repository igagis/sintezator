#include "Socket.hpp"


Socket::Socket(const utki::shared_ref<morda::context>& c, const treeml::forest& desc) :
		morda::widget(std::move(c), desc),
		WireSocket(this->context, desc)
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

