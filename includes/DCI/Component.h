#ifndef DCI_COMPONENT_H_INCLUDED
#define DCI_COMPONENT_H_INCLUDED

#include "DCI/IComponent.h"
#include "DCI/Object.h"

namespace DCI {

// Forward declarations

class ComponentInputPorts;     // internal implementation class
class ComponentOutputPorts;    // internal implementation class
class ComponentParameterPorts; // internal implementation class

// {group:Object Classes}
// Description: Component Default Implementation.
class Component : public IComponent, public Object {
DCI_IMPL_OBJECT
private:
	Component(IComponent *componentToClone); // not implemented

public:
	DCI_DLLEXPORT Component();
	DCI_DLLEXPORT virtual ~Component();

	// IObject
	DCI_DLLEXPORT virtual String       GetTypeName() const;
	DCI_DLLEXPORT virtual String       GetTypeDescription() const;

	// IComponent
	DCI_DLLEXPORT virtual Bool         Initialize(const String &ComponentTypeName, const String &ComponentTypeDescription);
	DCI_DLLEXPORT virtual IPortsHandle GetInputPorts();
	DCI_DLLEXPORT virtual IPortsHandle GetOutputPorts();
	DCI_DLLEXPORT virtual IPortsHandle GetParameterPorts();
	DCI_DLLEXPORT virtual Bool         ProcessMetaData();
	DCI_DLLEXPORT virtual Bool         ProcessData();
	DCI_DLLEXPORT virtual Bool         ProcessDataRecord(IPortHandle &port);
	DCI_DLLEXPORT virtual Bool         CheckRunnable();
	DCI_DLLEXPORT virtual Bool         Configure();
	DCI_DLLEXPORT virtual String       Invoke(const String &fncName, const String &args);

	// internal implementation

	DCI_DLLEXPORT virtual void         Release(Int Count);

protected:
    ComponentInputPorts     *m_InputPorts;
	ComponentOutputPorts    *m_OutputPorts;
	ComponentParameterPorts *m_ParameterPorts;
	String                   m_TypeName;
	String                   m_TypeDescription;
	Bool                     m_Initialized;

	// friendship forever
	friend class ComponentInputPorts;     // internal implementation class
	friend class ComponentOutputPorts;    // internal implementation class
	friend class ComponentParameterPorts; // internal implementation class
};

} /* namespace DCI */

#endif /* DCI_COMPONENT_H_INCLUDED */
