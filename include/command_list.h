#pragma once
#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include "command.h"
#include <list>
#include <px_mem/px_mem.h>

class CommandList
{

public:
    CommandList();
    virtual ~CommandList();
    CommandList(CommandList&& cl);

    void executeCommands();

private:
    std::list<px::Mem<Command>> cmd_list;
};

#endif // !COMMANDLIST_H