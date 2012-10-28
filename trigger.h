#pragma once
class trigger
{
public:
  trigger(void);
  ~trigger(void);
  int run(HANDLE SomeInfo);
  char* name;
  int type;
  char* action;
};

typedef vector<trigger*> TriggerVec;

class Triggers
{
public:
  Triggers(void);
  ~Triggers(void);
  TriggerVec vec;
  void clear();
  trigger* GetAt(int p);
  int Count();
  void Add(trigger* tr);
  trigger* Find(char* name);
};