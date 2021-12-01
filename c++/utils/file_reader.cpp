#include <fstream>
#include <string>
#include <charconv>

#include "file_reader.hpp"

using namespace std;


template vector<int> read_file<int>(string);
//template vector<string> read_file<string>(string input,string filename);

template <typename T>
vector<T> read_file(string filename)
{
    vector<T> output;
    T value{};
    string str_in;
    fstream file_in;
    
    file_in.open(filename, ios::in);
    
    if (!file_in.is_open())
    {
        cout << "Could not find file " << filename << endl;
        return {};
    }

    while(!file_in.eof())
    {
        getline(file_in,str_in);
        auto result = from_chars(str_in.data(), str_in.data() + str_in.size(), value);
        output.push_back(value);
        //cout << str_in << endl;
    }

    file_in.close();
    return output;
    
}
