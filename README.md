# Lookout
3d visualizer of the milky way


## C++ Features being used
1. Namespaces
   * We use name spaces like Planet to keep all the planet objects and planet related code together within the same unit
2. Header guards
   * Pragma once and #ifndef to help prevent multiple inclusions of the same header
   * Faster builds
3. Smart points
   * RAII managed ownership no manual new/delete clear single owner semantics
4. Factory
   * AllPlanets has factory to create all the planets
