#include <iostream>
#include <iomanip>
#include <stack>
#include <map>
#include <algorithm>

#include "../utils/file_reader.cpp"

typedef unsigned long long ull;
map<char,char> delims;

void set_delims()
{
    delims['('] = ')';
    delims['['] = ']';
    delims['{'] = '}';
    delims['<'] = '>';
}

bool opens(char inp)
{
    return delims.count(inp) > 0? true : false;
}

int calc_score(vector<char> const illegals)
{
    map<char,int> points;
    points[')'] = 3;
    points[']'] = 57;
    points['}'] = 1197;
    points['>'] = 25137;

    int score = 0;

    int n_illegals = illegals.size();
    for (int i = 0; i < n_illegals; i++)
    {
        score += points.at(illegals[i]);
    }
    return score;
}

int calc_score(vector<vector<char>> const missing)
{
    vector<ull> scores;
    map<char,int> points;
    points[')'] = 1;
    points[']'] = 2;
    points['}'] = 3;
    points['>'] = 4;

    int n_rows = missing.size();
    for (int i = 0; i < n_rows; i++)
    {
        ull row_score = 0;
        vector<char> row = missing[i];
        int row_size = row.size();
        for (int j = 0; j < row_size; j++)
        {
            row_score = row_score * 5 + points.at(row[j]);
        }
        scores.insert(upper_bound(scores.begin(), scores.end(),row_score),row_score);
    }

    return scores[scores.size()/2];
}

void scan_lines(vector<string> str_data, vector<vector<char>> &missing, vector<char> &illegals)
{
    set_delims();

    int n_rows = str_data.size();
    for (int row = 0; row < n_rows; row++)
    {
        stack<char> chunks;
        bool illegal = false;
        vector<char> row_miss;

        string row_d = str_data[row];
        int n_chars = row_d.length();
        for (int pos = 0; pos < n_chars; pos++)
        {
            char char_ = row_d[pos];
            if (opens(char_))
            {
                chunks.push(char_);
            }
            else
            {
                if (char_ != delims.at(chunks.top()))
                {
                    illegals.push_back(char_);
                    illegal = true;
                    break;
                }
                else
                {
                    chunks.pop();
                }
            }
        }
        if (!illegal)
        {
            while(chunks.size()>0)
            {
                row_miss.push_back(delims.at(chunks.top()));
                chunks.pop();
            }
            missing.push_back(row_miss);
        }
    }
}

vector<int> solve(vector<string> str_data)
{
    vector<vector<char>> missing;
    vector<char> illegals;
    vector<int> results;

    scan_lines(str_data, missing, illegals);
    
    results.push_back(calc_score(illegals));
    results.push_back(calc_score(missing));

    return results;

}

int main()
{
    string filename = "../../input/day_10.txt";
    vector<string> string_data = read_file<string>(filename,true);
    
    vector<int> result = solve(string_data);
    cout << setw(30) << left << "Day 10 Part 1 solution: " << result[0] << endl;
    cout << setw(30) << left << "Day 10 Part 2 solution: " << result[1] << endl;
}