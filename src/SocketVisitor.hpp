#pragma once

class SocketVisitor{
	
public:
	virtual ~SocketVisitor()noexcept{}
	
	virtual void connectAccept(SocketVisitor& v) = 0;
	
	virtual void disconnectAccept(SocketVisitor& v) = 0;
	
	virtual void connectVisit(class InputVisitor& v){}
	virtual void connectVisit(class SourceVisitor& v){}
	
	virtual void disconnectVisit(class InputVisitor& v){}
	virtual void disconnectVisit(class SourceVisitor& v){}
};
