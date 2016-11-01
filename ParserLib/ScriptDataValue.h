#ifndef _SCRIPT_DATA_VALUE_H_
#define _SCRIPT_DATA_VALUE_H_

class CScriptDataValue
{
public:
	CScriptDataValue(BYTE *dataBuffer);
	virtual ~CScriptDataValue();

	virtual int Parse(UINT32 &scriptValueLength) = 0;
	virtual void Dump_script_data_value() = 0;

protected:
	BYTE *m_dataBuffer;
	UINT8  m_dataType;
};

#endif

