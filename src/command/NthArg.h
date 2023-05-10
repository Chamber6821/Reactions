//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Argument.h"
#include "Command.h"
#include "misc/owning/in.h"

class NthArg : public Argument {
    in<Command> command{};
    int number{};

  public:
    explicit NthArg(in<Command> command, int number);

    auto value() -> std::string_view override;
};
