#include <iostream>
#include <fstream>
#include <vector>

template <typename T>
std::vector<T> read_file(std::string, bool = true);

template <>
std::vector<std::string> read_file(std::string,bool);