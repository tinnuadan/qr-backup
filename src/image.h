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

#ifndef QRCODE_IMAGE_H
#define QRCODE_IMAGE_H

// STL
#include <vector>

namespace qrcode
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
                return _data.at(y*_width+x);
            }

            T& at(unsigned int x, unsigned int y)
            {
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

#endif // QRCODE_IMAGE_H