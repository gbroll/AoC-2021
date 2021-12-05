#include <iostream>
#include <regex>

#include "../utils/file_reader.cpp"

struct line
{
    int x1;
    int y1;
    int x2;
    int y2;
};


vector<line> parse(vector<string> data, vector<vector<int>> &grid)
{
    vector<line> output;
    int x_max_grid = 0, y_max_grid = 0;
    int x1, x2, y1, y2;

    std::string regex_string = "^([0-9]+),([0-9]+)\\s->\\s([0-9]+),([0-9]+)$";
    regex regex(regex_string);
    smatch matches;

    int n_rows = data.size();
    for (int i = 0; i < n_rows; i++)
    {
        bool match = regex_search(data[i],matches,regex);
        if (match)
        {
            int x1 = stoi(matches[1]);
            int y1 = stoi(matches[2]);
            int x2 = stoi(matches[3]);
            int y2 = stoi(matches[4]);

            line new_line = {x1, y1, x2, y2};
            
            output.push_back(new_line);

            if (x1 > x_max_grid){x_max_grid = x1;}
            if (x2 > x_max_grid){x_max_grid = x2;}
            if (y1 > y_max_grid){y_max_grid = y1;}
            if (y2 > y_max_grid){y_max_grid = y2;}
        }
    }
    //output.push_back(grid_diagonal);
    grid.resize(x_max_grid + 1, vector<int> (y_max_grid + 1,0));

    return output;
}

int draw_lines(vector<line> lines,vector<vector<int>> grid, bool skip_diagonals = true)
{
    int count = 0;
    int n_lines = lines.size();
    int row_step,col_step;

    for (auto line : lines)
    {
        if (line.x1 == line.x2)
        {
            //vertical line
            line.y1 > line.y2? row_step = -1 : row_step = 1;
            int row = line.y1;
            while (row != (line.y2+row_step))
            {
                if (grid[line.x1][row] == 1)
                {
                    count++;
                }
                grid[line.x1][row]++;
                row += row_step;
            }

        }
        else if (line.y1 == line.y2)
        {
            //horizontal line
            line.x1 > line.x2? col_step = -1 : col_step = 1;
            int col = line.x1;
            while (col != (line.x2+col_step))
            {
                if (grid[col][line.y1] == 1)
                {
                    count++;
                }
                grid[col][line.y1]++;
                col+= col_step;
            }
        }
        else
        {
            if (skip_diagonals)
            {
                continue;
            }    
            //45 degree diagonal line
            int col = line.x1;
            line.x1 > line.x2? col_step = -1 : col_step = 1;
            int row = line.y1;
            line.y1 > line.y2? row_step = -1 : row_step = 1;
            while (col != (line.x2 + col_step))
            {
                if (grid[col][row] == 1)
                {
                    count++;
                }
                grid[col][row]++;
                col += col_step;
                row += row_step;
            }
        }
    }
    return count;
}

int main()
{

    string filename = "../../input/day_05.txt";
    vector<string> data = read_file<string>(filename,true);
    vector<vector<int>> grid;
    vector<line> lines = parse(data, grid);

    int part_1 = draw_lines(lines, grid, true);
    int part_2 = draw_lines(lines, grid, false);

    cout << "Day 5 Part 1 solution: " << part_1 << endl;
    cout << "Day 5 Part 2 solution: " << part_2 << endl;

    return 0;

}