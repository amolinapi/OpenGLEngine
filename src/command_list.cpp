#include "command_list.h"

CommandList::CommandList()
{

}

CommandList::~CommandList()
{

}

CommandList::CommandList(CommandList&& cl)
{
    cmd_list = std::move(cl.cmd_list);
}

void CommandList::executeCommands()
{
    for (std::list<px::Mem<Command>>::iterator it = cmd_list.begin(); it != cmd_list.end(); it++) {
        it->get()->command();
    }
}
