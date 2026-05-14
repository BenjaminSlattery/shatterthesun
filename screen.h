#pragma once
    #include "imgui.h"
    #include <string>

    class Screen {
    public:
        static const int WIDTH = 80;
        static const int HEIGHT = 50;
        static const int RIGHTVERTSPLIT = 27;
        static const int LEFTVERTSPLIT = 5;
        static const int HORIZSPLIT = 30;
        // Each cell holds a UTF-8 glyph (1+ bytes). std::string instead of char
        // so multi-byte box-drawing characters (═ ║ ╔ ╝ etc., 3 bytes each in
        // UTF-8) survive intact.
        std::string screen[WIDTH][HEIGHT];
        ImU32 screen_color[WIDTH][HEIGHT];

        Screen() {
            for (int x = 0; x < WIDTH; x++)
                for (int y = 0; y < HEIGHT; y++) {
                    screen[x][y] = " ";
                
            Update();
        }

        void Update() {
            for (int x = 1; x < WIDTH - 1; x++) {
                screen[x][0] = "═";
                screen[x][HEIGHT - 1] = "═";
                if (x < HORIZSPLIT)
                    screen[x][LEFTVERTSPLIT] = "═";
                else
                    screen[x][RIGHTVERTSPLIT] = "═";
            }

            for (int y = 1; y < HEIGHT - 1; y++) {
                screen[0][y] = "║";
                screen[WIDTH - 1][y] = "║";
                screen[HORIZSPLIT][y] = "║";
            }

            screen[HORIZSPLIT][HEIGHT-1] = "╣";
            screen[HORIZSPLIT][0] = "╠";
            screen[HORIZSPLIT][LEFTVERTSPLIT] = "╣";
            screen[HORIZSPLIT][RIGHTVERTSPLIT] = "╠";
            screen[0][0]   = "╚";
            screen[0][HEIGHT - 1]            = "╔";
            screen[WIDTH - 1][0]             = "╝";
            screen[WIDTH - 1][HEIGHT - 1]    = "╗";
        }

        // Draw the 80x50 grid into the current ImGui window at NATIVE 1:1 pixel
        // scale — each glyph is exactly 8×8 pixels, total render area is
        // 640×400. Caller is responsible for sizing/centering the host ImGui
        // window. No SetWindowFontScale: scaling makes the bitmap font blurry
        // and breaks the "each cell is exactly 8×8" contract.
        void Draw() {
            // Force line height to exactly the font size (8 px) so 50 rows fit
            // in 400 px with no extra leading.
            const float lineH = 8.0f;
            // Origin convention: screen[x][0] is the BOTTOM row, so we iterate
            // y from HEIGHT-1 down to 0 to render top-to-bottom on screen.
            std::string rowBuf;
            rowBuf.reserve(WIDTH * 4); // worst case: 4 UTF-8 bytes per glyph
            const ImVec2 origin = ImGui::GetCursorScreenPos();
            ImDrawList* dl = ImGui::GetWindowDrawList();
            const ImU32 col = ImGui::GetColorU32(ImGuiCol_Text);
            ImFont* font = ImGui::GetFont();
            int visRow = 0;
            for (int y = HEIGHT - 1; y >= 0; y--, visRow++) {
                rowBuf.clear();
                for (int x = 0; x < WIDTH; x++) {
                    rowBuf.append(screen[x][y].empty() ? " " : screen[x][y]);
                }
                // Draw via DrawList instead of TextUnformatted so we control
                // exact per-row Y position (8 px stride) without ImGui's
                // built-in line-spacing padding.
                dl->AddText(font, 8.0f,
                    ImVec2(origin.x, origin.y + (float)visRow * lineH),
                    col, rowBuf.c_str(), rowBuf.c_str() + rowBuf.size());
            }
            // Advance cursor so ImGui knows the window's content extent.
            ImGui::Dummy(ImVec2((float)WIDTH * 8.0f, (float)HEIGHT * lineH));
        }
    };
  