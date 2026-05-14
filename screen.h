#pragma once
    #include "imgui.h"
    #include <algorithm>
    #include <string>

    class Screen {
    public:
        static const int WIDTH = 80;
        static const int HEIGHT = 50;
        // Each cell holds a UTF-8 glyph (1+ bytes). Using std::string instead of
        // char so multi-byte box-drawing characters (═ ║ ╔ ╝ etc., 3 bytes each
        // in UTF-8) survive intact — assigning '═' to a char would truncate to
        // a single byte and ImGui would render '?' for the invalid sequence.
        std::string screen[WIDTH][HEIGHT];

        Screen() {
            for (int x = 0; x < WIDTH; x++)
                for (int y = 0; y < HEIGHT; y++)
                    screen[x][y] = " ";
            Update();
        }

        void Update() {
          for (int x = 1; x < WIDTH-1; x++) {
              screen[x][0] = "═";
              screen[x][HEIGHT-1] = "═";
              if (x < 20)
                  screen[x][17] = "═";
              else
                  screen[x][27] = "═";
          }

          for (int y = 1; y < HEIGHT-1; y++) {
              screen[0][y] = "║";
              screen[WIDTH-1][y] = "║";
              screen[20][y] = "║";
          }

          screen[20][17] = "╣";
          screen[20][27] = "╠";
          screen[0][0] = "╚";
          screen[0][HEIGHT-1] = "╔";
          screen[WIDTH-1][0] = "╝";
          screen[WIDTH-1][HEIGHT-1] = "╗";
      }

        // Draw the 80x50 grid into the current ImGui window. Auto-scales the
        // font so the grid fills whatever space the host ImGui window provides —
        // pair with a fullscreen ImGui::Begin in main() and the grid fills the
        // OS window.
        void Draw() {
            const ImVec2 avail = ImGui::GetContentRegionAvail();
            const float baseCharW = ImGui::CalcTextSize("M").x;
            const float baseCharH = ImGui::GetTextLineHeight();
            if (baseCharW > 0.0f && baseCharH > 0.0f) {
                const float scaleX = avail.x / (baseCharW * (float)WIDTH);
                const float scaleY = avail.y / (baseCharH * (float)HEIGHT);
                const float scale = std::max(0.1f, std::min(scaleX, scaleY));
                ImGui::SetWindowFontScale(scale);
            }
            // Origin convention: screen[x][0] is the BOTTOM row, screen[x][HEIGHT-1]
            // is the TOP. Iterate rows top-to-bottom on screen by walking y from
            // HEIGHT-1 down to 0, so the visual layout matches a math/Cartesian
            // coordinate system rather than a top-left raster.
            std::string rowBuf;
            rowBuf.reserve(WIDTH * 4); // worst case: 4 UTF-8 bytes per glyph
            for (int y = HEIGHT - 1; y >= 0; y--) {
                rowBuf.clear();
                for (int x = 0; x < WIDTH; x++) {
                    // Empty cell guard — append a space rather than nothing, so
                    // column alignment is preserved.
                    rowBuf.append(screen[x][y].empty() ? " " : screen[x][y]);
                }
                ImGui::TextUnformatted(rowBuf.data(), rowBuf.data() + rowBuf.size());
            }
            ImGui::SetWindowFontScale(1.0f);
        }
    };
  