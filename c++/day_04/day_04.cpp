#include <iostream>
#include <sstream>

#include "../utils/file_reader.cpp"

using namespace std;

const int N = 5;

struct board
{
    int nums[N][N];
    int checks[N][N] = {0};
    int row_checks[5] = {0};
    int col_checks[5]  = {0};
    int unchecked_total = 0;
    bool winner = false;
};

vector<int> get_nums(string data, char delim)
{
    vector<int> output;
    string str;
    int num;

    stringstream sstream(data);
    while (getline(sstream, str, delim))
    {
        if (!str.empty())
        {
            stringstream s(str);
            s >> num;
            output.push_back(num);
        }
    }

    return output;

}

vector<board> get_boards(vector<string> data)
{
    vector<board> boards;
    board new_board;
    string line;

    int row = 0;
    int n_rows = data.size();
    while (row < n_rows)
    {
        line = data[row];
        //empty line signals new board
        if (line.empty())
        {
            for (int i = 0; i < N; i ++)
            {
                row +=1;
                line = data[row];
                vector<int> nums = get_nums(line,' ');
                for (int j = 0; j < N; j++)
                {
                    new_board.nums[i][j] = nums[j];
                }
            }
            boards.push_back(new_board);
        } 
        row +=1;
    }

    return boards;

}

void play_bingo(vector<board> boards, vector<int> nums, board &winner_board, int &winner_num, bool return_first)
{
    
    for (auto num:nums)
    {
        int n = boards.size();
        
        for (auto &brd : boards)
        {
            if (brd.winner)
            {
                continue;
            }

            brd.unchecked_total = 0;

            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (brd.nums[i][j] == num)
                    {
                        brd.checks[i][j] = 1;
                        brd.row_checks[i] += 1;
                        brd.col_checks[j] += 1;                 
                    }

                    if (brd.checks[i][j] == 0)
                    {
                        brd.unchecked_total += brd.nums[i][j];
                    }

                    if ((brd.row_checks[i] == N || brd.col_checks[j] == N) && (!brd.winner))
                    {
                        brd.winner = true;
                    }
                }
            }
            if (brd.winner)
            {
                winner_board = brd;
                winner_num = num;
                if (return_first)
                {
                    return;
                } 
            }
        }
    }

    return;
}

int solve(vector<string> data, bool stop_at_first)
{
    vector<int> nums = get_nums(data[0], ',');
    vector<board> boards = get_boards(data);

    int winner_num;
    board winner_board;
    play_bingo(boards, nums, winner_board, winner_num,stop_at_first);

    return winner_board.unchecked_total * winner_num;

}

int main()
{

    string filename = "../../input/day_04.txt";
    vector<string> data = read_file<string>(filename,false);
    
    int part_1 = solve(data,true);
    int part_2 = solve(data,false);

    cout << "Day 4 Part 1 solution: " << part_1 << endl;
    cout << "Day 4 Part 2 solution: " << part_2 << endl;

    return 0;
}