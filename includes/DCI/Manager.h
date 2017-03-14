#ifndef DCI_MANAGER_H_INCLUDED
#define DCI_MANAGER_H_INCLUDED

#include "DCI/DCI.h"
#include "DCI/Component.h"
#include "DCI/Table.h"
#include "DCI/Utilities.h"

extern "C" {

// Function Prototypes for External DLL Functions

// {internal}
typedef int (GetVersionFunction)();
// {internal}
typedef GetVersionFunction *GetVersionFunctionPtr;
// {internal}
typedef DCI::IComponent *(CreateComponentFunction)(const char *ComponentTypeName);
// {internal}
typedef CreateComponentFunction *CreateComponentFunctionPtr;

} /* extern "C" */

// Description: DCI Namespace.
namespace DCI {

// Declarations for "DCI..." functions exported by external DLLs

// {internal}
// Description:
// Name of function to check version. Any DLL implementing a component must export such a function.
#define DCI_GETVERSION_FUNCTION_NAME      "DCIGetVersion"
// {internal}
// Description:
// Name of function to create a component. Any DLL implementing a component must export such a function.
#define DCI_CREATECOMPONENT_FUNCTION_NAME "DCICreateComponent"

// {group:Global Modules}
// Description: Manager Module.
//
// The manager provides factory and persistence functionality.
class Manager {
public:
	// Description:
	// Returns the DCI version number.
	// 
	// Returns:
	// the DCI version number.
	DCI_DLLEXPORT static String           GetVersion();

	// Description:
	// Returns the list of XML files contained in a directory with
	// configuration XML files.
	//
	// Arguments:
	// ConfigDirectory - The directory containing the configuration
	//                   files (optional). If omitted, a default
	//                   directory is used.
	//
	// Returns:
	// The list of XML files contained in a directory with
	// configuration XML files.
	DCI_DLLEXPORT static StringVector     GetXMLFileNames(Bool &ok, const String &ConfigDirectory="");

	// Description:
	// Returns the component type names from the specified list of XML files.
	//
	// Arguments:
	// XMLFileNames - The list of XML files.
	//
	// Returns:
	// The component type names from the specified list of XML files.
	DCI_DLLEXPORT static StringVector     GetComponentTypeNamesFromXMLFiles(const StringVector &XMLFileNames);

	// Description:
	// Returns the component type descriptions from the specified list of XML files.
	//
	// Arguments:
	// XMLFileNames - The list of XML files.
	//
	// Returns:
	// The component type descriptions from the specified list of XML files.
	DCI_DLLEXPORT static StringVector     GetComponentTypeDescriptionsFromXMLFiles(const StringVector &XMLFileNames);

	// Description:
	// Returns the component names from the specified list of XML files.
	//
	// Arguments:
	// XMLFileNames - The list of XML files.
	//
	// Returns:
	// The component names from the specified list of XML files.
	DCI_DLLEXPORT static StringVector     GetComponentNamesFromXMLFiles(const StringVector & XMLFileNames);

	// Description:
	// Returns the component descriptions from the specified list of XML files.
	//
	// Arguments:
	// XMLFileNames - The list of XML files.
	//
	// Returns:
	// The component descriptions from the specified list of XML files.
	DCI_DLLEXPORT static StringVector     GetComponentDescriptionsFromXMLFiles(const StringVector &XMLFileNames);

	// Description:
	// Creates a new component.
	//
	// The component created is *not* initialized from the XML data contained
	// in the default configuration file. In order to create a component
	// initialized by the default configuration, use LoadComponentFromXMLFile
	// with an empty string as the FileName argument.
	//
	// Arguments:
	// ComponentTypeName        - The type name of the component.
	// ComponentTypeDescription - The type description of the component.
	//
	// Returns:
	// The component created.
	//
	// See Also:
	// LoadComponentFromXMLFile, LoadComponentFromXMLString.
	DCI_DLLEXPORT static IComponentHandle CreateComponent(const String &ComponentTypeName, const String &ComponentTypeDescription);

	// Description:
	// Loads a component from an XML string.
	//
	// The component is created first using CreateComponent and then
	// initialized using the data contained in the specified XML string.
	// In order to create a component initialized by the default 
	// configuration, use LoadComponentFromXMLFile with an empty string 
	// as the FileName argument; if you want to create an uninitialized
	// component, use CreateComponent.
	//
	// Arguments:
	// XMLString - The XML data describing the component. Such a
	//             string could have been created by 
	//             SaveComponentToXMLString.
	//
	// Returns:
	// The component created.
	//
	// See Also:
	// CreateComponent, LoadComponentFromXMLFile, SaveComponentToXMLString.
	DCI_DLLEXPORT static IComponentHandle LoadComponentFromXMLString(const String &XMLString);

	// Description:
	// Loads a component from an XML file.
	//
	// The component is created first using CreateComponent and then
	// initialized using the data contained in the specified XML file.
	// In order to create a component initialized by the default 
	// configuration, use LoadComponentFromXMLFile with an empty string 
	// as the FileName argument; if you want to create an uninitialized
	// component, use CreateComponent.
	//
	// Arguments:
	// FileName - The XML file containing the data describing the 
	//            component. Such a file could have been created by 
	//            SaveComponentToXMLFile.
	//
	// Returns:
	// The component created.
	//
	// See Also:
	// CreateComponent, LoadComponentFromXMLString, SaveComponentToXMLFile.
	DCI_DLLEXPORT static IComponentHandle LoadComponentFromXMLFile(const String &FileName);

