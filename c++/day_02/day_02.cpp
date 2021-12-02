#include <regex>

#include "../utils/file_reader.cpp"

using namespace std;



int solve(vector<string> data, bool can_aim)
{

    int result;
        
    /*
    Variable for submarine state:
    [x_pos, aim, y_pos] if can_aim == true
    [x_pos, y_pos, aim] if can_aim == false
    */
    int state[3] {0,0,0}; 

    std::string regex_string = "^(\\w+)\\s([0-9]+)$";
    regex regex(regex_string);
    smatch matches;

    for (int i = 0, n = data.size(); i < n; i++)
    {
        regex_search(data[i],matches,regex);

        string dir = matches.str(1);
        int length = stoi(matches.str(2));

        if (dir == "forward")
        {
            state[0] += length;
            state[2] += length * state[1]; //dummy value if can_aim == false
        }
        else if (dir == "up")
        {
            state[1] -= length;
        }
        else if (dir == "down")
        {
            state[1] += length;
        }
    }

    can_aim? result = state[0]*state[2] : result = state[0]*state[1];
    return result;
    
}

int main()
{
    string filename = "../../input/day_02.txt";
    vector<string> data = read_file<string>(filename);

    int part_1 = solve(data, false);
    int part_2 = solve(data, true);

    cout << "Day 1 Part 1 solution: " << part_1 << endl;
    cout << "Day 1 Part 2 solution: " << part_2 << endl;

    return 0;

}