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

#include "qrcode_wrapper.h"
#include <qrcodegen/QrCode.hpp>

// stl
#include <iostream>

namespace qrcode
{
  Image<uint8_t> GenerateQrCode(std::string const &text, Options const options)
  {
    using namespace qrcodegen;

    auto const err_correction_lvl = QrCode::Ecc::HIGH;
    auto const qr = QrCode::encodeText(text.c_str(), err_correction_lvl);

    auto const px_size = static_cast<int>(options.pixel_size);
    auto const border = static_cast<int>(options.border); // * px_size;
    auto const qr_size = qr.getSize();
    auto const wh_mat = (qr_size + 2 * border) * px_size;

    auto result = Image<uint8_t>(wh_mat, wh_mat);

    for (int y = 0; y < qr_size + 2 * border; ++y)
    {
      auto const qrY = y - border;
      auto const matY = y * px_size;
      for (int x = 0; x < qr_size + 2 * border; ++x)
      {
        auto const qrX = x - border;
        auto const matX = x * px_size;
        uint8_t color = 0xFFu;
        if (utils::in_range(qrX, 0, qr_size) && utils::in_range(qrY, 0, qr_size))
        {
          color = qr.getModule(qrX, qrY) ? 0u : 0xFFu;
        }

        for (auto k = 0; k < px_size; ++k)
        {
          for (auto u = 0; u < px_size; ++u)
          {
            if (utils::in_range(matX + u, 0, wh_mat) && utils::in_range(matY + k, 0, wh_mat))
            {
              result.at(matX + u, matY + k) = color;
            }
            else
            {
              std::cerr << "ERR: " << matX + u << ", " << matY + k << " out of range" << std::endl;
            }
          }
        }
      }
    }

    return result;
  }
}