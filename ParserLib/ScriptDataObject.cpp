#include "stdafx.h"
#include "ParserLib.h"
#include "ScriptDataValue.h"
#include "ScriptDataObject.h"
#include "ScriptDataString.h"
#include "ScriptDataBoolean.h"
#include "ScriptDataNumber.h"
#include "ScriptDataStrictArray.h"

using namespace std;
CScriptDataObjectProperty::CScriptDataObjectProperty(BYTE *dataBuffer)
{
	m_classDataBuffer = dataBuffer;
	m_propertyName = NULL;
	m_propertyData = NULL;
	m_nextProperty = NULL;
}

CScriptDataObjectProperty::~CScriptDataObjectProperty()
{
	if (m_propertyName)
	{
		delete m_propertyName;
		m_propertyName = NULL;
	}
	if (m_propertyData)
	{
		delete m_propertyData;
		m_propertyData = NULL;
	}
}

CScriptDataObjectProperty* &CScriptDataObjectProperty::Get_next_property_ptr()
{
	return m_nextProperty;
}

char * CScriptDataObjectProperty::Get_property_name()
{
	return m_propertyName->Get_string_buffer();
}

int CScriptDataObjectProperty::Set_property_value(double newValue)
{
	CScriptDataNumber *newValueData = dynamic_cast<CScriptDataNumber *>(m_propertyData);
	if (NULL != newValueData)
	{
		return kFlvParserError_RunTimeError;
	}

	newValueData->Set_new_value(newValue);

	return kFlvParserError_NoError;
}

int CScriptDataObjectProperty::Parse(UINT32 &scriptValueLength)
{
	UINT32 valueLength = 0;

	m_propertyName = new CScriptDataString(m_classDataBuffer);
	m_propertyName->Parse(valueLength);

	UINT8 dataType = m_classDataBuffer[valueLength++];
	switch (dataType)
	{
	case 0:
		m_propertyData = new CScriptDataNumber(m_classDataBuffer + valueLength);
		break;
	case 1:
		m_propertyData = new CScriptDataBoolean(m_classDataBuffer + valueLength);
		break;
	case 2:
		m_propertyData = new CScriptDataString(m_classDataBuffer + valueLength);
		break;
	case 3:
		m_propertyData = new CScriptDataObject(m_classDataBuffer + valueLength, 512);
		break;
	case 10:
		m_propertyData = new CScriptDataStrictArray(m_classDataBuffer + valueLength);
		break;
	default:
		std::cout << "data type: " << std::to_string(dataType) << " detected." << std::endl;
		return kFlvParserError_IllegalScriptValueType;
	}

	m_propertyData->Parse(valueLength);
	scriptValueLength += valueLength;

	return kFlvParserError_NoError;
}

void CScriptDataObjectProperty::Dump_script_data_value()
{
#if DUMP_SCRIPT_INFO_ENABLED_LOG
	m_propertyName->Dump_script_data_value();
	g_logoutFile << ": ";
	m_propertyData->Dump_script_data_value();
	g_logoutFile << endl;
#endif
}

CScriptDataObject::CScriptDataObject(BYTE *dataBuffer, UINT32 numVariables) :CScriptDataValue(dataBuffer)
{
	m_objectBuffer = dataBuffer;
	m_numVariables = numVariables;
	m_headerProperty = NULL;
	m_tailProperty = NULL;

	m_dataType = 3;
}


CScriptDataObject::~CScriptDataObject()
{
	// free m_headerProperty linklist
	CScriptDataObjectProperty *headerProperty = m_headerProperty, *nextProperty = headerProperty->Get_next_property_ptr();
	while (!nextProperty)
	{
		delete headerProperty;
		headerProperty = nextProperty;
		nextProperty = nextProperty->Get_next_property_ptr();
	}
	delete headerProperty;
}

int CScriptDataObject::Parse(UINT32 &scriptValueLength)
{
	int err = 0;
	UINT32 dataObjectLength = 0;

	err = parse_object_properties(dataObjectLength);	
	if (err < 0)
	{
		return err;
	}
	scriptValueLength += dataObjectLength;

	return kFlvParserError_NoError;
}

void CScriptDataObject::Dump_script_data_value()
{
	CScriptDataObjectProperty *headerProperty = m_headerProperty;
	while (headerProperty)
	{
		headerProperty->Dump_script_data_value();
		headerProperty = headerProperty->Get_next_property_ptr();
	}
}

CScriptDataObjectProperty * CScriptDataObject::Get_first_object_property()
{
	return m_headerProperty;
}

int CScriptDataObject::parse_object_properties(UINT32 &totalLength)
{
	int err = 0;
	UINT32 propertyLength = 0;

	for (int idx = 0; idx < m_numVariables; idx++)
	{
		if ((m_objectBuffer[propertyLength] == 0) && (m_objectBuffer[propertyLength + 1] == 0) && (m_objectBuffer[propertyLength + 2] == 9))
		{
			break;;
		}

		CScriptDataObjectProperty *tempProperty = NULL;
		tempProperty = new CScriptDataObjectProperty(m_objectBuffer + propertyLength);
		err = tempProperty->Parse(propertyLength);
		if (err < 0)
		{
			return err;
		}

		if (!m_headerProperty)
		{
			m_headerProperty = tempProperty;
			m_tailProperty = m_headerProperty;
		} 
		else
		{
			m_tailProperty  = m_tailProperty->Get_next_property_ptr() = tempProperty;
		}
	}
	
	return kFlvParserError_NoError;
}
