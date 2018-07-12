#include "OutputSocket.hpp"


OutputSocket::OutputSocket(const stob::Node* chain) :
		morda::Widget(chain),
		Socket(chain)
{}
