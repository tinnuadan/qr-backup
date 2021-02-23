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
#include "qrcode_wrapper.h"

#include <algorithm>

#include "image.h"

#include <opencv2/opencv.hpp>


template <typename T>
cv::Mat_<T> img2cv(qrbackup::Image<T> const &img)
{
  cv::Mat_<T> result(img.height(), img.width());
  std::copy(img.data().begin(), img.data().end(), result.ptr(0));
  return result;
}

TEST(testQrBackup, testGeneration)
{
  const char *phrase = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";

  qrbackup::Options options{};

  for (int i = 2; i <= 10; i += 2)
  {
    std::stringstream filename;
    filename << "./testdata/qrcode_" << i << ".png";
    options.pixel_size = i;

    cv::Mat_<uint8_t> const groundTruth = cv::imread(filename.str(), cv::IMREAD_GRAYSCALE);
    auto const qrCode = qrbackup::GenerateQrCode(phrase, options);

    EXPECT_EQ(groundTruth.cols, qrCode.width());
    EXPECT_EQ(groundTruth.rows, qrCode.height());
    auto const size = std::min(static_cast<size_t>(groundTruth.cols*groundTruth.rows), qrCode.data().size());
    EXPECT_TRUE(std::memcmp(groundTruth.data, qrCode.data().data(), size)==0);
  }
}
