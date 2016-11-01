#include "stdafx.h"
#include "ParserLib.h"
#include "ScriptDataString.h"
#include "ScriptDataECMAArray.h"

using namespace std;

ScriptTag::ScriptTag(BYTE *dataBuf, UINT32 dataSize)
{
	m_dataBuffer = dataBuf;
	m_dataSize = dataSize;

	m_ScriptTagName = NULL;
	m_ScriptTagValue = NULL;
}

ScriptTag::~ScriptTag()
{
	if (m_ScriptTagName)
	{
		delete m_ScriptTagName;
		m_ScriptTagName = NULL;
	}

	if (m_ScriptTagValue)
	{
		delete m_ScriptTagValue;
		m_ScriptTagValue = NULL;
	}
}


int ScriptTag::Parse()
{
	int err = 0;
	UINT32 byteOffset = 0;

	assert(m_dataBuffer[byteOffset] == 2);
	m_ScriptTagName = new CScriptDataString(m_dataBuffer + (++byteOffset));
	m_ScriptTagName->Parse(byteOffset);

	assert(m_dataBuffer[byteOffset] == 8);
	m_ScriptTagValue = new CScriptDataECMAArray(m_dataBuffer + (++byteOffset));
	m_ScriptTagValue->Parse(byteOffset);

	return kFlvParserError_NoError;
}

void ScriptTag::Dump_script_tag_info()
{
#if DUMP_SCRIPT_INFO_ENABLED_LOG
	m_ScriptTagName->Dump_script_data_value();
//	g_logoutFile << endl;
	m_ScriptTagValue->Dump_script_data_value();
#endif
}


int ScriptTag::Set_script_property_value(const char *property, double newVal)
{
	int stringLength = strlen(property);
	BYTE* memCache = m_dataBuffer;
	double valCache = 0;
	read_len_swap(reinterpret_cast<BYTE *>(&valCache), reinterpret_cast<BYTE *>(&newVal), sizeof(double));

	while (memcmp(memCache, property, stringLength))
	{
		memCache++;
	}

	memcpy_s(memCache + stringLength + 1, sizeof(double), &valCache, sizeof(double));

	return kFlvParserError_NoError;
}

ScriptTag * CFlvTag::Get_script_tag()
{
	return m_scriptTag;
}
