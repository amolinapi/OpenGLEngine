#include "command.h"
#include <vector>

Command::Command()
{

}

Command::~Command()
{

}


Command::Command(Command&&)
{

}

Command& Command::operator=(Command&& other)
{
    return *this;
}