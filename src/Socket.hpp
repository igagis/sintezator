#pragma once

#include "WireSocket.hpp"

#include "SocketVisitor.hpp"

class Socket : public WireSocket{
public:
	Socket(const stob::Node* chain);
	
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;
	
private:

	void onConnected(WireSocket& to) override;
	void onDisconnected(WireSocket& from) override;
	
public:
	SocketVisitor* connectVisitor = nullptr;
	SocketVisitor* disconnectVisitor = nullptr;
};
