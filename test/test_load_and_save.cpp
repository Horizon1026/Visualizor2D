#include "basic_type.h"
#include "slam_log_reporter.h"
#include "visualizor_2d.h"

using namespace slam_utility;
using namespace slam_visualizor;

int main(int argc, char *argv[]) {
    ReportInfo(YELLOW ">> Test load and save image." RESET_COLOR);

    std::string image_file = "../example/image.png";
    RgbImage rgb_image;
    GrayImage gray_image;
    Visualizor2D::LoadImage(image_file, rgb_image);
    Visualizor2D::LoadImage(image_file, gray_image);
    Visualizor2D::ShowImage("rgb image from file", rgb_image);
    Visualizor2D::ShowImage("gray image from file", gray_image);
    Visualizor2D::SaveImage("../../Workspace/output/rgb.png", rgb_image);
    Visualizor2D::SaveImage("../../Workspace/output/gray.png", gray_image);

    // Convert rgb/gray to png, and do it back.
    std::vector<uint8_t> rgb_png_data;
    Visualizor2D::SaveToPngImageData(rgb_image, rgb_png_data);
    ReportInfo("rgb png data size " << rgb_png_data.size());
    RgbImage new_rgb_image;
    Visualizor2D::LoadFromPngImageData(rgb_png_data, new_rgb_image);
    Visualizor2D::ShowImage("rgb image from data bytes", new_rgb_image);

    std::vector<uint8_t> gray_png_data;
    Visualizor2D::SaveToPngImageData(gray_image, gray_png_data);
    ReportInfo("gray png data size " << gray_png_data.size());
    GrayImage new_gray_image;
    Visualizor2D::LoadFromPngImageData(gray_png_data, new_gray_image);
    Visualizor2D::ShowImage("gray image from data bytes", new_gray_image);
    Visualizor2D::WaitKey(0);

    return 0;
}
