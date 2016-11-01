#pragma once
#include "ScriptDataValue.h"

class CScriptDataObject;
class CScriptDataECMAArray :
	public CScriptDataValue
{
public:
	CScriptDataECMAArray(BYTE *dataBuffer);
	~CScriptDataECMAArray();

	int Parse(UINT32 &scriptValueLength);
	void Dump_script_data_value();

private:
	UINT32 m_EMCAArrayLength;
	CScriptDataObject *m_ECMAVariables;
};

