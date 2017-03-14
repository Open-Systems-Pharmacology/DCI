#ifndef DCI_UTILITIES_H_INCLUDED
#define DCI_UTILITIES_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/Attribute.h"
#include "DCI/FieldDef.h"
#include "DCI/Manager.h"
#include "DCI/Error.h"
#include "DCI/Math.h"


namespace DCI {

// {group:Global Modules}
// Description: Utilities Module.
//
// The utilities module provides general helper routines.
class Utilities {
public:
	// Description:
	// Sets the default format associated with a data type.
	//
	// Arguments:
	// dt - The data type associated with the default format.
	// format - The string format to be used for conversion.
	// 
	// Returns:
	// true if succesful, false otherwise.
	DCI_DLLEXPORT static Bool         SetDefaultFormat(DataType dt, String &format);

	// Description:
	// Sets the default format associated with multiple data types.
	//
	// Arguments:
	// formats - The format strings to be used for conversion.
	// 
	// Returns:
	// true if succesful, false otherwise.
	DCI_DLLEXPORT static Bool         SetDefaultFormats(StringVector &formats);

	// Description:
	// Returns the default format associated with a data type.
	//
	// Returns:
	// the default format associated with the data type.
	DCI_DLLEXPORT static String       GetDefaultFormat(DataType dt);

	// Description:
	// Returns the default format associated with multiple data types.
	//
	// Returns:
	// the default formats associated with multiple data types.
	DCI_DLLEXPORT static StringVector GetDefaultFormats();
    
	// Description:
	// Converts a date/time from string to double format.
	// A double value of 1.0 represents the date 01-01-0000.
	// A difference of 1.0 corresponds to a difference of one day.
	//
	// Arguments:
	// s   - The string representing the data/time value to be converted.
	// dt  - The double value to hold the result.
	// fmt - The string format to be used for conversion.
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	DCI_DLLEXPORT static Bool         StringToDateTime(const String &s, Double &dt, const String &fmt);

	// Description:
	// Converts a date/time from double to string format.
	// A double value of 1.0 represents the date 01-01-0000.
	// A difference of 1.0 corresponds to a difference of one day.
	//
	// Arguments:
	// dt  - The data/time value to be converted.
	// s   - The result string to hold the converted data/time value.
	// fmt - The string format to be used for conversion.
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	DCI_DLLEXPORT static Bool         DateTimeToString(Double dt, String &s, const String &fmt);

	// Description:
	// Converts a date/time vector from string to double format.
	// A double value of 1.0 represents the date 01-01-0000.
	// A difference of 1.0 corresponds to a difference of one day.
	//
	// Arguments:
	// sv  - A string vector containing the data/time string representations
	//       to be converted.
	// dtv - A double vector containing the data/time values after the
	//       conversion.
	// fmt - The string format to be used for conversion.
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	DCI_DLLEXPORT static Bool         StringVectorToDateTimeVector(const StringVector &sv, DoubleVector &dtv, const String &fmt);

	// Description:
	// Converts a date/time vector from double to string format.
	// A double value of 1.0 represents the date 01-01-0000.
	// A difference of 1.0 corresponds to a difference of one day.
	//
	// Arguments:
	// dtv - A double vector containing the data/time values to be converted.
	// sv  - A result string vector containing the data/time string representations
	//       after the conversion.
	// fmt - The string format to be used for conversion.
	//
	// Returns:
	// true if the conversion is succesful.
	DCI_DLLEXPORT static Bool         DateTimeVectorToStringVector(const DoubleVector &dtv, StringVector &sv, const String &fmt);

	// Description:
	// Converts an enumeration value from string to integer format.
	//
	// The integer returned is the index of the string in the list
	// of allowed values. If the string is not present in this list,
	// an error occurs. However, even in the case of an error, an
	// integer is assigned; the value of the integer will then be -1.
	//
	// Arguments:
	// s             - The string representing the enumeration value to be 
	//                 converted.
	// e             - The integer representation of the enumeration.
	// allowedValues - A string vector containing the string representation
	//                 of the enumeration values.
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	//
	// See also: StringToEnumEx.
	DCI_DLLEXPORT static Bool         StringToEnum(const String &s, Int &e, const StringVector &allowedValues);

	// Description:
	// Converts an enumeration value from string to integer format.
	//
	// The integer returned is the index of the string in the list
	// of allowed values. If the string is not present in this list,
	// it will be added to the list of allowed values.
	//
	// Arguments:
	// s             - The string representing the enumeration value to be 
	//                 converted.
	// e             - The integer representation of the enumeration.
	// allowedValues - A string vector containing the string representation
	//                 of the enumeration values.
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	//
	// See also: StringToEnum.
	DCI_DLLEXPORT static Bool         StringToEnumEx(const String &s, Int &e, StringVector &allowedValues);

