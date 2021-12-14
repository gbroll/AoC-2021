#include <iostream>
#include <regex>
#include <list>
#include <map>
#include <set>
#include <utility>

#include "../utils/file_reader.cpp"
#include "../utils/result_printer.cpp"

using namespace std;

typedef unsigned long long ull;

struct polymer
{
    map<string,char> rules;
    map<char,ull> char_counts;
    map<string,ull> pair_counts;
};

template <typename T>
void add_inc(map<T,ull> &counts, T key, ull val)
{
    pair<typename map<T,ull>::iterator,bool> ret;

    ret = counts.insert(pair<T,ull>(key,val));
    if (!ret.second)
    {
        counts.at(key) += val;
    }
}

polymer parse(vector<string> str_data)
{
    polymer p;
    
    string init_str = str_data[0];
    int n_chars = init_str.size();
    
    for (int i = 0; i < n_chars-1; i++)
    {
        string key = string() + init_str[i] + init_str[i+1];
        add_inc(p.pair_counts, key, 1);
    }

    string regex_str = "^(\\w{2})\\s->\\s(\\w)$";
    regex regex_obj(regex_str);
    smatch matches;

    for (int i = 2, n = str_data.size(); i < n; i++)
    {
        regex_search(str_data[i], matches, regex_obj);
        p.rules.insert(make_pair(matches.str(1),matches.str(2)[0]));
    }

    //add character counts for initial template
    for (int i = 0; i < n_chars; i++)
    {
        add_inc(p.char_counts, init_str[i], 1);
    }

    return p;
}

void evolve(polymer &p, int n_steps)
{

    map<string,ull> old_pair_counts;

    for (int step = 0; step < n_steps; step++)
    {
        old_pair_counts = p.pair_counts;       

        for (auto const& [key, val] : old_pair_counts)
        {
            if (val > 0)
            {
                char new_char = p.rules.at(key);
                string new_pair_1 = string() + key[0] + new_char;
                string new_pair_2 = string() + new_char + key[1];
                
                add_inc(p.pair_counts, new_pair_1, val);
                add_inc(p.pair_counts, new_pair_2, val);
                add_inc(p.pair_counts, key, -val);
              
                add_inc(p.char_counts, new_char, val);
            }
        }
    }

    return;
}

ull solve(polymer &p, bool part2 = false)
{
    int n_steps = part2? 30 : 10;
    evolve(p, n_steps);    

    ull mn=p.char_counts.begin()->second, mx = mn;
    //c++ 17
    for (auto const& [key, val] : p.char_counts)
    {
        if (val < mn) mn = val;
        if (val > mx) mx = val;
    }

    return mx-mn;
}

int main()
{
    int day = 14;

    auto start = chrono::high_resolution_clock::now();
    
    string filename = "../../input/day_" + to_string(day) + ".txt";
    vector<string> string_data = read_file<string>(filename,false);
    polymer p = parse(string_data);

    auto parsed = chrono::high_resolution_clock::now();

    ull part_1 = solve(p, false);
    ull part_2 = solve(p, true);

    auto solved = chrono::high_resolution_clock::now();
    
    vector<chrono::high_resolution_clock::time_point> time_stamps{start , parsed, solved};
    print_results<ull>(day, part_1, part_2, time_stamps);

    return 0;
    
}