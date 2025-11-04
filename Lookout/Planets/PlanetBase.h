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
        PlanetBase(const PlanetBase&)            = delete; // disables copying
        PlanetBase& operator=(const PlanetBase&) = delete;

        virtual void   draw()                 = 0;
        virtual void   update()               = 0;
        virtual dvec3  getPlanetPosition_Ws() = 0;
        virtual double getPlanetRadius_Ws()   = 0;
        virtual ~PlanetBase()                 = default;

        PlanetBase(double distFromSun, double radius_km, double mass_kg)
            : distFromSun(distFromSun)
            , radius_km(radius_km)
            , mass_kg(mass_kg)
        {
        }

      protected:
        PlanetBase(PlanetBase&&) noexcept            = default; // enables assignment
        PlanetBase& operator=(PlanetBase&&) noexcept = default;

        // Physics (heliocentric, kilometers)
        double mass_kg{0.0};
        double radius_km{0.0};
        double distFromSun{0.0};

        // World space
        dvec3 position_Ws;
        double radius_Ws;
    };
} // namespace Planet