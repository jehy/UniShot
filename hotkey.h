#pragma once

class hotkey
{
public:
  hotkey(void);
  ~hotkey(void);
  int KeyCode;
  char* action;
};

typedef vector<hotkey*> HotkeyVec; 


class Hotkeys
{
public:
  Hotkeys(void);
  ~Hotkeys(void);
  HotkeyVec vec;
  void clear();
  hotkey* GetAt(int p);
  int Count();
  void Add(hotkey* h);
  hotkey* Find(int KeyCode);
};