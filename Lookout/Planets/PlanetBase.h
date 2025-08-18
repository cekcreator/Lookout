#pragma once
#include "../helpers/units.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <iostream>

namespace Planet
{
    using namespace ci;

    class PlanetBase
    {
      public:
        virtual void draw()   = 0;
        virtual void update() = 0;
        virtual dvec3 getPlanetPosition_Ws() = 0;
        virtual ~PlanetBase() = default;
        double radius_Ws;

        PlanetBase(const vec3& position_Ws, double radius_km, double mass_kg, double scaleFactor = 1.0)
            : position_Ws(position_Ws)
            , radius_km(radius_km)
            , mass_kg(mass_kg)
            , scaleFactor(scaleFactor)
        {
          radius_Ws = units::planetSizeScale * radius_km * scaleFactor;
        }

      protected:
        PlanetBase(const PlanetBase&)            = delete;
        PlanetBase(PlanetBase&&)                 = delete;
        PlanetBase& operator=(const PlanetBase&) = delete;
        PlanetBase& operator=(PlanetBase&&)      = delete;

        // Physics (heliocentric, kilometers)
        double mass_kg{0.0};
        double radius_km{0.0};

        // World space
        dvec3  position_Ws;

        double scaleFactor = 1.0;

    };
} // namespace Planet