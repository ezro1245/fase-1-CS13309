#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>

typedef std::chrono::high_resolution_clock Clock;
using namespace std;

bool compareFunction (std::string a, std::string b) {return a<b;}

//Separa el string en palabras
vector<string> removeDupWord(string str)
{
    std::vector<std::string> list_words = {};

    string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            //cout << word << endl;
            list_words.push_back(word);
            word = "";
        }
        else {
            word = word + x;

        }
    }

    std::sort(list_words.begin(),list_words.end(),compareFunction);

    //TODO: Quitar espacios vacios

    return list_words;
}

int main(int argc, char** argv)
{
    auto t1 = Clock::now();     //Se incia el reloj del tiempo total de ejecución.

    std::ofstream myfile;

    myfile.open ("resultados.txt");     //Se abre el archivo para guardar los resultados.

    int iterator = 0;
    string base(".txt");

    //FOR PITUDO

    for (auto& file : std::__fs::filesystem::directory_iterator{"../archivos"}){
        iterator = iterator + 1;
        auto t1_ciclo = Clock::now();   //Se incia el reloj para medir la duración de apertura de archivos.

        //Se crea el file sin tangs
        ofstream("../sin_tags/"+to_string(iterator)+base);
        ofstream file_sin_tags;

        //Se quitan los tags html
        std::string no_tag_file = "";

        std::string line;
        std::fstream myfile2;
        myfile2.open(file.path().string(), std::ios::in);
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
        }

        //AQUI RECIBES EL VECTOR
        std::vector<std::string> html_file_sin_tags = removeDupWord(no_tag_file);



        file_sin_tags.open("../sin_tags/"+to_string(iterator)+base);

        for (std::vector<std::string>::iterator it=html_file_sin_tags.begin(); it!=html_file_sin_tags.end(); ++it)
            file_sin_tags << ' ' << *it << endl;

        //Se le mete al file sin tags el resultado del html
        file_sin_tags.close();

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