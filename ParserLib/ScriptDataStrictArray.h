#pragma once
#include "ScriptDataValue.h"
class CScriptDataStrictArray :
	public CScriptDataValue
{
public:
	CScriptDataStrictArray(BYTE *dataBuffer);
	~CScriptDataStrictArray();

	int Parse(UINT32 &scriptValueLength);
	void Dump_script_data_value();

private:
	UINT32 m_StrictArrayLength;
	CScriptDataValue **m_StrictArrayValue;

	int create_array_items(UINT32 &scriptValueLength);
};

