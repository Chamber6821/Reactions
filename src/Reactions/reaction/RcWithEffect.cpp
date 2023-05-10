//
// Created by Ivan on 10.05.2023.
//

#include "RcWithEffect.h"
#include "response/RsMapped.h"

auto RcWithEffect::result(in<Command> command) -> out<Response> {
    return makeOut<RsMapped>([command, this](auto &output) {
        reaction->result(command)->print(output);
        effect(command);
    });
}
