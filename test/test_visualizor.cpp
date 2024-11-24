#include "basic_type.h"
#include "datatype_image.h"
#include "image_painter.h"
#include "visualizor_2d.h"
#include "slam_log_reporter.h"
#include "slam_operations.h"

#include "iostream"
#include "dirent.h"
#include "vector"
#include "cstring"

using namespace SLAM_UTILITY;
using namespace SLAM_VISUALIZOR;
using namespace IMAGE_PAINTER;

namespace {
    constexpr int32_t kScale = 3;
    constexpr int32_t kMatrixRow = 90;
    constexpr int32_t kMatrixCol = 180;
}

void TestVisualizorStatic() {
    ReportInfo(YELLOW ">> Test visualizor show static image." RESET_COLOR);
    const std::string png_image_file = "../example/image.png";

    // Create rgb image from png file.
    RgbImage rgb_image_png;
    Visualizor::LoadImage(png_image_file, rgb_image_png);

    // Create gray image from png file.
    GrayImage gray_image_png;
    Visualizor::LoadImage(png_image_file, gray_image_png);

    // Test visualizor.
    Visualizor::ShowImage("Gray Png Image", gray_image_png);
    Visualizor::WaitKey(1);
    Visualizor::ShowImage("Rgb Png Image", rgb_image_png);
    Visualizor::WaitKey(0);
}

void TestVisualizorDynamic() {
    ReportInfo(YELLOW ">> Test visualizor show dynamic image." RESET_COLOR);

    std::vector<std::string> cam0_filenames;
    if (!SlamOperation::GetFilesNameInDirectory("/home/horizon/Desktop/date_sets/euroc/MH_01_easy/mav0/cam0/data", cam0_filenames)) {
        if (!SlamOperation::GetFilesNameInDirectory("/mnt/d/My_Github/Datasets/Euroc/MH_01_easy/mav0/cam0/data", cam0_filenames)) {
            RETURN_IF(!SlamOperation::GetFilesNameInDirectory("D:/My_Github/Datasets/Euroc/MH_01_easy/mav0/cam0/data", cam0_filenames));
        }
    }
    std::sort(cam0_filenames.begin(), cam0_filenames.end());

    std::vector<std::string> cam1_filenames;
    if (!SlamOperation::GetFilesNameInDirectory("/home/horizon/Desktop/date_sets/euroc/MH_01_easy/mav0/cam1/data", cam1_filenames)) {
        if (!SlamOperation::GetFilesNameInDirectory("/mnt/d/My_Github/Datasets/Euroc/MH_01_easy/mav0/cam1/data", cam1_filenames)) {
            RETURN_IF(!SlamOperation::GetFilesNameInDirectory("D:/My_Github/Datasets/Euroc/MH_01_easy/mav0/cam1/data", cam1_filenames));
        }
    }
    std::sort(cam1_filenames.begin(), cam1_filenames.end());

    for (uint32_t i = 0; i < 100; ++i) {
        GrayImage image_left;
        GrayImage image_right;
        Visualizor::LoadImage(cam0_filenames[i], image_left);
        Visualizor::LoadImage(cam1_filenames[i], image_right);

        Visualizor::ShowImage("Left", image_left);
        Visualizor::ShowImage("Right", image_right);

        Visualizor::WaitKey(15);
    }
    Visualizor::WaitKey(0);
}

int main(int argc, char **argv) {
    ReportInfo(YELLOW ">> Test visualizor." RESET_COLOR);

    if (argc == 1) {
        ReportInfo("Argc is 1, run static image test.");
        TestVisualizorStatic();
    } else {
        ReportInfo("Argc is not 1, run dynamic image test.");
        TestVisualizorDynamic();
    }

    return 0;
}
