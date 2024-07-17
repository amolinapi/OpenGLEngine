#pragma once
#ifndef COMMAND_H
#define COMMAND_H 1

class Command
{

public:
    Command();
    virtual ~Command();
    Command(const Command&) = delete;
    Command(Command&&);

    Command& operator=(const Command& other) = delete;
    Command& operator=(Command&& other);

    virtual void command() = 0;

};

#endif // !COMMAND_H