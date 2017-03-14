#ifndef DCI_ENUMS_H_INCLUDED
#define DCI_ENUMS_H_INCLUDED

#ifdef __cplusplus
namespace DCI {
#endif

#ifndef DCI_HELPSTRING
// {secret}
#define DCI_HELPSTRING(HelpString)
#endif

// {group:Enumeration Types}
// Description: Error Numbers.
typedef DCI_HELPSTRING("Error number") enum ErrorNumber {
	EN_OK            = 0, // No error.
	EN_ERROR         = 1, // An error has occurred.
	EN_BADARG        = 2, // An illegal argument was used.
	EN_BADPATH       = 3, // A bad path was supplied.
	EN_NOTIMPL       = 4, // The function or method is not implemented.
	EN_BADVERSION    = 5, // An illegal library version is installed.
	EN_CANTLOADLIB   = 6, // The library could not be loaded.
	EN_CANTCREATEOBJ = 7  // The object could not be created.
}	ErrorNumber;

#if defined(__cplusplus) && !defined(DCI_ENUMS_USE_NAMESPACE)
// {secret}
#define ErrorNumber DCI::ErrorNumber
#endif

// {group:Enumeration Types}
// Description: Port Types.
typedef DCI_HELPSTRING("Type of a component's port") enum PortType {
	PT_INPUT     = 1, // Input port.
	PT_OUTPUT    = 2, // Output port.
	PT_PARAMETER = 3  // Parameter port.
}	PortType;

#if defined(__cplusplus) && !defined(DCI_ENUMS_USE_NAMESPACE)
// {secret}
#define PortType DCI::PortType
#endif

// {group:Enumeration Types}
// Description: Data Types.
typedef DCI_HELPSTRING("Data type of a scalar or vector value") enum DataType {
	DT_VOID        = 0, // Void (no value).
    DT_DOUBLE      = 1, // Double precision floating point.
    DT_INT         = 2, // Integer (signed).
    DT_STRING      = 3, // String.
    DT_DATETIME    = 4, // Date/Time.
    DT_ENUMERATION = 5, // Enumeration.
	DT_VALUE       = 6, // Any value that can be assigned to an object of class Value.
    DT_BYTE        = 7  // Byte (signed)
}	DataType;

#if defined(__cplusplus) && !defined(DCI_ENUMS_USE_NAMESPACE)
// {secret}
#define DataType DCI::DataType
#endif

#ifdef __cplusplus
} /* namespace DCI */
#endif

#endif /* DCI_ENUMS_H_INCLUDED */
