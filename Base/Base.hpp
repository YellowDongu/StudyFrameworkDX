#pragma once
#include <memory>

class _declspec(dllexport) Base
{
public:
	Base(void) {}
	virtual ~Base(void) {}


	//friend void free(void) { release(); }

	virtual void release(void) = 0;
protected:

};
