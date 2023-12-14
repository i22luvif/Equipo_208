cmake_minimum_required(VERSION 3.5)
project(modio)
set(CMAKE_CXX_STANDARD 11)

# Configuración de la ejecución de pruebas
if(test AND test STREQUAL "on")
    message("Testing enabled")

    # Configurar GoogleTest
    add_subdirectory(ext/googletest)
    enable_testing()
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    # Configurar archivos de implementación
    set(SOURCE_FILES
        src/usuario.cc
        src/actividad.cc
        src/inicioSesion.cc
        src/organizador.cc
    )

    # Configurar archivos de prueba
    add_executable(usuario_test ${SOURCE_FILES} tests/usuario_test.cc)
    target_include_directories(usuario_test PRIVATE include)
    target_link_libraries(usuario_test gtest gtest_main)
    add_test(usuario_test usuario_test)

    add_executable(actividad_test ${SOURCE_FILES} tests/actividad_test.cc)
    target_include_directories(actividad_test PRIVATE include)
    target_link_libraries(actividad_test gtest gtest_main)
    add_test(actividad_test actividad_test)

    add_executable(inicioSesion_test ${SOURCE_FILES} tests/inicioSesion_test.cc)
    target_include_directories(inicioSesion_test PRIVATE include)
    target_link_libraries(inicioSesion_test gtest gtest_main)
    add_test(inicioSesion_test inicioSesion_test)

    add_executable(organizador_test ${SOURCE_FILES} tests/organizador_test.cc)
    target_include_directories(organizador_test PRIVATE include)
    target_link_libraries(organizador_test gtest gtest_main)
    add_test(organizador_test organizador_test)
endif()
