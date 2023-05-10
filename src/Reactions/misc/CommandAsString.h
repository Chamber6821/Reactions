//
// Created by Ivan on 09.05.2023.
//

#pragma once

#include "Command.h"
#include "Scalar.h"
#include "misc/owning/in.h"
#include <string>

class CommandAsString : public Scalar<std::string> {
    in<Command> command;

  public:
    explicit CommandAsString(in<Command> command)
        : command(std::move(command)) {}

    auto value() -> std::string override {
        return std::string(command->name()) + " : " +
               std::string(command->arguments());
    }
};
