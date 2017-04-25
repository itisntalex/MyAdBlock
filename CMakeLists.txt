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

# Description de la procédure d'empaquettage.
install(FILES LICENSE README.md CMakeLists.txt DESTINATION ./)
install(FILES assets/blocked.txt DESTINATION ./bin/assets/)

install(DIRECTORY docs/ DESTINATION doc/)
install(DIRECTORY src/ DESTINATION src/)
install(DIRECTORY wireshark/ DESTINATION wireshark/)

set(CPACK_GENERATOR "TGZ")

include(CPack)
