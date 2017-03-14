#ifndef DCI_UNKNOWN_H_INCLUDED
#define DCI_UNKNOWN_H_INCLUDED

#include "DCI/DCI.h"

namespace DCI {

// {group:Interfaces}
// {glyph:Interface|Interface}
// Description: Unknown Interface
//
// Objects implementing this interface support object life-cycle
// managment using reference counting. This interface is closely
// related to handles (see class PtrHandle).
interface IUnknown {
	// Description:
	// Destructs the object.
	virtual ~IUnknown() {}

	// Description:
	// Increments the reference count.
	virtual void AddRef() = 0;

	// Description:
	// Decrements the reference count. If a client does not own
	// any references to an object released, it must not use
	// the object anymore, because it may have been destructed.
	virtual void Release() = 0;
};

// {internal}
// {group:Object Classes}
// Description: Unknown Default Implementation.
class Unknown : virtual public IUnknown {
public:
	// Description:
	// Constructs an unknown object.
	DCI_DLLEXPORT Unknown();

	// Description:
	// Destructs an unknown object.
	DCI_DLLEXPORT virtual ~Unknown();

	// Description:
	// Allocates memory from the heap for a new object constructed
	// using the new operator. The default new operator is overridden
	// to make sure that memory is always allocated and freed in
	// the same DLL.
	//
	// Arguments:
	// size - The size (number of bytes) of the object for which 
	//        memory has to be allocated.
	//
	// Returns:
	// A pointer to the memory allocated for the new object.
	DCI_DLLEXPORT void *operator new(size_t size);

	// Description:
	// Frees memory allocated for the object on the heap
	// after the object has been destructed.
	//
	// Arguments:
	// p - Pointer to the memory that was allocated on the heap
	//     for the object.
	DCI_DLLEXPORT void operator delete(void *p);

	// IUnknown

	DCI_DLLEXPORT virtual void AddRef();
	DCI_DLLEXPORT virtual void Release();

protected:
	Int m_RefCount;
};

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Unknown Interface Handle.
typedef PtrHandle<IUnknown> IUnknownHandle;

// {internal}
// Description:
// Implements the IUnknown methods of a class derived from class Unknown.
#define DCI_IMPL_UNKNOWN        \
public:	                        \
	virtual void AddRef()       \
		{ Unknown::AddRef(); }  \
	virtual void Release()      \
		{ Unknown::Release(); } \
private:

} /* namespace DCI */

#endif /* DCI_UNKNOWN_H_INCLUDED */
