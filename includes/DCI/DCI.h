#ifndef DCI_DCI_H_INCLUDED
#define DCI_DCI_H_INCLUDED

// DCI Version Information
//
// Note that there's versioning information in the DCI.rc file as well!

// {secret}
#define DCI_VERSION             0x0300
// {secret}
#define DCI_VERSION_STRING      "3.0"
// {secret}
#define DCI_VERSION_BINARY_FILE 0x0300

// Check compiler option settings

#ifdef _MSC_VER
  #ifndef _CPPRTTI
    #error Please use the "Enable Run-Time Type Information (RTTI)" compiler option
  #endif
  #ifndef _DLL
    #ifdef _DEBUG
      #error Please use the "Use run-time library: Debug Multithreaded DLL" compiler option
    #else
      #error Please use the "Use run-time library: Multithreaded DLL" compiler option
    #endif
  #endif
#else
  #error Unknown Compiler -- cannot check compiler option settings
#endif

// Standard includes

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <float.h>

// DCI definitions

#ifndef SIZE_T_MAX 
  // {secret}
  #define SIZE_T_MAX ((size_t)-1)
#endif

#ifndef interface
  // {secret}
  #define interface struct
#endif

#ifndef NULL
  // {secret}
  #define NULL (0)
#endif

#ifdef WIN32
  // {secret}
  #define DCI_DLLEXPORT __declspec(dllexport)
#else
  // {secret}
  #define DCI_DLLEXPORT
#endif

namespace DCI {

// {group:Primitive Data Types}
// Decription: Boolean Data Type.
typedef bool Bool;

// {group:Primitive Data Types}
// Decription: Byte Data Type (Signed).
typedef char Byte;

// {group:Primitive Data Types}
// Decription: Integer Data Type (Signed).
typedef int Int;

// {group:Primitive Data Types}
// Description: Unsigned Integer Data Type.
typedef unsigned int UInt;

// {group:Primitive Data Types}
// Description: Double Precision Floating Point Data Type.
typedef double Double;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Minimum Integer Value Allowed.
//const Int INT_MIN = 0x80000010;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Maximum Integer Value Allowed.
//const Int INT_MAX = 0x7ffffff0;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Not A Number (NAN) Integer Value.
const Int INT_NAN = 0x80000008;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Infinity (INF) Integer Value.
const Int INT_INF = 0x7ffffff2;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Negative Infinity (NEGINF) Integer Value.
const Int INT_NEGINF = 0x8000000e;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Minimum Byte Value Allowed.
const Byte BYTE_MIN = -0x7e;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Maximum Byte Value Allowed.
const Byte BYTE_MAX = 0x7e;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Not A Number (NAN) Byte Value.
const Byte BYTE_NAN = -0x80;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Infinity (INF) Byte Value.
const Byte BYTE_INF = 0x7f;

// {group:Constants}
// {glyph:Const|Constant}
// Description: Negative Infinity (NEGINF) Byte Value.
const Byte BYTE_NEGINF = -0x7f;

}

// {internal}
// Description: Use namespace for enumerations
#define DCI_ENUMS_USE_NAMESPACE

// DCI Includes

#include "DCI/Enums.h"
#include "DCI/String.h"
#include "DCI/Value.h"
#include "DCI/Vector.h"
#include "DCI/Handle.h"
#include "DCI/Unknown.h"

#endif /* DCI_DCI_H_INCLUDED */
