

#include "../include/launch_manager.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

// === Gestion des erreurs GLFW ===
static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* main_window = glfwCreateWindow(1000, 700, "Larikio", nullptr, nullptr);
    if (!main_window)
    {
        return -1;
    }

    glfwMakeContextCurrent(main_window);
    glfwSwapInterval(1); // Synchronisation verticale (vsync)

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(main_window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImVec4 clear_color = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
    static std::string text_buffer; // stockage dynamique du texte

    while (!glfwWindowShouldClose(main_window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // === Fenêtre principale plein écran ===
        int fb_width, fb_height;
        glfwGetFramebufferSize(main_window, &fb_width, &fb_height);
        io.DisplaySize = ImVec2(static_cast<float>(fb_width), static_cast<float>(fb_height));

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));

        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("Larikio - Bloc Note", nullptr, window_flags);

        // === Zone d'édition adaptative ===
        ImVec2 text_size = ImGui::GetContentRegionAvail();
        text_buffer.reserve(8192);

        ImGui::InputTextMultiline(
            "##note",
            text_buffer.data(),
            text_buffer.capacity(),
            text_size,
            ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackResize,
            [](ImGuiInputTextCallbackData* data) -> int
            {
                if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
                {
                    auto* buffer = static_cast<std::string*>(data->UserData);
                    buffer->resize(data->BufTextLen);
                    data->Buf = buffer->data();
                }
                return 0;
            },
            &text_buffer
        );

        ImGui::End();

        // === Rendu ===
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(main_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(main_window);
    }

    // === Nettoyage ===
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(main_window);
    glfwTerminate();

    return 0;
}
