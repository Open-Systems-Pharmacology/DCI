#ifndef DCI_IPORT_H_INCLUDED
#define DCI_IPORT_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/ICollection.h"
#include "DCI/IObject.h"

namespace DCI {

// Forward declarations

interface ITable;
typedef PtrHandle<ITable>     ITableHandle;

interface IComponent;
typedef PtrHandle<IComponent> IComponentHandle;

// Description: Port Interface.
//
// Objects implementing this interface represent an input, output
// or paramter port of a component. A port may be associated with
// a table containing input, output or parameter data respectively.
interface IPort : virtual public IObject {
	// {group:Read-Only Properties}
	// Description:
	// Returns the type of the port.
	//
	// Returns:
	// The type of the port.
	virtual PortType GetPortType() const = 0;

	// {group:Read/Write Properties}
	// Description:
	// Returns the table associated with the port.
	//
	// Returns:
	// The handle of the table associated with the port.
	virtual ITableHandle GetTable() = 0;

	// {group:Read/Write Properties}
	// Description:
	// Sets the table associated with the port.
	//
	// Arguments:
	// - table: The handle table associated with the port 
	//          (may be unbound).
	//
	// Returns:
	// true if the assignment of the table succeeded, or false 
	// otherwise.
	virtual Bool SetTable(ITableHandle &table) = 0;

	// {group:Read-Only Properties}
	// Description:
	// Returns the component the port belongs to.
	//
	// Returns:
	// The handle of the port the component belongs to. This handle
	// is always bound.
	virtual IComponentHandle GetComponent() const = 0;
};

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Port Interface Handle.
typedef PtrHandle<IPort> IPortHandle;

// {group:Interfaces}
// {glyph:Interface|Interface}
// Description: Port Interface Collection Interface.
typedef ICollection<IPort> IPorts;

// {group:Handle Classes}
// {glyph:CPPClass|Class}
// Description: Port Interface Collection Interface Handle.
typedef PtrHandle<IPorts> IPortsHandle;

} /* namespace DCI */

#include "DCI/ITable.h"
#include "DCI/IComponent.h"

#endif /* DCI_IPORT_H_INCLUDED */
