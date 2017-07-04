#pragma once

#include <morda/widgets/core/container/Container.hpp>



class WiredArea : public morda::Container{
public:
	WiredArea(const WiredArea&) = delete;
	WiredArea& operator=(const WiredArea&) = delete;
	
	WiredArea(const stob::Node* chain = nullptr);
	
	class WireSocket : virtual public morda::Widget{
	public:
		WireSocket(const WireSocket&) = delete;
		WireSocket& operator=(const WireSocket&) = delete;
		
		WireSocket(const stob::Node* chain = nullptr);

	};
	
private:

};

