#include <climits>
#include <algorithm>
#include <set>
#include <map>


#include "../utils/file_reader.cpp"
#include "../utils/result_printer.cpp"

typedef pair<int,int> coord;
typedef map<coord,int> grid;

vector<coord> get_neighbours()
{
    vector<coord> neighbours = {{1,0},{0,1},{0,-1},{-1,0}};
    return neighbours;
}

grid parse(vector<string> str_data)
{
    grid data;

    int n_rows = str_data.size();
    int n_cols = str_data[0].size();
    for (int i = 0; i < n_rows; i++)
    {
        string str_row = str_data[i];
        for (int j = 0; j < n_cols; j++)
        {
            data.insert(make_pair(make_pair(i,j),int(str_row[j]-48)));
        }
        
    }

    return data;

}

pair<coord,int> get_min_dist(grid dist, set<coord> Q)
{
    int mn_val = INT_MAX;
    coord mn_coord;

    for (auto elem : Q)
    {
        int val = dist.at(elem);
        if (val < mn_val)
        {
            mn_coord = elem;
            mn_val = val;
        }
    }
    
    //pair<pair<int,int>,int> mn = *min_element(dist.begin(), dist.end(),
    //        [](const auto& l, const auto& r) { return l.second < r.second; });

    return make_pair(mn_coord,mn_val);
}

int solve(grid data)
{
    pair<coord,int> source;
    set<coord> Q;
    grid dist(data);
    vector<coord> nbs = get_neighbours();

    for (auto const& [key, val] : data)
    {
        dist.at(key) = INT_MAX;
        Q.insert(key);
    }
    dist.at(make_pair(0,0)) = 0;

    while(Q.size()>1)
    {
        //get minimum value of dist
        source = get_min_dist(dist, Q);
        //cout << Q.size() << endl;
        Q.erase(source.first);

        //check neighbours of source
        for (auto &nb:nbs)
        {
            coord u = make_pair(source.first.first+nb.first, source.first.second+nb.second);
            if (!Q.count(u)) continue;
            int risk = source.second + data.at(u);
            if (risk < dist.at(u))
            {
                dist.at(u) = risk;
            }

        }

    }

    return dist.at(make_pair(99,99));
}

int main()
{
    int day = 15;

    auto start = chrono::high_resolution_clock::now();
    
    string filename = "../../input/day_" + to_string(day) + ".txt";
    vector<string> string_data = read_file<string>(filename,false);
    grid data = parse(string_data);
    int part_1 = solve(data);
    cout << part_1 << endl;

}