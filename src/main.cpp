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

// STL
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

// C
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Linux
#include <linux/fb.h>

// project
#include "image.h"
#include "qrcode_wrapper.h"

int main()
{
  const char *fbdev = "/dev/fb0";

  std::stringstream strstream;
  {
    std::string input_line;
    while(std::getline(std::cin, input_line)) {
        // std::getline(std::cin, input_line);
        strstream << input_line;
        std::cout << input_line << std::endl;
    };
  }
  auto const message = strstream.str();



  std::cout << "opening frame buffer" << std::endl;
  auto framebuffer_fd = open(fbdev, O_RDWR);
  if (framebuffer_fd <= 0)
  {
    std::cerr << "unable to open " << fbdev << std::endl;
    return 1;
  }

  std::cout << "finding screen dimensions" << std::endl;
  struct fb_var_screeninfo vinfo;

  ioctl(framebuffer_fd, FBIOGET_VSCREENINFO, &vinfo);

  auto const screen_width = vinfo.xres;
  auto const screen_height = vinfo.yres;
  auto const screen_bpp = vinfo.bits_per_pixel;

  if (screen_bpp != 32u)
  {
    std::cerr << "display must have 32 bits per pixel" << std::endl;
    close(framebuffer_fd);
    return 1;
  }

  qrbackup::Options options;
  options.pixel_size = 5;
  auto const qrCode = qrbackup::GenerateQrCode(message, options);
  if (qrCode.width() > screen_width || qrCode.height() > screen_height)
  {
    std::cerr << "QR Code too large (" << qrCode.width() << "x" << qrCode.height() << ")" << std::endl; 
    close(framebuffer_fd);
    return 1;
  }

  std::cout << "mapping screen memory" << std::endl;
  auto const data_size = screen_width * screen_height;
  auto const data_byte_size = data_size * screen_bpp / 8;

  auto *framebuffer = static_cast<uint32_t *>(mmap(0, data_byte_size, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_fd, (off_t)0));
  if (framebuffer == nullptr)
  {
    std::cerr << "unable to get framebuffer" << std::endl;
    close(framebuffer_fd);
    return 0;
  }
  // save current screeen
  auto current_screen_data = std::make_unique<uint32_t[]>(data_size);
  std::memcpy(current_screen_data.get(), framebuffer, data_byte_size);

  // display qr code
  auto const dx = static_cast<int>((screen_width - qrCode.width()) / 2);
  auto const dy = static_cast<int>((screen_height - qrCode.height()) / 2);

  std::cout << "display" << std::endl;
  for (auto y = 0; y < static_cast<int>(screen_height); ++y)
  {
    auto const cvy = y - dy;
    for (auto x = 0; x < static_cast<int>(screen_width); ++x)
    {
      auto const i = y * screen_width + x;
      auto const cvy = y - dy;
      auto const cvx = x - dx;
      uint32_t pixel = 0u;
      if (qrbackup::utils::in_range(cvx, 0, static_cast<int>(qrCode.width())) &&
          qrbackup::utils::in_range(cvy, 0, static_cast<int>(qrCode.height())))
      {
        pixel = qrCode.at(cvx, cvy) == 0u ? 0u : 0xFFFFFFFF;
      }
      *(framebuffer + i) = pixel;
    }
  }

  // we need this little workaround to read from stdin since we read from it earlier until Ctrl+D is pressed
  auto* fstdin = std::fopen("/dev/tty", "r");
  if(fstdin == nullptr)
  { 
    std::cerr << "unable to open stdin, waiting 30s instead..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));
  }
  else
  {
    std::cout << "please press (enter) to exit" << std::endl;
    fgetc(fstdin);
    std::fclose(fstdin);
  }

  // restore screen
  std::memcpy(framebuffer, current_screen_data.get(), data_byte_size);

  std::cout << "cleaning up" << std::endl;
  munmap(framebuffer, data_byte_size);
  close(framebuffer_fd);
  return 0;
}