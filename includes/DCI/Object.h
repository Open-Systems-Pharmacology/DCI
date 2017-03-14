#ifndef DCI_OBJECT_H_INCLUDED
#define DCI_OBJECT_H_INCLUDED

#include "DCI/IObject.h"

namespace DCI {

// Forward declarations

class ObjectAttributes; // internal implementation class

// {internal}
// {group:Object Classes}
// Description: Object Default Implementation.
class Object : virtual public IObject, public Unknown {
DCI_IMPL_UNKNOWN
public:
	DCI_DLLEXPORT Object(IObject *objectToClone = 0);
    DCI_DLLEXPORT Object(FILE *fp);
	DCI_DLLEXPORT virtual ~Object();

	// IObject

	DCI_DLLEXPORT virtual String            GetName() const;
	DCI_DLLEXPORT virtual void              SetName(const String &newName);
	DCI_DLLEXPORT virtual String            GetDescription() const;
	DCI_DLLEXPORT virtual void              SetDescription(const String &newDescription);
	DCI_DLLEXPORT virtual IAttributesHandle GetAttributes() const;

protected:
	// {internal}
	// Description:
	// Assigns (copies) the data associated with an object 
	// (name, description, attributes etc.) from a specified 
	// source object to this object. 
	//
	// Arguments:
	// srcObj - Handle of the source object, from which the data
	//          is assigned (copied).
	//
	// Result:
	// true, if the method succeeds, or false otherwise.
	// In order to get extended error information, please make 
	// use of the Error module.	
	Bool AssignFrom(IObjectHandle &srcObj);

	// {internal}
	// Description:
    // Saves the object to a binary file.
    Bool SaveToBinaryFile(FILE *fp) const;

protected:
	String                      m_Name;
	String                      m_Description;
	PtrHandle<ObjectAttributes> m_Attributes;
};

// {internal}
// Description:
// Implements the IObject methods of a class derived from class Object
// without implementing the IUnknown methods.
#define DCI_IMPL_OBJECT_ONLY                                  \
public:	                                                      \
	virtual String GetName() const                            \
		{ return Object::GetName(); }                         \
	virtual void SetName(const String &newName)               \
		{ Object::SetName(newName); }                         \
	virtual String GetDescription() const                     \
		{ return Object::GetDescription(); }                  \
	virtual void SetDescription(const String &newDescription) \
		{ Object::SetDescription(newDescription); }           \
	virtual IAttributesHandle GetAttributes() const           \
		{ return Object::GetAttributes(); }                   \
private:

// {internal}
// Description:
// Implements the IObject methods of a class derived from class Object.
#define DCI_IMPL_OBJECT                                       \
public:	                                                      \
	virtual void AddRef()                                     \
		{ Unknown::AddRef(); }                                \
	virtual void Release()                                    \
		{ Unknown::Release(); }                               \
	DCI_IMPL_OBJECT_ONLY

} /* namespace DCI */

#endif /* DCI_OBJECT_H_INCLUDED */
