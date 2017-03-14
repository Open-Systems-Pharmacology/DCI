#ifndef DCI_STRING_H_INCLUDED
#define DCI_STRING_H_INCLUDED

#include "DCI/DCI.h"

namespace DCI {

// Forware declarations

class Vector;
class Value;
template<class T> struct CVectorRep;

// {internal}
// Description: The actual string representation.
struct StringRep {
    size_t Len;
    int    RefCount;
    char   s[1];
};

// {group:Data Classes}
// Description: String Class.
//
// This class represents a string which automatically manages the
// memory necessary. If a string object is copied, the actuall
// string representation is shared until modifications are made.
// This way, using strings is very efficient.
class DCI_DLLEXPORT String {
public:
	// Description:
	// Constructs a new string.
	//
	// Arguments:
	// pc  - A pointer to a zero-terminated character array
	//       representing the string.
	// Len - The number of characters to be used at most
	//       (optional).
	// s   - The string to be copied.
	// pc1 - A pointer to a zero-terminated character array
	//       representing the first string to be concatenated.
	// pc2 - A pointer to a zero-terminated character array
	//       representing the second string to be concatenated.
    // fp  - The file pointer of the file storing the string
    //       in a DCI-specific binary format.
    String();
    String(const char *pc, size_t Len=SIZE_T_MAX);
    String(const String &s);
    String(const char *pc1, const char *pc2);
    String(FILE *fp);

	// Description:
	// Destructs the string.
    ~String();

    // Description:
    // Saves the string to a binary file.
    //
    // Arguments:
    // fp  - The file pointer of the file storing the string
    //       in a DCI-specific binary format.
    //
    // Returns:
    // True, if the operation succeeded, false otherwise.
    Bool SaveToBinaryFile(FILE *fp) const;

	// Description:
	// Assigns the string from another one.
	//
	// Arguments:
	// pc - A pointer to a zero-terminated character array
	//      representing the string to be assigned
	// s  - String object to be assigned.
	//
	// Returns:
	// The reference of the string.
    String &operator = (const char *pc);
    String &operator = (const String &s);

    // Description:
	// Calculates the hash value of the string.
	//
	// Used for efficiently finding items in a collection by key.
	//
	// Returns:
	// The hast value.
    UInt Hash() const;

    // Description:
	// Calculates the length of the string, i.e. the number of characters
	// in the string.
	//
	// Returns:
	// The string length.
    size_t Len() const { 
		return p->Len; 
	}

    // Description:
	// Provides access to individual characters of the string.
	// Please note, that the index must be valid, i.e. a number
	// between 0 and Len()-1.
	//
	// Arguments:
	// i - The index (number) of the character in the string.
	//     The first character has the index 0.
	//
	// Returns:
	// A reference of the character.
    const char &operator[] (size_t i) const { 
		return p->s[i]; 
	}

	// Description:
	// Returns a pointer to the zero-terminated character array
	// representing the string. 
	// Please note, that you may not modify the characters 
	// in the character array and that you are not the owner
	// of the string memory.
	//
	// Returns:
	// A pointer to the zero-terminated character array
	// representing the string.
    operator const char *() const { 
		return p->s; 
	}

	// Description:
	// Returns a sub string contained in the string with a specified
	// length and starting position.
	//
	// Arguments:
	// first - The index (number) of the sub string's first character
	//         in the string. The original string's first character 
	//         has the index 0.
	// Len   - The (maximum) length of the substring (optional). If
	//         this argument is ommited, the right part of the original
	//         string starting at the specified position is returned.
	//
	// Returns:
	// The specified sub string. If the position in the original string
	// is invalid, an empty string is returned.
    String SubStr(size_t first, size_t Len=SIZE_T_MAX) const;

	// Description:
	// Concatenates another string to this string.
	//
	// Arguments:
	// s - The string to be concatenated to this string.
	//
	// Returns:
	// The reference of the string.
    String &operator += (const String &s);

