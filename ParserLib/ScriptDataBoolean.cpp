#include "stdafx.h"
#include "ParserLib.h"
#include "ScriptDataBoolean.h"

using namespace std;

CScriptDataBoolean::CScriptDataBoolean(BYTE *dataBuffer):CScriptDataValue(dataBuffer)
{
	m_booleanValue = false;

	m_dataType = 1;
}


CScriptDataBoolean::~CScriptDataBoolean()
{
}

int CScriptDataBoolean::Parse(UINT32 &scriptValueLength)
{
	m_booleanValue = m_dataBuffer[0];
	scriptValueLength++;
	return kFlvParserError_NoError;
}

void CScriptDataBoolean::Dump_script_data_value()
{
#if DUMP_SCRIPT_INFO_ENABLED_LOG
	g_logoutFile << '\t' << to_string(m_booleanValue);
#endif
}
