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

      // Window flags that turn an ImGui window into a borderless fullscreen
      // viewport — no title bar, no resize handle, no padding, no scrollbars,
      // so the Screen grid inside genuinely fills the OS window edge-to-edge.
      const ImGuiWindowFlags screenFlags =
          ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
          ImGuiWindowFlags_NoMove     | ImGuiWindowFlags_NoCollapse |
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
          ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

      while (!glfwWindowShouldClose(win)) {
          glfwPollEvents();
          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplGlfw_NewFrame();
          ImGui::NewFrame();

          // Pin the ImGui window to the full framebuffer every frame so it
          // tracks user resizes of the OS window.
          int fbW, fbH;
          glfwGetFramebufferSize(win, &fbW, &fbH);
          ImGui::SetNextWindowPos(ImVec2(0, 0));
          ImGui::SetNextWindowSize(ImVec2((float)fbW, (float)fbH));

          ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
          ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
          ImGui::Begin("Screen", nullptr, screenFlags);
          screen->Draw();
          ImGui::End();
          ImGui::PopStyleVar(2);

          ImGui::Render();
          glClear(GL_COLOR_BUFFER_BIT);
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
          glfwSwapBuffers(win);
      }

      delete screen;
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
      glfwDestroyWindow(win);
      glfwTerminate();
      return 0;
  }
  