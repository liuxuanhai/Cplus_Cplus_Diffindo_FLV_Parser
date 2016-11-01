#include "stdafx.h"
#include "ParserLib.h"
#include "ScriptDataString.h"

using namespace std;

CScriptDataString::CScriptDataString(BYTE *dataBuffer):CScriptDataValue(dataBuffer)
{
	m_stringLength = 0;
	m_stringBuffer = NULL;

	m_dataType = 2;
}


CScriptDataString::~CScriptDataString()
{
	if (m_stringBuffer)
	{
		delete m_stringBuffer;
		m_stringBuffer = NULL;
	}
}

int CScriptDataString::Parse(UINT32 &scriptValueLength)
{
	read_len_swap(reinterpret_cast<BYTE *>(&m_stringLength), m_dataBuffer, sizeof(UINT16));

	m_stringBuffer = new BYTE[m_stringLength + 1];
	memcpy_s(m_stringBuffer, m_stringLength + 1, m_dataBuffer + sizeof(UINT16), m_stringLength);
	m_stringBuffer[m_stringLength] = 0;

	scriptValueLength += m_stringLength + sizeof(UINT16);

	return kFlvParserError_NoError;
}

void CScriptDataString::Dump_script_data_value()
{
#if DUMP_SCRIPT_INFO_ENABLED_LOG
	g_logoutFile << m_stringBuffer;
#endif

#if DUMP_SCRIPT_INFO_ENABLED_CONSOLE
	cout << m_stringBuffer << endl;
#endif
}
