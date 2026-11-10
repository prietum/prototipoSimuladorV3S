cmake_minimum_required(VERSION 4.2.3)
project(prototipo)

#Esse comando compartilha com '.clangd' (exporta) os diretórios onde procurar headers.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_Declare(raygui
    GIT_REPOSITORY https://github.com/raysan5/raygui.git
    GIT_TAG master
)
FetchContent_Declare(box3d
    GIT_REPOSITORY https://github.com/erincatto/box3d.git
    GIT_TAG main
)

FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(raygui)
FetchContent_MakeAvailable(box3d)

##Cria biblioteca 'raygui', que permite desenhar botões e outros elementos de interface.
##Como se trata de um único arquivo '.h', chamamos de 'single-file header library'.
##Este é um dos casos em que se utiliza o modo INTERFACE ao contrário de PRIVATE ou PUBLIC.
##  PRIVATE: "Compilo, mas não passo meus requerimentos para baixo."
##  PUBLIC: "Compilo e passo meus requerimentos para baixo."
##  INTERFACE: "Não compilo, mas passo meus requerimentos para baixo." (não se compila headers.)
add_library(raygui INTERFACE)
target_include_directories(raygui INTERFACE ${raygui_SOURCE_DIR}/src)

add_executable(main src/main.c src/sim.c src/gui.c)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE box3d raylib raygui)