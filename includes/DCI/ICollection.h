#ifndef DCI_ICOLLECTION_H_INCLUDED
#define DCI_ICOLLECTION_H_INCLUDED

#include "DCI/DCI.h"

namespace DCI {

// Description: Collection Interface.
//
// Arguments:
// - T: Type of the items contained in the collection.
template <class T> interface ICollection : virtual public IUnknown {
	// Description:
	// Clears the collection (removes all items).
	//
	// Returns:
	// true if the collection was cleared, or false otherwise.
	virtual Bool Clear() = 0;

	// Description:
	// Adds a new item to the collection. Optionally, a key to be 
	// associated with the item in the collection can be specified.
	//
	// Arguments:
	// Key          - Key of the item in the collection.
	// ObjectToCopy - The new item will be a copy of this object
	//                (optional).
	// posIdx       - The new item will be placed at this position
	//                (optional).
	//
	// Returns:
	// A bound handle of the new item if a new item was added,
	// or an unbound handle otherwise.
	virtual PtrHandle<T> AddNew(PtrHandle<T> &ObjectToCopy=PtrHandle<T>(), UInt posIdx=0) = 0;
	virtual PtrHandle<T> AddNew(const String &Key, PtrHandle<T> &ObjectToCopy=PtrHandle<T>(), UInt posIdx=0) = 0;

	// Description:
	// Removes the item at the specified position (given by index or by
	// key) from the collection.
	//
	// Arguments:
	// Index - The position (index) of the item to be removed.
	// Key   - The key associated with the item to be removed.
	//
	// Returns:
	// true if the item was removed, or false otherwise.
	virtual Bool Remove(const String &Key) = 0;
	virtual Bool Remove(UInt Index) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the number of items in the collection.
	//
	// Returns:
	// The number of items in the collection.
	virtual UInt GetCount() const = 0;

	// Description:
	// Tests, if an item with a specified key currently exists in the
	// collection.
	//
	// Arguments:
	// Key - Key to be tested (to be searched for in the collection).
	//
	// Returns:
	// true if an item with the specified key currently exists in the
	// the collection, or false otherwise.
	virtual Bool Exists(const String &Key) const = 0;

	// Description:
	// Returns the index of the item with a specified key in the
	// collection.
	//
	// Arguments:
	// Key - Key of the item whose index is queried.
	//
	// Returns:
	// The index of the item with the key specified, or 0 otherwise
	// (if there's no item with the key specified).
	virtual UInt IndexOf(const String &Key) const = 0;

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
	virtual String KeyOf(UInt Index) const = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the item with a specified index or key in collection.
	//
	// Arguments:
	// Index - Index of the item in the collection.
	// Key   - Key associated with the item in the collection.
	//
	// Returns:
	// A bound handle of the item with the index specified, or an unbound
	// handle if the index is out of range.
	virtual PtrHandle<T> Item(const String &Key) const = 0;
	virtual PtrHandle<T> Item(UInt Index) const = 0;
};

} /* namespace DCI */

#endif /* DCI_ICOLLECTION_H_INCLUDED */
