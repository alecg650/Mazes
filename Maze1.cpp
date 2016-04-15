//Maze Project #1:
//Alec Griego
//1/17/15
//CST-200
// Luke Kanuchok
//This program takes an input file containing dimensions for a maze, then prints the maze with a starting point, ending poimt, and the walls of the maze.
//Collaborated with Connor Segneri, Michael Hesseltine, Brandon Wood, Eric Weimer, Lamarr Pace, Alec Ferko.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <sstream>
#include <array>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

//The class that sets all basic function for creating the maze.
class Maze_Assign
{
private:

    //Declare initial variables for all dimensions
    string MazeArray[100][100];
    int Xmax, Ymax;
    int xstart, ystart;
    int xfinish, yfinish;

public:
    void printMaze();
    void dot_maze();
    void set_range(int x, int y);
    void set_wall(int x, int y);
    void Set_StartFinish(int sx, int sy, int fx, int fy);
};

//Declare the maze to work with
Maze_Assign maze;

void Maze_Assign::printMaze()
//Function that prints the formatted maze with the points needed.
{
    int LoopCont = 0;
    cout << "  ";
    for (int i = 0; i < maze.Xmax; i++)
    {
        if (i>9) {
            cout << " " << i;
        }
        else {
            cout << " " << i << " ";
        }
    }
    cout << endl;
    for (int k = 0; k < maze.Ymax; k++)
    {
        while (LoopCont < 3)
        {
            if (LoopCont == 1)
            {
                if (k>9) {
                    cout << k;
                }
                else {
                    cout << k << " ";
                }
            }
            if (LoopCont != 1)
            {
                cout << "  ";
            }

            for (int j = 0; j < maze.Xmax; j++)
            {
                cout << MazeArray[j][k];
            }
            LoopCont += 1;
            cout << endl;
        }
        LoopCont = 0;
    }
    cout << endl;
}

void Maze_Assign::dot_maze() {
    //Sets all of the spaces in the array to dots
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            maze.MazeArray[i][j] = "...";
        }
    }
}

void Maze_Assign::set_range(int x, int y) {
    //sets the range of the maze and the start and finish points
    Xmax = x + 1;
    Ymax = y + 1;
}

void Maze_Assign::Set_StartFinish(int sx, int sy, int fx, int fy) {
    MazeArray[sx][sy] = "-S-";
    MazeArray[fx][fy] = "-F-";
}

void Maze_Assign::set_wall(int x, int y) {
    MazeArray[x][y] = "XXX";
}



int main()
{


    //Creates a vector and imports the data from the file.
    vector<string> data;
    ifstream inputFile("input.txt");
    while (inputFile) {
        string s;
        if (!getline(inputFile, s)) break;
        istringstream ss(s);
        while (ss)
        {
            //Adds each item from the string into the vector dellimeted by period.
            string s;
            if (!getline(ss, s, '.')) break;
            data.push_back(s);
        }
    }

    string dimensions = data.at(0);
    string start = data.at(2);
    string finish = data.at(4);
    string walls = data.at(6) += data.at(7) += data.at(8) += data.at(9) += data.at(10) += data.at(11) += data.at(12) += data.at(13) += data.at(14) += data.at(15) += data.at(16);
    
    //Delete the spaces from the dimensions
    dimensions.erase(remove(dimensions.begin(), dimensions.end(), ' '), dimensions.end());

    //Create a vector that splits by comma.
    stringstream test(dimensions);
    string segment;
    vector<string> range_list;
    while (getline(test, segment, ','))
    {
        range_list.push_back(segment);
    }

    //Remove the spaces and parenthesis from the start and finish
    start.erase(remove(start.begin(), start.end(), ' '), start.end());
    start.erase(remove(start.begin(), start.end(), '('), start.end());
    start.erase(remove(start.begin(), start.end(), ')'), start.end());
    finish.erase(remove(finish.begin(), finish.end(), ' '), finish.end());
    finish.erase(remove(finish.begin(), finish.end(), '('), finish.end());
    finish.erase(remove(finish.begin(), finish.end(), ')'), finish.end());

    //Create a new vector that splits by the comma for the start list	
    stringstream start_test(start);
    vector<string> start_list;
    while (getline(start_test, segment, ','))
    {
        start_list.push_back(segment);
    }


    //Create a new vector that splits by the comma for the end list
    stringstream finish_test(finish);
    vector<string> finish_list;
    while (getline(finish_test, segment, ','))
    {
        finish_list.push_back(segment);
    }

    //Remove the spaces and parens for the walls.
    walls.erase(remove(walls.begin(), walls.end(), ' '), walls.end());
    walls.erase(remove(walls.begin(), walls.end(), '('), walls.end());
    walls.erase(remove(walls.begin(), walls.end(), ')'), walls.end());
    walls.erase(remove(walls.begin(), walls.end(), ' '), walls.end());

    //Create a new vector that splits by the comma for the walls
    stringstream walls_test(walls);
    vector<string> walls_list;
    while (getline(walls_test, segment, ','))
    {
        walls_list.push_back(segment);
    }


    //Sets array to all dots
    maze.dot_maze();


    //Sets the dimensions, the start, and the finish points from the file
    maze.set_range(atoi(range_list.at(0).c_str()),
                   atoi(range_list.at(1).c_str()));

    //Sets the start and end points from the file
    maze.Set_StartFinish(atoi(start_list.at(0).c_str()), atoi(start_list.at(1).c_str()),
                         atoi(finish_list.at(0).c_str()),
                         atoi(finish_list.at(1).c_str()));


    //Set the walls from the file
    int testt = -2;
    for (int y = 1; y<walls_list.size(); y += 2) {
        testt += 2;
        if (testt != '.' || y != '.') {
            maze.set_wall(atoi(walls_list.at(testt).c_str()),
                          atoi(walls_list.at(y).c_str()));
        }
    }

    //Print the maze
    maze.printMaze();

    return 0;
}