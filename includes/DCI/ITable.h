#ifndef DCI_ITABLE_H_INCLUDED
#define DCI_ITABLE_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/IObject.h"
#include "DCI/ICollection.h"

namespace DCI {

// Forward declarations

interface ITable;
typedef PtrHandle<ITable> ITableHandle;

interface IFieldDef;
typedef PtrHandle<IFieldDef>   IFieldDefHandle;
typedef ICollection<IFieldDef> IFieldDefs;
typedef PtrHandle<IFieldDefs>  IFieldDefsHandle;

interface IVariable;
typedef PtrHandle<IVariable>   IVariableHandle;
typedef ICollection<IVariable> IVariables;
typedef PtrHandle<IVariables>  IVariablesHandle;

interface IRecord;
typedef PtrHandle<IRecord>     IRecordHandle;
typedef ICollection<IRecord>   IRecords;
typedef PtrHandle<IRecords>    IRecordsHandle;

// Description: Table Interface.
//
// Objects implementing this interface represent a table organizing
// data in columns (variables) and rows (records). Each column is 
// associated with a set of meta information (field definition), which
// specifies the name of the column, its data type and other things.
//
// A table can either be non-record-based or record-based. A non-
// record-based table lacks the concept of a record (row); it organizes
// the data just as a collection of columns (variables), each column
// containing vector data of a certain type with any length. The layout
// of a non-record-based table is thus very flexible. A record-based 
// table on the other hand can be regared as a two-dimensional matrix 
// which can be accessed and manipulated not only using the columns 
// (variables) but also using records (rows). In a record-based table, 
// all column data vectors have the same length. Such a table is less
// flexible, but it is possible to handle rows of data.
interface ITable : virtual public IObject {
	// Description:
	// Queries, if the table is record-based (record-functionality 
	// enabled) or not.
	//
	// Returns:
	// true if the table is record-based, or false if the table is not
	// record-based.
	virtual Bool GetRecordBased() = 0;

	// Description:
	// Sets, if the table is record-based (record-functionality 
	// enabled) or not. Usually, this method is called immediately after
	// a table object has been created. However, it might also be used
	// in order to change the type of the table. It is always possible
	// to switch from a record-based table to a non-record-based table;
	// however, a non-record-based table can only be converted to a
	// record-based table, if all column (variable) data vectors have the
	// same vector length.
	//
	// Arguments: 
	// recBsd - Determines, if the table should be record-based (true)
	//          or non-record-based (false).
	//
	// Returns:
	// true if the method succeeds, or false in case of an error. In order 
	// to get extended error information, please make use of the Error module.
	virtual Bool SetRecordBased(Bool recBsd) = 0;

	// Description:
	// Changes the dimension (size) of the table to specified values.
	//
	// If the table is record-based and the method succeeded, the table
	// will have the specified number of records (rows) and colums
	// (variables). 
	// If the table shrinks when it is redimensioned, the respective
	// rows (records) and columns (variables) will be deleted. If it
	// grows, new rows (records) and columns (variables) will be created;
	// the rows (records) will be inititialzed with their default
	// values and the columns (rows) will be uninitialized.
	//
	// If the table is not record-based and the method 
	// succeeded, the number of records is ignored and the table will
	// have the specified number of columns (variables).
	// If the table shrinks when it is redimensioned, the respective
	// columns (variables) will be deleted. If it grows, columns 
	// (variables) will be created;	these columns will be uninitialized.
	//
	// Arguments:
	// noRecs - The desired number of records if the table is record-based.
	//          If the table is not record-based, this argument is ignored.
	// noCols - The desired number of columns (variables).
	//
	// Results:
	// true if the method succeeds and the table is redimensioned,
	// or false otherwise (e.g. if a client still holds a reference to
	// a column which must be removed for redimensioning the table).
	virtual Bool ReDim(UInt noRecs, UInt noCols) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the collection of field definitions of the table.
	// The collection is identical with each record's field definition
	// collection.
	//
	// Returns:
	// The handle of the collection of field definitions. This handle
	// is always bound.
	virtual IFieldDefsHandle GetFieldDefs() = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the field definition associated with a specified (column) 
	// index or associated (column) key. The field definition is identical
	// with each record's field definition with that index or key.
	//
	// Arguments:
	// colIdx - Index of the column of the table. The index
	//          of the first column is 1.
	// colKey - Key associated with the column of the table.
	//
	// Returns:
	// The handle of the field definition if the index is valid 
	// or a column with the key exists, or an unbound handle otherwise.
	virtual IFieldDefHandle GetFieldDef(UInt colIdx) = 0;
	virtual IFieldDefHandle GetFieldDef(const String &colKey) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the collection of records (rows) of the table. In order to
	// use this method, the table must be record-based.
	//
	// Returns:
	// The handle of the collection of recordsof the table. This handle
	// is always bound.
	virtual IRecordsHandle GetRecords() = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the table's record with the specified index. 
	// Please note, that it is not possible to access records by key.
	//
	// Arguments:
	// recIdx - Index of the record of the table. The index
	//          of the first record is 1.
	//
	// Returns:
	// The handle of the record if the index is valid, or an 
	// unbound handle otherwise.
	virtual IRecordHandle GetRecord(UInt recIdx) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the collection of columns (variables) of the table.
	//
	// Returns:
	// The handle of the collection of columns. This handle
	// is always bound.
	virtual IVariablesHandle GetColumns() = 0;
	
