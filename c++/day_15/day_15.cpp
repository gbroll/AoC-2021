#include <climits>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>

#include "../utils/file_reader.cpp"
#include "../utils/result_printer.cpp"

typedef pair<int,int> coord;
typedef pair<coord,int> point;
typedef map<coord,int> grid;

struct risk_map_struct
{
    int x_size;
    int y_size;
    grid risk_level;
};

vector<coord> get_neighbours()
{
    vector<coord> neighbours = {{1,0},{0,1},{0,-1},{-1,0}};
    return neighbours;
}

risk_map_struct parse(vector<string> str_data)
{
    risk_map_struct risk_map;
    grid risk_level;

    int n_rows = str_data.size();
    int n_cols = str_data[0].size();
    for (int i = 0; i < n_rows; i++)
    {
        string str_row = str_data[i];
        for (int j = 0; j < n_cols; j++)
        {
            risk_level.insert(make_pair(make_pair(i,j),int(str_row[j]-48)));
        }
        
    }

    risk_map.risk_level = risk_level;
    risk_map.x_size = n_cols;
    risk_map.y_size = n_rows;

    return risk_map;

}

risk_map_struct expand_grid(risk_map_struct risk_map)
{
    risk_map_struct expanded_map;
    expanded_map.x_size = risk_map.x_size*5;
    expanded_map.y_size = risk_map.y_size*5;
    grid exp_risk_level;
    vector<vector<int>> test;

    for (int i = 0; i < expanded_map.y_size; i++)
    {   
        vector<int> str_row;
        for (int j = 0; j < expanded_map.x_size; j++)
        {
            
            int col = j%risk_map.x_size;
            int row = i%risk_map.y_size;

            coord coord_ = make_pair(row, col);
            int val = (risk_map.risk_level.at(coord_));
            int add = i/risk_map.y_size + j/risk_map.x_size;
            int new_val = val + add;

            while (new_val > 9)
            {
                new_val-=9;
            }

            exp_risk_level.insert(make_pair(make_pair(i,j), new_val));
            
        }
        test.push_back(str_row);
    }


    expanded_map.risk_level = exp_risk_level;
    
    
    return expanded_map;
}

int solve(risk_map_struct risk_map)
{
    point source;

    coord start = make_pair(0,0);
    coord target = make_pair(risk_map.x_size-1 ,risk_map.y_size-1);

    grid risk(risk_map.risk_level);
    map<coord,coord> prevs;

    auto cmp = [](const point &a, const point &b) {
        return a.second > b.second;
    };  
    priority_queue< point, vector<point>, decltype(cmp)> queue(cmp);
    
    vector<coord> nbs = get_neighbours();
    
    for (auto const& [key, val] : risk_map.risk_level)
    {
        risk.at(key) = INT_MAX;  
    }
    risk.at(make_pair(0,0)) = 0;

    source = make_pair(start,0);
    queue.push(source);

    while(queue.size()>0)
    {
        cout << queue.size() << endl;;
        source = queue.top();
        queue.pop();
        

        for (auto &nb:nbs)
        {
            coord u = make_pair(source.first.first+nb.first, source.first.second+nb.second);
            
            if (!risk.count(u)) continue;
            int new_risk = source.second + risk_map.risk_level.at(u);
            if (new_risk < risk.at(u))
            {
                risk.at(u) = new_risk;
                queue.push(make_pair(u,new_risk));
                prevs.insert(make_pair(u,source.first));
            }
        }
    }

    //backtrack route
    stack<coord> route;
    coord loc = target;
    route.push(loc);
    while (loc != start)
    {
        loc = prevs.at(loc);
        route.push(loc);
    }


    return risk.at(target);

}

int main()
{
    int day = 15;

    auto start = chrono::high_resolution_clock::now();
    
    string filename = "../../input/day_" + to_string(day) + "_test.txt";
    vector<string> string_data = read_file<string>(filename,false);
    risk_map_struct risk_map = parse(string_data);
    //risk_map = expand_grid(risk_map);

    int part_1 = solve(risk_map);
    cout << part_1 << endl;

}