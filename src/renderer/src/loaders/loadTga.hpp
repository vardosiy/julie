#pragma once

#include <string_view>
#include <memory>

std::unique_ptr<char[]> loadTga(std::string_view fileName, int * width, int * height, int * bpp);