	// {group:Read-Only Properties}
	// Description:
	// Returns the column (variale) with a specified  index or 
	// associated key.
	//
	// Arguments:
	// colIdx - Index of the column of the table. The index
	//          of the first column is 1.
	// colKey - Key associated with the column of the table.
	//
	// Returns:
	// The handle of the column if the index is valid or a column 
	// with the key exists, or an unbound handle otherwise.
	virtual IVariableHandle GetColumn(UInt colIdx) = 0;
	virtual IVariableHandle GetColumn(const String &colKey) = 0;
	
	// {group:Read/Write Properties}
	// Description:
	// Returns the value of a table field (cell) with a specified
	// column index or associated column key and a specified
	// record (row) index. As the value may be represented by either 
	// a void, a byte, an integer, a double precision floating point  
	// or a string, a Value object wrapping the value similar to a 
	// discriminated union is returned.
	// Please note, that it is not possible to specify the record
	// by key.
	//
	// This method should be used, when table data is accessed in
	// a random-access manner. If data is accessed record-wise
	// (row-wise) or column-wise (variable-wise), it is more efficient
	// to work with the value vector of the record or column.
	//
	// Arguments:
	// recIdx - Record index of the field in the table.
	// colIdx - Column index of the field in the table. The index
	//          of the the first column is 1.
	// colKey - Column key of the field in the table.
	//
	// Returns:
	// The Value of the field.
	virtual Value GetValue(UInt recIdx, UInt colIdx) const = 0;
	virtual Value GetValue(UInt recIdx, const String &colKey) const = 0;
	
    // {group:Read/Write Properties}
	// Description:
	// Sets the value of a table field (cell) with a specified column
	// index or associated column key and a specified record (row)
	// index. As the value may be represented by either a void, a byte,
	// an integer, a double precision floating point or a string, a 
	// Value object wrapping the value similar to a discriminated union 
	// has to be provided. The data type of the value must be in 
	// accordance with the data type of the column (variable) the 
	// field belongs to and appropriate access rights must exist 
	// (AR_CHANGE_VALUE).
	// Please note, that it is not possible to specify the record
	// by key.
	//
	// This method should be used, when table data is accessed in
	// a random-access manner. If data is accessed record-wise
	// (row-wise) or column-wise (variable-wise), it is more efficient
	// to query the value vector of the record or column, to modify
	// it and to write it back.
	//
	// Returns:
	// true, if the new value is accepted, or false otherwise.
	// In order to get extended error information, please make 
	// use of the Error module.	
	virtual Bool SetValue(UInt recIdx, UInt colIdx, const Value &newValue) = 0;
	virtual Bool SetValue(UInt recIdx, const String &colKey, const Value &newValue) = 0;
	
	// {group:Read-Only Properties}
	// Description:
	// eturns the value of a table field (cell) with a specified
	// column index or associated column key and a specified
	// record (row) index in string format.
	//
	// Arguments:
	// recIdx - Record index of the field in the table.
	// colIdx - Column index of the field in the table. The index
	//          of the the first column is 1.
	// colKey - Column key of the field in the table.
	//
	// Returns:
	// The string representing the value of the table's field (cell)
    // in string format.
    virtual String GetValueAsString(UInt recIdx, UInt colIdx) const = 0;
    virtual String GetValueAsString(UInt recIdx, const String &colKey) const = 0;

	// Description:
	// Assigns (copies) the data and meta data from a specified 
	// source table to this table. 
	//
	// Please note, that this method may fail if the table is
	// not empty and there are still references to columns 
	// (variables), records (rows) or fields (cells). However,
	// the method always succeeds, if this table (the table to be
	// assigned to) is empty (was just created), unless the system
	// memory is exhausted.
	//
	// Arguments:
	// srcTbl - Handle of the source table, from which the data
	//          and meta data is assigned (copied).
	//
	// Result:
	// true, if the method succeeds, or false otherwise.
	// In order to get extended error information, please make 
	// use of the Error module.	
	virtual Bool AssignFrom(ITableHandle &srcTbl) = 0;
	
	// Description:
	// Assigns (copies) only the table schema (meta data)
	// from a specified source table to this table. The
	// table will not contain any data, i.e. it will not
	// have any records (rows) and the columns' (variables')
	// value vectors will be emtpy.
	//
	// Please note, that this method may fail if the table is
	// not empty and there are still references to columns 
	// (variables), records (rows) or fields (cells). However,
	// the method always succeeds, if this table (the table to be
	// assigned to) is empty (was just created), unless the system
	// memory is exhausted.
	//
	// Arguments:
	// srcTbl - Handle of the source table, from which the schema
	//          (meta data) is assigned (copied).
	//
	// Result:
	// true, if the method succeeds, or false otherwise.
	// In order to get extended error information, please make 
	// use of the Error module.	
	virtual Bool AssignSchemaFrom(ITableHandle &srcTbl) = 0;
};

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Table Interface Handle.
typedef PtrHandle<ITable> ITableHandle;

} /* namespace DCI */

#include "DCI/IFieldDef.h"
#include "DCI/IVariable.h"
#include "DCI/IRecord.h"

#endif /* DCI_ITABLE_H_INCLUDED */
