#ifndef DCI_IRECORD_H_INCLUDED
#define DCI_IRECORD_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/ICollection.h"

namespace DCI {

// Forward declarations

interface ITable;
typedef PtrHandle<ITable>      ITableHandle;

interface IFieldDef;
typedef PtrHandle<IFieldDef>   IFieldDefHandle;
typedef ICollection<IFieldDef> IFieldDefs;
typedef PtrHandle<IFieldDefs>  IFieldDefsHandle;

// Description: Record Interface.
//
// Objects implementing this interface represent a record (row)
// of a record-based table (see the ITable interface). A record
// contains all fields (table cells) of the table row and their
// associated values. The field values of the record (row) may
// have different data types, as defined in the field definition
// of the column (variable) the respective field belongs to.
//
// Whenever a new record is created, its field values are initalized
// with their default value as defined in the associated field
// definitions.
interface IRecord : virtual public IUnknown {
	// {group:Read-Only Properties}
	// Description:
	// Returns the table the record (row) belongs to.
	//
	// Returns:
	// The handle of the table the record belongs to. This handle
	// is always bound.
	virtual ITableHandle GetTable() = 0;

	// {group:Read/Write Properties}
	// Description:
	// Returns the vector of field values of the record. As any 
	// value of the vector may be represented by either a void, a
	// byte, an integer, a double precision floating point or a string, 
	// a ValueVector containing Value objects wrapping the vector 
	// values similar to a discriminated union is returned.
	//
	// Returns:
	// The value vector of the record.
	virtual ValueVector GetValues() const = 0;

    // {group:Read/Write Properties}
	// Description:
	// Sets the vector of field values of the record. As any value of
	// the vector may be represented by either a void, a byte, an integer, 
	// a double precision floating point or a string, a ValueVector
	// object containing Value objects wrapping the vector values
	// similar to a discriminated union has to be provided. The data 
	// types of the values must be in accordance with the data types
	// of the column (variable) the field values belong to and 
	// appropriate access rights must exist (AR_CHANGE_VALUE).
	//
	// Returns:
	// true, if the new value vector is accepted, or false otherwise.
	// In order to get extended error information, please make 
	// use of the Error module.	
	virtual Bool SetValues(const ValueVector &newValues) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the vector of field values of the record in string format.
	//
	// Returns:
	// The string vector representing the values of the record 
    // in string format.
    virtual StringVector GetValuesAsString() const = 0;

	// {group:Read/Write Properties}
	// Description:
	// Returns the value of a record field with a specified
	// (column) index or associated (column) key. As the value may 
	// be represented by either a void, a byte, an integer, a double 
	// precision floating point or a string, a Value object wrapping 
	// the value similar to a discriminated union is returned.
	//
	// This method should be used, when record data is accessed in
	// a random-access manner. If data of the entire record is
	// accessed, it is more efficient to work with the value vector
	// of the record.
	//
	// Arguments:
	// colIdx - Index of the field in the record (identical with
	//          the index of the column in the table). The index
	//          of the first field (the first column) is 1.
	// colKey - Key associated with the field in the record
	//          (identical with the key of the column in the table).
	//
	// Returns:
	// The Value of the field.
	virtual Value GetValue(UInt colIdx) const = 0;
	virtual Value GetValue(const String &colKey) const = 0;

    // {group:Read/Write Properties}
	// Description:
	// Sets the value of a record field with a specified (column)
	// index or associated (column) key. As the value may be represented 
	// by either a void, a byte, an integer, a double precision
	// floating point or a string, a Value object wrapping the value 
	// similar to a discriminated union has to be provided. The data 
	// type of the value must be in accordance with the data type of 
	// the column (variable) the field belongs to and appropriate 
	// access rights must exist (AR_CHANGE_VALUE).
	//
	// This method should be used, when record data is accessed in
	// a random-access manner. If data of the entire record is
	// accessed, it is more efficient to query the value vector of 
	// the record, to modify it and to write it back.
	//
	// Arguments:
	// colIdx   - Index of the field in the record (identical with
	//            the index of the column in the table). The index
	//            of the first field (the first column) is 1.
	// colKey   - Key associated with the field in the record
	//            (identical with the key of the column in the table).
	// newValue - The new value of the field.
	//
	// Returns:
	// true, if the new value is accepted, or false otherwise.
	// In order to get extended error information, please make 
	// use of the Error module.	
	virtual Bool SetValue(UInt colIdx, const Value &newValue) = 0;
	virtual Bool SetValue(const String &colKey, const Value &newValue) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the value of a record field with a specified
	// (column) index or associated (column) key in string format.
	//
	// Arguments:
	// colIdx - Index of the field in the record (identical with
	//          the index of the column in the table). The index
	//          of the first field (the first column) is 1.
	// colKey - Key associated with the field in the record
	//          (identical with the key of the column in the table).
	//
	// Returns:
	// The string representing the value of the record's field 
    // in string format.
    virtual String GetValueAsString(UInt colIdx) const = 0;
    virtual String GetValueAsString(const String &colKey) const = 0;
};

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Record Interface Handle.
typedef PtrHandle<IRecord> IRecordHandle;

// {group:Interfaces}
// {glyph:Interface|Interface}
// Description: Record Interface Collection Interface.
typedef ICollection<IRecord> IRecords;

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Record Interface Collection Interface Handle.
typedef PtrHandle<IRecords> IRecordsHandle;

} /* namespace DCI */

#include "DCI/ITable.h"
#include "DCI/IFieldDef.h"

#endif /* DCI_IRECORD_H_INCLUDED */
