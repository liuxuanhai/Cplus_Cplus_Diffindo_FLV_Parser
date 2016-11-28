// ConsoleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ParserLib.h"
#include <iostream>
using namespace std;

UINT32 g_lastVideoTimeStamp = 0, g_lastAudioTimeStamp = 0;

bool edit_tag(CFlvTag *tag)
{
	return true;
}

int main(int argc, char **argv)
{
	int err = 0;
	CFlvParser parser(argv[1]);
	err = parser.Parse();
	if (err < 0)
	{
		cout << argv[1] <<" : " << errorHints[-err] << endl;
		return -1;
	}
//	parser.Set_script_value("framerate", 25.21);

	return 0;

// 	CFlvParser parser2(argv[2]);
// 	err = parser2.Parse();
// 	if (err < 0)
// 	{
// 		cout << argv[1] << " : " << errorHints[-err] << endl;
// 		return -1;
// 	}

	CFlvWriter writer(argv[2], &parser);
	if (writer.Init(true, true))
	{
		cout << argv[2] << " : " << errorHints[-err] << endl;
		return -1;
	}

//	writer.Append_flv_file_with_frame_sample_rate(23.985, 22.05, &parser2);
	writer.Clone_FLV_with_video();
//	writer.Create_FLV_with_edited_tag(edit_tag);
//	writer.Extract_tags_with_range(0, 50);
	
    return 0;
}

