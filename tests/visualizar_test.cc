#include <gtest/gtest.h>
#include "../include/actividad.h"


TEST(ActividadTest, Mostrar) {
    // Crear una instancia de Actividad con valores conocidos
    Actividad actividad("NombreActividad", "Descripción", "Ponente", "Fecha", "Ubicacion", 10, "Categoria", 20.0);

    // Redirigir la salida estándar a un stringstream para capturarla
    std::ostringstream output;
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // Llamar a la función mostrar con la actividad
    std::vector<Actividad> actividades = {actividad};
    Actividad::mostrar(actividades);

    // Restaurar la salida estándar
    std::cout.rdbuf(coutBuffer);

    // Verificar que la salida contiene la información esperada
    std::string expectedOutput = 
        "\nNombre: NombreActividad\n"
        "Descripción: Descripción\n"
        "Ponente: Ponente\n"
        "Fecha y Hora: Fecha\n"
        "Ubicación: Ubicacion\n"
        "Plazas Disponibles: 10\n"
        "Categoría: Categoria\n"
        "Precio: 20 €\n";

    ASSERT_EQ(output.str(), expectedOutput);
}


TEST(ActividadTest, MostrarListaVacia) {
    // Redirigir la salida estándar para capturarla
    testing::internal::CaptureStdout();

    // Crear una lista vacía de actividades
    std::vector<Actividad> actividades;

    // Llamar a la función mostrar con la lista vacía
    Actividad::mostrar(actividades);

    // Obtener la salida capturada
    std::string output = testing::internal::GetCapturedStdout();

    // Restaurar la salida estándar
    testing::internal::CaptureStdout();  // Esto debería restablecer la salida estándar a la consola

    // Verificar que la salida contiene un mensaje indicando que no hay actividades
    std::string expectedOutput = "No hay actividades disponibles.\n";

    ASSERT_EQ(output, expectedOutput);
}
