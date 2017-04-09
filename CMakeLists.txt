cmake_minimum_required(VERSION 3.4)

# Déclaration du projet.
project(MyAdBlock)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Génération de liste des fichiers sources à compiler.
file(
    GLOB_RECURSE
    source_files
    src/*
)

# Déclaration de l'éxécutable
add_executable(
    MyAdBlock
    ${source_files}
)
