#include "masterheader.h"
    #include <iostream>
    #include <string>
    #include <vector>
    #include <cstdlib>
    #include "screen.h"

    #include "imgui.h"
    #include "imgui_impl_glfw.h"
    #include "imgui_impl_opengl3.h"
    #include <GLFW/glfw3.h>

    using namespace std;

    int main() {

        glfwInit();
        // Match the Xvnc virtual display geometry (1280x720) so the GLFW window
        // fills the visible OpenGL Display panel instead of sitting tiny in the
        // top-left of the virtual desktop.
        GLFWwindow* win = glfwCreateWindow(1280, 720, "ImGui Demo", nullptr, nullptr);
        glfwMakeContextCurrent(win);

        Screen *screen = new Screen();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        // Load the pcface ModernDOS 8x8 bitmap-style TTF so the box-drawing
        // glyphs ('═','║','╔','╗','╚','╝','╠','╣') render properly instead of as
        // '?' from the default ImGui font. The C++ Studio compile pipeline
        // exposes the cloned deps directory via the DEPS_DIR env var.
        ImGuiIO& io = ImGui::GetIO();
        const char* depsDir = std::getenv("DEPS_DIR");
        if (depsDir && *depsDir) {
            std::string fontPath = std::string(depsDir) + "/pcface/src/font/moderndos/ModernDOS8x8.ttf";
            // Static so the array outlives the AddFontFromFileTTF call — ImGui
            // keeps a pointer to it for the lifetime of the atlas.
            static const ImWchar ranges[] = {
                0x0020, 0x00FF, // Basic Latin + Latin-1 Supplement
                0x2500, 0x257F, // Box Drawing
                0x2580, 0x259F, // Block Elements
                0,
            };
            // 8.0f keeps glyphs at their native 8x8 source size; we then upscale
            // via SetWindowFontScale in screen.h to fill the window cleanly.
            io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 8.0f, nullptr, ranges);
        }

        ImGui_ImplGlfw_InitForOpenGL(win, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        while (!glfwWindowShouldClose(win)) {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Fullscreen ImGui window so screen->Draw()'s auto-scaling fills the
            // OS window. NoTitleBar/NoResize/NoMove make it feel like a canvas
            // rather than a draggable subwindow.
            const ImGuiViewport* vp = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(vp->Pos);
            ImGui::SetNextWindowSize(vp->Size);
            ImGui::Begin("ScreenGrid", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoBringToFrontOnFocus);
            screen->Draw();
            ImGui::End();

            ImGui::Render();
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(win);
        }
        return 0;
    }
  