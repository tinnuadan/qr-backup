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

#include "gtest/gtest.h"
#include "image.h"

#include <algorithm>

TEST(testImage, testConstruction)
{
  auto const width = 14;
  auto const height = 19;
  qrbackup::Image<uint8_t> const img(width, height);

  EXPECT_EQ(width, img.width());
  EXPECT_EQ(height, img.height());
  EXPECT_EQ(static_cast<size_t>(width*height), img.data().size());
}


template<typename T>
void testData()
{
  auto const width = 5;
  auto const height = 10;
  qrbackup::Image<uint8_t> img(width, height);
  T i = 0;
  for(int y=0; y<height; ++y)
  {
    for(int x=0; x<width; ++x)
    {
      img.at(x,y) = i++;
    }
  }
  auto const cimg = img;

  EXPECT_EQ(cimg.at(0,0), static_cast<T>(0));
  EXPECT_EQ(cimg.at(1,0), static_cast<T>(1));
  EXPECT_EQ(cimg.at(0,1), static_cast<T>(5));
  EXPECT_EQ(cimg.at(4,9), static_cast<T>(49));

  EXPECT_THROW(cimg.at(4,10), std::out_of_range);
  EXPECT_THROW(cimg.at(10,5), std::out_of_range);
  EXPECT_THROW(img.at(4,10), std::out_of_range);
  EXPECT_THROW(img.at(10,5), std::out_of_range);
}

TEST(testImage, testData)
{
  testData<uint8_t>();
  testData<uint16_t>();
  testData<uint32_t>();
}
