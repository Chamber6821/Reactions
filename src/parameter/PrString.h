//
// Created by Ivan on 07.05.2023.
//

#pragma once

#include "Parameter.h"

class PrString : public Parameter<std::string_view> {
  public:
    PrString() = default;

    auto valueOf(in<Argument> argument) -> std::string_view override {
        return argument->value();
    }
};
