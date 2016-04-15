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
#include <string>
#include <sstream>
#include <array>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;


//Create the class for the doubly linked list
 class DLList{
    public:

        //The two members of what is included in a node. 
        struct node
        {
            string data;
            struct node *next;
            struct node *prev;
            struct node *top;
            struct node *bottom; 
        };

        //Set the head and the tail
        node* head;
        node* tail;

        //Set the constructor to create null pointers for the head and tail. 
        DLList(){
            head = nullptr;
            tail = nullptr;
        }
        
        //Method for reversing a list in place. 
        void reverseList(){
            DLList newList;
            while (head != NULL)
            {
                newList.newNodeAtFront(this -> head -> data);
                head = head -> next;
            }

            head = newList.head;
            tail = newList.tail;
        }

        //Method for copying a list to a new list. 
        DLList copyList(){
            DLList newList2;
            node *temp = head;
            while (temp != NULL)
            {
                newList2.newNodeAtEnd(temp -> data);
                temp = temp -> next;
            }

            return newList2;
        }

        //Add a new node at the beginning of a list
        void *newNodeAtFront(string key)
        {
            node *newNode = new node;
            newNode -> data = key;
            if (head == NULL){
                head = newNode;
                tail = newNode;
            }

            else
            {
                newNode -> next = head;
                head -> prev = newNode;
                head = newNode;
            }
        }

        //Create a new node at the end. 
        void *newNodeAtEnd(string key)
        {
            node *newNode = new node;
            newNode -> data = key;
            if (head == NULL){
                head = newNode;
                tail = newNode;
            }

            else
            {
                tail -> next = newNode;
                newNode -> prev = tail; 
                tail = newNode;
            }


        }
         
        //Printing the List. 
        void printlist()
        {
            node* temp =head;
            while(temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }

        //Appending a list on another list. 
        void appendListonList(DLList aList)
        {
            this -> tail -> next = aList.head;
            this -> tail = aList.tail; 
            

        }

        //Removing an element at an ith position. 
        void removeElement(int position)
        {
            node *temp = head; 
            for (int i = 0; i <= position; i++)
            {
                if (i +1 == position)
                {
                    temp -> next = temp -> next -> next; 
                }
                temp = temp -> next;
            }
        }
        
        //Inserting an element at an ith position. 
        void insertElement (int position, string data1)
        {
            node *temp = head;


            for (int i = 1; i <= position; i++)
            {
                if (i == position){
                    node *nodeTest = new node;
                    nodeTest -> data = data1;
                    nodeTest -> next = temp -> next;
                    temp -> next = nodeTest; 
                }
                temp = temp -> next;
            }
        }


        //Run a comparison to see if two lists are equal. 
        bool compareLists(DLList list2)
        {
            bool ListsEqual = true;
            bool continueToken = true;
            node *temp1 = head;
            node *temp2 = list2.head;
            while (ListsEqual == true && continueToken == true)
            {
                //Case where one or both lists are null. 
                if (this -> head == NULL || list2.head == NULL)
                {
                    //If they are both null. 
                    if (this -> head == NULL && list2.head == NULL){
                        cout << "You gave me two empty lists!";
                        continueToken = false;
                    }
                    else
                    {
                    cout << "You gave me an empyty list!" << endl; 
                    ListsEqual = false;
                    } 
                }

                //If the data matches:
                else if (temp1 -> data == temp2 -> data)
                {
                    //If one or the other is null 
                    if (temp1 -> next == NULL && temp2 -> next != NULL || temp2 -> next == NULL && temp1 -> next != NULL)
                    {
                        cout << "These two functions are not equal ";
                        ListsEqual = false; 
                        break;
                    }
                    //If they both are at the end stop. 
                    else if (temp1 -> next == NULL & temp2 -> next == NULL)
                    {
                        continueToken = false;
                    }
                    //Increment the temp tokens
                    else 
                    {
                        temp1 = temp1 -> next;
                        temp2 = temp2 -> next; 
                    }
                }

                //Condition if the data is not equal
                else if (temp1 -> data != temp2 -> data)
                {
                    cout << "These are not the same";
                    ListsEqual = false;
                }


            }

            return ListsEqual;
        }
};

//The class that sets all basic function for creating the maze.
class Maze_Assign : DLList
{
private:

    //Declare initial variables for all dimensions

    int Xmax, Ymax;
    int xstart, ystart;
    int xfinish, yfinish;

public:
    DLList Maze;
    void printMaze(int dim1, int dim2);
    void dot_maze();
    void set_range(int x, int y);
    void set_wall(int x, int y);
    void CreateMaze(int dim1, int dim2);
    void populateMaze(int dim1, int dim2, int startx, int starty, int finishx, 
                            int finishy, vector<string> walls_list);
    void Set_StartFinish(int sx, int sy, int fx, int fy);
    void printRow(int indexOfX, int lengthOfX);


    void printlist()
    {
        node* temp = Maze.head;
        while(temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    Maze_Assign()
    {
        DLList Maze; 

    }
};

//Declare the maze to work with



void Maze_Assign::CreateMaze(int dim1, int dim2)
{
    for (int i = 0; i < dim1; i++)
    {
        for (int j = 0; j < dim2; j++)
        {
           Maze.newNodeAtEnd("...");
       }
   }
    //Maze.printlist();
}

void Maze_Assign::populateMaze (int dim1, int dim2, int startx, int starty, int finishx, int finishy, vector<string> walls_list)
{
    node* temp = Maze.head; 
    int testt = -2;
    int wallsx;
    int wallsy;
    for (int j = 1; j<walls_list.size(); j += 2) 
     {
                    testt += 2;
                    if (testt != '.' || j != '.') 
                    {
                        wallsx = atoi(walls_list.at(testt).c_str());
                        wallsy = atoi(walls_list.at(j).c_str());
                        //return wallsx, wallsy;
                        
                    }
     }


    cout << wallsx << wallsy << "The walls";
    for (int x = 0; x <= dim1; x++)
    {
        for (int y = 0; y <= dim2; y++)
        {
            // if (startx == x && starty == y)
            // {
                // temp -> data = "-s-";
                // temp = temp -> next; 
                // temp = temp -> next; 
                // y += 1;
                // x += 1;
            

            if (finishx == x && finishy == y)
            {
                temp -> data = "-f-";
                temp = temp -> next; 
            }
            
            if (wallsx == x && wallsy == y)
            {
                temp -> data = "XXX";
            }

            //temp = temp -> next; 


            if (temp == NULL)
            {
                cout << "here!";
                break;
            }
        }
        temp = temp -> next;
 
    }
    
    //Maze.printlist();
}

void Maze_Assign::printRow(int indexOfX, int lengthOfX)
{
    node* temp = Maze.head;
    //cout << "the data is" << temp -> data; 
    for (int i = 0; i < indexOfX; i++)
    {
        temp = temp -> next;    
    }
    for (int j = 0; j < lengthOfX; j++)
    {
         cout << temp -> data << " " ; 
    }
    cout << endl;
}

void Maze_Assign::printMaze(int dim1, int dim2)
//Function that prints the formatted maze with the points needed.
{
    //int test = 0; 
    cout << "Here" << endl;
    node* temptest = Maze.head;

    for (int i = 0; i <= dim1 ; i++)
    {
        cout << i << "   ";
    }
    cout <<  endl;

    while(temptest -> next != NULL)
    {

        printRow(0, dim2);
        temptest = temptest -> next; 
    }
    
    
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

    //Sets the dimensions from the file
    int dim1 = atoi(range_list.at(0).c_str());
    int dim2 = atoi(range_list.at(1).c_str());

    //Sets the start and end points from the file
    int startx= atoi(start_list.at(0).c_str()); 
    int starty = atoi(start_list.at(1).c_str());
    int finishx = atoi(finish_list.at(0).c_str());
    int finishy = atoi(finish_list.at(1).c_str());

     cout << dim1 << dim2 << startx << starty << finishx << finishy;
    /*//Set the walls from the file
    int testt = -2;
    for (int y = 1; y<walls_list.size(); y += 2) {
        testt += 2;
        if (testt != '.' || y != '.') {
            maze.set_wall(atoi(walls_list.at(testt).c_str()),
                          atoi(walls_list.at(y).c_str()));
        }
    }
*/


    //Make the maze 
    Maze_Assign theMaze;
    theMaze.CreateMaze(dim1, dim2);
    //theMaze.printRow(0, 3);
    //theMaze.printRow(3, 3);

    //theMaze.printlist();
    theMaze.populateMaze(dim1, dim2, startx, starty, finishx, finishy, walls_list);

    theMaze.printMaze(dim1, dim2);


    return 0;

}