#include <set>
#include <climits>
#include <chrono>

#include "../utils/file_reader.cpp"
#include "../utils/result_printer.cpp"

typedef pair<int,int> coord;
typedef vector<vector<int>> grid;

grid parse(vector<string> str_data)
{
    vector<vector<int>> data;
    int n_rows = str_data.size();
    for (auto const row:str_data)
    {
        vector<int> row_data;
        for (char const num:row)
        {
            row_data.push_back(num-48);
        }
        data.push_back(row_data);
    }

    return data;
}

vector<coord> get_neighbours()
{
    vector<coord> neighbours = {{1,-1},{1,0},{1,1},{0,1},{0,-1},{-1,-1},{-1,0},{-1,1}};
    return neighbours;
}

int solve(grid data, bool part2)
{
    int n_flashes = 0;
    int step_flashes;
    int n_steps = part2? INT_MAX : 100;
    
    int n = data[0].size();
    int m = data.size();
    int nm = n*m;

    set<pair<int,int>> flash_coords;
    vector<coord> nbs = get_neighbours();

    for (int step = 0; step < n_steps; step++)
    {
        if (part2 && step_flashes == nm)
        {
            return step;
        }
        step_flashes = 0;

        //first substep
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (data[i][j] == 9)
                {
                    data[i][j] = 0;
                    n_flashes++;
                    step_flashes++;
                    flash_coords.insert(make_pair(i, j));
                }
                else
                {
                    data[i][j]++;
                }
            }
        }

        //second substep
        while (flash_coords.size() > 0)
        {
            set<pair<int, int>> coords(flash_coords);
            flash_coords.clear();

            for (const auto &coord : coords)
            {                
                for (const auto &nb:nbs)
                {
                    int ip = coord.first + nb.first;
                    int jp = coord.second + nb.second;
                    if (ip >= 0 && ip < m && jp >= 0 && jp < n)
                    {
                        if (data[ip][jp] == 9)
                        {
                            data[ip][jp] = 0;
                            n_flashes++;
                            step_flashes++;
                            flash_coords.insert(make_pair(ip,jp));
                        }
                        else if (data[ip][jp]>0)
                        {
                            data[ip][jp]++;
                        }    
                    }
                }
            }
        }
    }

    return n_flashes;
}

int main()
{
   
    int day = 11;

    auto start = chrono::high_resolution_clock::now();
    
    string filename = "../../input/day_" + to_string(day) + ".txt";
    vector<string> string_data = read_file<string>(filename,true);
    grid data = parse(string_data);
    auto parsed = chrono::high_resolution_clock::now();
    
    int part_1 = solve(data, false);
    int part_2 = solve(data, true);
    auto solved = chrono::high_resolution_clock::now();
    
    vector<chrono::high_resolution_clock::time_point> time_stamps{start , parsed, solved};
    print_results<int>(day, part_1, part_2, time_stamps);

}