	// Description:
	// Converts the string to upper case.
    void ToUpper();

	// Description:
	// Creates a new string which is this string in upper case,
	// leaving this string intact.
	//
	// Returns:
	// The upper case string.
    String ToUpper() const;

	// Description:
	// Converts the string to lower case.
    void ToLower();

	// Description:
	// Creates a new string which is this string in lower case,
	// leaving this string intact.
	//
	// Returns:
	// The upper lower string.
    String ToLower() const;

    // friends (accessors)
    friend bool operator == (const String &s,  const char *pc)   { return strcmp(s.p->s, pc) == 0; }
    friend bool operator == (const String &s1, const String &s2) { return strcmp(s1.p->s, s2.p->s) == 0; }
    friend bool operator != (const String &s,  const char *pc)   { return strcmp(s.p->s, pc) != 0; }
    friend bool operator != (const String &s1, const String &s2) { return strcmp(s1.p->s, s2.p->s) != 0; }
    friend bool operator <  (const String &s1, const String &s2) { return strcmp(s1.p->s, s2.p->s) < 0; }
    friend bool operator <= (const String &s1, const String &s2) { return strcmp(s1.p->s, s2.p->s) <= 0; }
    friend bool operator >  (const String &s1, const String &s2) { return strcmp(s1.p->s, s2.p->s) > 0; }
    friend bool operator >= (const String &s1, const String &s2) { return strcmp(s1.p->s, s2.p->s) >= 0; }

protected:
	// {internal}
    // Description:
    // Creates an empty string stored in a memory buffer with the 
    // given size (string len without the terminating zero). If len
    // is zero, no buffer will be allocated; instead the string
    // created will use the empty string representation.
    String(size_t Len);

private:
	// Please note the sequence of the arguments, which is different
	// from a public constructor with swapped arguments. This is
	// necessary in order to have constructors with different
	// signatures.

	// {internal}
    // Description:
	// Clones the string, when needed -- that is, when more than one 
	// String object makes use of the internal string representation
	// (member StringRep *p) and the string is modified.
	//
	// This way, strings are only duplicated, when necessary, which 
	// is benefitial for performance, especially when strings are
	// return values of methods or functions.
    void CloneIfNeeded();

    // needed for string vector and value implementation
    void Construct() { this->String::String(); }
    void Construct(const String &s) { this->String::String(s); }
    void Construct(FILE *fp) { this->String::String(fp); }
    void Destruct() { this->String::~String(); }
    static void ConstructArray(String *pFirst, size_t Len);
    static void ConstructArray(String *pFirst, size_t Len, const String &initVal);
    static void ConstructArray(String *pFirst, size_t Len, FILE *fp);
    static void DestructArray(String *pFirst, size_t Len);
    static void CloneArray(String *pFirstDest, const String *pFirstSrc, size_t Len);
    static Bool SaveArrayToBinaryFile(String *pFirst, size_t Len, FILE *fp);
    friend class Vector;
    friend struct CVectorRep<String>;
    friend class Value;

	// {internal}
    // Description: 
    // Takes ownership of the given string representation
	String(StringRep *np);

protected:
    StringRep *p;
};

// {group:Data Classes}
// Description:
// Concatenates two strings.
//
// Arguments:
// s  - String object representing one of the strings to be
//      concatenated.
// s1 - String object representing one of the strings to be
//      concatenated.
// s2 - String object representing one of the strings to be
//      concatenated.
// pc - Pointer to a zero-terminated character array 
//      representing one of the strings to be concatenated.
//
// Returns:
// A String object representing the concatenated string.
inline String operator + (const String &s1, const String &s2) { 
	return String(s1, s2); 
}
inline String operator + (const char *pc, const String &s) { 
	return String(pc, s); 
}
inline String operator + (const String &s, const char *pc) { 
	return String(s, pc); 
}

} /* namespace DCI */

#endif /* DCI_STRING_H_INCLUDED */
