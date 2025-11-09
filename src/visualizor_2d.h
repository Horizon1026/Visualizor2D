#ifndef _SLAM_UTILITY_IMAGE_VISUALIZOR_H_
#define _SLAM_UTILITY_IMAGE_VISUALIZOR_H_

#include "basic_type.h"
#include "datatype_image.h"
#include "slam_log_reporter.h"

#include "glad.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

namespace SLAM_VISUALIZOR {

struct VisualizorWindow {
    GLFWwindow *glfw_window = nullptr;
    GLuint texture_id = 0;
};

// Class Visualizor2D Declaration.
class Visualizor2D {

public:
    virtual ~Visualizor2D();
    static Visualizor2D &GetInstance();

    // Support for matrix visualization.
    static void ShowMatrix(const std::string &window_title, const Mat &matrix, int32_t delay_ms = 1, float max_value = 1e-2f, int32_t scale = 4);

    // Support for feature tracking result visualization.
    static void ShowImageWithDetectedFeatures(const std::string &window_title, const GrayImage &image, const std::vector<Vec2> &pixel_uv,
                                              RgbPixel color = RgbColor::kRed);
    static void DrawImageWithDetectedFeatures(const GrayImage &image, const std::vector<Vec2> &pixel_uv, RgbPixel color, RgbImage &show_image);
    static void ShowImageWithTrackedFeatures(const std::string &window_title, const GrayImage &cur_image, const std::vector<Vec2> &ref_pixel_uv,
                                             const std::vector<Vec2> &cur_pixel_uv, const std::vector<uint8_t> &track_status,
                                             uint8_t min_valid_track_status_value = 2, RgbPixel tracked_color = RgbColor::kCyan,
                                             RgbPixel untracked_color = RgbColor::kRed, RgbPixel flow_line_color = RgbColor::kGreen);
    static void DrawImageWithTrackedFeatures(const GrayImage &cur_image, const std::vector<Vec2> &ref_pixel_uv, const std::vector<Vec2> &cur_pixel_uv,
                                             const std::vector<uint8_t> &track_status, uint8_t min_valid_track_status_value, RgbPixel tracked_color,
                                             RgbPixel untracked_color, RgbPixel flow_line_color, RgbImage &show_image);
    static void ShowImageWithTrackedFeatures(const std::string &window_title, const GrayImage &ref_image, const GrayImage &cur_image,
                                             const std::vector<Vec2> &ref_pixel_uv, const std::vector<Vec2> &cur_pixel_uv,
                                             const std::vector<uint8_t> &track_status, uint8_t min_valid_track_status_value = 2,
                                             RgbPixel tracked_color = RgbColor::kCyan, RgbPixel untracked_color = RgbColor::kRed);
    static void DrawImageWithTrackedFeatures(const GrayImage &ref_image, const GrayImage &cur_image, const std::vector<Vec2> &ref_pixel_uv,
                                             const std::vector<Vec2> &cur_pixel_uv, const std::vector<uint8_t> &track_status,
                                             uint8_t min_valid_track_status_value, RgbPixel tracked_color, RgbPixel untracked_color, RgbImage &show_image);
    static void ShowImageWithTrackedFeaturesWithId(const std::string &window_title, const GrayImage &ref_image, const GrayImage &cur_image,
                                                   const std::vector<Vec2> &ref_pixel_uv, const std::vector<Vec2> &cur_pixel_uv,
                                                   const std::vector<uint32_t> &ref_ids, const std::vector<uint32_t> &cur_ids,
                                                   const std::vector<uint8_t> &tracked_status, uint8_t min_valid_track_status_value = 2,
                                                   const std::vector<uint32_t> &ref_tracked_cnt = std::vector<uint32_t>(),
                                                   const std::vector<Vec2> &cur_optical_velocity = std::vector<Vec2>());
    static void DrawImageWithTrackedFeaturesWithId(const GrayImage &ref_image, const GrayImage &cur_image, const std::vector<Vec2> &ref_pixel_uv,
                                                   const std::vector<Vec2> &cur_pixel_uv, const std::vector<uint32_t> &ref_ids,
                                                   const std::vector<uint32_t> &cur_ids, const std::vector<uint8_t> &tracked_status,
                                                   uint8_t min_valid_track_status_value, const std::vector<uint32_t> &ref_tracked_cnt,
                                                   const std::vector<Vec2> &cur_optical_velocity, RgbImage &show_image);
    static void ShowImageWithTrackedFeaturesWithId(const std::string &window_title, const GrayImage &ref_image_left, const GrayImage &ref_image_right,
                                                   const GrayImage &cur_image_left, const GrayImage &cur_image_right,
                                                   const std::vector<Vec2> &ref_pixel_uv_left, const std::vector<Vec2> &ref_pixel_uv_right,
                                                   const std::vector<Vec2> &cur_pixel_uv_left, const std::vector<Vec2> &cur_pixel_uv_right,
                                                   const std::vector<uint32_t> &ref_ids_left, const std::vector<uint32_t> &ref_ids_right,
                                                   const std::vector<uint32_t> &cur_ids_left, const std::vector<uint32_t> &cur_ids_right,
                                                   const std::vector<uint8_t> &frame_tracked_status, const std::vector<uint8_t> &ref_stereo_tracked_status,
                                                   const std::vector<uint8_t> &cur_stereo_tracked_status, uint8_t min_valid_track_status_value = 2,
                                                   const std::vector<uint32_t> &ref_tracked_cnt = std::vector<uint32_t>(),
                                                   const std::vector<Vec2> &cur_optical_velocity = std::vector<Vec2>());
    static void DrawImageWithTrackedFeaturesWithId(const GrayImage &ref_image_left, const GrayImage &ref_image_right, const GrayImage &cur_image_left,
                                                   const GrayImage &cur_image_right, const std::vector<Vec2> &ref_pixel_uv_left,
                                                   const std::vector<Vec2> &ref_pixel_uv_right, const std::vector<Vec2> &cur_pixel_uv_left,
                                                   const std::vector<Vec2> &cur_pixel_uv_right, const std::vector<uint32_t> &ref_ids_left,
                                                   const std::vector<uint32_t> &ref_ids_right, const std::vector<uint32_t> &cur_ids_left,
                                                   const std::vector<uint32_t> &cur_ids_right, const std::vector<uint8_t> &frame_tracked_status,
                                                   const std::vector<uint8_t> &ref_stereo_tracked_status, const std::vector<uint8_t> &cur_stereo_tracked_status,
                                                   uint8_t min_valid_track_status_value, const std::vector<uint32_t> &ref_tracked_cnt,
                                                   const std::vector<Vec2> &cur_optical_velocity, RgbImage &show_image);

