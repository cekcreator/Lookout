#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include "../Planets/AllPlanets.h"
#include "../helpers/units.h"
#include "Lookout.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <algorithm>
#include <chrono>
#include <cinder/CinderImGui.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <imgui/imgui_internal.h>
#include <sstream>

using namespace ci;
using namespace ci::app;

void Lookout::mouseDown(MouseEvent event)
{
    // if (uiWantsMouse()) return;
    mCamUi.mouseDown(event);
    mMouseActive = true;
    mCursorPrev = event.getPos();
}

void Lookout::mouseDrag(MouseEvent event)
{
    // if (uiWantsMouse()) return;
    mCamUi.mouseDrag(event);
    if (!mMouseActive) return;

    vec2 delta = vec2(event.getPos() - mCursorPrev);
    mYaw -= delta.x * mMouseSens;
    mPitch -= delta.y * mMouseSens;

    mPitch = std::clamp(mPitch, -glm::half_pi<float>(), glm::half_pi<float>());
    mCursorPrev = event.getPos();
}

void Lookout::mouseUp(MouseEvent event)
{
    mCamUi.mouseUp(event);
    mMouseActive = false;
}

void Lookout::keyDown(KeyEvent event)
{
    mActiveKeys.insert(event.getCode());
}

void Lookout::keyUp(KeyEvent event)
{
    mActiveKeys.erase(event.getCode());
}

void Lookout::setup()
{
    mCam.setPerspective(45.0f, getWindowAspectRatio(), 0.01f, 1000.0f);
    // mCam.lookAt(vec3(500, 500, 500), vec3(0, 0, 0));
    mCam.lookAt( vec3( 200, 200, 200 ), vec3( 0 ) );
    mCamUi = CameraUi(&mCam, getWindow(), -1);
    // WindowRef window = app::getWindow();
    // ImGui::Options options = ImGui::Options();
    // options.window(window, 1);
    // ImGui::Initialize(options);

}

void Lookout::update()
{
    auto sun = std::make_unique<Planet::Sun>(dvec3(0, 0, 0), units::sunRadius, 1.989e30);
    sun->update();
    mPlanets.push_back(std::move(sun));
}

void Lookout::draw() // main
{
    gl::clear(Color(0, 0, 0));
    gl::enableDepthRead();
    gl::enableDepthWrite();
    gl::setMatrices(mCam);

    // ImGui::Begin("Hello World");
    // ImGui::Text("Solar System");
    // ImGui::End();

    // ImGuiIO& io = ImGui::GetIO(); (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Always);
    //
    // ImGui::NewFrame();
    //
    // bool show_demo_window = true;
    // ImGui::ShowDemoWindow(&show_demo_window);

    mPlanets[0]->draw();
}

CINDER_APP(Lookout, RendererGl)