#include "stdafx.h"
#include "ParserLib.h"
#include "ScriptDataECMAArray.h"
#include "ScriptDataObject.h"

using namespace std;

CScriptDataECMAArray::CScriptDataECMAArray(BYTE *dataBuffer):CScriptDataValue(dataBuffer)
{
	m_EMCAArrayLength = 0;
	m_ECMAVariables = NULL;

	m_dataType = 8;
}


CScriptDataECMAArray::~CScriptDataECMAArray()
{
	if (m_ECMAVariables)
	{
		delete m_ECMAVariables;
		m_ECMAVariables = NULL;
	}
}

int CScriptDataECMAArray::Parse(UINT32 &scriptValueLength)
{
	UINT32 currentDataLength = 0;
	read_len_swap(reinterpret_cast<BYTE *>(&m_EMCAArrayLength), m_dataBuffer + currentDataLength, sizeof(UINT32));
	currentDataLength += sizeof(UINT32);

	m_ECMAVariables = new CScriptDataObject(m_dataBuffer + currentDataLength, m_EMCAArrayLength);
	m_ECMAVariables->Parse(currentDataLength);

	return kFlvParserError_NoError;
}

void CScriptDataECMAArray::Dump_script_data_value()
{
#if DUMP_SCRIPT_INFO_ENABLED_LOG
	CScriptDataObjectProperty *firstProperty = m_ECMAVariables->Get_first_object_property();

	while (firstProperty)
	{
		firstProperty->Dump_script_data_value();
		firstProperty = firstProperty->Get_next_property_ptr();
	}
	
#endif
}

int CScriptDataECMAArray::Transversing_properties(const char *property, double newVal)
{
	CScriptDataObjectProperty *target = m_ECMAVariables->Get_first_object_property();
	while (strcmp(target->Get_property_name(), property))
	{
		target = target->Get_next_property_ptr();
	}

	if (!target)
	{
		return kFlvParserError_PropertyNotFound;
	}

	target->Set_property_value(newVal);

	return kFlvParserError_NoError;
}
