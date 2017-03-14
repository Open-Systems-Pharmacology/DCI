#ifndef DCI_RECORD_H_INCLUDED
#define DCI_RECORD_H_INCLUDED

#include "DCI/IRecord.h"
#include "DCI/Collection.h"

namespace DCI {

// Forward declarations

class Table;

// {internal}
// {group:Object Classes}
// Description: Record Default Implementation.
class Record : public IRecord, public Unknown {
DCI_IMPL_UNKNOWN
private:
	Record();                       // forbidden
	Record(IRecord *recordToClone); // forbidden

public:
	Record(Table *table, UInt Index, IRecord *recordToClone = 0);
	virtual ~Record();
	//
	virtual ITableHandle     GetTable();
	virtual ValueVector      GetValues() const;
	virtual Bool             SetValues(const ValueVector &newValues);
    virtual StringVector     GetValuesAsString() const;
	virtual Value            GetValue(UInt colIdx) const;
	virtual Value            GetValue(const String &colKey) const;
	virtual Bool             SetValue(UInt colIdx, const Value &newValue);
	virtual Bool             SetValue(const String &colKey, const Value &newValue);
    virtual String           GetValueAsString(UInt colIdx) const;
    virtual String           GetValueAsString(const String &colKey) const;

private:
	PtrHandle<Table> m_Table;
	UInt             m_Index;

	// friendship
	friend class Table;
};

} /* namespace DCI */

#include "DCI/Table.h"

#endif /* DCI_RECORD_H_INCLUDED */
