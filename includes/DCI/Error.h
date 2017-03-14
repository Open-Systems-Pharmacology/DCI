#ifndef DCI_ERROR_H_INCLUDED
#define DCI_ERROR_H_INCLUDED

#ifdef WIN32
#include <Windows.h>
#endif

#include "DCI/DCI.h"

namespace DCI {

// {group:Global Modules}
// Description: Error Module.
//
// The error module provides error handling routines.
class Error {
public:
    // {internal}
    // Description:
    // Prints a warning text to standard out
    //
    // Arguments:
    // ErrorMsg - The warning text
    static void LogWarning(const String &ErrorMsg);

	// Description:
	// Resets the error information.
	//
    // The error source and description are set to empty strings, the error number is set to EN_OK.
	DCI_DLLEXPORT static void Clear();

	// Description:
	// Sets the error information.
	//
	// Arguments:
	// SourceObject - The object in which the error occured.
	// Number       - The error number.
	// Description  - A text describing the error (optional).
	DCI_DLLEXPORT static void SetError(const IUnknownHandle &SourceObject, ErrorNumber Number, const String &Description=String());

	// Description:
	// Returns the error source information.
	//
	// Returns:
	// the error source information.
	DCI_DLLEXPORT static String GetSource();

	// Description:
	// Returns the error number.
	//
	// Returns:
	// the error number.
	DCI_DLLEXPORT static ErrorNumber GetNumber();

	// Description:
	// Returns the error description.
	//
	// Returns:
	// the error description.
	DCI_DLLEXPORT static String GetDescription();

	// Description:
	// Opens a logfile with the specified name.
	//
	// Arguments:
	// Filename	- The name of the logfile.
	//
	// Returns:
	// true if the logfile is open, false otherwise.
	DCI_DLLEXPORT static Bool SetLogFile(const String &FileName);

#ifdef WIN32
	// {internal}
	// Description:
	// Gets the error description text resulting fom a COM.
	// error code (HRESULT).
	// 
	// Arguments:
	// hr - The result from a COM.
	//
	// Returns:
	// The error description text.
	DCI_DLLEXPORT static String GetCOMErrorText(HRESULT hr);
#endif
};

} /* namespace DCI */

#endif /* DCI_ERROR_H_INCLUDED */
