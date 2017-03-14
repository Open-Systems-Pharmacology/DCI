#ifndef DCI_IVARIABLE_H_INCLUDED
#define DCI_IVARIABLE_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/ICollection.h"

namespace DCI {

// Forward declarations

interface ITable;
typedef PtrHandle<ITable>    ITableHandle;

interface IFieldDef;
typedef PtrHandle<IFieldDef> IFieldDefHandle;

// Description: Variable Interface.
//
// Objects implementing this interface represent a variable 
// (column) of a table (see the ITable interface). A variable
// contains all fields (table cells) of the table column and their
// associated values. All field values of the variable (column) 
// have the same data type, as defined in the field definition
// associated with the variable (column).
interface IVariable : virtual public IUnknown {
	// {group:Read-Only Properties}
	// Description:
	// Returns the table the variable (column) belongs to.
	//
	// Returns:
	// The handle of the table the variable belongs to. This handle
	// is always bound.
	virtual ITableHandle GetTable() const = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the field definition (meta data) associated with
	// the column (variable).
	//
	// Returns:
	// The handle of the field definition of the column. This 
	// handle is always bound.
	virtual IFieldDefHandle GetFieldDef() const = 0;

	// {group:Read/Write Properties}
	// Description:
	// Returns the vector of field values of the variable (column).
	// As the vector values may be represented by either a void, 
	// a byte, an integer, a double precision floating point or a string, 
	// a Vector object wrapping the vector values similar to a 
	// discriminated union is returned.
	//
	// Returns:
	// The value vector of the variable.
	virtual Vector GetValues() const = 0;

	// {group:Read/Write Properties}
	// Description:
	// Sets the vector of field values of the variable (column). As 
	// the vector values may be represented by either a void, a byte, an 
	// integer, a double precision floating point or a string, a Vector
	// object wrapping the vector values similar to a discriminated 
	// union has to be provided. The data type of the vector values 
	// must be in accordance with the data type specified in the
	// field definition associated with the variable (column) and
	// appropriate access rights must exist (AR_CHANGE_VALUE).
	//
	// Returns:
	// true, if the new value vector is accepted, or false otherwise.
	// In order to get extended error information, please make 
	// use of the Error module.	
	virtual Bool SetValues(const Vector &newValues) = 0;
	
	// {group:Read-Only Properties}
	// Description:
	// Returns the vector of field values of the variable (column)
    // in string format.
	//
	// Returns:
	// The string vector representing the values of the variable
    // (column) in string format.
    virtual StringVector GetValuesAsString() const = 0;
	
	// {group:Read/Write Properties}
	// Description:
	// Returns the value of a variable (column) field with a specified
	// record index. As the value may be represented by either a void, 
	// a byte, an integer, a double precision floating point or a string,
	// a Value object wrapping the value similar to a discriminated union 
	// is returned.
	// Please note, that it is not possible to specify the record
	// by key.
	//
	// This method should be used, when variable (column) data is 
	// accessed in a random-access manner. If data of the entire 
	// variable is accessed, it is more efficient to work with the 
	// value vector of the variable.
	//
	// Arguments:
	// recIdx - Index of the field in the variable (identical with
	//          the index of the record in the table). The index
	//          of the first field (the first record) is 1.
	//
	// Returns:
	// The Value of the field.
	virtual Value GetValue(UInt recIdx) const = 0;
	
    // {group:Read/Write Properties}
	// Description:
	// Sets the value of a variable (column) field with a specified
	// record index. As the value may be represented by either a void, 
	// a byte, an integer, a double precision floating point or a string,
	// a Value object wrapping the value  similar to a discriminated 
	// union has to be provided. The data type of the value must be 
	// in accordance with the data type specified in the field
	// definition associated with the variable (column) and access 
	// rights must exist (AR_CHANGE_VALUE).
	// Please note, that it is not possible to specify the record
	// by key.
	//
	// This method should be used, when record data is accessed in
	// a random-access manner. If data of the entire record is
	// accessed, it is more efficient to query the value vector of 
	// the record, to modify it and to write it back.
	//
	// Arguments:
	// recIdx   - Index of the field in the variable (identical with
	//            the index of the record in the table). The index
	//            of the first field (the first record) is 1.
	// newValue - The new value of the field.
	//
	// Returns:
	// true, if the new value is accepted, or false otherwise.
	// In order to get extended error information, please make 
	// use of the Error module.	
	virtual Bool SetValue(UInt recIdx, const Value &newValue) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the value of a variable (column) field with a specified
	// record index in string format.
	//
	// Arguments:
	// recIdx  - Index of the field in the variable (identical with
	//           the index of the record in the table). The index
	//           of the first field (the first record) is 1.
	//
	// Returns:
	// The string representing the value of the variable's (column's) 
    // field in string format.
    virtual String GetValueAsString(UInt recIdx) const = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the length of the variable.
	//
	// Returns: 
	// The length of the variable.
	virtual UInt GetLength() const = 0;
};

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Variable Interface Handle.
typedef PtrHandle<IVariable> IVariableHandle;

// {group:Interfaces}
// {glyph:Interface|Interface}
// Description: Variable Interface Collection Interface.
typedef ICollection<IVariable> IVariables;

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Variable Interface Collection Interface Handle.
typedef PtrHandle<IVariables> IVariablesHandle;

} /* namespace DCI */

#include "DCI/ITable.h"
#include "DCI/IFieldDef.h"

#endif /* DCI_IVARIABLE_H_INCLUDED */
