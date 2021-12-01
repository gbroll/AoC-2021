#include <numeric>
#include <algorithm>

#include "../utils/file_reader.cpp"

int solve_part1(vector<int> data)
{

    adjacent_difference(data.begin(), data.end(), data.begin());
    int count = count_if(data.begin()+1, data.end(), [](int i){ return i>0; });

    return count;
    
}

int solve_part2(vector<int> data)
{
    vector<int> sums(data.size()-2);

    for (int i = 0, n = sums.size(); i < n; i++)
    {
        sums[i] = accumulate(data.begin()+i,data.begin()+(i+3),0);
    }
    
    int count = solve_part1(sums);
    
    return count;
}

int main()
{
    
    vector<int> data = read_file<int>("../../input/day_01.txt");
    
    int part_1 = solve_part1(data);
    int part_2 = solve_part2(data);

    cout << "Day 1 Part 1 solution: " << part_1 << endl;
    cout << "Day 1 Part 2 solution: " << part_2 << endl;

    return 0;
}