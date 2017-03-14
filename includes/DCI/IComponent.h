#ifndef DCI_ICOMPONENT_H_INCLUDED
#define DCI_ICOMPONENT_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/IObject.h"

namespace DCI {

// Forward declarations

interface IPort;
typedef PtrHandle<IPort>   IPortHandle;
typedef ICollection<IPort> IPorts;
typedef PtrHandle<IPorts>  IPortsHandle;

interface ITable;
typedef PtrHandle<ITable>  ITableHandle;

// Description: Component Interface.
//
// Objects implementing this interface represent a user-supplied
// component capable of performing data mining or data preprocessing
// calculations. 
//
// A component consists of a collection of input ports containing 
// dynamic input data, a collection of parameter containg the 
// component's configuration and a collection of output ports
// containing the calculated results. 
//
// The data contained in the ports is organized in tables (see
// the ITable interface). Tables in input and output ports should
// be record-based (i.e. the data is a two-dimensional matrix).
// Tables in parameters ports may be non-record-based, which 
// allows for a more flexible structure of the table.
//
// The calculations provided by a component of a certain type are
// split into two parts: the processing of the meta data, which
// only defines the structure (meta data) of the output tables for 
// given input and parameter table structures (meta data), and the
// processing of the data itself.
interface IComponent : virtual public IObject {
	// Description:
	// This method is called after the component has been created
	// or loaded from an XML file/string.
	//
	// Arguments:
	// ComponentTypeName        - The type name of the component.
	// ComponentTypeDescription - The type description of the component.
	//
	// Returns:
	// True, if the initalization is successful, false otherwise.
	virtual Bool Initialize(const String &ComponentTypeName, const String &ComponentTypeDescription) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the collection of input ports of the component.
	//
	// Returns:
	// The handle of the collection of input ports of the component.
	virtual IPortsHandle GetInputPorts() = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the collection of output ports of the component.
	//
	// Returns:
	// The handle of the collection of output ports of the component.
	virtual IPortsHandle GetOutputPorts() = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the collection of parameter ports of the component.
	//
	// Returns:
	// The handle of the collection of parameter ports of the component.
	virtual IPortsHandle GetParameterPorts() = 0;

	// Description:
	// Processes the component-specific meta data, i.e. it creates
	// the meta data of the output tables from the meta data of the
	// input and parameter tables.
	//
	// Returns:
	// true if processing the meta data succeeds, or false otherwise.
	// In order to get extended error information, please make use of 
	// the Error module.
	virtual Bool ProcessMetaData() = 0;

	// Description:
	// Processes the component-specific data, i.e. it calculates the
	// data contained in the output tables from data contained in the
	// input and paramter tables. Please note, that the meta data of 
	// the output tables created must match the meta data, which would
	// be the result of ProcessMetaData().
	//
	// Returns:
	// true if processing the data succeeds, or false otherwise.
	// In order to get extended error information, please make use of 
	// the Error module.
	virtual Bool ProcessData() = 0;

	// Description:
	// Processes the component-specific data for new records of a
	// specified port, i.e. it calculates the new data (records) 
	// contained in the output tables. Please note, that the meta data of 
	// the output tables created must still match the meta data, which would
	// be the result of ProcessMetaData().
	//
	// Arguments:
	// inputPort - Handle of the input port with additional record data.
	//
	// Returns:
	// true if processing the record data succeeds, or false otherwise.
	// In order to get extended error information, please make use of 
	// the Error module.
	virtual Bool ProcessDataRecord(IPortHandle &inputPort) = 0;

	// Description:
	// Checks, if the component can be run in its current state. If the
	// component is runnable, the client may call ProcessData().
	//
	// Returns:
	// true, if the component is ready to be run, or false otherwise.
	virtual Bool CheckRunnable() = 0;

	// Description:
	// Opens the component's configuration dialog which enables the
	// user to set its parametrization.
	//
	// Returns:
	// true, if the configuration succeeds, or false otherwise.
	// In order to get extended error information, please make use of 
	// the Error module.
	virtual Bool Configure() = 0;

	// Description:
	// Invokes a component-specific user-defined function on the
	// component.
	//
	// Arguments:
	// fncName - Name of the user-defined function to be invoked.
	// args    - String containing the arguments for the user-defined
	//           function.
	//
	// Returns:
	// A string containing the result of the user-defined function.
	// In order to get error information, please make use of the Error module.
	virtual String Invoke(const String &fncName, const String &args) = 0;
};

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Component Interface Handle.
typedef PtrHandle<IComponent> IComponentHandle;

} /* namespace DCI */

#include "DCI/IPort.h"
#include "DCI/ITable.h"

#endif /* DCI_ICOMPONENT_H_INCLUDED */
