//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reaction.h"
#include "misc/owning/makeOut.h"
#include "response/RsEmpty.h"

class RcNothing : public Reaction {
  public:
    auto result(in<Command> /*unused*/) -> out<Response> override {
        return makeOut<RsEmpty>();
    }
};
