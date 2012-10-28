#pragma once
#include "stdafx.h"
void WriteLog(CString data)
{
  //EvfDataChanged - Live view image transfer complete notification.
  //PropertyChanged - Notifies that a camera property value has been changed
  data.Append("\n");
	FILE *stream;
	size_t  numwritten;
	if( fopen_s( &stream, "log.txt", "a+t" ) == 0 )
	{
	  // Write 25 characters to stream
    numwritten=fwrite(data.GetBuffer(), sizeof(char),data.GetLength(), stream );
	  fclose( stream );
	}
	else
	  MessageBox(NULL, "Problem opening the file","ERROR",MB_OK);
}