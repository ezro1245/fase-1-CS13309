#include <iostream>
#include <time.h>
#include <fstream>
#include <filesystem>

/*
    TODO:
    -Abrir path y leer archivos dentro
    -Abrir cada archivo
    -Cerrar cada archivo
    -Cronometrar cuanto tiempo tomo abrir y cerrar cada archivo
    -Cronometrar cuanto tardo toda la ejecucion completa
    -Guardar resultado en un archivo de texto   EJ- 001.html  0.10s
                                                tiempo total 3.40 segundos.
*/

using namespace std;

//**************Metodos**************
//readFile se encarga de abrir cada archivo individualmente y medir el tiempo que tarda en hacerlo.
double readFile(string path){
    double timeTotalApertura = 0;
    clock_t tiempoInicio = clock(); //se inicia el cronometraje para cada archivo
    ifstream archivo;       //se declara el paquete para abrir los archivos
    archivo.open(path, ios::app);
    if(archivo.fail()){
        cout << "El archivo no existe";
        exit(1);
    }

    else cout << path << " "; //se imprime para ver si funciona
    //std::cout << archivo.rdbuf();
    archivo.close(); //se cierra el archivo
    clock_t tiempoFin = clock(); //se termina de cronometrar el tiempo de apertura de los archivos
    double time = (double(tiempoFin - tiempoInicio) / CLOCKS_PER_SEC); //Se calcula el tiempo
    timeTotalApertura += time; //tiempo sumado de las aperturas

    //writeLog(path,time,timeTotalApertura);
    cout << "Tiempo de apertura: " << fixed  << time << endl;
    cout << "Tiempo total: " << timeTotalApertura <<endl;

    return timeTotalApertura;
}

/*
void writeLog(string basicString, time_t (*time)(time_t *const), double apertura) {
}

void writeLog(string path, double time, double timeTotalApertura){
    std::string stime( double time );
    std::string stotal( double timeTotalApertura );

    ofstream MyFile("resultados.txt");

    // Write to the file
    MyFile << path << stime << stotal;

    // Close the file
    MyFile.close();
}
*/

int main() {

    clock_t tiempoTotalInicio = clock(); //Tiempo total
    string path = "/Users/davidharos/CLionProjects/untitled/archivos"; //Directorio con los archivos
    double time_file = 0;
    for (auto& file : std::__fs::filesystem::directory_iterator{path}){  //Se abre todo el directorio
        time_file = time_file + readFile(file.path().string()); //Se envia al metodo para leerse
    }

    cout << "Tiempo total de apertura de archivos" << time_file;

    clock_t tiempoTotalFin = clock();

    double timeFINAL = (double(tiempoTotalFin - tiempoTotalInicio) / CLOCKS_PER_SEC);
    cout << "TIEMPO FINAL FINAL " << timeFINAL;
    return 0;
}

//ESTO ES DE LA ACTIVIDAD 2
/*
//Eliminar tags html
while (html.find("<") != string::npos)
{
    auto startpos = html.find ("<");
    auto endpos = html.find (">") + 1;

    if (endpos != string::npos)
    {
        html.erase(startpos, endpos - startpos);
    }
}
*/
