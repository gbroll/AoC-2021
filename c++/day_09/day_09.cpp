#include <utility>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <set>

#include "../utils/file_reader.cpp"

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
    vector<coord> neighbours;
    neighbours.push_back(make_pair(1,0));
    neighbours.push_back(make_pair(-1,0));
    neighbours.push_back(make_pair(0,1));
    neighbours.push_back(make_pair(0,-1));

    return neighbours;
}


vector<coord> find_low_points(grid data, vector<coord> &neighbours)
{
    vector<coord> low_points;

    int n = data[0].size();
    int m = data.size();
    
    neighbours = get_neighbours();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            bool low_point = true;
            int val = data[i][j];
            for(const auto nghrb : neighbours)
            {
                int ip = i + nghrb.first;
                int jp = j + nghrb.second;

                if (ip >= 0 && ip < m && jp >= 0 && jp < n)
                {
                    if (data[ip][jp] <= val) low_point = false;
                }
            }
            if (low_point)
            {
                low_points.push_back(make_pair(i,j));
            }
        }
    }

    return low_points;
}

int solve_part1(grid data)
{
    
    int count = 0;
    vector<coord> neighbours;
    vector<coord> low_points = find_low_points(data, neighbours);

    for (auto const &point:low_points)
    {
        count += (data[point.first][point.second]+1);
    }   
    
    return count;

}

int solve_part2(grid data)
{

    int n = data[0].size();
    int m = data.size();

    vector<coord> nghbrs;
    vector<coord> low_points = find_low_points(data, nghbrs);

    vector<int> b_sizes(3,0);
    vector<int> b_copy(4,0);

    set<coord>::iterator it;
    std::pair<set<coord>::iterator,bool> ret;

    for (auto const &low_point : low_points)
    {
        set<coord> basin;
        set<coord> coords,new_coords;
        
        new_coords.insert(low_point);

        do
        {
            coords = new_coords;
            new_coords.clear();

            for (it = coords.begin(); it != coords.end(); ++it)
            {

                int i = it->first;
                int j = it->second;

                for (auto const &nghbr : nghbrs)
                {
                    int ip = i + nghbr.first;
                    int jp = j + nghbr.second;
                    
                    if (ip >= 0 && ip < m && jp >= 0 && jp < n)
                    {
                        if (data[ip][jp] < 9)
                        {
                            ret = basin.insert(make_pair(ip, jp));
                            if (ret.second == true)
                            {
                                new_coords.insert(make_pair(ip, jp));
                            }
                        }
                    }
                }
            }
        } while (new_coords.size() > 0);

        copy(b_sizes.begin(), b_sizes.end(),b_copy.begin());
        b_copy.insert
        (
            upper_bound(b_copy.begin(), b_copy.end(), basin.size(),greater<int>()),
            basin.size()
        );
        copy(b_copy.begin(), --b_copy.end(), b_sizes.begin());
        b_copy.erase(--b_copy.end());
    }

    return b_sizes[0] * b_sizes[1] * b_sizes[2];

}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    string filename = "../../input/day_09.txt";
    vector<string> string_data = read_file<string>(filename,true);
    grid data = parse(string_data);
    
    auto parsed = chrono::high_resolution_clock::now();
    
    int part_1 = solve_part1(data);
    int part_2 = solve_part2(data);

    auto solved = chrono::high_resolution_clock::now();

    auto parse_dur = chrono::duration_cast<chrono::microseconds>(parsed - start);
    auto solve_dur = chrono::duration_cast<chrono::microseconds>(solved - parsed);
    auto total_dur = chrono::duration_cast<chrono::microseconds>(solved - start);


    cout << setw(30) << left << "Day 9 Part 1 solution: " << part_1 << endl;
    cout << setw(30) << left << "Day 9 Part 2 solution: " << part_2 << endl;
    cout << endl;

    cout << setw(30) << left << "Total time taken: " << total_dur.count() << " µs" << endl;
    cout << setw(30) << left << "Reading/parsing data: " << parse_dur.count() << " µs" << endl;
    cout << setw(30) << left << "Solving: " << solve_dur.count() << " µs" << endl;
 

}