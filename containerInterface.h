//Authors: Ryan Cornwall, Christopher Son, Alex McElroy, Brandon Mattingly, and John Coffey

#ifndef _CONTAINER
#define _CONTAINER

class BADINDEX {};

template <class T>
class containerInterface
{
   public:
	 virtual containerInterface <T>& pushFront(T)                  =0;
	 virtual containerInterface <T>& pushBack(T)                   =0;
	 virtual containerInterface <T>& popFront(T&)                  =0;
	 virtual containerInterface <T>& popBack(T&)                   =0;
	 virtual int  getSize()                                        =0;
	 virtual bool isFull()                                         =0;
	 virtual bool isEmpty()                                        =0;
	 virtual T    front()                                          =0;
	 virtual T    back()                                           =0;
	 virtual T&   operator [](int)                                 =0;
	 virtual void erase()                                          =0;
};



#endif

