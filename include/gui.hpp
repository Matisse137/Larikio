//
// Created by admin on 29/10/2025.
//

#ifndef LARIKIO_GUI_HPP
#define LARIKIO_GUI_HPP
#include "defines.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Gui
{
    public:
        Return_code launch_app();
    private:
        GLFWwindow* main_window = nullptr;
        ImGuiIO& in_out;
};


#endif //LARIKIO_GUI_HPP