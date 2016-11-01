#include "stdafx.h"
#include "ParserLib.h"
#include "ScriptDataNumber.h"

using namespace std;
CScriptDataNumber::CScriptDataNumber(BYTE *dataBuffer):CScriptDataValue(dataBuffer)
{
	m_scriptValueNumber = 0;
}


CScriptDataNumber::~CScriptDataNumber()
{
}

int CScriptDataNumber::Parse(UINT32 &scriptValueLength)
{
	read_len_swap(reinterpret_cast<BYTE *>(&m_scriptValueNumber), m_dataBuffer, sizeof(double));
	scriptValueLength += sizeof(double);

	return kFlvParserError_NoError;
}

void CScriptDataNumber::Dump_script_data_value()
{
#if DUMP_SCRIPT_INFO_ENABLED_LOG
	g_logoutFile << '\t' << to_string(m_scriptValueNumber);
#endif
}
