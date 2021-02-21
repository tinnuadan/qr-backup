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


#include "gtest/gtest.h"
#include "qrcode_wrapper.h"

#include <algorithm>

#include "image.h"

#include <opencv2/opencv.hpp>

template<typename T>
cv::Mat_<T> img2cv(qrcode::Image<T> const& img)
{
    cv::Mat_<T> result(img.height(), img.width());
    std::copy(img.data().begin(), img.data().end(), result.ptr(0));
    return result;
}

TEST(testMath, myCubeTest)
{
    auto qrCode = qrcode::GenerateQrCode("https://zeit.de", qrcode::Options{});
    cv::imwrite("test.png", img2cv(qrCode));
}
