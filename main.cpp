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

    myfile.open ("resultados.txt");

    for (auto& file : std::__fs::filesystem::directory_iterator{"../archivos"}){

        auto t1_ciclo = Clock::now();

        std::fstream html_file;
        html_file.open(file.path().string(),std::ios::in); //Todos los nombres de los archivos

        //ACTIVIDAD 2

        std::string no_tag_file = "";

        std::string line;

        if (!html_file)
            std::cout << "file cannot open!";

        bool inside = false;
        while (getline(html_file, line))
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
        }
        std::cout<<no_tag_file << endl;
        //ACTIVIDAD 2

        //ACTIVIDAD 3

        std::ofstream outFile;

        //ESTE ES EL ARRAY DE NOMBRES DE ARCHIVOS file.path().string()

        outFile.open("file.txt"); //archivo de salida.

        std::stringstream ss;
        // Se copian todos los contenidos del archivo a un string de tipo StringStream.
        ss << html_file.rdbuf();
        // Se extrae el String del StringStream.
        std::string contents = ss.str();

        //Se imprime para ver si jala
        //std::cout << contents;

        // Se hace un vector del String creado previamente de los contenidos del archivo.
        std::vector<char> buff(contents.begin(), contents.end());

        //Se ordena el vector por orden alfabetico con la funcion sort
        sort(buff.begin(), buff.end());

        //Se escriben los datos al archivo de salida
        for(std::vector<char>::const_iterator i = buff.begin(); i != buff.end(); ++i) {
            outFile.fill(*i);
        }

        html_file.close();

        auto t2_ciclo = Clock::now();

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