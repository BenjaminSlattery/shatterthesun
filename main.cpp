#include "masterheader.h"
  #include <iostream>
  #include <string>
  #include <vector>
  #include "screen.h"

  #include "imgui.h"
  #include "imgui_impl_glfw.h"
  #include "imgui_impl_opengl3.h"
  #include <GLFW/glfw3.h>

  using namespace std;

  int main() {

      glfwInit();
      GLFWwindow* win = glfwCreateWindow(800, 600, "ImGui Demo", nullptr, nullptr);
      glfwMakeContextCurrent(win);

      Screen *screen = new Screen();

      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
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
  