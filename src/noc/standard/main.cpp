
#include "main.h"

// constructor
NeuroNOC::NeuroNOC(int someInt)
{
  theVar = someInt;
  string = new char[10];
}

NeuroNOC::~NeuroNOC()
{
  delete[];
}

int NeuroNOC::GetVar()
{
  return theVar;
}

void NeuroNOC::SetVar(int someInt) {
  theVar = someInt;
  return;
}

void NeuroNOC::Step() {
  //do nothing.
  return;
}

