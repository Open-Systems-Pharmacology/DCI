#ifndef DCI_IATTRIBUTE_H_INCLUDED
#define DCI_IATTRIBUTE_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/ICollection.h"

namespace DCI {

// Description: Attribute Interface.
//
// Objects implementing this interface represent a named string value. 
// Attributes are part of all objects implementing (derived from) the 
// IObject interface.
interface IAttribute : virtual public IUnknown {
	// {group:Read/Write Properties}
	// Description:
	// Returns the string value assigned to the attribute.
	//
	// Returns:
	// The string value assiged to the attribute.
	virtual String GetStringValue() = 0;

	// {group:Read/Write Properties}
	// Description:
	// Sets the string value assigned to the attribute.
	//
	// Arguments:
	// - newStringValue: The string value to be assigned to the
	//                   attribute.
	virtual void SetStringValue(const String &newStringValue) = 0;

	// {group:Read/Write Properties}
	// Description:
	// Returns the name of the attribute. Please note, that the name
	// of the attribute and its key in a containing Attributes
	// collection is not necessarily the same.
	//
	// Returns:
	// The name of the attribute.
	virtual String GetName() = 0;

	// {group:Read/Write Properties}
	// Description:
	// Sets the name of the attribute. Please note, that setting the
	// name of the attribute does not change its key in a containig
	// Attributes collection.
	//
	// Arguments:
	// - newName: The new name of the attribute.
	virtual void SetName(const String &newName) = 0;
};

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Attribute Interface Handle.
typedef PtrHandle<IAttribute> IAttributeHandle;

// {group:Interfaces}
// {glyph:Interface|Interface}
// Description: Attribute Interface Collection Interface.
typedef ICollection<IAttribute> IAttributes;

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Attribute Interface Collection Interface Handle.
typedef PtrHandle<IAttributes> IAttributesHandle;

} /* namespace DCI */

#endif /* DCI_IATTRIBUTE_H_INCLUDED */
