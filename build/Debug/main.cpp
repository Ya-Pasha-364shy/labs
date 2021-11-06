#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <tuple>

typedef unsigned int u_int;
typedef std::string str;


struct Stroke {
    size_t lenght;
    str payload_data;

    Stroke(size_t* m_lenght, str& m_payload_data) {
        this->lenght = *m_lenght;
        this->payload_data = m_payload_data;
    }
};



std::tuple<std::vector<Stroke>, u_int> readTextAndRemember(str& file_name) {
    u_int rows = 0;
    str s;
    std::ifstream file(file_name.c_str());
    std::vector<Stroke> datas;


    if (file.is_open()) {
        while (true) {
            getline(file, s);

            rows++;

            size_t len = s.length();
            datas.push_back(Stroke(&len, s));

            if (file.eof())
                break;
        }
    }
    else {
        std::cout << "File is closed!" << std::endl;
    }
   
    return std::make_tuple(datas, rows);
}


str createBinaryFile(str& file_name) {

    u_int dot_ind = 0;
    
    for (dot_ind; ;dot_ind++) {
        if (file_name[dot_ind] == '.') 
            break;
    }
    str part1 = file_name.substr(0, dot_ind);
    str part2 = ".bin";

    str binary_file_name = part1 + part2;



    std::ofstream fout;
    fout.open(binary_file_name);
    fout.close();

    return binary_file_name;

}

void writeIntoBinary(str& file_name, std::vector<Stroke>& arr, u_int* rows) {

    const char* sep = " ";
    const char* endl = "\n";

    std::ofstream foutb(file_name, std::ios::binary);
    
    for (u_int i(0); i != *rows; i++) {
        size_t len = arr[i].lenght;
        const char* payload = arr[i].payload_data.c_str();

        foutb.write((char*)&len, sizeof(len));
        foutb.write((char*)&sep, sizeof(sep));      
        foutb.write((char*)&payload, sizeof(payload));
        foutb.write((char*)&endl, sizeof(endl));
    }

    foutb.close();

    return;
}

void readFromBinary(str& file_name, u_int* rows) {
    
    const char* sep = " ";
    const char* endl = "\n";

    std::ifstream in(file_name, std::ios::binary);
    size_t len = 0;
    const char* payload;

    for (u_int i(0); i != *rows; i++) {

        in.read((char*)&len, sizeof(len));
        in.read((char*)&sep, sizeof(sep));
        in.read((char*)&payload, sizeof(payload));
        in.read((char*)&endl, sizeof(endl));

        std::cout << len << sep << payload << endl;
    }

    in.close();

    return;
}


int main(int argc, char* argv[]) {

    char* file_name = new char[64];
    
    if (argc == 1) {
        std::cout << "Enter some stroke when start program!" << std::endl;
        std::cout << "Try to restart this program with some parameters\nExiting.." << std::endl;
        
        exit(0);
    }
    else
        file_name = *(argv+1);
    
     if (!std::strlen(file_name)) {
                std::cout << "Ooops! Your input is empty string..";
                std::cout << "Exiting..\n";
                return -1;
    }
    std::cout << "Inputed file name: " << file_name << std::endl;
    str string_file_name = static_cast<str>(file_name);

    str bin_file_name = createBinaryFile(string_file_name);

    std::vector<Stroke> arr;
    u_int rows = 0;

    tie(arr, rows) = readTextAndRemember(string_file_name);
    
    writeIntoBinary(bin_file_name, arr, &rows);

    readFromBinary(bin_file_name, &rows);

    return 0;
}