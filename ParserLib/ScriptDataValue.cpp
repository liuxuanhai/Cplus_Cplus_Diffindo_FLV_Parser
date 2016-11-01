#include "stdafx.h"
#include "ScriptDataValue.h"


CScriptDataValue::CScriptDataValue(BYTE *dataBuffer)
{
	m_dataBuffer = dataBuffer;
	m_dataType = m_dataBuffer[-1];
}


CScriptDataValue::~CScriptDataValue()
{
}
