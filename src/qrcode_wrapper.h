/*
* Licensed to the Apache Software Foundation (ASF) under one
* or more contributor license agreements.  See the NOTICE file
* distributed with this work for additional information
* regarding copyright ownership.  The ASF licenses this file
* to you under the Apache License, Version 2.0 (the
* "License"); you may not use this file except in compliance
* with the License.  You may obtain a copy of the License at
* 
*   http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing,
* software distributed under the License is distributed on an
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
* KIND, either express or implied.  See the License for the
* specific language governing permissions and limitations
* under the License.
*/

#ifndef QRCODE_QRCODE_WRAPPER_H
#define QRCODE_QRCODE_WRAPPER_H

#include <cstdint>
#include <string>

#include "image.h"

namespace qrcode
{
  namespace utils
  {
    template <typename T>
    constexpr bool in_range(T value, T min, T max)
    {
      return value >= min && value < max;
    }
  }

  struct Options
  {
    int pixel_size = 10u;
    int border = 1u;
  };

  Image<uint8_t> GenerateQrCode(std::string const &text, Options const options);
}

#endif
