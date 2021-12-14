#include <vector>
#include <chrono>
#include <iomanip>

#include "result_printer.hpp"

typedef unsigned long long ull;

using namespace std;

template void print_results<int>(int day, int part1, int part2, vector<chrono::high_resolution_clock::time_point>);
template void print_results<ull>(int day, ull part1, ull part2, vector<chrono::high_resolution_clock::time_point>);

template <typename T>
void print_results(int day, T part_1, T part_2, vector<chrono::high_resolution_clock::time_point> time_stamps)
{
    auto parse_dur = chrono::duration_cast<chrono::milliseconds>(time_stamps[1] - time_stamps[0]);
    auto solve_dur = chrono::duration_cast<chrono::milliseconds>(time_stamps[2] - time_stamps[1]);
    auto total_dur = chrono::duration_cast<chrono::milliseconds>(time_stamps[2] - time_stamps[0]);
    
    cout << setw(30) << left << "Day 9 Part 1 solution: " << part_1 << endl;
    cout << setw(30) << left << "Day 9 Part 2 solution: " << part_2 << endl;
    cout << endl;

    cout << setw(30) << left << "Total time taken: " << total_dur.count() << " ms" << endl;
    cout << setw(30) << left << "Reading/parsing data: " << parse_dur.count() << " ms" << endl;
    cout << setw(30) << left << "Solving: " << solve_dur.count() << " ms" << endl;

}