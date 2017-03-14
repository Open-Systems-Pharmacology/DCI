#ifndef DCI_PORT_H_INCLUDED
#define DCI_PORT_H_INCLUDED

#include "DCI/IPort.h"
#include "DCI/Object.h"
#include "DCI/Collection.h"

namespace DCI {

// Forward declarations

class Component;
template<PortType PT> class ComponentPorts;

// {internal}
// {group:Object Classes}
// Description: Port Default Implementation.
class Port : virtual public IPort, public Object {
DCI_IMPL_OBJECT_ONLY
private:
	Port() {}                   // forbidden
	Port(IPort *portToClone) {} // forbidden
	Port(PortType portType, Component *component, IPort *portToClone = 0);

public:
	virtual ~Port();

	// IUnknown
	virtual void             AddRef();
	virtual void             Release();

	// IObject
	virtual String           GetTypeName() const;
	virtual String           GetTypeDescription() const;

	// IPort
	virtual PortType         GetPortType() const;
	virtual ITableHandle     GetTable();
	virtual Bool		     SetTable(ITableHandle &table);
	virtual IComponentHandle GetComponent() const;

protected:
	PortType     m_PortType;
	Component   *m_Component;
	ITableHandle m_Table;

	// friendship
	friend class Component;
	friend class Collection<IPort, Port>;
	friend class ComponentPorts<PT_INPUT>;
	friend class ComponentPorts<PT_OUTPUT>;
	friend class ComponentPorts<PT_PARAMETER>;
};

} /* namespace DCI */

#include "DCI/Component.h"

#endif /* DCI_PORT_H_INCLUDED */
