#include "stdafx.h"
#include "ParserLib.h"
#include "ScriptDataStrictArray.h"
#include "ScriptDataNumber.h"

using namespace std;

CScriptDataStrictArray::CScriptDataStrictArray(BYTE *dataBuffer):CScriptDataValue(dataBuffer)
{
	m_StrictArrayLength = 0;
	m_StrictArrayValue = NULL;

	m_dataType = 10;
}


CScriptDataStrictArray::~CScriptDataStrictArray()
{
	if (m_StrictArrayValue)
	{
		for (int idx = 0; idx < m_StrictArrayLength; idx++)
		{
			delete m_StrictArrayValue[idx];
			m_StrictArrayValue[idx] = NULL;
		}

		delete[] m_StrictArrayValue;
		m_StrictArrayValue = NULL;
	}
}

int CScriptDataStrictArray::Parse(UINT32 &scriptValueLength)
{
	int err = 0;
	UINT32 currentDataLength = 0;
	read_len_swap(reinterpret_cast<BYTE *>(&m_StrictArrayLength), m_dataBuffer + currentDataLength, sizeof(UINT32));

	err = create_array_items(currentDataLength);
	if (err < 0)
	{
		return err;
	}
	scriptValueLength += currentDataLength;

	return kFlvParserError_NoError;
}

void CScriptDataStrictArray::Dump_script_data_value()
{
#if DUMP_SCRIPT_INFO_ENABLED_LOG
	for (int idx = 0; idx < m_StrictArrayLength; idx++)
	{
		m_StrictArrayValue[idx]->Dump_script_data_value();
	}
#endif
}

int CScriptDataStrictArray::create_array_items(UINT32 &scriptValueLength)
{
	UINT32 valueLength = sizeof(UINT32);
	UINT8 dataType = -1;

	m_StrictArrayValue = new CScriptDataValue*[m_StrictArrayLength];
	for (int idx = 0; idx < m_StrictArrayLength; idx++)
	{
		dataType = m_dataBuffer[valueLength++];
		switch (dataType)
		{
		case 0:
			m_StrictArrayValue[idx] = new CScriptDataNumber(m_dataBuffer + valueLength);
			m_StrictArrayValue[idx]->Parse(valueLength);
			break;
		default:
			return kFlvParserError_UnsupportedValueTypeInStrictArray;
		}
	}

	scriptValueLength += valueLength;
	return kFlvParserError_NoError;
}
