#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <sstream>

typedef std::chrono::high_resolution_clock Clock;
using namespace std;

int main(int argc, char** argv)
{
    auto t1 = Clock::now();     //Se incia el reloj del tiempo total de ejecución.

    std::ofstream myfile;

    myfile.open ("resultados.txt");     //Se abre el archivo para guardar los resultados.
    for (auto& file : std::__fs::filesystem::directory_iterator{"../archivos"}){

        auto t1_ciclo = Clock::now();   //Se incia el reloj para medir la duración de apertura de archivos.


        auto t2_ciclo = Clock::now();   //Se termina el reloj para medir la duración de apertura de archivos.

        auto time_elapsed_cycle = (std::chrono::duration_cast<std::chrono::microseconds>(t2_ciclo - t1_ciclo).count());

        myfile << file.path().string() << " " << time_elapsed_cycle << " microsegundos" << std::endl;
    }
    myfile.close(); //Se cierra el archivo para guardar los resultados.


    /*
     * TEST: En este codigo se lee el archivo 002.html que es uno que le añadi codigo manualmente
     * ya que chingaron su mare todos los html, se lee cada linea, dime si le entiendes a la logica
     */
    std::string no_tag_file = "";

    std::string line;
    std::fstream myfile2;
    myfile2.open("../archivos/002.html", std::ios::in);
    if (!myfile2)
        std::cout << "file cannot open!";

    bool inside = false;
    while (getline(myfile2, line))
    {
        for (char c : line) {
            if (c == '>'){
                inside = true;
                no_tag_file += " ";
            }
            else if (c == '<')
                inside = false;
            else if (inside)
                no_tag_file += c;
        }

        myfile2.close();

        //ACTIVIDAD 3 ************
        std::ifstream myfile2;

        myfile2.open("../archivos/002.html", std::ios::in); //Se abre el archivo

        std::ofstream outFile;

        outFile.open("file.txt",std::ios::in); //archivo de salida.

        std::stringstream ss;
        // Se copian todos los contenidos del archivo a un string de tipo StringStream.
        ss << myfile2.rdbuf();
        // Se extrae el String del StringStream.
        std::string contents = ss.str();
        //std::cout << contents;

        // Se hace un vector del String creado previamente de los contenidos del archivo.
        std::vector<char> buff(contents.begin(), contents.end());

        //Se ordena el vector por orden alfabetico con la funcion sort
        sort(buff.begin(), buff.end());

        //Se escriben los datos al archivo de salida
        for(std::vector<char>::const_iterator i = buff.begin(); i != buff.end(); ++i) {
            outFile.fill(*i);
        }
        //ACTIVIDAD 3 ********
    }

    std::cout << no_tag_file << endl;

    /*
     * TEST: fin del test
     *
     * TODO: meter esta madre en el ciclo de arriba
     * da como resultdo un string, ese estring lo podemos limpiar y meterlo en otro archivo o idealmente
     * ya con ese string procesar de una vez el orden alfabetico y meter eso a un file final
     */

    auto t2 = Clock::now();     //Se deja de medir el tiempo total de ejecución.


    //Devuelve el tiempo que tardó el algoritmo en milisegundos
    auto time_elapsed = (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count());

    std::cout << "Tiempo total: "
              << time_elapsed
              << " milisegundos" << std::endl;

}