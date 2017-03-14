#ifndef DCI_IFIELDDEF_H_INCLUDED
#define DCI_IFIELDDEF_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/IObject.h"
#include "DCI/ICollection.h"

namespace DCI {

// Forward declarations

interface ITable;
typedef PtrHandle<ITable> ITableHandle;

// Description: Field Definition Interface.
//
// Objects implementing this interface represent a field definition
// defining the meta data associated with a column (variable) of a table
// (see the ITable interface). The most important property of this 
// attribute is the data type, which determines the data types allowed
// for representing data in the column (variable) associated with the
// field definition.
interface IFieldDef : virtual public IObject {
	// {group:Read-Only Properties}
	// Description:
	// Returns the table the field belongs to.
	//
	// Returns:
	// The handle of the table the field belongs to. This handle
	// is always bound.
	virtual ITableHandle GetTable() const = 0;

	// {group:Read/Write Properties}
	// Description:
	// Returns the data type of the associated column (variable).
	//
	// Returns:
	// The data type of the associated column (variable).
	virtual DataType GetDataType() const = 0;

	// {group:Read/Write Properties}
	// Description:
	// Sets the data type of the associated column (variable). 
	// In order to use this method, appropriate access rights must 
	// exist (AR_CHANGE_DATATYPE).
	//
	// Arguments:
	// - newDataType: The data type to be used for representing the
	//                values of the associated column (variable).
	//
	// Returns:
	// true, if the data type is set to the new value, or false otherwise.
	// In order to get extended error information, please use the 
	// Error module.
	virtual Bool SetDataType(DataType newDataType) = 0;

	// {group:Read/Write Properties}
	// Description:
	// Returns the default value for the associated column (variable).
	// As the value may be represented by either a void, an integer, a double 
	// precision floating point or a string, a Value object wrapping the value 
	// similar to a discriminated union is returned.
	//
	// Returns:
	// The default value for the associated column (variable).
	virtual Value GetDefaultValue() const = 0;

	// {group:Read/Write Properties}
	// Description:
	// Sets the default value for the associated column (variable). 
	// As the value may be represented by either a void, an integer, a double 
	// precision floating point or a string, a Value object wrapping the 
	// value similar to a discriminated union has to be provided. The data 
	// type of the value must be in accordance with the column's data type 
	// defined by this field definition. 
	// In order to use this method, appropriate access rights must 
	// exist (AR_CHANGE_DEFAULT_VALUE).
	//
	// Arguments:
	// - newDefaultValue: The new default value for the associated column 
	//                    (variable).
	//
	// Returns:
	// true, if the default value is set to the new value, or false otherwise. 
	// In order to get extended error information, please use the 
	// Error module.
	virtual Bool SetDefaultValue(const Value &newDefaultValue) = 0;
	
	// {group:Read/Write Properties}
	// Description:
	// Returns the minimum value for the associated column (variable).
	// As the value may be represented by either a void, an integer, a double 
	// precision floating point or a string, a Value object wrapping the value 
	// similar to a discriminated union is returned.
	// Please note, that this value only provides information; when
	// setting a value, its range is not actully checked against this
	// minimum value.
	//
	// Returns:
	// The minimum value for the associated column (variable).
	virtual Value GetMinValue() const = 0;

	// {group:Read/Write Properties}
	// Description:
	// Sets the minimum value for the associated column (variable). 
	// As the value may be represented by either a void, an integer, a double 
	// precision floating point or a string, a Value object wrapping the 
	// value similar to a discriminated union has to be provided. The data 
	// type of the value must be in accordance with the column's data type 
	// defined by this field definition. 
	// In order to use this method, appropriate access rights must 
	// exist (AR_CHANGE_MIN_VALUE).
	// Please note, that this value only provides information; when
	// setting a value, its range is not actully checked against this
	// minimum value.
	//
	// Arguments:
	// - newMinValue: The new minimum value for the associated column 
	//                (variable).
	//
	// Returns:
	// true, if the minimum value is set to the new value, or false otherwise. 
	// In order to get extended error information, please use the 
	// Error module.
	virtual Bool SetMinValue(const Value &newMinValue) = 0;
	
	// {group:Read/Write Properties}
	// Description:
	// Returns the maximum value for the associated column (variable).
	// As the value may be represented by either a void, an integer, a double 
	// precision floating point or a string, a Value object wrapping the value 
	// similar to a discriminated union is returned.
	// Please note, that this value only provides information; when
	// setting a value, its range is not actully checked against this
	// maximum value.
	//
	// Returns:
	// The maximum value for the associated column (variable).
	virtual Value GetMaxValue() const = 0;
	
	// {group:Read/Write Properties}
	// Description:
	// Sets the maximum value for the associated column (variable). 
	// As the value may be represented by either a void, an integer, a double 
	// precision floating point or a string, a Value object wrapping the 
	// value similar to a discriminated union has to be provided. The data 
	// type of the value must be in accordance with the column's data type 
	// defined by this field definition. 
	// In order to use this method, appropriate access rights must 
	// exist (AR_CHANGE_MAX_VALUE).
	// Please note, that this value only provides information; when
	// setting a value, its range is not actully checked against this
	// maximum value.
	//
	// Arguments:
	// - newMaxValue: The new maximum value for the associated column 
	//                (variable).
	//
	// Returns:
	// true, if the maximum value is set to the new value, or false otherwise. 
	// In order to get extended error information, please use the 
	// Error module.
	virtual Bool SetMaxValue(const Value &newMaxValue) = 0;
	
	// {group:Read/Write Properties}
	// Description:
	// Returns a vector containing a list of allowed values for the 
	// associated column (variable). If the vector is empty, all values
	// are allowed.
	// As the values may be represented by either a void, an integer, a double 
	// precision floating point or a string, a Vector object wrapping the values 
	// similar to a discriminated union is returned.
	// Please note, that this vector only provides information; when
	// setting a value, it is not actully checked against this list of 
	// allowed values.
	//
	// Returns:
	// The vector containing the list of allowed values for the associated 
	// column (variable).
	virtual Vector GetAllowedValues() const = 0;
	
	// {group:Read/Write Properties}
	// Description:
	// Sets the vector containing a list of allowed values for the associated
	// column (variable). If the vector is empty, all values are allowed.
	// As the values may be represented by either a void, an integer, a double 
	// precision floating point or a string, a Vector object wrapping the 
	// values similar to a discriminated union has to be provided. The data 
	// type of the vector must be in accordance with the column's data type 
	// defined by this field definition. 
	// In order to use this method, appropriate access rights must 
	// exist (AR_CHANGE_ALLOWED_VALUES).
	// Please note, that this vector only provides information; when
	// setting a value, it is not actully checked against this list of 
	// allowed values.
	//
	// Arguments:
	// - newAllowedValues: The vector containing the list of allowed
	//                     values for the associated column (variable).
	//
	// Returns:
	// true, if the maximum value is set to the new value, or false otherwise. 
	// In order to get extended error information, please use the 
	// Error module.
	virtual Bool SetAllowedValues(const Vector &newAllowedValues) = 0;
};

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Field Definition Interface Handle.
typedef PtrHandle<IFieldDef> IFieldDefHandle;

// {group:Interfaces}
// {glyph:Interface|Interface}
// Description: Field Definition Interface Collection Interface.
typedef ICollection<IFieldDef> IFieldDefs;

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Field Definition Interface Collection Interface Handle.
typedef PtrHandle<IFieldDefs> IFieldDefsHandle;

} /* namespace DCI */

#include "DCI/ITable.h"

#endif /* DCI_IFIELDDEF_H_INCLUDED */
