//
// Created by Ivan on 02.05.2023.
//

#pragma once

#include "Response.h"
#include <iostream>
#include <ranges>
#include <string_view>

template <class T>
concept Printable = requires(T &x, std::ostream &out) {
    { out << x };
};

template <std::ranges::range T>
    requires Printable<std::ranges::range_value_t<T>>
class RsText : public Response {
    T printable;

  public:
    explicit RsText(T printable) : printable(printable) {}

    void print(std::ostream &output) override {
        for (const auto &part : printable) {
            output << part;
        }
    }
};
