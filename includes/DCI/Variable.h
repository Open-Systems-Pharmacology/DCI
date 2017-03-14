#ifndef DCI_VARIABLE_H_INCLUDED
#define DCI_VARIABLE_H_INCLUDED

#include "DCI/IVariable.h"
#include "DCI/Collection.h"

namespace DCI {

// Forward declarations

class Table;
class FieldDef;
class Record;
class TableVariables;

// {internal}
// {group:Object Classes}
// Description: Variable Default Implementation.
class Variable : virtual public IVariable, public Unknown {
private:
	Variable() {}                           // forbidden
	Variable(IVariable *variableToClone) {} // forbidden
	Variable(Table *table, FieldDef *fieldDef, IVariable *variableToClone = 0);
    Variable(Table *table, FieldDef *fieldDef, FILE *fp);

public:
	virtual ~Variable();

	// IUnknown
	virtual void            AddRef();
	virtual void            Release();

	// IVariable
	virtual ITableHandle    GetTable() const;
	virtual IFieldDefHandle GetFieldDef() const;
	virtual Vector          GetValues() const;
	virtual Bool            SetValues(const Vector &newValues);
    virtual StringVector    GetValuesAsString() const;
	virtual Value           GetValue(UInt recIdx) const;
	virtual Bool            SetValue(UInt recIdx, const Value &newValue);
    virtual String          GetValueAsString(UInt recIdx) const;
	virtual UInt            GetLength() const;

private:
	// internal implementation
	Bool InternalReDim();
    Bool InternalRemove(UInt Index);
	void InternalSetDataType(DataType newDataType);
	Bool InternalCanSetValue(UInt recIdx, const Value &newValue);
    Bool SaveToBinaryFile(FILE *fp) const;

private:
	Table    *m_Table;
	Vector   *m_Values;
	FieldDef *m_FieldDef;

	// friendship
	friend class Table;
	friend class FieldDef;
	friend class Record;
	friend class Collection<IVariable, Variable>;
	friend class TableVariables;
};

} /* namespace DCI */

#include "DCI/Table.h"
#include "DCI/FieldDef.h"
#include "DCI/Record.h"

#endif /* DCI_VARIABLE_H_INCLUDED */
