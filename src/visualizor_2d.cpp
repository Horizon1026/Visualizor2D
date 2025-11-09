#include "visualizor_2d.h"
#include "slam_log_reporter.h"
#include "slam_memory.h"
#include "slam_operations.h"

namespace slam_visualizor {

std::map<std::string, VisualizorWindow> Visualizor2D::windows_;
bool Visualizor2D::some_key_pressed_ = false;

Visualizor2D &Visualizor2D::GetInstance() {
    static Visualizor2D instance;
    return instance;
}

Visualizor2D::~Visualizor2D() {
    // Clear all windows and recovery resources.
    Visualizor2D::windows_.clear();
    glfwTerminate();
}

void Visualizor2D::ErrorCallback(int32_t error, const char *description) { ReportError("[Visualizor] Error detected :" << description); }

void Visualizor2D::KeyboardCallback(GLFWwindow *window, int32_t key, int32_t scan_code, int32_t action, int32_t mods) {
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (action == GLFW_PRESS) {
        Visualizor2D::some_key_pressed_ = true;
    }
}

VisualizorWindow *Visualizor2D::GetWindowPointer(const std::string &title, int32_t width, int32_t height) {
    auto item = Visualizor2D::windows_.find(title);
    if (item == Visualizor2D::windows_.end()) {
        // If window with selected title is not found, create a new window.
        auto iter = Visualizor2D::windows_.insert(std::make_pair(title, VisualizorWindow()));
        iter.first->second.glfw_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        // If insert failed, clear it.
        if (iter.first->second.glfw_window == nullptr) {
            Visualizor2D::windows_.erase(title);
            return nullptr;
        }
        return &(iter.first->second);
    } else {
        // Resize window size.
        glfwSetWindowSize(item->second.glfw_window, width, height);
        // Return the exist window.
        return &(item->second);
    }
}

}  // namespace slam_visualizor
