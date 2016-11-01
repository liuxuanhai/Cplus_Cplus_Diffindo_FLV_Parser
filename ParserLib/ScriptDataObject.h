#pragma once

class CScriptDataString;
class CScriptDataValue;
class CScriptDataObjectProperty
{
public:
	CScriptDataObjectProperty(BYTE *dataBuffer);
	~CScriptDataObjectProperty();

	CScriptDataObjectProperty* &Get_next_property_ptr();
	int Parse(UINT32 &scriptValueLength);
	void Dump_script_data_value();

private:
	BYTE *m_classDataBuffer;

	CScriptDataString *m_propertyName;
	CScriptDataValue *m_propertyData;

	CScriptDataObjectProperty *m_nextProperty;
};


class CScriptDataObject :
	public CScriptDataValue
{
public:
	CScriptDataObject(BYTE *dataBuffer, UINT32 numVariables);
	~CScriptDataObject();

	int Parse(UINT32 &scriptValueLength);
	void Dump_script_data_value();
	CScriptDataObjectProperty *Get_first_object_property();

private:
	BYTE *m_objectBuffer;
	UINT32 m_numVariables;

	CScriptDataObjectProperty *m_headerProperty;
	CScriptDataObjectProperty *m_tailProperty;
	int parse_object_properties(UINT32 &totalLength);
};

