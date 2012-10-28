#include "StdAfx.h"
#include "trigger.h"

trigger::trigger(void)
{
  action=NULL;
  type=0;
  //name=NULL;
}

trigger::~trigger(void)
{
  if(action!=NULL)
    delete[] action;
  //if(name!=NULL)
  //  delete[] name;
}

int trigger::run(HANDLE SomeInfo)
{
  if(this->type==1)//php script from some server
  {
    char* url=(char*)SomeInfo;
    CString answer;
    HINTERNET hINet, hFile;
    hINet = InternetOpen("UniShot/2.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
    if ( !hINet )
    {
      AfxMessageBox("InternetOpen Failed");
      return 0;
    }
    hFile = InternetOpenUrl( hINet, url, NULL, 0, 0, 0 );
    if ( hFile )
    {
      CHAR buffer[1024];
      DWORD dwRead;
      while ( InternetReadFile( hFile, buffer, 1023, &dwRead ) )
      {
        if ( dwRead == 0 )
          break;
        buffer[dwRead] = 0;
        answer.Append(buffer);
      }
      InternetCloseHandle( hFile );
    }
    InternetCloseHandle( hINet );
    AfxMessageBox(answer);
  }
  return 1;
}