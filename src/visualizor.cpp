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

}
