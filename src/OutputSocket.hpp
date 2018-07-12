#pragma once

#include "Socket.hpp"

class OutputSocket : public Socket {
public:
	OutputSocket(const stob::Node* chain);
	
	OutputSocket(const OutputSocket&) = delete;
	OutputSocket& operator=(const OutputSocket&) = delete;
private:

};
