#include <iostream>
#include <bitset>

#include "../puzzle.hpp"

using namespace std;

typedef vector<vector<int>> img;

class Puzzle : public Puzzle_base<int>
{

    //inherit constructors from base class
    using Puzzle_base::Puzzle_base;

public:
    void parse_input();
    void solve_part1();
    void solve_part2();
    
    int get_bit(int i, int j);
    void enhance();
    void enhance_n(int n);
    void show_image();
    void reset_image();
    int count();

private:
    vector<int> iea;
    img input_img, curr_img;
    pair<int,int> input_img_size, curr_img_size;
    int pad_bit = 0;
};

void Puzzle::parse_input()
{  
    int i = 0,val;
    int n = str_data.size();

    while(!str_data[i].empty())
    {
        string row = str_data[i];
        int n_cols = row.size();
        for (int j = 0; j < n_cols; j++)
        {
            val = (row[j] == '.')? 0:1;
            iea.push_back(val);
        }
        i++;
    }

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
    
    curr_img = input_img;
    input_img_size = make_pair(input_img.size(), input_img[0].size());
    curr_img_size = input_img_size;
}

int Puzzle::get_bit(int i, int j)
{
    if (i < 0 || j < 0 || i >= curr_img_size.first || j>= curr_img_size.second) return pad_bit;
    return curr_img[i][j];
}

void Puzzle::enhance()
{
    bitset<9> bits;
    int bit ,bitindex;
    int n_rows = Puzzle::curr_img_size.first+2;
    int n_cols = Puzzle::curr_img_size.second+2;
    vector<vector<int>> output_img(n_rows , vector<int> (n_cols, 0));

    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_cols; j++)
        {
            bitindex = 8;
            bits.reset();
            for (int k1 = -1; k1<2; k1++)
            {
                for (int k2 = -1; k2<2; k2++)
                {              
                    bit = get_bit(i+k1-1,j+k2-1);
                    if (bit==1) bits.set(bitindex);
                    bitindex--;                 
                }
            }
        output_img[i][j] = iea[bits.to_ulong()];
        }
    }

    //set pad_bit
    pad_bit = (pad_bit==0)? iea[0] : iea.back();

    //replace current data
    curr_img_size = make_pair(n_rows,n_cols);
    curr_img = output_img;

}

void Puzzle::show_image()
{
    for (int i = 0; i < curr_img_size.first; i++)
    {
        for (int j = 0; j < curr_img_size.second; j++)
        {
            cout << curr_img[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void Puzzle::enhance_n(int n)
{
    for (int i = 0; i < n; i++)
    {
        enhance();
    }
}

void Puzzle::reset_image()
{
    curr_img = input_img;
    input_img_size = make_pair(input_img.size(), input_img[0].size());
    curr_img_size = input_img_size;

}

int Puzzle::count()
{
    int sm = 0;
    for (auto& row : curr_img)
    {
        for (auto& val : row)
        {
            sm += val;
        }
    }
    return sm;
}

void Puzzle::solve_part1()
{
    int n = 2;
    reset_image();
    enhance_n(n);
    //show_image();  
    part1_solution = count();
}

void Puzzle::solve_part2()
{
    int n = 50;
    reset_image();
    enhance_n(n);
    //show_image();  
    part2_solution = count();
}

int main()
{
    int day = 20;
    bool skip_empty_lines = false;
    bool test_input = false;

    Puzzle p = Puzzle(day, skip_empty_lines, test_input);
    p.solve();
  
}