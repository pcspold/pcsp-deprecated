/*
This file is part of pcsp.

pcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "stdafx.h"
#include "debugger.h"
#include "memory.h"


static FILE *&get_log_file()
{
	static FILE *file = 0;
	char const *filename = "emulator.log";
	if (!file)
	{
		file = ::fopen(filename, "w");
	}
	return file;
}
FILE *&m_file=get_log_file();
debugger_s &debugger_s::self()
{
  static debugger_s instance;
  return instance;
}

debugger_s &debugger = debugger_s::self();

debugger_s::debugger_s()
{
	Memory::initialize();
	if (m_file)
	{
		::fclose(m_file);
		m_file = 0;
	}
	if(!m_file)
	{
       m_file = get_log_file();
	}
}
void debugger_s::writelog(QString text)
{
  if(m_file)
   ::fprintf(m_file, "%s", text.toLatin1().data());
}
debugger_s::~debugger_s()
{
	Memory::release();
	::fflush(m_file);
}

void debugger_s::initialize()
{

}

void debugger_s::finalize()
{

}
