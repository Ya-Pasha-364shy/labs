#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <tuple>

// type alias
typedef unsigned int u_int;
typedef std::string str;

// создаем структуру для
// удобной записи и
// чтения из фалйа, а также для удобной передачи
// данных по ходу выполнения программы
struct Stroke {
    size_t lenght;
    str payload_data;

    Stroke(size_t* m_lenght, str& m_payload_data) {
        this->lenght = *m_lenght;
        this->payload_data = m_payload_data;
    }
};


// функция чтения из файла(.txt) и возврата данных в кортеже
std::tuple<std::vector<Stroke>, u_int> readTextAndRemember(str& file_name) {
    u_int rows = 0;
    str s;
    std::ifstream file(file_name.c_str());
    std::vector<Stroke> datas;

    // если файл открыт, читаем данные из файла и кладем их в массив
    if (file.is_open()) {
        while (true) {
            getline(file, s);

            rows++;

            size_t len = s.length();
            // перед тем как положить данные в массив, 
            // приводим наши данные к структуре
            datas.push_back(Stroke(&len, s));

            if (file.eof())
                break;
        }
    }
    else {
        std::cout << "File is closed!" << std::endl;
    }

    file.close();

    // возвращаем кортеж из двух элементов, 
    // где первый - данные из текстового файла
    // второй - количество строк
    return std::make_tuple(datas, rows);
}

// функция создания бинарного файла
str createBinaryFile(str& file_name) {

    u_int dot_ind = 0;
    
    for (dot_ind; ;dot_ind++) {
        if (file_name[dot_ind] == '.') 
            break;
    }
    // обрезаем значение file_name до точки
    str part1 = file_name.substr(0, dot_ind);

    str part2 = ".bin";
    // добавляем .bin к имени файла
    str binary_file_name = part1 + part2;

    // создаем бинарный файл
    std::ofstream fout;
    fout.open(binary_file_name);
    fout.close();

    // возвращаем имя бинарного файла
    return binary_file_name;

}

// функция записи в бинарный файл
void writeIntoBinary(str& file_name, std::vector<Stroke>& arr, u_int* rows) {

    const char* sep = " ";
    const char* endl = "\n";
    // с помощью потока ofstream будем записывать данные в файл
    std::ofstream foutb(file_name, std::ios::binary);
    
    // записываем в файл, до тех пор, пока не достигнем i == rows
    for (u_int i(0); i != *rows; i++) {
        size_t len = arr[i].lenght;
        // запись будет производиться с помощью получения данных из структуры
        const char* payload = arr[i].payload_data.c_str();

        foutb.write((char*)&len, sizeof(len));
        foutb.write((char*)&sep, sizeof(sep));      
        foutb.write((char*)&payload, sizeof(payload));
        foutb.write((char*)&endl, sizeof(endl));
    }
    // закрываем запись в потока
    foutb.close();

    return;
}

// функция чтения из бинарного файла
void readFromBinary(str& file_name, u_int* rows) {
    
    const char* sep = " ";
    const char* endl = "\n";

    // чтение из бинарного файла будет производиться 
    // с помощью потока ifstream
    std::ifstream in(file_name, std::ios::binary);
    size_t len = 0;
    const char* payload;

    for (u_int i(0); i != *rows; i++) {
        // считываем с помощью метода read из потока
        in.read((char*)&len, sizeof(len));
        in.read((char*)&sep, sizeof(sep));
        in.read((char*)&payload, sizeof(payload));
        in.read((char*)&endl, sizeof(endl));

        std::cout << len << sep << payload << endl;
    }
    // закрываем чтение из потока
    in.close();

    return;
}

// точка начала выполнения программы
int main(int argc, char* argv[]) {

    char* file_name = new char[64];
    
    // проверка на количество аргументов, переданных
    // при вызове программы. Если их количество равно 1, то выходим с кодом 0
    if (argc == 1) {
        std::cout << "Enter some stroke when start program!" << std::endl;
        std::cout << "Try to restart this program with some parameters\nExiting.." << std::endl;
        
        exit(0);
    }
    // иначе берем переданный аргумент и заносим его в переменную file_name
    else
        file_name = *(argv+1);

    // проверяем на длину 
    if (!std::strlen(file_name)) {
                std::cout << "Ooops! Your input is empty string..";
                std::cout << "Exiting..\n";
                return -1;
    }
    std::cout << "Inputed file name: " << file_name << std::endl;
    // конвертируем значение переданного аргумента из char в std::string
    str string_file_name = static_cast<str>(file_name);
    
    // создаем файл с тем же именем, но расширением bin
    str bin_file_name = createBinaryFile(string_file_name);

    std::vector<Stroke> arr;
    u_int rows = 0;

    // читаем текст в переданном файле и возвращаем этот файл построчно
    // и вместе со строками возвращаем количество этих строк
    tie(arr, rows) = readTextAndRemember(string_file_name);

    // Записываем в бинарный файл текст
    writeIntoBinary(bin_file_name, arr, &rows);

    // читаем построчно из бинарного файла 
    readFromBinary(bin_file_name, &rows);

    return 0;
}