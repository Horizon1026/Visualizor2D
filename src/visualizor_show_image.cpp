#include "visualizor.h"
#include "image_painter.h"
#include "slam_log_reporter.h"
#include "slam_memory.h"
#include "slam_operations.h"

#include "unistd.h"

using namespace IMAGE_PAINTER;

namespace SLAM_VISUALIZOR {

template bool Visualizor::ShowImage<GrayImage>(const std::string &window_title, const GrayImage &image, bool resizable);
template bool Visualizor::ShowImage<RgbImage>(const std::string &window_title, const RgbImage &image, bool resizable);
template <typename T>
bool Visualizor::ShowImage(const std::string &window_title, const T &image, bool resizable) {
    if (image.data() == nullptr || image.rows() < 1 || image.cols() < 1) {
        ReportError("[Visualizor] ShowImage() got an invalid image.");
        return false;
    }

    auto item = Visualizor::windows_.find(window_title);
    if (item == Visualizor::windows_.end()) {
        // New window. Create a new window and a new texture.
        glfwSetErrorCallback(Visualizor::ErrorCallback);

        if (!glfwInit()) {
            ReportError("[Visualizor] GLFW initialize failed.");
            return false;
        }

        if (resizable) {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        } else {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        }

        VisualizorWindow *window = GetWindowPointer(window_title, image.cols(), image.rows());
        glfwMakeContextCurrent(window->glfw_window);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSwapInterval(1);
        glfwShowWindow(window->glfw_window);
        glfwSetKeyCallback(window->glfw_window, Visualizor::KeyboardCallback);

        Visualizor::CreateTextureByImage<T>(image, window->texture_id);

        glColor3f(1.0f, 1.0f, 1.0f);
        glfwHideWindow(window->glfw_window);

    } else {
        // Exist window. Only change its texture.
        VisualizorWindow *window = GetWindowPointer(window_title, image.cols(), image.rows());
        glfwMakeContextCurrent(window->glfw_window);
        glfwSetWindowShouldClose(window->glfw_window, GLFW_FALSE);
        Visualizor::CreateTextureByImage<T>(image, window->texture_id);
    }

    return true;
}

void Visualizor::WaitKey(int32_t delay_ms) {
    // Display add window hidden in ShowImage().
    for (const auto &item : Visualizor::windows_) {
        const auto &glfw_window = item.second.glfw_window;
        if (!glfwWindowShouldClose(glfw_window)) {
            // If this window is already shown, do not focus on it.
            if (glfwGetWindowAttrib(glfw_window, GLFW_FOCUS_ON_SHOW) != GLFW_FALSE) {
                glfwSetWindowAttrib(glfw_window, GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
            }
            glfwShowWindow(glfw_window);
        } else {
            glfwHideWindow(glfw_window);
        }
    }

    while (!Visualizor::windows_.empty()) {
        uint32_t closed_window_cnt = 0;
        for (const auto &item : Visualizor::windows_) {
            const auto &window = item.second;

            if (!glfwWindowShouldClose(window.glfw_window)) {
                glfwMakeContextCurrent(window.glfw_window);
                Visualizor::ShowTextureInCurrentWindow(window.texture_id);
                glfwSwapBuffers(window.glfw_window);
            } else {
                glfwHideWindow(window.glfw_window);
                ++closed_window_cnt;
            }

            glfwPollEvents();
        }

        if (delay_ms > 0) {
            usleep(delay_ms * 1000);
            break;
        }

        BREAK_IF(closed_window_cnt == Visualizor::windows_.size());
        BREAK_IF(Visualizor::some_key_pressed_);
    }

    // Resource recovery is in Destructor Function.
    Visualizor::some_key_pressed_ = false;
}

template <> void Visualizor::PreprocessImage<GrayImage>(const GrayImage &image, uint8_t *buff) {
    ImagePainter::ConvertUint8ToRgbAndUpsideDown(image.data(), buff, image.rows(), image.cols());
}

template <> void Visualizor::PreprocessImage<RgbImage>(const RgbImage &image, uint8_t *buff) {
    ImagePainter::ConvertRgbToBgrAndUpsideDown(image.data(), buff, image.rows(), image.cols());
}

template void Visualizor::CreateTextureByImage<GrayImage>(const GrayImage &image, GLuint &texture_id);
template void Visualizor::CreateTextureByImage<RgbImage>(const RgbImage &image, GLuint &texture_id);
template <typename T>
void Visualizor::CreateTextureByImage(const T &image, GLuint &texture_id) {
    if (texture_id == 0) {
        glGenTextures(1, &texture_id);
    }
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    const int32_t size = image.rows() * image.cols();
    uint8_t *image_buff = (uint8_t *)SlamMemory::Malloc(size * 3 * sizeof(uint8_t));
    Visualizor::PreprocessImage<T>(image, image_buff);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols(), image.rows(), 0, GL_BGR, GL_UNSIGNED_BYTE, image_buff);

    SlamMemory::Free(image_buff);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Visualizor::ShowTextureInCurrentWindow(GLuint texture_id) {
    int32_t width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, 1.f, 0.f, 1.f, 0.f, 1.f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBegin(GL_QUADS);

    glTexCoord2f(0.f, 0.f);
    glVertex2f(0.f, 0.f);

    glTexCoord2f(1.f, 0.f);
    glVertex2f(1.f, 0.f);

    glTexCoord2f(1.f, 1.f);
    glVertex2f(1.f, 1.f);

    glTexCoord2f(0.f, 1.f);
    glVertex2f(0.f, 1.f);

    glEnd();
}

void Visualizor::WindowList() {
    ReportInfo("[Visualizor] All stored window.");
    for (auto &item : Visualizor::windows_) {
        ReportInfo(">> window title " << item.first);
        ReportInfo("   window ptr " << item.second.glfw_window);
        ReportInfo("   window texture " << item.second.texture_id);
        ReportInfo("   should close " << glfwWindowShouldClose(item.second.glfw_window));
    }
}

}
