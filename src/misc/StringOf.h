//
// Created by Ivan on 10.05.2023.
//

#pragma once

#include "Scalar.h"
#include <string_view>

class StringOf : public Scalar<std::string_view> {
    std::string_view view;

  public:
    explicit StringOf(std::string_view view) : view(view) {}

    StringOf(std::string_view::const_iterator begin,
             std::string_view::const_iterator end)
        : StringOf(std::string_view{begin, end}) {}

    auto value() -> std::string_view override { return view; }
};