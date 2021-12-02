#include <iostream>
#include <fstream>
#include <vector>

template <typename T>
std::vector<T> read_file(std::string);

template <>
std::vector<std::string> read_file(std::string);