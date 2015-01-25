#include <iostream>

class NeuroNOC
{
public:
  NeuroNOC(int someInt);
  ~NeuroNOC();
  //---
  int GetVar() const;
  void SetVar(int var);
  void Step();
private:
  int theVar;
  char * someString;
};
