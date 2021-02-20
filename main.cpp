#include <iostream>
#include <chrono>
#include <iostream>
#include <fstream>

typedef std::chrono::high_resolution_clock Clock;




int main()
{
    auto t1 = Clock::now();     //Se incia el reloj del tiempo total de ejecución.

    std::ofstream myfile;

    myfile.open ("resultados.txt");     //Se abre el archivo para guardar los resultados.
    for (auto& file : std::__fs::filesystem::directory_iterator{"../archivos"}){

        auto t1_ciclo = Clock::now();   //Se incia el reloj para medir la duración de apertura de archivos.

        std::ofstream html_file;
        html_file.open(file.path().string());  //Se abre el archivo.

        //********ACTIVIDAD 2************



        //*******ACTIVIDAD 2**************


        html_file.close();//Se cierra el archivo.

        auto t2_ciclo = Clock::now();   //Se termina el reloj para medir la duración de apertura de archivos.

        auto time_elapsed_cycle = (std::chrono::duration_cast<std::chrono::microseconds>(t2_ciclo - t1_ciclo).count());

        myfile << file.path().string() << " " << time_elapsed_cycle << " microsegundos" << std::endl;
    }
    myfile.close(); //Se cierra el archivo para guardar los resultados.


    auto t2 = Clock::now();     //Se deja de medir el tiempo total de ejecución.


    //Devuelve el tiempo que tardó el algoritmo en milisegundos
    auto time_elapsed = (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());

    std::cout << "Tiempo total: "
              << time_elapsed
              << " milisegundos" << std::endl;

}