/*
*
* Copyright 2021 Tinnuadan
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
*
* You may obtain a copy of the License at
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#ifndef QRBACKUP_IMAGE_H
#define QRBACKUP_IMAGE_H

// STL
#include <stdexcept>
#include <vector>

namespace qrbackup
{
  template<typename T>
  class Image
  {
    public:
      Image(unsigned int width, unsigned int height) :
        _width(width),
        _height(height),
        _data(width*height)
        {}

      T at(unsigned int x, unsigned int y) const
      {
        if(x >= _width || y >= _height)
        {
          throw std::out_of_range("index not valid");
        }
        return _data.at(y*_width+x);
      }

      T& at(unsigned int x, unsigned int y)
      {
        if(x >= _width || y >= _height)
        {
          throw std::out_of_range("index not valid");
        }
        return _data[y*_width+x];
      }

      auto width() const
      {
        return _width;
      }

      auto height() const
      {
        return _height;
      }

      std::vector<T> const& data() const
      {
        return _data;
      }

    private:
      unsigned int _width {0u};
      unsigned int _height {0u};
      std::vector<T> _data{};

  };
}

#endif // QRBACKUP_IMAGE_H