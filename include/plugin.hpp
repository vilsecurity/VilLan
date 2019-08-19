#pragma once
//! The villan publicly exposed api

#include "api.grpc.pb.h"

#include <optional>

namespace VilSecurity::villan {
  class plugin : public proto::Plugin::Service {
  };
}
