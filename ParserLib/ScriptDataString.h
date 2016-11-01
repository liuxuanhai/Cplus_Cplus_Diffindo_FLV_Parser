#pragma once
#include "ScriptDataValue.h"
class CScriptDataString :
	public CScriptDataValue
{
public:
	CScriptDataString(BYTE *dataBuffer);
	~CScriptDataString();

	int Parse(UINT32 &scriptValueLength);
	void Dump_script_data_value();

private:
	UINT16 m_stringLength;
	BYTE *m_stringBuffer;
};