	// Description:
	// Saves a component to an XML string.
	//
	// This string may later be used when creating a component using
	// LoadComponentFromXMLString.
	//
	// Arguments:
	// Component - The component to be saved to the XML string.
	//
	// Returns:
	// The XML string describing the component.
	//
	// See Also:
	// LoadComponentFromXMLString.
	DCI_DLLEXPORT static String           SaveComponentToXMLString(IComponentHandle &hComponent);

	// Description:
	// Saves a component to an XML file.
	//
	// This file may later be used when creating a component using
	// LoadComponentFromXMLFile.
	//
	// Arguments:
	// Component - The component to be saved to the XML file.
	// FileName  - The XML file to which the data describing the 
	//             component is saved.
	//
	// See Also:
	// LoadComponentFromXMLFile.
	DCI_DLLEXPORT static Bool             SaveComponentToXMLFile(IComponentHandle &hComponent, const String &FileName);



	// Description:
	// Creates a new table.
	//
	// The table created is *not* initialized from the XML data contained
	// in the default configuration file. In order to create a table
	// initialized by the default configuration, use LoadTableFromXMLFile
	// with an empty string as the FileName argument.
	//
	// Returns:
	// The table created.
	//
	// See Also:
	// LoadTableFromXMLFile, LoadTableFromXMLString.
	DCI_DLLEXPORT static ITableHandle     CreateTable();

	// Description:
	// Loads a table from an XML string.
	//
	// The table is created first using CreateTable and then
	// initialized using the data contained in the specified XML string.
	// In order to create a table initialized by the default 
	// configuration, use LoadTableFromXMLFile with an empty string 
	// as the FileName argument; if you want to create an uninitialized
	// table, use CreateTable.
	//
	// Arguments:
	// XMLString - The XML data describing the table. Such a
	//             string could have been created by 
	//             SaveTableToXMLString.
	//
	// Returns:
	// The table created.
	//
	// See Also:
	// CreateTable, LoadTableFromXMLFile, SaveTableToXMLString.
	DCI_DLLEXPORT static ITableHandle     LoadTableFromXMLString(const String &XMLString);

	// Description:
	// Loads a table from an XML file.
	//
	// The table is created first using CreateTable and then
	// initialized using the data contained in the specified XML file.
	// In order to create a table initialized by the default 
	// configuration, use LoadTableFromXMLFile with an empty string 
	// as the FileName argument; if you want to create an uninitialized
	// table, use CreateTable.
	//
	// Arguments:
	// FileName - The XML file containing the data describing the 
	//            table. Such a file could have been created by 
	//            SaveTableToXMLFile.
	//
	// Returns:
	// The table created.
	//
	// See Also:
	// TableTypeNames, CreateTable, LoadTableFromXMLString,
	// SaveTableToXMLFile.
	DCI_DLLEXPORT static ITableHandle     LoadTableFromXMLFile(const String &FileName);

	// Description:
	// Saves a table to an XML string.
	//
	// This string may later be used when creating a table using
	// LoadTableFromXMLString.
	//
	// Arguments:
	// Table - The table to be saved to the XML string.
	//
	// Returns:
	// The XML string describing the table.
	//
	// See Also:
	// LoadTableFromXMLString.
	DCI_DLLEXPORT static String           SaveTableToXMLString(ITableHandle &hTable);

	// Description:
	// Saves a table to an XML file.
	//
	// Arguments:
	// Table     - The table to be saved to the XML file.
	// FileName  - The XML file to which the data describing the 
	//             table is saved.
	//
	// See Also:
	// LoadTableFromXMLFile.
	DCI_DLLEXPORT static Bool             SaveTableToXMLFile(ITableHandle &hTable, const String &FileName);

	// Description:
	// Loads a table from a binary file.
	//
	// The table is created first using CreateTable and then
	// initialized using the data contained in the specified XML file.
	// In order to create a table initialized by the default 
	// configuration, use LoadTableFromXMLFile with an empty string 
	// as the FileName argument; if you want to create an uninitialized
	// table, use CreateTable.
	//
	// Arguments:
	// FileName - The binary file containing the data describing the 
	//            table. Such a file must have been created by 
	//            SaveTableToBinaryFile.
	//
	// Returns:
	// The table loaded.
	//
	// See Also:
	// SaveTableToBinaryFile.
	DCI_DLLEXPORT static ITableHandle     LoadTableFromBinaryFile(const String &FileName);

	// Description:
	// Saves a table to a binary file.
	//
	// Arguments:
	// Table     - The table to be saved to the binary file.
	// FileName  - The binary file to which the data describing the 
	//             table is saved.
	//
	// See Also:
	// LoadTableFromBinaryFile.
	DCI_DLLEXPORT static Bool             SaveTableToBinaryFile(ITableHandle &hTable, const String &FileName);

};

} /* namespace DCI */

#include "DCI/IComponent.h"
#include "DCI/ITable.h"

#endif /* DCI_MANAGER_H_INCLUDED */
