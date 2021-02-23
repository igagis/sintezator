#pragma once

#include "wire_socket.hpp"

#include "SocketVisitor.hpp"

class Socket : public WireSocket{
public:
	Socket(std::shared_ptr<morda::context> c, const puu::forest& desc);
	
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;
	
private:

	void onConnected(WireSocket& to) override;
	void onDisconnected(WireSocket& from) override;
	
public:
	SocketVisitor* visitor = nullptr;
};
