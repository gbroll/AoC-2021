#include <iostream>

#include "../puzzle.hpp"

using namespace std;

class Puzzle : public Puzzle_base<int>
{
    //inherit construvtors from base class
    using Puzzle_base::Puzzle_base;

public:
    void parse_input();
    void solve();

private:
    string iea;
    vector<vector<int>> input_img;
};

void Puzzle::parse_input()
{  
    int i = 0;
    int n = str_data.size();
    while(!str_data[i].empty())
    {
        iea.append(str_data[i]);
        //cout << str_data[i] << endl;
        i++;
    }
    cout << iea.length() << endl;

    string row;
    i++;
    while(i < n)
    {
        row = str_data[i];
        vector<int> row_ints;
        for (int j = 0; j < row.size(); j++)
        {
            char ch = row[j];
            int num = (ch=='.')? 0:1;
            row_ints.push_back(num);
        }
        input_img.push_back(row_ints);
        i++;

    }
}

void Puzzle::solve()
{

}

int main()
{
    int day = 20;
    bool skip_empty_lines = false;
    bool test_input = true;

    Puzzle p = Puzzle(day, skip_empty_lines, test_input);
    p.read_file();
    p.parse_input();

}