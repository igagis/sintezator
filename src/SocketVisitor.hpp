#pragma once

class SocketVisitor{
	
public:
	virtual ~SocketVisitor()noexcept{}
	
	virtual void accept(SocketVisitor& v) = 0;
	
	virtual void visit(class InputVisitor& v) = 0;
	virtual void visit(class SourceVisitor& v) = 0;
};
