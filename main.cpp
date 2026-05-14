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

    // Logical screen-grid pixel dimensions. 80 cols × 50 rows of 8×8 glyphs from
    // the pcface ModernDOS 8x8 font, rendered 1:1 with no scaling.
    static const float GRID_PX_W = 8.0f * 80.0f; // 640
    static const float GRID_PX_H = 8.0f * 50.0f; // 400

    int main() {

        glfwInit();
        // Match the Xvnc virtual display geometry (1280x720) so the GLFW window
        // fills the visible OpenGL Display panel; the grid is then centered
        // inside that window at native 1:1 pixel size.
        GLFWwindow* win = glfwCreateWindow(1280, 720, "ImGui Demo", nullptr, nullptr);
        glfwMakeContextCurrent(win);

        Screen *screen = new Screen();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        // Load the pcface ModernDOS 8x8 bitmap-style TTF so the box-drawing
        // glyphs (═ ║ ╔ ╗ ╚ ╝ ╠ ╣) render properly instead of as '?' from the
        // default ImGui font. The C++ Studio compile pipeline exposes the
        // cloned deps directory via DEPS_DIR and clones each dep into
        // ${DEPS_DIR}/${owner}__${repo}.
        ImGuiIO& io = ImGui::GetIO();
        const char* depsDir = std::getenv("DEPS_DIR");
        if (depsDir && *depsDir) {
            std::string fontPath = std::string(depsDir) + "/susam__pcface/src/font/moderndos/ModernDOS8x8.ttf";
            static const ImWchar ranges[] = {
                0x0020, 0x00FF, // Basic Latin + Latin-1 Supplement
                0x2500, 0x257F, // Box Drawing
                0x2580, 0x259F, // Block Elements
                0,
            };
            // 8.0f = native source size. screen.h renders at 1.0x scale so each
            // glyph is exactly 8×8 pixels in the framebuffer.
            ImFont* f = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 8.0f, nullptr, ranges);
            if (!f) {
                std::cerr << "[font] Failed to load " << fontPath
                          << " — falling back to default ImGui font.\n";
            }
        } else {
            std::cerr << "[font] DEPS_DIR not set — falling back to default ImGui font.\n";
        }

        ImGui_ImplGlfw_InitForOpenGL(win, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        while (!glfwWindowShouldClose(win)) {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Center a 640×400 ImGui window (the exact pixel size of an 80×50
            // grid of 8×8 glyphs) inside the GLFW window. No padding/border so
            // the inner content region is exactly GRID_PX_W × GRID_PX_H and
            // each cell maps 1:1 to a screen pixel — no auto-scaling.
            const ImGuiViewport* vp = ImGui::GetMainViewport();
            const ImVec2 pos(
                vp->Pos.x + (vp->Size.x - GRID_PX_W) * 0.5f,
                vp->Pos.y + (vp->Size.y - GRID_PX_H) * 0.5f
            );
            ImGui::SetNextWindowPos(pos);
            ImGui::SetNextWindowSize(ImVec2(GRID_PX_W, GRID_PX_H));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing,    ImVec2(0, 0));
            // Tight line spacing: ImGui's default line height is the font size
            // plus extra leading; force it to exactly the font size so 50 rows
            // of 8px text == 400 px tall with no overflow.
            ImGui::Begin("ScreenGrid", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoBringToFrontOnFocus);
            screen->Draw();
            ImGui::End();
            ImGui::PopStyleVar(3);

            ImGui::Render();
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(win);
        }
        return 0;
    }
  