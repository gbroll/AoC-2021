#include <iostream>
#include <bitset>

#include "../utils/file_reader.cpp"

using namespace std;

bitset<12> bit_mode(vector<string> data, bool default_bit = true)
{

    bitset<12> output;
    string bin_str;
    int str_len;
    vector<int> sum_bits;
    int n_rows = data.size();

    for (int i = 0; i < n_rows; i++)
    {
        bin_str = data[i];
        if (i==0)
        {
            str_len = bin_str.length();
            sum_bits.resize(str_len,0);
        }
        for (int j = 0; j < str_len; j++)
        {
            sum_bits[j]+=stoi(bin_str.substr(j,1));
        }
    }

    //calculate if 0 or 1 has the highest prevalence
    //set corresponding bit in the bitset (note reverse ordering)
    for (int i = 0; i < str_len; i++)
    {
        int bit_pos = str_len-i-1;
        if (sum_bits[i]*2 == n_rows)
        {
            output.set(bit_pos, true);
        }
        else if (sum_bits[i] > n_rows/2.0)
        {
            output.set(bit_pos, true);
        }
        else
        {
            output.set(bit_pos, false);
        }
    }

    return default_bit == false? ~output : output;
}

bitset<12> recursive_solver(vector<string> data, bool default_bit, int bit_pos = 0)
{
    
    int n_rows = data.size();
    int n_bits = data[0].length();
    
    //base case
    if (bit_pos == n_bits || n_rows == 1)
    {
        bitset<12> remaining_bits(data[0]);
        return remaining_bits;
    }

    vector<string> data_next;

    //get the most common bits
    bitset<12> bitset_ = bit_mode(data, default_bit);

    for (int i = 0; i < n_rows; i++)
    {
        bitset<12> temp(data[i]);
        int bit_pos_reversed = n_bits-1-bit_pos;  //bit-order from right in bitset
        if (temp.test(bit_pos_reversed) == bitset_.test(bit_pos_reversed))
        {
            data_next.push_back(data[i]);
        }
    }
    
    return recursive_solver(data_next, default_bit, ++bit_pos);

}

int solve_part1(vector<string> data)
{
   
    bitset<12> gamma_rate_bits = bit_mode(data, true);
    bitset<12> epsilon_rate_bits = bit_mode(data, false);

    int gamma_rate = (int)gamma_rate_bits.to_ulong();
    int epsilon_rate = (int) epsilon_rate_bits.to_ulong();

    return gamma_rate * epsilon_rate;

}

int solve_part2(vector<string> data)
{
    bitset<12> oxgen_rate_bits = recursive_solver(data,true);
    bitset<12> co2scrub_rate_bits = recursive_solver(data,false);

    int oxgen_rate = (int)oxgen_rate_bits.to_ulong();
    int co2scrub_rate = (int) co2scrub_rate_bits.to_ulong();
   
    return oxgen_rate * co2scrub_rate;
}

int main()
{
    vector<string> data = read_file<string>("../../input/day_03.txt");

    int part_1 = solve_part1(data);
    int part_2 = solve_part2(data);

    cout << "Day 3 Part 1 solution: " << part_1 << endl;
    cout << "Day 3 Part 2 solution: " << part_2 << endl;
    
}