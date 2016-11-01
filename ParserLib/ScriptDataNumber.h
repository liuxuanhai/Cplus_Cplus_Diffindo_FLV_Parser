#pragma once
#include "ScriptDataValue.h"
class CScriptDataNumber :
	public CScriptDataValue
{
public:
	CScriptDataNumber(BYTE *dataBuffer);
	~CScriptDataNumber();

	int Parse(UINT32 &scriptValueLength);
	void Dump_script_data_value();

private:
	double m_scriptValueNumber;
};

