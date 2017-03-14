#ifndef DCI_IOBJECT_H_INCLUDED
#define DCI_IOBJECT_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/ICollection.h"

namespace DCI {

// Forward declarations

interface IAttribute;
typedef ICollection<IAttribute> IAttributes;
typedef PtrHandle<IAttributes> IAttributesHandle;

// Description: Object Interface.
//
// Objects implementing this interface represent named and typed
// objects containing a list of user-defined attributes (see the 
// IAttribute interface).
interface IObject : virtual public IUnknown {
	// {group:Read-Only Properties}
	// Description:
	// Returns the name of the object's type.
	//
	// Returns:
	// The name of the object's type.
	virtual String GetTypeName() const = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the type-specific description of the object's type.
	//
	// Returns:
	// The description of the object's type.
	virtual String GetTypeDescription() const = 0;

	// {group:Read-Write Properties}
	// Description:
	// Returns the type name of the object. Please note, that the name
	// of the object and its key in a containing collection is not 
	// necessarily the same.
	//
	// Returns:
	// The name of the object.
	virtual String GetName() const = 0;

	// {group:Read-Write Properties}
	// Description:
	// Sets the name of the object. Please note, that setting the
	// name of the object does not change its key in a containig
	// collection.
	//
	// Arguments:
	// - newName: The new name of the object.
	virtual void SetName(const String &newName) = 0;

	// {group:Read-Write Properties}
	// Description:
	// Returns the instance-specific description of the object. 
	//
	// Returns:
	// The instance-specific description of the object.
	virtual String GetDescription() const = 0;

	// {group:Read-Write Properties}
	// Description:
	// Sets the instance-specific description of the object.
	//
	// Arguments:
	// - newDescription: The new description of the object.
	virtual void SetDescription(const String &newDescription) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the collection of user-defined attributes of the object.
	//
	// Returns:
	// The handle of the collection of user-defined attributes of 
	// the object.
	virtual IAttributesHandle GetAttributes() const = 0;
};

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Object Interface Handle.
typedef PtrHandle<IObject> IObjectHandle;

} /* namespace DCI */

#include "DCI/IAttribute.h"

#endif /* DCI_IOBJECT_H_INCLUDED */
