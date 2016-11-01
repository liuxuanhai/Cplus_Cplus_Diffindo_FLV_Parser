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
	int Transversing_properties(const char *property, double newVal);

private:
	UINT32 m_EMCAArrayLength;
	CScriptDataObject *m_ECMAVariables;
};

