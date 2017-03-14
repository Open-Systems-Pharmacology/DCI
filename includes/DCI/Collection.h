#ifndef DCI_COLLECTION_H_INCLUDED
#define DCI_COLLECTION_H_INCLUDED

#include "DCI/ICollection.h"

namespace DCI {

// Forward declarations

template <class I, class C> class Collection;

// {internal}
// Description: Basic Collection Implementation.
//
// Generic base class used for deriving type-safe collection classes.
// Collections contain items objects associated with an index and an 
// optional key which must be unique within the collection (string). 
// The index of the first item is 1.
class DCI_DLLEXPORT CollectionBase {
public:
	// Description:
	// Creates a new collection object.
    CollectionBase() : m_Count(0), m_Nodes(0) {}

	// Description:
	// Clears the collection (removes all items).
	//
	// Returns:
	// true if the collection was cleared, or false otherwise.
	Bool Clear();

	// Description:
	// Adds an item to the collection. Optionally, a key to be
	// associated with the item can be specified.
	//
	// Arguments:
	// Key    - Key to be associated with the item in the collection.
	// Object - The item to be added to the collection.
	// posIdx - The new item will be placed at this position
	//          (0 or > Count+1 = at the end).
	//
	// Returns:
	// true if the item was added, or false otherwise.
	Bool Add(IUnknown *Object, UInt posIdx=0);
	Bool Add(const String &Key, IUnknown *Object, UInt posIdx=0);

	// Description:
	// Removes the item at the specified position (index) from the 
	// collection.
	//
	// Arguments:
	// Index - The position (index) of the item to be removed.
	//
	// Returns:
	// true if the item was removed, or false otherwise.
	Bool Remove(UInt Index);

	// Description:
	// Tests if an item with a specified key already exists in the
	// collection.
	//
	// Arguments:
	// Key - Key to be tested (searched for in the collection).
	//
	// Returns:
	// true if an item with the specified key alread exists in the
	// the collection, or false otherwise.
	Bool Exists(const String &Key) const { 
		return (IndexOf(Key) > 0); 
	}

	// Description:
	// Returns the index of the item with a specified key in the
	// collection.
	//
	// Arguments:
	// Key - Key to be tested (searched for in the collection).
	//
	// Returns:
	// The index of the item with the key specified, or 0 otherwise
	// (if there's no item with the key specified).
	UInt IndexOf(const String &Key) const;

	// Description:
	// Returns the key associated with the item with a specified index
	// collection.
	//
	// Arguments:
	// Index - Index of the item in the collection.
	//
	// Returns:
	// The key of the item with the index specified, or an empty string
	// otherwise (if there's no key associated with the item with the
	// specified index or if the index is out of range).
	String KeyOf(UInt Index) const;

	// Description:
	// Returns the item with a specified index in collection.
	//
	// Arguments:
	// Index - Index of the item in the collection.
	//
	// Returns:
	// The item with the index specified, or NULL if the index is out of 
	// range.
	IUnknown *Item(UInt Index) const;

protected:
	// Description:
	// Collection Node.
	// This struct internally represents the information associated
	// with an item.
	struct CollectionNode {
		char     *Key;
		UInt      Hash;
		IUnknown *Item;
	};

	UInt            m_Count;
	CollectionNode *m_Nodes;
};

// {internal}
// {group:Object Classes}
// Description: Default Collection Implementation.
//
// This class is a type-safe collection template class.
// Collections contain items objects associated with an index and an 
// optional key which must be unique within the collection (string). 
// The index of the first item is 1.
//
// Arguments:
// I - Interface of the items in the collection.
// C - Class implementing the interface of the items in the collection.
//     This is the class instantiated when using AddNew() or InsertNew().
template <class I, class C> class Collection : virtual public ICollection<I>, protected CollectionBase, public Unknown {
DCI_IMPL_UNKNOWN

	// {internal}
	// Description: Super Class.
	typedef CollectionBase super;

public:
	// IUnknown

	virtual ~Collection() { 
		Bool ok = CollectionBase::Clear(); assert(ok); 
	}

	// ICollection<I>

	virtual Bool Clear() { 
		return super::Clear(); 
	}
	virtual PtrHandle<I> AddNew(PtrHandle<I> &ObjectToCopy=PtrHandle<I>(), UInt posIdx=0) {
		PtrHandle<I> hC(new C(ObjectToCopy.GetPtr()));
		return super::Add(hC.GetPtr(), posIdx)?hC:0;
	}
	virtual PtrHandle<I> AddNew(const String &Key, PtrHandle<I> &ObjectToCopy=PtrHandle<I>(), UInt posIdx=0) {
		PtrHandle<I> hC(new C(ObjectToCopy.GetPtr()));
		return super::Add(Key, hC.GetPtr(), posIdx)?hC:0;
	}
	virtual Bool Remove(UInt Index) { 
		return super::Remove(Index); 
	}
	virtual Bool Remove(const String &Key) { 
		return super::Remove(super::IndexOf(Key)); 
	}
	virtual UInt GetCount() const { 
		return m_Count; 
	}
	virtual Bool Exists(const String &Key) const { 
		return super::Exists(Key); 
	}
	virtual UInt IndexOf(const String &Key) const { 
		return super::IndexOf(Key); 
	}
	virtual String KeyOf(UInt Index) const { 
		return super::KeyOf(Index); 
	}
	virtual PtrHandle<I> Item(UInt Index) const { 
		return PtrHandle<I>(dynamic_cast<I *>(super::Item(Index))); 
	}
	virtual PtrHandle<I> Item(const String &Key) const { 
		return PtrHandle<I>(dynamic_cast<I *>(super::Item(super::IndexOf(Key)))); 
	}
};

} /* namespace DCI */

#endif /* DCI_COLLECTION_H_INCLUDED */
