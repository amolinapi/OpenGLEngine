#include "command_list_deque.h"

CommandListDeque& CommandListDeque::Instance()
{
    static px::Mem<CommandListDeque> inst;
    if (!inst.valid()) {
        inst.alloc();
    }

    return *inst.get();
}

CommandListDeque::CommandListDeque()
{

}

CommandListDeque::~CommandListDeque()
{

}

void CommandListDeque::addList(CommandList&& cl)
{
    logic_list.push_back(std::move(cl));
}

void CommandListDeque::execute()
{
    std::deque<CommandList>::iterator it;
    for (it = render_list.begin(); it != render_list.end(); it++) {
        it->executeCommands();
    }
}

void CommandListDeque::swapList()
{
    render_list.clear();
    render_list = std:: move(logic_list);
}
