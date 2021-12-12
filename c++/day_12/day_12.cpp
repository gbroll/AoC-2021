#include <iostream>
#include <map>
#include <list>
#include <stack>
#include <regex>
#include <algorithm>
#include <cctype>

#include "../utils/file_reader.cpp"
#include "../utils/result_printer.cpp"

struct cave
{
    bool big;
    int n_visits = 0;
    list<string> nb;
};

typedef map<string,cave> cave_map;

void add_cave(string cave_1, string cave_2, cave_map &caves)
{
    if (caves.count(cave_1) == 0)
    {
        cave new_cave;
        new_cave.big = any_of(cave_1.begin(), cave_1.end(), [](char c)
                              { return isupper(c); });
        new_cave.nb.push_back(cave_2);
        caves.insert(make_pair(cave_1, new_cave));
    }
    else
    {
        caves.at(cave_1).nb.push_back(cave_2);
    }
}

cave_map parse(vector<string> str_data)
{
    cave_map caves;

    string regex_str = "^(\\w+)-(\\w+)$";
    regex regex_obj(regex_str);
    smatch matches;

    int n_rows = str_data.size();
    for (int i = 0; i < n_rows; i++)
    {
        regex_search(str_data[i], matches, regex_obj);

        string cave_1 = matches.str(1);
        string cave_2 = matches.str(2);

        add_cave(cave_1, cave_2, caves);
        add_cave(cave_2, cave_1, caves); 
    }

    return caves;

}

int recursive_dfs(string start, cave_map &caves, bool allow_twice)
{
    int n_paths = 0;
    int n_caves = caves.size();
    list<string>::iterator list_it;
    cave_map::iterator cave_it;

    cave &ccave = caves.at(start);
    if (!ccave.big) ccave.n_visits++;
   
    if (ccave.n_visits==2) allow_twice = false;

    for (list_it = ccave.nb.begin(); list_it!= ccave.nb.end(); ++list_it)
    {
        if ((*list_it) == "start") ; //do nothing
        else if ((*list_it) == "end")
        {
            n_paths++;
            continue;
        }

        else if (allow_twice || caves.at(*list_it).n_visits <= 0)
        {
            n_paths += recursive_dfs(*list_it, caves, allow_twice);
        }
  
    }

    ccave.n_visits--;
    if (ccave.n_visits == 1) allow_twice = true;

    return n_paths;
}

int solve(cave_map caves, bool part_2)
{
    //using DFS

    int n_paths = recursive_dfs("start", caves, part_2);
    return n_paths;
}

int main()
{
   
    int day = 12;

    auto start = chrono::high_resolution_clock::now();
    
    string filename = "../../input/day_" + to_string(day) + ".txt";
    vector<string> string_data = read_file<string>(filename,true);
    cave_map caves = parse(string_data);

    auto parsed = chrono::high_resolution_clock::now();

    int part_1 = solve(caves, false);
    int part_2 = solve(caves, true);

    auto solved = chrono::high_resolution_clock::now();
    
    vector<chrono::high_resolution_clock::time_point> time_stamps{start , parsed, solved};
    print_results<int>(day, part_1, part_2, time_stamps);

    return 0;
    
}

