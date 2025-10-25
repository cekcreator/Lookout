//
// Created by Caleb Kumar on 8/17/25.
//

#ifndef ALLPLANETS_H
#define ALLPLANETS_H
#include "Earth/Earth.h"
#include "Jupiter/Jupiter.h"
#include "Mars/Mars.h"
#include "Mercury/Mercury.h"
#include "Neptune/Neptune.h"
#include "Saturn/Saturn.h"
#include "Sun/Sun.h"
#include "Uranus/Uranus.h"
#include "Venus/Venus.h"

#include <memory>
#include <stdexcept>

namespace Planet
{
    enum class AllPlanets
    {
        Sun,
        Mercury,
        Venus,
        Earth,
        Mars,
        Jupiter,
        Saturn,
        Uranus,
        Neptune
    };

    struct PlanetSpec
    {
        AllPlanets  planet;
        const char* name;
        double      distFromSun_km;
        double      radius_km;
        double      mass_kg;
        double      scaleFactor = 100;
    };

    inline const PlanetSpec kSpecs[] = {
        {AllPlanets::Sun, "Sun", 0.0, 695700, 1.989e30},
        {AllPlanets::Mercury, "Mercury", 5.8e7, 2440.0, 3.30e23},
        {AllPlanets::Venus, "Venus", 1.08e8, 6052.0, 4.87e24},
        {
            AllPlanets::Earth,
            "Earth",
            1.50e8,
            6371.0,
            5.97e24,
        },
        {AllPlanets::Mars, "Mars", 2.27e8, 3389.0, 6.42e23},
        {AllPlanets::Jupiter, "Jupiter", 7.78e8, 69911.0, 1.90e27},
        {AllPlanets::Saturn, "Saturn", 1.433e9, 58232.0, 5.68e26},
        {AllPlanets::Uranus, "Uranus", 2.872e9, 25362.0, 8.68e25},
        {AllPlanets::Neptune, "Neptune", 4.495e9, 24622.0, 1.02e26},
    };

    inline std::unique_ptr<PlanetBase>
    createPlanet(const PlanetSpec& s, const glm::dvec3& sunPos, double orbitSizeScale)
    {
        // const double distWs = s.distFromSun_km * orbitSizeScale;
        // const dvec3  posWs  = sunPos + dvec3(distWs, 0.0, 0.0);

        switch (s.planet)
        {
        case AllPlanets::Sun:
            return std::make_unique<Sun>(s.distFromSun_km, s.radius_km, s.mass_kg);
        case AllPlanets::Mercury:
            return std::make_unique<Mercury>(s.distFromSun_km, s.radius_km, s.mass_kg);
        case AllPlanets::Venus:
            return std::make_unique<Venus>(s.distFromSun_km, s.radius_km, s.mass_kg);
        case AllPlanets::Earth:
            return std::make_unique<Earth>(s.distFromSun_km, s.radius_km, s.mass_kg);
        case AllPlanets::Mars:
            return std::make_unique<Mars>(s.distFromSun_km, s.radius_km, s.mass_kg);
        case AllPlanets::Jupiter:
            return std::make_unique<Jupiter>(s.distFromSun_km, s.radius_km, s.mass_kg);
        case AllPlanets::Saturn:
            return std::make_unique<Saturn>(s.distFromSun_km, s.radius_km, s.mass_kg);
        case AllPlanets::Uranus:
            return std::make_unique<Uranus>(s.distFromSun_km, s.radius_km, s.mass_kg);
        case AllPlanets::Neptune:
            return std::make_unique<Neptune>(s.distFromSun_km, s.radius_km, s.mass_kg);
        }
        throw std::runtime_error("Unknown PlanetKind");
    }

    // !! no const here - operator= for std::vector requires the right-hand side to be movable — and
    // the const qualifier disables moving.
    inline std::vector<std::unique_ptr<PlanetBase>> getAllPlanets()
    {
        std::vector<std::unique_ptr<PlanetBase>> planets;
        planets.reserve(std::size(kSpecs));
        auto sun = std::make_unique<Sun>(0.0, units::sunRadius, 1.989e30);
        dvec3 sunPos = sun->getPlanetPosition_Ws();
        for (const auto& spec : kSpecs)
        {
            planets.emplace_back(createPlanet(spec, sunPos, units::orbitSizeScale));
        }
        return planets;
    }
} // namespace Planet
#endif // ALLPLANETS_H
