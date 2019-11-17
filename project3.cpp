/*
 * Sanika Buche
 *
 * A program that takes a file full of commands and with it draws
 * a picture the user wants
 *
 * commands:
 * 1 - pen is up meaning nothing prints to screen
 * 2 - pen is down meaning either * or # prints to screen
 *
 * N, S, E, W - direction to move pointer
 *
 * int - distance to move pointer
 *
 * B (optional) - prints a bold character (#) which can write over unbold character
 *
 * P (optional) - prints everything to consle
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//node structure
struct Node{
    char draw;
    Node *up, *down, *left, *right;
};

Node *head = new Node;
//Node *savePosition = head;

//protypes

//creates grid
void createGrid();

//prints file at the end
void printFile(fstream&, Node *head);

//draw north south east and west
void drawUp(fstream&, int, bool, bool, bool, Node *&);
void drawDown(fstream&, int, bool, bool, bool, Node *&);
void drawLeft(fstream&, int, bool, bool, bool, Node *&);
void drawRight(fstream&, int, bool, bool, bool, Node *&);

/*
 * A function that moves the pointer to the right in the grid of nodes
 *
 * returns: void
 * parameters:
 *      fstream& file - use to print to paint.txt
 *      int distance - how many nodes to move in the grid
 *      bool boldStatus - true if user wants output to be bold (#) false otherwise
 *      bool printStatus - true if user wants to output to consle false otherwise
 *      Node *&savePos - saves the position of pointer so other functions can start where this one finished
 */
void drawRight(fstream& file, int distance, bool boldStatus, bool down, bool printStatus, Node *&savePos){
    Node *temp = savePos;
    Node *peek = temp->right;
    
    //if pen is down move through grid while printing * or #
    if(down){
        for(int i = 0; i < distance; i++){
            //check if peek->right is null or not
            if(peek == NULL && i < distance){
                cout << "command isn't valid" << endl;
                return;
            }
            else{
                //increment temp and peek
                temp = temp->right;
                peek = peek->right;
            }
        }
        
        //bring temp back to initial position
        temp = savePos;
        for(int i = 0; i < distance; i++){
            if(boldStatus){
                //write #
                temp->draw = '#';

                //increment pointer
                temp = temp->right;
            }
            else{
                //check if next is bold
                //peek = temp->right;
                if(temp->draw != '#'){
                    temp->draw = '*';

                    //incement pointer
                    temp = temp->right;
                }
            }
        }
    }
    //if pen is up move through grid
    else{
        //check if peek->right is null or not
        for(int i = 0; i < distance; i++){
            if(peek == NULL && i <= distance){
                cout << "command isn't valid" << endl;
                return;
            }
            else{
                temp = temp->right;
                peek = peek->right;
            }
        }
    }
    //save the position of where pointer is currently at
    savePos = temp;
    
    if(printStatus)
        printFile(file, head);
}

/*
 * A function that moves the pointer to the left in the grid of nodes
 *
 * returns: void
 * parameters:
 *      fstream& file - use to print to paint.txt
 *      int distance - how many nodes to move in the grid
 *      bool boldStatus - true if user wants output to be bold (#) false otherwise
 *      bool printStatus - true if user wants to output to consle false otherwise
 *      Node *&savePos - saves the position of pointer so other functions can start where this one finished
 */
