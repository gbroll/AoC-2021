#include <regex>
#include <math.h>

#include "../utils/file_reader.cpp"
#include "../utils/result_printer.cpp"

struct area
{
    int xmin,xmax,ymin,ymax;
};

area parse(vector<string> str_data)
{
    area target;
    string regex_str = "x=(-?[0-9]+)..(-?[0-9]+), y=(-?[0-9]+)..(-?[0-9]+)$";
    regex regex_obj(regex_str);
    smatch matches;
    regex_search(str_data[0], matches, regex_obj);

    target.xmin = stoi(matches.str(1));
    target.xmax = stoi(matches.str(2));
    target.ymin = stoi(matches.str(3));;
    target.ymax = stoi(matches.str(4));

    return target;

}

int solve_part1(area t)
{
    int v0_ymax = abs(t.ymin)-1;  //the maximum y velocity still hitting y_min
    int y_max = v0_ymax * (v0_ymax+1)/2; //integrate to velocity zero (arithmetic series sum)

    return y_max;

}

int solve_part2(area t)
{

    int v0x_min = int( -.5+sqrt((2.0d*double(t.xmin)+0.25d)));
    int v0x_max = t.xmax;
    int v0y_min = t.ymin;
    int v0y_max = abs(t.ymin) -1 ;

    int x,y,vx,vy,i;

    int n = 0;
    for (int v0x = v0x_min; v0x <= v0x_max; v0x++)
    {
        for (int v0y = v0y_min; v0y <= v0y_max; v0y++)
        {
            vy = v0y;
            vx = v0x;
            
            x = y = 0;
            while (true)
            {
                x += (vx > 0) * vx;
                y += vy;
                if (x > t.xmax || y < t.ymin)
                {
                    //this is a miss
                    break;
                }
                else if (x >= t.xmin && x <= t.xmax)           
                {
                    if (y >= t.ymin && y <= t.ymax)
                    {
                        n++;
                        break;
                    }
                }
                vx--;
                vy--;
            }
        }
    }

    return n;
}

int main()
{
    int day = 17;

    auto start = chrono::high_resolution_clock::now();
    
    string filename = "../../input/day_" + to_string(day) + ".txt";
    vector<string> string_data = read_file<string>(filename,false);
    area target = parse(string_data);

    auto parsed = chrono::high_resolution_clock::now();

    int part_1 = solve_part1(target);
    int part_2 = solve_part2(target);

    auto solved = chrono::high_resolution_clock::now();
    
    vector<chrono::high_resolution_clock::time_point> time_stamps{start , parsed, solved};
    print_results<int>(day, part_1, part_2, time_stamps);

    return 0;
    
}

