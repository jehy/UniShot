#pragma once

class trigger
{
public:
  trigger(void);
  ~trigger(void);
  int run(HANDLE SomeInfo);
  //char* name;
  int type;
  char* action;
};