void drawLeft(fstream& file, int distance, bool boldStatus, bool down, bool printStatus, Node *&savePos){
    Node *temp = savePos;
    Node *peek = temp->left;
    
    //if pen is down move through grid while printing * or #
    if(down){
        for(int i = 0; i < distance; i++){
            //check if peek->left is null or not
            if(peek == NULL && i <= distance){
                cout << "command isn't valid" << endl;
                return;
            }
            //increment pointers
            temp = temp->left;
            peek = peek->left;
        }
        
        temp = savePos;
        for(int i = 0; i < distance; i++){
            if(boldStatus){
                //write #
                temp->draw = '#';
                
                //increment pointer
                temp = temp->left;
            }
            else{
                //check if next is bold
                if(temp->draw != '#'){
                    temp->draw = '*';
                    
                    //incement pointer
                    temp = temp->left;
                }
            }
        }
    }
    //if pen is up move through grid
    else{
        //check if peek->left is null or not
        for(int i = 0; i < distance; i++){
            if(peek == NULL && i < distance){
                cout << "command isn't valid" << endl;
                return;
            }
            temp = temp->left;
            peek = peek->left;
        }
    }
    savePos = temp;
    
    if(printStatus)
        printFile(file, head);
}

/*
 * A function that moves the pointer down in the grid of nodes
 *
 * returns: void
 * parameters:
 *      fstream& file - use to print to paint.txt
 *      int distance - how many nodes to move in the grid
 *      bool boldStatus - true if user wants output to be bold (#) false otherwise
 *      bool printStatus - true if user wants to output to consle false otherwise
 *      Node *&savePos - saves the position of pointer so other functions can start where this one finished
 */
void drawDown(fstream& file, int distance, bool boldStatus, bool down, bool printStatus, Node *&savePos){
    Node *temp = savePos;
    Node *peek = temp->down;
    
    //if pen is down move through grid while printing * or #
    if(down){
        for(int i = 0; i < distance; i++){
            //check if peek->down is null or not
            if(peek == NULL && i < distance){
                cout << "command isn't valid" << endl;
                return;
            }
            //increment
            temp = temp->down;
            peek = peek->down;
        }
        //bring temp back to initial position
        temp = savePos;
        for(int i = 0; i < distance; i++){
            if(boldStatus){
                //write #
                temp->draw = '#';
                
                //increment pointer
                temp = temp->down;
            }
            else{
                //check if next is bold
                if(temp->draw != '#'){
                    temp->draw = '*';
                    
                    //incement pointer
                    temp = temp->down;
                }
            }
        }
    }
    //if pen is up move through grid
    //check if node->left is null or not
    else{
        
        for(int i = 0; i < distance; i++){
            if(peek->down == NULL && i < distance){
                cout << "command isn't valid" << endl;
                return;
            }
            else{
                temp = temp->down;
                peek = peek->down;
            }
        }
    }
    //save the position of where pointer is currently at
    savePos = temp;
    
    if(printStatus)
        printFile(file, head);
}

/*
 * A function that moves the pointer up in the grid of nodes
 *
 * returns: void
 * parameters:
 *      fstream& file - use to print to paint.txt
 *      int distance - how many nodes to move in the grid
 *      bool boldStatus - true if user wants output to be bold (#) false otherwise
 *      bool printStatus - true if user wants to output to consle false otherwise
 *      Node *&savePos - saves the position of pointer so other functions can start where this one finished
 */
void drawUp(fstream& file, int distance, bool boldStatus, bool down, bool printStatus, Node *&savePos){
    Node *temp = savePos;
    Node *peek = temp->up;
    
    //if pen is down move through grid while printing * or #
    //check if node->up is null or not
    if(down){
        for(int i = 0; i < distance; i++){
            if(peek == NULL){
                cout << "command isn't valid" << endl;
                return;
            }
            temp = temp->up;
            peek = peek->up;
        }
        //bring temp back to initial position
        temp = savePos;
        for(int i = 0; i < distance; i++){
            if(boldStatus){
                //write #
                temp->draw = '#';
                
                //increment pointer
                temp = temp->up;
            }
            else{
                //check if next is bold
                if(temp->draw != '#'){
                    temp->draw = '*';
                    
                    //incement pointer
                    temp = temp->up;
                }
            }
        }
    }
    //if pen is up move through grid
    else{
        for(int i = 0; i < distance; i++){
            //check if peek->up is null or not
            if(peek == NULL){
                cout << "command isn't valid" << endl;
                return;
            }
            else{
                temp = temp->up;
                peek = peek->up;
            }
        }
    }
    //save the position of where pointer is currently at
    savePos = temp;
    
    if(printStatus)
        printFile(file, head);
}

