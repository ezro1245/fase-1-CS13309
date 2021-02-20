#include <iostream>
#include <chrono>
#include <iostream>
#include <fstream>

typedef std::chrono::high_resolution_clock Clock;



int main()
{

    auto t1 = Clock::now();     //Tiempo inicial

    std::ofstream myfile;

    myfile.open ("resultados.txt");
    for (auto& file : std::__fs::filesystem::directory_iterator{"../archivos"}){

        auto t1_ciclo = Clock::now();

        std::ofstream html_file;
        html_file.open(file.path().string());
        html_file.close();

        auto t2_ciclo = Clock::now();

        auto time_elapsed_cycle = (std::chrono::duration_cast<std::chrono::microseconds>(t2_ciclo - t1_ciclo).count());

        myfile << file.path().string() << " " << time_elapsed_cycle << " microsegundos" << std::endl;
    }
    myfile.close();


    auto t2 = Clock::now();     //Tiempo final


    //Devuelve el tiempo que tardó el algoritmo en milisegundos
    auto time_elapsed = (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());

    std::cout << "Tiempo total: "
              << time_elapsed
              << " milisegundos" << std::endl;

}