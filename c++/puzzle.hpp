#include <string>
#include <vector>
#include <fstream>

using namespace std;

template<class T>
class Puzzle_base
{
public:
    Puzzle_base(int day, bool skip_empty_input, bool test_input);

    //abstract methods to be implemented by inheriting class
    virtual void parse_input() = 0;
    virtual void solve() = 0;
    
    void read_file();

    bool skip_empty_lines;
    bool test_input;
    int day;
    vector<string> str_data;
    T part1_solution;
    T part2_solution;
};

template <class T>
Puzzle_base<T>::Puzzle_base(int _day, bool _skip_empty_lines, bool _test_input)
{
    day = _day;
    skip_empty_lines = _skip_empty_lines;
    test_input = _test_input;
};

template <class T>
void Puzzle_base<T>::read_file()
{
    vector<string> output;
    string str_in;
    fstream file_in;

    string filename = "../../input/day_";
    filename += (day>9)? "":"0";
    filename += to_string(day); 
    filename +=  test_input? "_test.txt" : ".txt";

    cout << filename << endl;

    file_in.open(filename, ios::in);
    
    if (!file_in.is_open())
    {
        cout << "Could not find file " << filename << endl;
        return;
    }

    while(!file_in.eof())
    {
        getline(file_in,str_in);
        if (!str_in.empty())
        {
            output.push_back(str_in);
        }
        else
        {
            if (!skip_empty_lines)
            {
                output.push_back(str_in);
            }
        }
    }
    file_in.close();
    str_data = output;
}