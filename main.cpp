
// STL
#include <iostream>

// C
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Linux
#include <linux/fb.h>




int main()
{
  const char* fbdev = "/dev/fb0";

  std::cout << "opening frame buffer" << std::endl;
  auto framebuffer_fd = open (fbdev, O_RDWR);
  if(framebuffer_fd <= 0)
  {
    std::cerr << "unable to open " << fbdev << std::endl;
    return 1;
  }


  std::cout << "finding screen dimensions" << std::endl;
  struct fb_var_screeninfo vinfo;

  ioctl (framebuffer_fd, FBIOGET_VSCREENINFO, &vinfo);

  auto const screen_width = vinfo.xres;
  auto const screen_height = vinfo.yres;
  auto const screen_bpp = vinfo.bits_per_pixel;
  
  if(screen_bpp != 32u)
  {
    std::cerr << "display must have 32 bits per pixel" << std::endl;
    close (framebuffer_fd);
    return 1;
  }

  std::cout << "mapping screen memory" << std::endl;
  auto const data_size = screen_width * screen_height;
  auto const data_byte_size = data_size * screen_bpp / 8;


  auto *framebuffer = static_cast<uint32_t*> (mmap (0, data_byte_size, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_fd, (off_t)0));
  if(framebuffer == nullptr)
  {
    std::cerr << "unable to get framebuffer" << std::endl;
    close (framebuffer_fd);
    return 0;
  }


  std::cout << "cleaning up" << std::endl;
  munmap (framebuffer, data_byte_size);
  close (framebuffer_fd);
  return 0;
}