    // Support for image show.
    template <typename T>
    static bool ShowImage(const std::string &window_title, const T &image, bool resizable = false);
    static void WaitKey(int32_t delay_ms);
    static void WindowList();

    // Support for image load and save.
    template <typename ImageType>
    static bool LoadImage(const std::string &image_file, ImageType &image);
    template <typename ImageType>
    static bool SaveImage(const std::string &image_file, const ImageType &image);
    template <typename ImageType>
    static bool LoadFromPngImageData(const std::vector<uint8_t> &png_data, ImageType &image);
    template <typename ImageType>
    static bool SaveToPngImageData(const ImageType &image, std::vector<uint8_t> &png_data);

    // Reference for member variables.
    static std::map<std::string, VisualizorWindow> &windows() { return windows_; }

private:
    Visualizor2D() = default;

    // Callback function for image show.
    static void ErrorCallback(int32_t error, const char *description);
    static void KeyboardCallback(GLFWwindow *window, int32_t key, int32_t scan_code, int32_t action, int32_t mods);

    // Inner support for image show.
    static VisualizorWindow *GetWindowPointer(const std::string &title, int32_t width, int32_t height);
    template <typename T>
    static void PreprocessImage(const T &image, uint8_t *buff);
    template <typename T>
    static void CreateTextureByImage(const T &image, GLuint &texture_id);
    static void ShowTextureInCurrentWindow(GLuint texture_id);

    // Inner support for feature tracking result visualization.
    static void DrawFeaturesWithIdByTrackedNumbers(const std::vector<Vec2> &pixel_uv, const std::vector<uint32_t> &ids, const Pixel &pixel_offset,
                                                   const std::vector<uint8_t> &status, const uint8_t min_valid_status_value,
                                                   const std::vector<uint32_t> &tracked_cnt, RgbImage &image);
    static void DrawFeaturesWithIdByOpticalVelocity(const std::vector<Vec2> &pixel_uv, const std::vector<uint32_t> &ids, const Pixel &pixel_offset,
                                                    const std::vector<uint8_t> &status, const uint8_t min_valid_status_value,
                                                    const std::vector<Vec2> &optical_velocity, RgbImage &image);

private:
    // Member variables for image show.
    static std::map<std::string, VisualizorWindow> windows_;
    static bool some_key_pressed_;
};

}  // namespace SLAM_VISUALIZOR

#endif  // end of _SLAM_UTILITY_IMAGE_VISUALIZOR_H_
