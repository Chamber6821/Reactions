//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reaction.h"
#include "response/RsError.h"

class RcNothrow : public Reaction {
    in<Reaction> wrapped{};

  public:
    explicit RcNothrow(in<Reaction> wrapped) : wrapped(std::move(wrapped)) {}

    auto result(in<Command> command) -> out<Response> override {
        try {
            return wrapped->result(command);
        } catch (const std::exception &e) {
            return makeOut<RsError>(e);
        }
    }
};
