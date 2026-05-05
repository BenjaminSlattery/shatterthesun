#pragma once
  #include "imgui.h"
  #include <algorithm>

  class Screen {
  public:
      int width = 80;
      int height = 50;
      char screen[80][50];

      Screen() {
          // Initialize so uninitialized memory doesn't render as garbage glyphs.
          for (int x = 0; x < width; x++)
              for (int y = 0; y < height; y++)
                  screen[x][y] = ' ';
          Update();
      }

      void Update() {
          // Border so the screen is visibly bounded; replace with game state later.
          for (int x = 0; x < width; x++) {
              screen[x][0] = '#';
              screen[x][height - 1] = '#';
          }
          for (int y = 0; y < height; y++) {
              screen[0][y] = '#';
              screen[width - 1][y] = '#';
          }
      }

      // Draw the 80x50 grid into the current ImGui window. Auto-scales the font
      // so the grid fills whatever space the host ImGui window provides — pair
      // with a fullscreen ImGui::Begin in main() and the grid fills the OS window.
      void Draw() {
          const ImVec2 avail = ImGui::GetContentRegionAvail();
          const float baseCharW = ImGui::CalcTextSize("M").x;
          const float baseCharH = ImGui::GetTextLineHeight();
          if (baseCharW > 0.0f && baseCharH > 0.0f) {
              const float scaleX = avail.x / (baseCharW * (float)width);
              const float scaleY = avail.y / (baseCharH * (float)height);
              const float scale = std::max(0.1f, std::min(scaleX, scaleY));
              ImGui::SetWindowFontScale(scale);
          }
          // Origin convention: screen[x][0] is the BOTTOM row, screen[x][height-1]
          // is the TOP. Iterate rows top-to-bottom on screen by walking y from
          // height-1 down to 0, so the visual layout matches a math/Cartesian
          // coordinate system rather than a top-left raster.
          char rowBuf[81];
          rowBuf[width] = '\0';
          for (int y = height - 1; y >= 0; y--) {
              for (int x = 0; x < width; x++) rowBuf[x] = screen[x][y];
              ImGui::TextUnformatted(rowBuf, rowBuf + width);
          }
          ImGui::SetWindowFontScale(1.0f);
      }
  };
  