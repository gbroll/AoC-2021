#include <sstream>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <iomanip>

#include "../utils/file_reader.cpp"

using namespace std;

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


int solve_part1(vector<int> data)
{
    //median minimizes the sum of absolute deviations
    sort(data.begin(), data.end());
    int median = data[data.size()/2];

    int result = accumulate(data.begin(), data.end(),0,[median](int a, int b){return a + abs(b - median);});
    
    return result;
}

int solve_part2(vector<int> data)
{
    //f(m) = sum_i((x_i-m)² + abs(x_i-m))/2
    //df/dm = 0 -> m = sum_i(x_i)/n +-1/2
    //optimal position m is within +-1/2 of the mean (sum_i(x_i)/n)

    float mean = accumulate(data.begin(),data.end(),0)/(float)data.size();

    int f1 = accumulate(data.begin(), data.end(),0,
        [mean](int a, int b){int d = abs(b-int(mean+.5)); return a + (d*d + d)/2;});
    int f2 = accumulate(data.begin(), data.end(),0,
        [mean](int a, int b){int d = abs(b-int(mean-.5)); return a + (d*d + d)/2;});

    return f1 < f2? f1 : f2; 

}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    string filename = "../../input/day_07.txt";
    vector<string> string_data = read_file<string>(filename,true);
    vector<int> data = parse(string_data[0]);

    auto parsed = chrono::high_resolution_clock::now();
    
    int part_1 = solve_part1(data);
    int part_2 = solve_part2(data);

    auto solved = chrono::high_resolution_clock::now();

    cout << setw(30) << left << "Day 7 Part 1 solution: " << part_1 << endl;
    cout << setw(30) << left << "Day 7 Part 2 solution: " << part_2 << endl;

    auto parse_dur = chrono::duration_cast<chrono::microseconds>(parsed - start);
    auto solve_dur = chrono::duration_cast<chrono::microseconds>(solved - parsed);
    auto total_dur = chrono::duration_cast<chrono::microseconds>(solved - start);

    cout << setw(30) << left << "Total time taken: " << total_dur.count() << " µs" << endl;
    cout << setw(30) << left << "Reading/parsing data: " << parse_dur.count() << " µs" << endl;
    cout << setw(30) << left << "Solving: " << solve_dur.count() << " µs" << endl;

}
