#include "visualizor.h"
#include "slam_memory.h"
#include "slam_operations.h"
#include "log_report.h"

namespace SLAM_VISUALIZOR {

std::map<std::string, VisualizorWindow> Visualizor::windows_;
bool Visualizor::some_key_pressed_ = false;

Visualizor &Visualizor::GetInstance() {
    static Visualizor instance;
    return instance;
}

Visualizor::~Visualizor() {
    // Clear all windows and recovery resources.
    Visualizor::windows_.clear();
    glfwTerminate();
}

void Visualizor::ErrorCallback(int32_t error, const char *description) {
    ReportError("[Visualizor] Error detected :" << description);
}

void Visualizor::KeyboardCallback(GLFWwindow *window, int32_t key, int32_t scan_code, int32_t action, int32_t mods) {
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (action == GLFW_PRESS) {
        Visualizor::some_key_pressed_ = true;
    }
}

VisualizorWindow *Visualizor::GetWindowPointer(const std::string &title, int32_t width, int32_t height) {
    auto item = Visualizor::windows_.find(title);
    if (item == Visualizor::windows_.end()) {
        // If window with selected title is not found, create a new window.
        auto iter = Visualizor::windows_.insert(std::make_pair(title, VisualizorWindow()));
        iter.first->second.glfw_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        // If insert failed, clear it.
        if (iter.first->second.glfw_window == nullptr) {
            Visualizor::windows_.erase(title);
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

}
