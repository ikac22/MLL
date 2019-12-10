#ifndef _MNIST_PARSER_HPP
#define _MNIST_PARSER_HPP

#define DATA_MAGICNO 0x00000803
#define LABEL_MAGICNO 0x00000801

#include<vector>
#include<fstream>

void reverse_int(int& x){
    unsigned char c1, c2, c3, c4;

    c1 = x & 255;
    c2 = (x >> 8) & 255;
    c3 = (x >> 16) & 255;
    c4 = (x >> 24) & 255;

    x = ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

std::vector<float> get_data(const char* t_filename){
    std::ifstream fin(t_filename, std::ios::in | std::ios::binary);

    if(!fin.is_open()){
        std::cout << "Couldn't open file \"" << t_filename << "\"!\n";
        return std::vector<float>();
    }

    fin.seekg(0, std::ios::beg);

    int magic_no;
    int data_size;
    int row_count;
    int col_count;

    fin.read((char*)&magic_no, sizeof(int));
    reverse_int(magic_no);
    fin.read((char*)&data_size, sizeof(int));
    reverse_int(data_size);
    fin.read((char*)&row_count, sizeof(int));
    reverse_int(row_count);
    fin.read((char*)&col_count, sizeof(int));
    reverse_int(col_count);

    if(DATA_MAGICNO != magic_no){
        std::cout << "Invalid magic number\n";
        return std::vector<float>();
    }

    std::vector<float> result(data_size * row_count *  col_count);

    std::cout << "Loading the data...\n";
    for(auto& el : result){
        unsigned char tmp;
        fin.read((char*)&tmp, sizeof(unsigned char));
        el = (float)tmp / 255;
    }

    return result;
}

std::vector<int> get_labels(const char* t_filename){
    std::ifstream fin(t_filename, std::ios::in | std::ios::binary);

    if(!fin.is_open()){
        std::cout << "Couldn't open file \"" << t_filename << "\"!\n";
        return std::vector<int>();
    }

    int magic_no;
    int data_size;

    fin.read((char*)&magic_no, sizeof(int));
    reverse_int(magic_no);
    fin.read((char*)&data_size, sizeof(int));
    reverse_int(data_size);

    if(LABEL_MAGICNO != magic_no){
        std::cout << "Invalid magic number\n";
        return std::vector<int>();
    }

    std::vector<int> result(data_size);

    std::cout << "Loading labels...\n";
    for(auto& el : result){
        unsigned char tmp;
        fin.read((char*)&tmp, sizeof(unsigned char));
        el = (int)tmp;
    }

    return result;
}

#endif//_MNIST_PARSER_HPP
