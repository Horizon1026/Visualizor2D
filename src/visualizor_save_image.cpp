#include "visualizor_2d.h"
#include "image_painter.h"
#include "slam_memory.h"
#include "slam_operations.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace IMAGE_PAINTER;

namespace SLAM_VISUALIZOR {

template <>
bool Visualizor2D::SaveImage<GrayImage>(const std::string &image_file, const GrayImage &image) {
    return stbi_write_png(image_file.c_str(), image.cols(), image.rows(), 1, image.data(), image.cols());
}

template <>
bool Visualizor2D::SaveImage<RgbImage>(const std::string &image_file, const RgbImage &image) {
    return stbi_write_png(image_file.c_str(), image.cols(), image.rows(), 3, image.data(), 3 * image.cols());
}

template <>
bool Visualizor2D::SaveToPngImageData<GrayImage>(const GrayImage &image, std::vector<uint8_t> &png_data) {
    int data_len = 0;
    uint8_t *data_in_mem = stbi_write_png_to_mem(image.data(), image.cols(), image.cols(), image.rows(), 1, &data_len);
    if (data_in_mem == nullptr) {
        ReportError("[Visualizor] Cannot save image to memory.");
        return false;
    }
    png_data.resize(data_len);
    std::copy_n(data_in_mem, data_len, png_data.data());
    STBIW_FREE(data_in_mem);
    return true;
}

template <>
bool Visualizor2D::SaveToPngImageData<RgbImage>(const RgbImage &image, std::vector<uint8_t> &png_data) {
    int data_len = 0;
    uint8_t *data_in_mem = stbi_write_png_to_mem(image.data(), 3 * image.cols(), image.cols(), image.rows(), 3, &data_len);
    if (data_in_mem == nullptr) {
        ReportError("[Visualizor] Cannot save image to memory.");
        return false;
    }
    png_data.resize(data_len);
    std::copy_n(data_in_mem, data_len, png_data.data());
    STBIW_FREE(data_in_mem);
    return true;
}

}
