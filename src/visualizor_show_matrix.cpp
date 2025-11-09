#include "image_painter.h"
#include "slam_log_reporter.h"
#include "slam_memory.h"
#include "slam_operations.h"
#include "visualizor_2d.h"

using namespace image_painter;

namespace slam_visualizor {

void Visualizor2D::ShowMatrix(const std::string &window_title, const Mat &matrix, int32_t delay_ms, float max_value, int32_t scale) {
    uint8_t *buf = (uint8_t *)malloc(matrix.rows() * matrix.cols() * scale * scale * sizeof(uint8_t));
    GrayImage image_matrix(buf, matrix.rows() * scale, matrix.cols() * scale, true);
    ImagePainter::ConvertMatrixToImage(matrix, image_matrix, max_value, scale);
    Visualizor2D::ShowImage(window_title, image_matrix);
    Visualizor2D::WaitKey(delay_ms);
}

}  // namespace slam_visualizor
