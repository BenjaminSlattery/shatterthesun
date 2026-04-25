#pragma once

  // TinySoundFont — single-header soundfont synth.
  // TSF_IMPLEMENTATION must be defined in exactly one translation unit;
  // since masterheader.h is currently included only by main.cpp, that's fine here.
  #define TSF_IMPLEMENTATION
  #include "tsf.h"

  // SAM — software speech synthesizer (pure C).
  extern "C" {
      #include "sam.h"
      #include "reciter.h"
      #include "render.h"
  }
  