//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Reaction.h"
#include "misc/owning/makeOut.h"
#include "response/RsText.h"
#include <string>

class RcText : public Reaction {
    std::string text;

  public:
    explicit RcText(std::string text) : text(std::move(text)) {}

    auto result(in<Command> /*unused*/) -> out<Response> override {
        return makeOut<RsText>(text);
    }
};
