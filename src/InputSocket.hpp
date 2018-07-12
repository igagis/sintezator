#pragma once

#include "Socket.hpp"

class InputSocket : public Socket{
public:
	InputSocket(const stob::Node* chain);
	
	InputSocket(const InputSocket&) = delete;
	InputSocket& operator=(const InputSocket&) = delete;
	
private:

};
