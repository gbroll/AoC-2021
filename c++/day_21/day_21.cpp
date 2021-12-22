
#include "../puzzle.hpp"

using namespace std;
typedef unsigned long long ull;

struct game_state
{
    int score[2];
    int pos[2];
    int player_turn;

};

class Puzzle: public Puzzle_base<ull>
{
    //inherit constructors from base class
    using Puzzle_base::Puzzle_base;

public:
    void parse_input();
    void solve_part1();
    void solve_part2();

    void advance_game();

private:
    int player1_startpos;
    int player2_startpos;

    vector<pair<game_state,ull>> games;
    ull wins[2] = {0};
};

void Puzzle::parse_input()
{
    player1_startpos = stoi(str_data[0].substr(str_data[0].find(':')+2));
    player2_startpos = stoi(str_data[1].substr(str_data[1].find(':')+2));
}

void Puzzle::solve_part1()
{
    bool playing = true;
    int score[2]={0}, pos[2], roll_nr = 0, roll = 0, roll_sum = 0;
    int loser;
    pos[0] = player1_startpos;
    pos[1] = player2_startpos;

    while (playing)
    {    
        for (int i = 0; i < 2; i++)
        {       
            roll_sum = 0;
            for (int j = 0; j < 3; j++)
            { 
                roll = (j + roll_nr*3) % 100 + 1;
                roll_sum += roll;
            }
            roll_nr++;
            pos[i] = (pos[i] + roll_sum - 1) % 10 + 1;
            score[i] += pos[i];
            if (score[i]>=1000)
            {
                loser = abs(i-1);
                playing = false;
                break;
            } 
        }
    }

    part1_solution = score[loser] * 3 *roll_nr;

}

void Puzzle::advance_game()
{
    vector<int> rolls   = {3,4,5,6,7,8,9}; //possible outcomes of rollig dice with 1,2,3 three times
    vector<int> spawns  = {1,3,6,7,6,3,1}; //frequencies of possible outcomes
    vector<pair<game_state,ull>> next_gen;

    for (auto const &game_ : games)
    {
        game_state game = game_.first;

        for (int i = 0; i < rolls.size(); i++)
        {
            game_state next(game);
            next.pos[game.player_turn] = (next.pos[game.player_turn] + rolls[i] - 1) % 10 +1;
            next.score[game.player_turn] = next.score[game.player_turn] + next.pos[game.player_turn];
            if (next.score[game.player_turn]>=21)
            {
                wins[game.player_turn] += game_.second*spawns[i];
            }
            else
            {
                next.player_turn = abs(next.player_turn-1);
                next_gen.push_back(make_pair(next,game_.second*spawns[i]));
            }
        }
    }
    games = next_gen;
}

void Puzzle::solve_part2()
{

    game_state init;
    init.score[0] = 0;
    init.score[1] = 0;
    init.pos[0] = player1_startpos;
    init.pos[1] = player2_startpos;
    init.player_turn = 0;

    games.push_back(make_pair(init,1));
    while (games.size()>0)
    {
        advance_game();
    }    

    part2_solution = (wins[0] > wins[1])? wins[0] : wins[1];
}

int main()
{
    int day = 21;
    bool skip_empty_lines = false;
    bool test_input = false;

    Puzzle p = Puzzle(day, skip_empty_lines, test_input);
    p.solve();

}