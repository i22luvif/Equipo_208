#include <gtest/gtest.h>
#include "../include/actividad.h"

TEST(ActividadTest, GuardarActividad) {
    // Crear una instancia de Actividad
    Actividad nuevaActividad("NombreActividad", "Descripción", "Ponente", "Fecha", "Ubicacion", 10, "Categoria", 20.0);

    // Definir un nombre de archivo temporal para las pruebas
    const std::string nombreArchivoTemp = "actividades_temp.txt";

    // Guardar la actividad en el archivo temporal
    Actividad::guardarActividad(nuevaActividad, nombreArchivoTemp);

    // Verificar si la actividad se guardó correctamente
    std::ifstream archivo(nombreArchivoTemp);
    ASSERT_TRUE(archivo.is_open());

    // Limpiar el archivo temporal
    archivo.close();
    std::remove(nombreArchivoTemp.c_str());
}

// Test para mostrar inscritos en una actividad
TEST(ActividadTest, MostrarPreinscritos) {
    // Crear una instancia de Actividad
    Actividad::guardarActividad(Actividad("Actividad1", "Descripción1", "Ponente1", "FechaHora1", "Ubicacion1", 10, "Categoria1", 20.0), "actividades.txt");

    // Supongamos que hay usuarios inscritos en "preinscritos.txt"
    ofstream archivoPreinscritos("preinscritos.txt");
    archivoPreinscritos << "Usuario1 - Actividad1\n";
    archivoPreinscritos << "Usuario2 - Actividad1\n";
    archivoPreinscritos.close();

    // Capturar la salida estándar para verificarla
    testing::internal::CaptureStdout();
    
    // Ejecutar la función para mostrar inscritos en "Actividad1"
    Actividad::mostrarInscritos("Actividad1");

    // Obtener la salida capturada
    std::string output = testing::internal::GetCapturedStdout();

    // Verificar si la salida contiene los nombres de usuarios inscritos
    EXPECT_TRUE(output.find("Usuario1") != std::string::npos);
    EXPECT_TRUE(output.find("Usuario2") != std::string::npos);
    // ... Continuar verificando otros usuarios inscritos
}
