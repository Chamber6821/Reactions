//
// Created by Ivan on 10.05.2023.
//

#pragma once

#include "Response.h"
#include "misc/owning/in.h"
#include <vector>

class RsGlued : public Response {
    std::vector<in<Response>> parts{};

  public:
    RsGlued(std::initializer_list<in<Response>> parts) : parts(parts) {}

    template <std::convertible_to<in<Response>>... Types>
    explicit RsGlued(Types... parts) : RsGlued({parts...}) {}

    void print(std::ostream &output) override {
        for (auto &part : parts) {
            part->print(output);
        }
    }
};