	// Description:
	// Converts an enumeration value from integer to string format.
	//
	// The integer is treated as index into the list of allowed
	// values. If the index is invalid (out of bounds), an error occurs.
	// However, the value will still be converted, if the index is
	// invalid; in this case an empty string will be returned.
	//
	// Arguments:
	// e             - The integer representing the enumeration value to be 
	//                 converted.
	// s             - The result string representing the enumeration value after
	//                 convertion.
	// allowedValues - A string vector containing the string representation
	//                 of the enumeration values.
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	DCI_DLLEXPORT static Bool         EnumToString(Int e, String &s, const StringVector &allowedValues);

	// Description:
	// Converts an enumeration vector from string to integer format.
	//
	// The list of allowed values is left unchanged. If the string
	// vector contains values missing in the list of allowed values,
	// an error occurs. However, the vector will be converted even
	// in case of an error; values of -1 will be entered for values
	// missing in the list of allowed values. If the value is
	// available, its index in the list of allowed values will be
	// entered.
	//
	// Arguments:
	// sv            - The string vector containing the strings representing 
	//                 the enumeration values to be converted.
	// ev            - The integer vector holding the result of the enumeration.
	// allowedValues - A string vector containing the string representation
	//                 of the enumeration values.
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	//
	// See also: StringVectorToEnumVectorEx.
	DCI_DLLEXPORT static Bool         StringVectorToEnumVector(const StringVector &sv, IntVector &ev, const StringVector &allowedValues);

	// Description:
	// Converts an enumeration vector from string to integer format.
	//
	// String values missing in the list of allowed values are added 
	// to the list. The values entered into the integer vector are
	// the indexes of the corresponding strings in the list of allowed
	// values.
	//
	// Arguments:
	// sv            - The string vector containing the strings representing 
	//                 the enumeration values to be converted.
	// ev            - The integer vector holding the result of the enumeration.
	// allowedValues - A string vector containing the string representation
	//                 of the enumeration values.
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	//
	// See also: StringVectorToEnumVector.
	DCI_DLLEXPORT static Bool         StringVectorToEnumVectorEx(const StringVector &sv, IntVector &ev, StringVector &allowedValues);

	// Description:
	// Converts an enumeration vector from integer to string format.
	//
	// The integers are treated as indexes into the list of allowed
	// values. If an index is invalid (out of bounds), an error occurs.
	// However, the vector will still be converted, if indexes are 
	// invalid; in this case an empty string will be entered into the
	// string vector.
	//
	// Arguments:
	// ev            - The integer vector containing the integers representing 
	//                 the enumeration values to be converted.
	// sv            - The result string vector containing the strings representing 
	//                 the enumeration values after conversion.
	// allowedValues - A string vector containing the string representation
	//                 of the enumeration values.
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	DCI_DLLEXPORT static Bool         EnumVectorToStringVector(const IntVector &ev, StringVector &sv, const StringVector &allowedValues);

	// Description:
	// Converts a string to a specific data type using the given format specification.
	// 
	// Arguments:
	// s	- The string to be converted.
	// dt	- The datatype of the expected result.
	// v	- The variable to hold the result. (must fit the given datatype).
	// fmt	- The format string to be used for the conversion. (optional).
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	DCI_DLLEXPORT static Bool         StringToValue(const String &s, DataType dt, Value &v, const String &fmt="");

	// Description:
	// Converts a value of a specific data type to a string using the given format specification.
	// The data type is implied from the format specification, if given.
	// 
	// Arguments:
	// s	- The string to hold the converted data.
	// v	- The value to be converted. (must fit the datatype implied from the format string).
	// fmt	- The format string to be used for the conversion. (optional).
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	DCI_DLLEXPORT static Bool         ValueToString(const Value &v, String &s, const String &fmt="");

	// Description:
	// Converts a string to a vector of the same data type using the given format specification.
	// 
	// Arguments:
	// s	- The string to be converted.
	// dt	- The datatype of the expected results.
	// v	- The vector to hold the results. (must fit the given datatype).
	// fmt	- The format string to be used for the conversion. (optional).
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	DCI_DLLEXPORT static Bool         StringToVector(const String &s, DataType dt, Vector &v, const String &fmt="");

	// Description:
	// Converts a vector of values of a specific data type to a string using the given format specification.
	// The data type is implied from the format specification, if given.
	// 
	// Arguments:
	// s	- The string to hold the converted data.
	// v	- The vector of the values to be converted. (must fit the datatype implied from the format string).
	// fmt	- The format string to be used for the conversion. (optional).
	//
	// Returns:
	// true if the conversion was succesful, false otherwise.
	DCI_DLLEXPORT static Bool         VectorToString(const Vector &v, String &s, const StringVector &allowedValues, const String &fmt="",DataType dt=DT_VOID);


};

} /* namespace DCI */

#endif /* DCI_UTILITIES_H_INCLUDED */
