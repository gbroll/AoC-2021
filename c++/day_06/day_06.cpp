#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <chrono>

#include "../utils/file_reader.cpp"

using namespace std;

typedef unsigned long long ull;

vector<int> parse(string string_data)
{
    vector<int> output;
    string input_str;
    int input_int;
    stringstream sstream(string_data);

    while(getline(sstream,input_str,','))
    {
        stringstream s(input_str);
        s >> input_int;
        output.push_back(input_int);
    }
    return output;
}

void step(vector<ull> &old_fish, vector<ull> &new_fish)
{

    //old fish rotation
    rotate(old_fish.begin(),old_fish.begin()+1,old_fish.end());

    //new fish rotation
    rotate(new_fish.begin(),new_fish.begin()+1,new_fish.end());

    //fish going old, respawn as old
    ull aging_fish = new_fish.back();
    old_fish.back() += aging_fish;

    //spawn new fish
    new_fish.back() = old_fish.back();

}


ull solve(vector<int> data, int n_days)
{  
    vector<ull> old_fish(7,0);
    vector<ull> new_fish(9,0);

    for (auto ix : data)
    {
        old_fish[ix]++;
    }

    for (int i = 0; i < n_days ; i++)
    {
        step(old_fish, new_fish);
        //cout << "After " << i+1 << " days: " << n_fish << " fishes" << endl;  
    }    
    ull n_fish = accumulate(old_fish.begin(), old_fish.end(), 0ULL) + 
        accumulate(new_fish.begin(), new_fish.end(), 0ULL);
        
    return n_fish;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    string filename = "../../input/day_06.txt";
    vector<string> string_data = read_file<string>(filename,true);
    vector<int> data = parse(string_data[0]);

    ull part_1 = solve(data, 80);
    ull part_2 = solve(data, 256);

    cout << "Day 6 Part 1 solution: " << part_1 << endl;
    cout << "Day 6 Part 2 solution: " << part_2 << endl;

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " µs" << endl;

    return 0;
}