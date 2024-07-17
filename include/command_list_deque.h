#pragma once
#ifndef COMMAND_LIST_DEQUE_H
#define COMMAND_LIST_DEQUE_H

#include "command_list.h"
#include <deque>

class CommandListDeque
{

public:
    static CommandListDeque& Instance();
    CommandListDeque();
    ~CommandListDeque();

    void addList(CommandList &&cl);
    void execute();
    void swapList();

private:
    std::deque<CommandList> logic_list;
    std::deque<CommandList> render_list;
};


#endif // !COMMAND_LIST_DEQUE_H