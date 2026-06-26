#pragma once
#ifndef THICKLINE_H
#define THICKLINE_H

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

namespace tl {

class ThickLine
{
  public:
    ThickLine(vec3 a, vec3 b, float width, Color color)
        : mA(a), mB(b), mWidth(width), mColor(color)
    {
        mGlsl = gl::GlslProg::create(loadAsset("thickline.vert"), loadAsset("thickline.frag"));
        rebuild();
    }

    void setWidth(float w) { mWidth = w; }
    void setPoints(vec3 a, vec3 b) { mA = a; mB = b; rebuild(); }

    void draw()
    {
        gl::ScopedGlslProg shader(mGlsl);
        mGlsl->uniform("uResolution", vec2(getWindowSize()));
        mGlsl->uniform("uWidth",      mWidth);
        mGlsl->uniform("uColor",      vec4(mColor.r, mColor.g, mColor.b, 1.0f));
        mBatch->draw();
    }

  private:
    struct Vertex {
        vec3  pos;
        vec3  other;
        float sign;
    };

    void rebuild()
    {
        // 4 verts: A+, A-, B+, B-
        std::vector<Vertex> verts = {
            { mA, mB, +1.0f },
            { mA, mB, -1.0f },
            { mB, mA, +1.0f },
            { mB, mA, -1.0f },
        };

        std::vector<uint32_t> indices = { 0, 1, 2,  1, 3, 2 };

        auto layout = geom::BufferLayout();
        layout.append(geom::Attrib::CUSTOM_0, 3, sizeof(Vertex), offsetof(Vertex, pos));
        layout.append(geom::Attrib::CUSTOM_1, 3, sizeof(Vertex), offsetof(Vertex, other));
        layout.append(geom::Attrib::CUSTOM_2, 1, sizeof(Vertex), offsetof(Vertex, sign));

        auto vbo = gl::Vbo::create(GL_ARRAY_BUFFER,   verts,   GL_DYNAMIC_DRAW);
        auto ibo = gl::Vbo::create(GL_ELEMENT_ARRAY_BUFFER, indices, GL_STATIC_DRAW);

        auto mesh = gl::VboMesh::create(
            4, GL_TRIANGLES,
            { { layout, vbo } },
            6, GL_UNSIGNED_INT, ibo
        );

        mBatch = gl::Batch::create(mesh, mGlsl, {
            { geom::Attrib::CUSTOM_0, "aPos"   },
            { geom::Attrib::CUSTOM_1, "aOther" },
            { geom::Attrib::CUSTOM_2, "aSign"  },
        });
    }

    vec3  mA, mB;
    float mWidth;
    Color mColor;

    gl::GlslProgRef mGlsl;
    gl::BatchRef    mBatch;
};

} // namespace tl

#endif // THICKLINE_H
