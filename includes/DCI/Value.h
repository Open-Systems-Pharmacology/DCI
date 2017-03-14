#ifndef DCI_VALUE_H_INCLUDED
#define DCI_VALUE_H_INCLUDED

#include "DCI/DCI.h"

namespace DCI {

// Forward declarations

class String;
class Vector;
template<class T> struct CVectorRep;

// {group:Data Classes}
// Description: Value Class.
//
// This class represents a value with a variant data type similar
// to a discriminated union (the discriminator being the data type).
// Depending on the actual data type, the value may be void or 
// represented by either a (signed) integer, a double precision 
// floating point or a string.
class DCI_DLLEXPORT Value {
public:
	// Description:
	// Constructs a new value object. Optionally, a value can
	// be assigned during construction. If the corresponding
	// argument to the constructor is omitted, the value is
	// initialized as a void value (DT_VOID).
	//
	// Arguments:
	// v  - A value object to be copied. The value will have
	//      the same value and data type as v.
    // b  - A byte to be assigend to the value object.
    //      The value will have the data type DT_BYTE.
	// i  - An integer to be assigned to the value object.
	//      The value will have the data type DT_INT.
	// d  - A double precision floating point to be assigned to the
	//      value object. The value will have the data type DT_DOUBLE.
	// s  - A string to be assigned to the value object.
	//      The value will have the data type DT_STRING.
	// pc - A string to be assigned to the value object represented by
	//      a zero-terminated character array. The value will have 
	//      the data type DT_STRING.
    // fp  - The file pointer of the file storing the value
    //       in a DCI-specific binary format.
	Value();
	Value(const Value &v);
    Value(Byte b);
	Value(Int i);
	Value(Double d);
	Value(const String &s);
	Value(const char *pc);
    Value(FILE *fp);

	// Description:
	// Destructs the value object.
	~Value();

    // Description:
    // Saves the value to a binary file.
    //
    // Arguments:
    // fp  - The file pointer of the file storing the value
    //       in a DCI-specific binary format.
    //
    // Returns:
    // True, if the operation succeeded, false otherwise.
    Bool SaveToBinaryFile(FILE *fp) const;

    // {group: Read-Only Properties}
	// Description:
	// Returns the data type of the value.
	//
	// Returns:
	// The data type of the value.
	DataType GetDataType() const { 
		return m_DataType; 
	}

    // Description:
	// Converts the value to a (signed) byte value of type Byte.
	// In order to use this operator, the data type of the value
	// must be DT_BYTE, or 0 is returned.
	//
	// Returns:
	// The (signed) byte value of the value object
	// if it has data type DT_BYTE, or 0 otherwise.
	operator Byte() const;

	// Description:
	// Converts the value to a (signed) integer value of type Int.
	// In order to use this operator, the data type of the value
	// must be DT_INT, or 0 is returned.
	//
	// Returns:
	// The (signed) integer value of the value object
	// if it has data type DT_INT, or 0 otherwise.
	operator Int() const;

	// Description:
	// Converts the value to a double precision floating point value of 
	// type Double.
	// In order to use this operator, the data type of the value
	// must be DT_DOUBLE, or 0 is returned.
	//
	// Returns:
	// The (signed) double precision floating point value of the 
	// value object if it has data type DT_INT, or 0 otherwise.
	operator Double() const;

	// Description:
	// Converts the value to a string value of type String.
	// In order to use this operator, the data type of the value
	// must be DT_STRING, or an empty string is returned.
	//
	// Returns:
	// A String object representing the string value of the 
	// value object if it has data type DT_STRING, or an empty
	// string otherwise.
	operator String() const;

	// Description:
	// Converts the value to a string value represented by
	// a zero-terminated character array.
	// In order to use this operator, the data type of the value
	// must be DT_STRING, or an empty string is returned.
	// Please note, that you may not modify the characters 
	// in the character array and that you are not the owner
	// of the string memory.
	//
	// Returns:
	// A pointer to the zero-terminated character array representing 
	// the string value of the value object if it has data type 
	// DT_STRING, or a pointer to an empty zero-terminated character
	// array otherwise.
	operator const char *() const;
	
	// Description:
	// Assigns a new value to the value object. The data type of
	// the new value will be the new data type of the value
	// object.
	//
	// Arguments:
	// v  - A value object to be assigned. The new value will have
	//      the same value and data type as v.
	// b  - A byte to be assigned to the value object.
	//      The value will have the data type DT_BYTE.
	// i  - An integer to be assigned to the value object.
	//      The value will have the data type DT_INT.
	// d  - A double precision floating point to be assigned to the 
	//      value obect. The value will have the data type DT_DOUBLE.
	// s  - A string to be assigned to the value object.
	//      The value will have the data type DT_STRING.
	// pc - A string to be assigned to the value object represented by
	//      a zero-terminated character array. The value will have 
	//      the data type DT_STRING.
	//
	// Returns:
	// The reference of the value object.
	Value &operator = (const Value &v);
	Value &operator = (Byte b);
	Value &operator = (Int i);
	Value &operator = (Double d);
	Value &operator = (const String &s);
	Value &operator = (const char *pc);

private:
    // needed for value vector implementation
    void Construct() { this->Value::Value(); }
    void Construct(const Value &v) { this->Value::Value(v); }
    void Construct(FILE *fp) { this->Value::Value(fp); }
    void Destruct() { this->Value::~Value(); }
    static void ConstructArray(Value *pFirst, size_t Len);
    static void ConstructArray(Value *pFirst, size_t Len, const Value &initVal);
    static void ConstructArray(Value *pFirst, size_t Len, FILE *fp);
    static void DestructArray(Value *pFirst, size_t Len);
    static void CloneArray(Value *pFirstDest, const Value *pFirstSrc, size_t Len);
    static Bool SaveArrayToBinaryFile(Value *pFirst, size_t Len, FILE *fp);
    friend class Vector;
    friend struct CVectorRep<Value>;

    DataType m_DataType;
	union {
        Byte    byteVal;
		Int     intVal;
		Double  dblVal;
		char    strVal[4]; // actually a String object
	}	m_Value;
};

} /* namespace DCI */

#include "DCI/String.h"

#endif /* DCI_VALUE_H_INCLUDED */
