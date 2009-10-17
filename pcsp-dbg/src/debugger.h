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
#ifndef DEBUGGER_H_
#define DEBUGGER_H_

struct debugger_s;

struct debugger_s
{
    static debugger_s &self();

    debugger_s();

    ~debugger_s();

    void initialize();

    void finalize();
	void update_debugger();
};

extern debugger_s &debugger;

#endif /* DEBUGGER_H_ */