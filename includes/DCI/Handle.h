#ifndef DCI_HANDLE_H_INCLUDED
#define DCI_HANDLE_H_INCLUDED

#include "DCI/DCI.h"

namespace DCI {

// {group:Handle Classes}
// Description: Pointer-like Object Handle.
//
// A handle manages the life-time of an object by automatically
// counting references whenever a new reference to the object
// is created or destroyed. Therefore, the object must implement
// the IUnknown interface. Objects bound to a handle must be
// allocated using the new operator.
//
// A handle acts like a pointer, i.e. methods of the handled objects
// can be access using the -> operator.
//
// Arguments:
// - T: Type of the object handled. T must be derived from IUnknown.
template <class T> class PtrHandle {
public:
	// Description:
	// Constructs a new handle. The handle is bound to an object, if 
	// the object's handle or pointer is supplied. Otherwise, the 
	// handle is unbound and acts like a NULL-pointer.
	//
	// Arguments:
	// - p: Pointer to the object to be handled. If this argument is
	//      supplied, a bound handle is created. The reference count
	//      of the object pointed to is automatically incremented.
	// - h: Handle of the object to be handled. If this argument is
	//      supplied, a bound handle is created. The reference count
	//      of the object pointed to is automatically incremented.
    PtrHandle() : m_Object(0) {}
    PtrHandle(T *p) : m_Object(p) { 
        if (m_Object) m_Object->AddRef(); 
    }
    PtrHandle(const PtrHandle &h) : m_Object(h.m_Object) { 
        if (m_Object) m_Object->AddRef();
    }

	// Description:
	// Destructs the handle. If the handle is bound to an object,
	// its reference count is decremented.
    ~PtrHandle() { 
        if (m_Object) m_Object->Release(); 
    }

    // Description:
	// Returns the pointer to the object. Please note, that using the
	// pointer instead of the handle circumvents automatic reference 
	// counting, which may result in crashes or memory leaks if used
	// improperly!
	//
	// Returns:
	// If the handle is bound to an object, its pointer is returned.
	// If the handle is unbound, a NULL pointer is returned.
    T* GetPtr() const { 
        return m_Object; 
    }

	// Description:
	// Tests, if the handle is bound to an object.
	//
	// Returns:
	// true if the handle is bound, or false if the handle is unbound.
    operator bool () const { 
        return m_Object?true:false; 
    }

	// Description:
	// Returns the reference to the object handled. In order to use this
	// operator, the handle must be bound to an object.
	//
	// Returns:
	// The reference of the object handled.
    T& operator *() const { 
        return *m_Object; 
    }

	// Description:
	// Returns a pointer to the object handled enabling the client
	// to access the object's members (methods). In order to use this
	// operator, the handle must be bound to an object.
	//
	// Returns:
	// The pointer of the object handled.
    T* operator ->() const { 
        return m_Object; 
    }

	// Description:
	// Tests, if two handles refer to the same object.
	//
	// Arguments:
	// - h: Handle of the object to be compared with.
	//
	// Returns:
	// true if the handles refer to the same object, or false otherwise.
    Bool operator == (const PtrHandle &h) const { 
        return (m_Object == h.m_Object)?true:false; 
    }

	// Description:
	// Tests, if two handles refer to different objects.
	//
	// Arguments:
	// - h: Handle of the object to be compared with.
	//
	// Returns:
	// true if the handles refer to different objects, or false otherwise.
    Bool operator != (const PtrHandle &h) const { 
        return (m_Object != h.m_Object)?true:false; 
    }

    // Description:
	// Assigns the handle from another one. If this handle was initially
	// bound, the reference count of the bound object is decremented.
	// If the handle is bound after assignment, the reference count of the
	// new object refered to is incremented.
	//
	// Arguments:
	// - h: Handle to be assigned.
	//
	// Returns:
	// The reference of the handle.
    PtrHandle & operator = (const PtrHandle &);

	// Description:
	// Binds the handle to a new object or makes it unbound. If this handle
	// was initially bound, the reference count of the bound object is decremented.
	// If the handle is bound after assignment, the reference count of the
	// new object refered to is incremented.
	//
	// Arguments:
	// - p: Pointer to the object to be bound by the handle.
	void BindTo(T *p) { 
        if (m_Object) m_Object->Release(); 
        if (p) p->AddRef(); 
        m_Object = p; 
    }

private:
    // state representation
    T *m_Object;
};

template <class T> inline PtrHandle<T> &PtrHandle<T>::operator=(const PtrHandle<T> &h) {
    if (h.m_Object) h.m_Object->AddRef();
    if (m_Object) m_Object->Release();
    m_Object = h.m_Object;
    return *this;
}

} /* namespace DCI */

#endif /* DCI_HANDLE_H_INCLUDED */
