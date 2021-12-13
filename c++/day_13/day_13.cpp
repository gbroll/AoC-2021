#include <iostream>
#include <utility>
#include <set>
#include <regex>

#include "../utils/file_reader.cpp"
#include "../utils/result_printer.cpp"

struct manual
{
    set<pair<int,int>> dots;
    vector<pair<bool,int>> folds;
    pair<int,int> grid_size;
    bool folded = false;
};

manual parse(vector<string> str_data)
{
    
    manual data;
    int n_rows = str_data.size();

    string regex_str = "^([0-9]+),([0-9]+)$";
    regex regex_obj(regex_str);
    smatch matches;
    int row = 0;
    while (!str_data[row].empty())
    {
        regex_search(str_data[row], matches, regex_obj);
        data.dots.insert(make_pair(stoi(matches.str(1)),stoi(matches.str(2))));

        row++;
    }

    regex_obj.assign("(\\w)=([0-9]+)$");
    bool fold_x;
    int fold_nr = 0;
    while (row < n_rows)
    {
        if (str_data[row].empty())
        {
            row++;
            continue;
        }

        regex_search(str_data[row], matches, regex_obj);
        fold_x = (matches.str(1)=="x")? 1:0;    
        data.folds.push_back(make_pair(fold_x,stoi(matches.str(2))));

        row++;
    }
    
    return data;

}

void draw(manual f_manual)
{
    set<pair<int,int>>::iterator it;
    vector<vector<char>> frame(f_manual.grid_size.second, vector<char>(f_manual.grid_size.first,'.'));

    for (it = f_manual.dots.begin(); it != f_manual.dots.end(); ++it)
    {
        frame[(*it).second][(*it).first] = '#';
    }
    
    for (int i = 0; i < f_manual.grid_size.second; i++)
    {
        for (int j = 0; j < f_manual.grid_size.first; j++)
        {
            cout << frame[i][j];
        }
        cout << endl;        
    }
    cout << endl;
}

int solve(manual &man, bool part2 = false)
{
    set<pair<int,int>> new_dots;;
    set<pair<int,int>>::iterator dot_it;
    int x, y, fold_val, n_dots;

    int n_folds = man.folds.size();

    for (int i = 0; i < n_folds; i++)
    {
        man.folded = true;
        fold_val = man.folds[i].second;

        new_dots.clear();
        for (dot_it = man.dots.begin(); dot_it != man.dots.end(); ++dot_it)
        {
            x = get<0>(*dot_it);
            y = get<1>(*dot_it);

            switch (man.folds[i].first)
            {
                case true:
                    x = (x > fold_val)? 2*fold_val-x : x;
                    man.grid_size.first = fold_val;
                break;
                case false:
                    y = (y > fold_val)? 2*fold_val-y : y;
                    man.grid_size.second = fold_val;
                break;
            }

            new_dots.insert(make_pair(x,y));

        }
        man.dots = new_dots;
        if (!part2) return new_dots.size();
    }

    draw(man);
    return 0;
}

int main()
{
   
    int day = 13;

    auto start = chrono::high_resolution_clock::now();
    
    string filename = "../../input/day_" + to_string(day) + ".txt";
    vector<string> string_data = read_file<string>(filename,false);
    manual data = parse(string_data);

    auto parsed = chrono::high_resolution_clock::now();

    int part_1 = solve(data, false);
    int part_2 = solve(data, true);

    auto solved = chrono::high_resolution_clock::now();
    
    vector<chrono::high_resolution_clock::time_point> time_stamps{start , parsed, solved};
    print_results<int>(day, part_1, part_2, time_stamps);
    
    return 0;
    
}