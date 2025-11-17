#pragma once
#pragma once
#include "cinder/app/App.h"
#include "cinder/Perlin.h"
#include "cinder/gl/gl.h"
#include <iostream>

namespace ss
{
    class SpaceStation
    {
    public:
        gl::BatchRef box;
        gl::BatchRef asteroid;
        SpaceStation(const SpaceStation&)            = delete; // disables copying
        SpaceStation& operator=(const SpaceStation&) = delete;
        SpaceStation()
        {
            return;
        }

        void update()
        {
            auto cube = geom::WireCube().size(vec3(55, 45, 45)); // white cube
            auto shader = gl::getStockShader(gl::ShaderDef().color());
            box = gl::Batch::create(cube, shader);

            auto mesh = ci::geom::Icosphere().subdivisions(3);
            ci::TriMesh::Format fmt = ci::TriMesh::Format().positions().normals().colors(3);
            ci::TriMesh triMesh(mesh, fmt);
            auto* triMeshPos = triMesh.getPositions<3>();
            size_t count = mesh.getNumVertices();
            std::vector<Colorf> colors(count);
            for (size_t i = 0; i < count; i++) {
                vec3 &v = triMeshPos[i];
                if (v.y > 0.0f) {
                    v.y = 0.0f;
                    colors[i] = Colorf(0.8f, 0.7f, 0.4f);
                } else {
                    float n = Perlin().noise(v.x * 2.0f, v.y * 2.0f, v.z * 2.0f);
                    float bump = n * (1.0f + abs(v.y)) * 0.5f;
                    v += vec3(v.x * bump, v.y * bump, v.z * bump);

                    float t = clamp(abs(v.y) * 0.5f, 0.0f, 1.0f);
                    vec3 a(0.25f, 0.15f, 0.1f);
                    vec3 b(0.6f, 0.4f, 0.2f);

                    vec3 mixed = glm::mix(a, b, t);
                    colors[i] = Colorf(mixed.r, mixed.g, mixed.b);
                }
            }
            triMesh.appendColors(colors.data(), colors.size());
            asteroid = gl::Batch::create(triMesh, shader);

        }

        void draw()
        {

            {
                gl::ScopedModelMatrix scopedMatrix;
                gl::ScopedColor(Color(1,0,0));
                gl::translate(vec3(100,96,100));
                gl::rotate(vec3(75.10, -.10, 0.11));
                gl::ScopedColor scopedColor(Color(1,0,0));
                box->draw();
            }
            {
                gl::ScopedModelMatrix scopedMatrix;
                gl::translate(vec3(100,71.05,100));
                // gl::rotate(glm::angleAxis(glm::radians(60.0f), vec3(0,0,1)) );
                gl::rotate(vec3(75.10, 0, 0.10));
                gl::scale(vec3(55,55,55));
                asteroid->draw();
            }

        }
        // void getCenter();

        protected:
            SpaceStation(SpaceStation&&) noexcept            = default; // enables assignment
            SpaceStation& operator=(SpaceStation&&) noexcept = default;
    };
}