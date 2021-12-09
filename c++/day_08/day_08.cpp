#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

#include "../utils/file_reader.cpp"

using namespace std;

bool string_in_string(string string1, string string2)
{
    bool return_value;
    for (int i = 0; i < string1.size(); i++)
    {
        return_value = false;
        for (int j = 0; j < string2.size(); j++)
        {
            if (string1[i]==string2[j]) return_value = true;
        }
        if (!return_value) break;
    }
    return return_value;
}

int solve_part1(vector<string> string_data)
{
    int count = 0;
    int n = string_data.size();
    string input;

    for (int i = 0; i < n; i++)
    {
        string tmp = string_data[i];
        tmp = tmp.substr(tmp.find("|")+2, tmp.length()-1);
        
        stringstream sstream(tmp);
        while(getline(sstream,input,' '))
        {
            int strlen = input.length();
            if (strlen == 2) count++;
            if (strlen == 3) count++;
            if (strlen == 4) count++;
            if (strlen == 7) count++;
        }

    }

    return count;

}

int solve_part2(vector<string> string_data)
{

    int count = 0;
    int n = string_data.size();
    string input,input_nums, output_nums;

    for (int i = 0; i < n; i++)
    {
        map<char,string> test;
        vector<string> strings_in;
        string tmp = string_data[i];
        input_nums = tmp.substr(0, tmp.find("|")-1);
        output_nums = tmp.substr(tmp.find("|")+2, tmp.size()-1);

        stringstream sstream(input_nums);
        int index = 0;
        
        while(getline(sstream,input,' '))
        {
            sort(input.begin(), input.end());
            strings_in.push_back(input);
            
            int strlen = input.length();
            if (strlen == 2)
            {
                test.insert({'1',input});
            }
            if (strlen == 3)
            {
                test.insert({'7',input});
            }
            if (strlen == 4)
            {
                test.insert({'4',input});
            }
            if (strlen == 7)
            {
                test.insert({'8',input});
            }
        }

        for (int j = 0; j < strings_in.size(); j++)
        {
            if (strings_in[j].length() == 6)
            {
                cout << strings_in[j] << endl;
                cout << test['7'] << endl;

                if (!string_in_string(test['7'],strings_in[j]))
                {
                    test.insert({'6', strings_in[j]});
                } 
                else if (string_in_string(test['4'], strings_in[j]))
                {
                    test.insert({'9', strings_in[j]});
                }
                else
                {
                    test.insert({'0', strings_in[j]});
                }   
            }
        }

        for (int j = 0; j < strings_in.size(); j++)
        {
            if ((strings_in[j].length() == 5))
            {
                if (string_in_string(test['1'], strings_in[j]))
                {
                    test.insert({'3', strings_in[j]});
                }
                else if (string_in_string(strings_in[j],test['6']))
                {
                    test.insert({'5', strings_in[j]});
                }
                else
                {
                    test.insert({'2', strings_in[j]});
                }
            }
        }


    stringstream sstream2(output_nums);
    string output_digits = "";
    while (getline(sstream2,input,' '))
    {
        sort(input.begin(), input.end());
        for (const auto& [key, value] : test)
            if (value == input)
            {
                output_digits.push_back(key);
            }
        
    }

    count += stoi(output_digits);

    }

    return count;
}

int main()
{
    string filename = "../../input/day_08.txt";
    vector<string> str_data = read_file<string>(filename, true);

    int part_1 = solve_part1(str_data);
    int part_2 = solve_part2(str_data);

    cout << setw(30) << left << "Day 8 Part 1 solution: " << part_1 << endl;
    cout << setw(30) << left << "Day 8 Part 2 solution: " << part_2 << endl;


}