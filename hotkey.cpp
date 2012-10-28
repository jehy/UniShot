#include "StdAfx.h"
#include "hotkey.h"

hotkey::hotkey(void)
{
  this->KeyCode=0;
  this->action=NULL;
}

hotkey::~hotkey(void)
{
  if(action!=NULL)
    delete[] action;
}

void Hotkeys::clear()
{
  for(int i=0;i<vec.size();i++)
    delete(vec[i]);
  vec.clear();
}
hotkey* Hotkeys::GetAt(int p)
{
  if(p>=this->vec.size())
    MessageBox(NULL,"Trigger index out of borders","Error",MB_OK);
  return vec.at(p);
}
int Hotkeys::Count()
{
  return this->vec.size();
}

void Hotkeys::Add(hotkey* h)
{
  this->vec.push_back(h);
}

hotkey* Hotkeys::Find(int KeyCode)
{
  for(int i=0;i<vec.size();i++)
    if(vec.at(i)->KeyCode==KeyCode)
      return vec.at(i);
  return NULL;
}


Hotkeys::~Hotkeys(void)
{
  clear();
}


Hotkeys::Hotkeys(void)
{
}
