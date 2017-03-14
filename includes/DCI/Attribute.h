#ifndef DCI_ATTRIBUTE_H_INCLUDED
#define DCI_ATTRIBUTE_H_INCLUDED

#include "DCI/IAttribute.h"
#include "DCI/Collection.h"

namespace DCI {

// {internal}
// {group:Object Classes}
// Description: Attribute Default Implementation.
class Attribute : virtual public IAttribute, public Unknown {
DCI_IMPL_UNKNOWN
public:
	DCI_DLLEXPORT Attribute(IAttribute *attributeToClone = 0);
	DCI_DLLEXPORT Attribute(FILE *fp);
	DCI_DLLEXPORT virtual ~Attribute();

	DCI_DLLEXPORT virtual String GetName();
	DCI_DLLEXPORT virtual void   SetName(const String &newName);
	DCI_DLLEXPORT virtual String GetStringValue();
	DCI_DLLEXPORT virtual void   SetStringValue(const String &newStringValue);

    DCI_DLLEXPORT Bool SaveToBinaryFile(FILE *fp) const;

protected:
	String m_Name;
	String m_StringValue;
};

// {internal}
// Description: Attribute Collection Default Implementation
typedef Collection<IAttribute, Attribute> Attributes;

// {internal}
// Description: Attribute Collection Default Implementation Handle
typedef PtrHandle<Attributes> AttributesHandle;

} /* namespace DCI */

#endif /* DCI_ATTRIBUTE_H_INCLUDED */
