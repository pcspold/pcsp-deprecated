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
};

extern debugger_s &debugger;

#endif /* DEBUGGER_H_ */