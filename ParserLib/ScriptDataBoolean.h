#pragma once
#include "ScriptDataValue.h"
class CScriptDataBoolean :
	public CScriptDataValue
{
public:
	CScriptDataBoolean(BYTE *dataBuffer);
	~CScriptDataBoolean();

	int Parse(UINT32 &scriptValueLength);
	void Dump_script_data_value();

private:
	UINT8 m_booleanValue;
};

