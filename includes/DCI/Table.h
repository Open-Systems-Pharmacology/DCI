#ifndef DCI_TABLE_H_INCLUDED
#define DCI_TABLE_H_INCLUDED

#include "DCI/ITable.h"
#include "DCI/Object.h"

namespace DCI {

// Forward declarations

class TableFieldDefs; // internal implementation class
class TableRecords;   // internal implementation class
class TableVariables; // internal implementation class

// {group:Object Classes}
// Description: Table Default Implementation.
class Table : public ITable, public Object {
DCI_IMPL_OBJECT

	typedef Object super;

private:
	Table(ITable *tableToClone); // not implemented

public:
	// construction/destruction
	DCI_DLLEXPORT Table();
	DCI_DLLEXPORT Table(FILE *fp);
	DCI_DLLEXPORT virtual ~Table();
	
	// IObject
	DCI_DLLEXPORT virtual String           GetTypeName() const;
	DCI_DLLEXPORT virtual String           GetTypeDescription() const;

	// ITable
	DCI_DLLEXPORT virtual Bool             GetRecordBased();
	DCI_DLLEXPORT virtual Bool             SetRecordBased(Bool recBsd);
	DCI_DLLEXPORT virtual Bool             ReDim(UInt noRecs, UInt noCols);
	DCI_DLLEXPORT virtual IFieldDefsHandle GetFieldDefs();
	DCI_DLLEXPORT virtual IFieldDefHandle  GetFieldDef(UInt colIdx);
	DCI_DLLEXPORT virtual IFieldDefHandle  GetFieldDef(const String &colKey);
	DCI_DLLEXPORT virtual IVariablesHandle GetColumns();
	DCI_DLLEXPORT virtual IVariableHandle  GetColumn(UInt colIdx);
	DCI_DLLEXPORT virtual IVariableHandle  GetColumn(const String &colKey);
	DCI_DLLEXPORT virtual IRecordsHandle   GetRecords();
	DCI_DLLEXPORT virtual IRecordHandle    GetRecord(UInt recIdx);
	DCI_DLLEXPORT virtual Value            GetValue(UInt recIdx, UInt colIdx) const;
	DCI_DLLEXPORT virtual Value            GetValue(UInt recIdx, const String &colKey) const;
	DCI_DLLEXPORT virtual Bool             SetValue(UInt recIdx, UInt colIdx, const Value &newValue);
	DCI_DLLEXPORT virtual Bool             SetValue(UInt recIdx, const String &colKey, const Value &newValue);
	DCI_DLLEXPORT virtual String           GetValueAsString(UInt recIdx, UInt colIdx) const;
	DCI_DLLEXPORT virtual String           GetValueAsString(UInt recIdx, const String &colKey) const;
	DCI_DLLEXPORT virtual Bool			   AssignFrom(ITableHandle &srcTbl);
	DCI_DLLEXPORT virtual Bool             AssignSchemaFrom(ITableHandle &srcTbl);

    // internal implementation
    DCI_DLLEXPORT   Bool SaveToBinaryFile(FILE *fp) const;

private:
	// internal implementation
	Bool            ColumnsClear();
	IVariableHandle ColumnsAddNew(IVariableHandle &ObjectToCopy, UInt posIdx);
	IVariableHandle ColumnsAddNew(const String &Key, IVariableHandle &ObjectToCopy, UInt posIdx);
	IFieldDefHandle ColumnsAddNew(IFieldDefHandle &ObjectToCopy, UInt posIdx);
	IFieldDefHandle ColumnsAddNew(const String &Key, IFieldDefHandle &ObjectToCopy, UInt posIdx);
	Bool            ColumnsRemove(const String &Key);
	Bool            ColumnsRemove(UInt Index);
	UInt            ColumnsGetCount() const;
	Bool			ColumnsReDim() const;

	Bool            RecordsClear();
	IRecordHandle   RecordsAddNew(IRecordHandle &ObjectToCopy);
	Bool            RecordsRemove(UInt Index);
	UInt            RecordsGetCount() const;

private:
	Bool            m_RecordBased;
	TableFieldDefs *m_FieldDefs;
	TableRecords   *m_Records;
	TableVariables *m_Columns;

	// friendship forever
	friend class TableFieldDefs; // internal implementation class
	friend class TableVariables; // internal implementation class
	friend class TableRecords;   // internal implementation class
	friend class FieldDef;
	friend class Variable;
	friend class Record;
};

} /* namespace DCI */

#include "DCI/FieldDef.h"
#include "DCI/Variable.h"
#include "DCI/Record.h"

#endif /* DCI_TABLE_H_INCLUDED */
