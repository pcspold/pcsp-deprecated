#include "debugger.h"
#include "memory.h"

debugger_s &debugger_s::self()
{
  static debugger_s instance;
  return instance;
}

debugger_s &debugger = debugger_s::self();

debugger_s::debugger_s()
{
  Memory::initialize();
}

debugger_s::~debugger_s()
{
	Memory::release();
}

void debugger_s::initialize()
{

}

void debugger_s::finalize()
{

}
