//
// Created by Caleb Kumar on 8/17/25.
//
#pragma once
namespace units
{
    constexpr double G         = 6.67430e-11;
    constexpr double c         = 299792458.0; // m/s
    constexpr double solarMass = 1.989e30;
    constexpr double M         = solarMass * 4297000.0;
    constexpr double sunRadius = 695'700; // km
    // distance to the furthest point on plutos orbit
    constexpr double furthestDistance = 4'498'396'441.0; // km
    constexpr double planetSizeScale  = 1'000 / sunRadius;
    constexpr double orbitSizeScale   = 18'000 / furthestDistance;
} // namespace units
