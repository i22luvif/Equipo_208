#include <gtest/gtest.h>
#include "../include/organizador.h"

TEST(OrganizadorTest1, CrearActividad) {
    // Crear una instancia de Organizador
    Organizador organizador("organizador", "contrasena");

    // Crear un vector de actividades
    std::vector<Actividad> actividades;

    // Simular la creación de una nueva actividad por parte del organizador
    Actividad nuevaActividad = Organizador::crearActividad();
    actividades.push_back(nuevaActividad);

    // Verificar que la actividad se haya agregado correctamente
    ASSERT_EQ(1, actividades.size());
    std::cout<<"Actividad agregada con exito\n";    //Si se imprime el mensaje es que ha pasado el assert

}

TEST(OrganizadorTest2, EliminarActividad) {
    // Crear una instancia de Organizador
    Organizador organizador("organizador", "contrasena");

    std::vector<Actividad> actividades;
    Actividad nuevaActividad = Organizador::crearActividad();
    actividades.push_back(nuevaActividad);

    // Simular la eliminación de la actividad por parte del organizador
    Organizador::eliminarActividad(actividades);
    
    // Verificar que la actividad se haya eliminado correctamente
    ASSERT_EQ(0, actividades.size());
    std::cout<<"Actividad eliminada con exito\n";    //Si se imprime el mensaje es que ha pasado el assert
}