/*
 * A function that creates a 50 x 50 grid of linked lists
 *
 * returns: void
 * parameters: none
 */
void createGrid()   {
    Node *temp1 = head, *node, *temp2;
    
    temp1->draw = ' ';
    
    //connecting first row
    for(int i = 0; i < 50; i++){
        temp2 = new Node;
        
        //fill node
        temp2->draw = ' ';
        
        //connect 2 pointers
        temp1->right = temp2;
        temp2->left = temp1;
        
        //move temp1 pointer forwards
        temp1 = temp1->right;
    }
    
    temp1 = head;
    
    for(int i = 0; i < 49; i++){
        temp2 = new Node;
        Node *temp3 = temp2;
        
        for(int j = 0; j < 50; j++){
            node = new Node;
            
            temp2->draw = ' ';
            
            //connect pointers
            temp2->right = node;
            node->left = temp2;
            
            temp1->down = temp2;
            temp2->up = temp1;
            
            //move pointers forward
            temp1 = temp1->right;
            temp2 = temp2->right;
        }
        temp1 = temp3;
    }
}

/*
 * A function that recursivly (change it) prints the output to the file
 *
 * returns: void
 * parameters:
 *      fstream &paint - paint is the file the output will print to
 *      Node *head - head pointer to linked list grid
 */
void printFile(fstream& paint, Node *head){
    Node *current = head;
    Node *temp = head;

    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            paint << current->draw;
            cout << current->draw;
            current = current->right;
        }
        current = temp->down;
        temp = temp->down;
        paint << endl;
        cout << endl;
    }
    cout << "done with output" << endl;
    paint << "Done with output" << endl;
}


int main() {
    head->up = NULL;
    head->left = NULL;
    Node *savePosition = head;
    string input;
    char direction, ch;
    int distance;
    
    createGrid();
    
    //set file stream
    ifstream commands;
    fstream paint;
    
    commands.open("commands.txt");
    paint.open("paint.txt", ios::in | ios::out | ios::app);

    //loop until end of file marker is reached and get character
    while(getline(commands, input)){
    
        bool down = false;
        bool boldStatus = false;
        bool printStatus = false;
        stringstream getCommands;

        getCommands.str(input);

        getCommands.get(ch);
        if(ch == '1'){
            down = false;
        }
        
        //if command is 2 pen is down
        else if(ch == '2'){
            down = true;
        }
        else if(ch != '1' || ch != '2'){
            getline(commands, input);
        }
        //cout << "ch: " << ch << endl;

        //gets the comma
        getCommands.get();

        //stores direction
        getCommands.get(direction);
        //cout << "direction: " << direction << endl;

        //get comma
        getCommands.get();

        //get all digits including 2 digit numbers
        getCommands >> distance;
        //cout << "distance: " << distance << endl;

        //check if p and b are in file
        while(getCommands.get(ch)){
            if(toupper(ch) == 'P'){
                printStatus = true;
            }
            if(toupper(ch) == 'B'){
                boldStatus = true;
            }
        }

        //if direction is N call drawUp
        if(toupper(direction) == 'N')
            drawUp(paint, distance, boldStatus, down, printStatus, savePosition);

        //if direction is S call drawDown
        if(toupper(direction) == 'S')
            drawDown(paint, distance, boldStatus, down, printStatus, savePosition);

        //if direction is W call drawLeft
        if(toupper(direction) == 'W')
            drawLeft(paint, distance, boldStatus, down, printStatus, savePosition);

        //if direction is E call drawRight
        if(toupper(direction) == 'E')
            drawRight(paint, distance, boldStatus, down, printStatus, savePosition);
    }
    
    //print everything to file
    printFile(paint, head);

    //close file
    commands.close();
    paint.close();
    
    return 0;
}
