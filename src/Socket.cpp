#include "Socket.hpp"


Socket::Socket(const stob::Node* chain) :
		morda::Widget(chain),
		WireSocket(chain)
{}
