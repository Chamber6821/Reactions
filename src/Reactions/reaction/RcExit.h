//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reaction.h"
#include "exit/ExFlag.h"
#include "misc/owning/makeOut.h"
#include "response/RsEmpty.h"

class RcExit : public Reaction {
    in<ExFlag> exit{};

  public:
    explicit RcExit(in<ExFlag> exit) : exit(std::move(exit)) {}

    auto result(in<Command> /*unused*/) -> out<Response> override {
        exit->up();
        return makeOut<RsEmpty>();
    }
};
