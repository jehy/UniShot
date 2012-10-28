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


void Triggers::clear()
{
  for(int i=0;i<vec.size();i++)
    delete(vec[i]);
  vec.clear();
}
trigger* Triggers::GetAt(int p)
{
  if(p>=this->vec.size())
    MessageBox(NULL,"Trigger index out of borders","Error",MB_OK);
  return vec.at(p);
}
int Triggers::Count()
{
  return this->vec.size();
}


void Triggers::Add(trigger* tr)
{
  this->vec.push_back(tr);
}


trigger* Triggers::Find(char* name)
{
  for(int i=0;i<vec.size();i++)
    if(!strcmp(name,vec.at(i)->name))
      return vec.at(i);
  return NULL;
}

Triggers::Triggers(void)
{
}

Triggers::~Triggers(void)
{
  clear();
}