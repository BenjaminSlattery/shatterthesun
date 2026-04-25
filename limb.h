#pragma once

  #include <vector>

  class Limb {
  public:
      int durability;
      std::vector<Limb> children;
  };
  