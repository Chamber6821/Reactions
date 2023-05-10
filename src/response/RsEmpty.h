//
// Created by Ivan on 03.05.2023.
//

#pragma once

#include "Response.h"

class RsEmpty : public Response {
  public:
    void print(std::ostream &output) override {}
};
