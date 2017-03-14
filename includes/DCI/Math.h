#ifndef DCI_MATH_H_INCLUDED
#define DCI_MATH_H_INCLUDED

#include "DCI/DCI.h"

namespace DCI {

// {group:Global Modules}
// Description: Math Module.
//
// The math module provides math helper routines.
class Math {
public:
	// Description:
	// Returns the double value representing NaN (not a number).
	DCI_DLLEXPORT static Double GetNaN();

	// Description:
	// Tests if a double value is NaN (not a number).
	//
	// Arguments:
	// DoubleValue - The double value to be tested for NaN (not a number).
	//
	// Returns:
	// True  - The double value represent the special NaN (not a number)
	//         value.
	// False - The double value does not represent the special NaN (not 
	//         a number) value.
	DCI_DLLEXPORT static Bool   IsNaN(Double d);

	// Description:
	// Returns the double value representing Inf (infinity).
	DCI_DLLEXPORT static Double GetInf();

	// Description:
	// Returns the double value representing -Inf (negative infinity).
	DCI_DLLEXPORT static Double GetNegInf();

	// Description:
	// Tests if a double value is finite.
	//
	// Arguments:
	// DoubleValue - The double value to be tested for being finite.
	//
	// Returns:
	// True  - The double value is not infinite: -Inf < DoubleValue < Inf.
	// False - The double value is infinite or NaN (not a number).
	DCI_DLLEXPORT static Bool   IsFinite(Double d);
};

} /* namespace DCI */

#endif /* DCI_MATH_H_INCLUDED */
