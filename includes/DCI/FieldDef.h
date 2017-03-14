#ifndef DCI_FIELDDEF_H_INCLUDED
#define DCI_FIELDDEF_H_INCLUDED

#include "DCI/IFieldDef.h"
#include "DCI/Object.h"
#include "DCI/Collection.h"

namespace DCI {

// Forward declarations

class Table;
class Variable;
class TableFieldDefs;

// {internal}
// {group:Object Classes}
// Description: Field Definition Default Implementation.
class FieldDef : public IFieldDef, public Object {
DCI_IMPL_OBJECT_ONLY
private:
	FieldDef() {}                           // forbidden
	FieldDef(IFieldDef *fieldDefToClone) {} // forbidden
	FieldDef(Table *table, IFieldDef *fieldDefToClone = 0);
    FieldDef(Table *table, FILE *fp);

public:
	virtual ~FieldDef();

	// IUnknown
	virtual void         AddRef();
	virtual void         Release();

	// IObject
	virtual String       GetTypeName() const;
	virtual String       GetTypeDescription() const;

	// IFieldDef
	virtual ITableHandle GetTable() const;
	virtual DataType     GetDataType() const;
	virtual Bool         SetDataType(DataType newDataType);
	virtual Value        GetDefaultValue() const;
	virtual Bool         SetDefaultValue(const Value &newDefaultValue);
	virtual Value        GetMinValue() const;
	virtual Bool         SetMinValue(const Value &newMinValue);
	virtual Value        GetMaxValue() const;
	virtual Bool         SetMaxValue(const Value &newMaxValue);
	virtual Vector       GetAllowedValues() const;
	virtual Bool         SetAllowedValues(const Vector &newAllowedValues);

private:
	// internal implementation
    Bool InternalCheckDataType(DataType dt);
    Bool SaveToBinaryFile(FILE *fp) const;

private:
	Table       *m_Table;
	Variable    *m_Column;
	DataType     m_DataType;
	Value        m_DefaultValue;
	Value        m_MinValue;
	Value        m_MaxValue;
	Vector       m_AllowedValues;

	// friendship
	friend class Table;
	friend class Variable;
	friend class Collection<IFieldDef, FieldDef>;
	friend class TableFieldDefs;
};

} /* namespace DCI */

#include "DCI/Table.h"
#include "DCI/Variable.h"

#endif /* DCI_FIELDDEF_H_INCLUDED */
