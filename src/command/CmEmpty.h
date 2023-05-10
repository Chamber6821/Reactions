//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Command.h"

class CmEmpty : public Command {
  public:
    auto name() -> std::string_view override { return ""; }

    auto arguments() -> std::string_view override { return ""; }
};
