
#include "../utils/file_reader.cpp"
#include "../utils/result_printer.cpp"

typedef vector<pair<int,int>> num;

vector<num> parse(vector<string> str_data)
{
    
    vector<num> output;

    int n_cols;
    int n_rows = str_data.size();
    for (int i = 0; i < n_rows; i++)
    {
        num nm;
        string row = str_data[i];
        int level = 0, digit;
        for (int j = 0, n_cols = row.size(); j < n_cols; j++)
        {
            char ch = row[j];
            if (ch == ',')
            {
                continue;
            }
            else if (ch == '[')
            {
                level++;
            }
            else if (ch == ']')
            {
                level--;
            } 
            else
            {
                digit = ch-48;
                nm.push_back(make_pair(level,digit));
            }
        }
        output.push_back(nm);
    }
    return output;
}

num add(num n1, num n2)
{
    n1.insert(n1.end(),n2.begin(), n2.end());
    for (auto &nm : n1)
    {
        nm.first++;
    }
    return n1;   
}

num explode(num nm,int index)
{
    if (index>0) nm[index-1].second += nm[index].second;
    if (index<nm.size()-2) nm[index+2].second += nm[index+1].second;

    nm[index].first--;
    nm[index].second = 0;
    nm.erase(nm.begin()+=(index+1));

    return nm;

}

num split(num nm, int index)
{
    float digit = float(nm[index].second);
    int level = nm[index].first;

    nm[index].first++;
    nm[index].second = int (digit/2.0f);
    
    nm.insert(nm.begin()+index+1, make_pair(++level,int (digit/2.0f+.5)));

    return nm;

}

num reduce(num nm)
{
    bool done = false;
    int i,n;

    while (!done)
    {
        i = 0;
        n = nm.size();  
        while (i < n)
        {
            if (nm[i].first > 4)
            {
                nm = explode(nm, i);
                i = 0;
                continue;
            }
            n = nm.size();
            i++;
        }

        i = 0;
        n = nm.size();
        while (i < n)
        {
            if (nm[i].second > 9)
            {
                nm = split(nm, i);
                i = 0;
                break;
            }
            n = nm.size();
            i++;
        }
        if (i == n) done = true;
    }

    return nm;

}

num sum_up(vector<num> nums)
{
    vector<num>::iterator it;
    num nm = nums.front();
    for (it = ++nums.begin(); it != nums.end(); ++it)
    {
        nm = reduce(add(nm, (*it)));
    }

    return nm;
}

int magnitude(num nm)
{
    int i,l1,l2;

    while (nm.size() > 1)
    {
        l1 = nm[0].first;
        i = 1;
        while (i < nm.size())
        {
            l2 = nm[i].first;
            if (l2==l1)
            {
                nm[i-1].second = 3*nm[i-1].second + 2*nm[i].second;
                nm[i-1].first--;
                nm.erase(nm.begin()+i);
                break;
            }
            else
            {
                l1 = l2;
            }
            i++;
        }
    }
    return nm[0].second;
}

int solve_part2(vector<num> nums)
{
    int res, mx = 0;
    int n_nums = nums.size();

    for (int i = 0; i < n_nums; i++)
    {
        for (int j = 0; j < n_nums; j++)
        {
            if (i==j) continue;
            vector<num> input = {nums[i],nums[j]};
            res = magnitude(sum_up(input));
            if (res > mx) mx = res;
        }
    }
    return mx;
}

int solve(vector<num> nums, bool part2)
{
    if (!part2)
    {
        return magnitude(sum_up(nums));
    }
    else
    {
        return solve_part2(nums);
    }
}

int main()
{
    int day = 18;

    auto start = chrono::high_resolution_clock::now();
    
    string filename = "../../input/day_" + to_string(day) + ".txt";
    vector<string> string_data = read_file<string>(filename,false);
    vector<num> nums = parse(string_data);
    
    auto parsed = chrono::high_resolution_clock::now();

    int part_1 = solve(nums, false);
    int part_2 = solve(nums, true);

    auto solved = chrono::high_resolution_clock::now();
    
    vector<chrono::high_resolution_clock::time_point> time_stamps{start , parsed, solved};
    print_results<int>(day, part_1, part_2, time_stamps);

    return 0;
    
}

