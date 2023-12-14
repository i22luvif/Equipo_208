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

    # Agregar visualizar_test.cc
    add_executable(visualizar_test ${SOURCE_FILES} tests/visualizar_test.cc)
    target_include_directories(visualizar_test PRIVATE include)
    target_link_libraries(visualizar_test gtest gtest_main)
    add_test(visualizar_test visualizar_test)

    # Agregar uso_usuario_test.cc
    add_executable(uso_usuario_test ${SOURCE_FILES} tests/uso_usuario_test.cc)
    target_include_directories(uso_usuario_test PRIVATE include)
    target_link_libraries(uso_usuario_test gtest gtest_main)
    add_test(uso_usuario_test uso_usuario_test)

    # Agregar gestionar_actividades_test.cc
    add_executable(gestionar_actividades_test ${SOURCE_FILES} tests/gestionar_actividades_test.cc)
    target_include_directories(gestionar_actividades_test PRIVATE include)
    target_link_libraries(gestionar_actividades_test gtest gtest_main)
    add_test(gestionar_actividades_test gestionar_actividades_test)

endif()
