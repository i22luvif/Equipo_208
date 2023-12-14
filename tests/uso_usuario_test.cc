#include <gtest/gtest.h>
#include "../include/usuario.h"

TEST(UsuarioTest, Preinscribirse) {
    // Crear una instancia de Usuario
    Usuario usuario("NombreUsuario", "Contraseña");

    // Crear una actividad y añadirla al vector de actividades
    vector<Actividad> actividades;
    Actividad nuevaActividad("Actividad1", "Descripción1", "Ponente1", "FechaHora1", "Ubicacion1", 10, "Categoria1", 20.0);
    actividades.push_back(nuevaActividad);

    // Crear un stream stringstream para simular la entrada del usuario
    std::stringstream input_stream;
    input_stream << "1\n";  // Simula que el usuario ingresa '1' como número de actividad

    // Crear un stream stringstream para capturar la salida del usuario
    std::stringstream output_stream;

    // Redirigir entrada y salida estándar
    std::streambuf* old_cin = std::cin.rdbuf(input_stream.rdbuf());
    std::streambuf* old_cout = std::cout.rdbuf(output_stream.rdbuf());

    // Ejecutar el método preinscribirse
    usuario.preinscribirse(actividades);

    // Restaurar entrada y salida estándar
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    // Verificar que la salida contiene un mensaje indicando la preinscripción
    EXPECT_TRUE(output_stream.str().find("¡Preinscripción exitosa para la actividad 'Actividad1'!") != std::string::npos);

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
    Actividad::mostrarPreinscritos("Actividad1");

    // Obtener la salida capturada
    std::string output = testing::internal::GetCapturedStdout();

    // Verificar si la salida contiene los nombres de usuarios inscritos
    EXPECT_TRUE(output.find("Usuario1") != std::string::npos);
    EXPECT_TRUE(output.find("Usuario2") != std::string::npos);
    // ... Continuar verificando otros usuarios inscritos
}