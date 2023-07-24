cmake_minimum_required(VERSION 3.25)
project(ParticleSimulation)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 CONFIG REQUIRED)

add_executable(ParticleSimulation
        src/imgui/imgui_impl_sdlrenderer2.cpp
        src/imgui/imgui_impl_sdlrenderer2.h
        src/imgui/imgui_impl_sdl2.cpp
        src/imgui/imgui_impl_sdl2.h
        src/imgui/imconfig.h
        src/imgui/imgui.cpp
        src/imgui/imgui.h
        src/imgui/imgui_demo.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_internal.h
        src/imgui/imgui_tables.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imstb_rectpack.h
        src/imgui/imstb_textedit.h
        src/imgui/imstb_truetype.h
        src/Particle.cpp
        src/Particle.h
        src/ParticleSimulation.cpp
        src/Screen.cpp
        src/Screen.h
        src/Swarm.cpp
        src/Swarm.h
        src/Vec.cpp
        src/Vec.h)

target_link_libraries(ParticleSimulation PRIVATE SDL2::SDL2)
target_compile_definitions(ParticleSimulation PRIVATE SDL_MAIN_HANDLED)
