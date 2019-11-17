/*
 * A program that reads commands from a file and displays a picture on another
 * file.
 * The commands used are saying if the pen is up or down, if the pen should move
 * north, south, east or west, the distance and 2 optional commands: a bold
 * print and printing steps to the console.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void drawUpDown(fstream& paint, char direction, int numCharacters, bool boldStatus, bool down, bool printStatus);
void drawLeftRight(fstream& paint, char direction, int numCharacters, bool boldStatus, bool down, bool printStatus);
void printFile();

/*
 * this function moves the file pointer up and down on the output file
 * 
 * returns:
 *      nothing
 * parameters:
 *      fstream& paint - filestream called by reference to output to file paint
 *      char direction - gives north south east or west direction to go
 *      int numCharacters - gives the number of characters for the file pointer
 *                          to move
 *      bool boldStatus - tells function if the command needs to be printed bold
 *                        or not
 *      bool down - tells function know if pointer needs to write to screen or not
 *      bool printStatus - lets function know if command says to print to output
 */
void drawUpDown(fstream& paint, char direction, int numCharacters, bool boldStatus, bool down, bool printStatus){
    char c;
    //loop to move pointer
    for(int i = 0; i < numCharacters; i++){
        if(toupper(direction) == 'N')
            paint.seekp(-52, ios::cur);
        else{
            paint.seekp(52, ios::cur);
        }
        //if pen is down then draw
        if(down){
            //check if bold if bold print #
            if(boldStatus){
                paint.write("#", 1);
                //move pointer back 1 to offset where # was drawn
                paint.seekp(-1, ios::cur);
            }
            //if not bold print *
            else{
                //check if next character over is #
                c = paint.get();
                //move pointer back
                paint.seekp(-1,ios::cur);
                //make sure next character isn't a bold character
                if(c != '#'){
                    //if not print *
                    paint.put('*');
                    paint.seekp(-1, ios::cur);
                }
            }
        }
    }
    if(printStatus)
        printFile();
}

/*
 * this function moves the file pointer left and right on the output file
 * 
 * returns:
 *      nothing
 * parameters:
 *      fstream& paint - filestream called by reference to output to file paint
 *      char direction - gives north south east or west direction to go
 *      int numCharacters - gives the number of characters for the file pointer
 *                          to move
 *      bool boldStatus - tells function if the command needs to be printed bold
 *                        or not
 *      bool down - tells function know if pointer needs to write to screen or not
 *      bool printStatus - lets function know if command says to print to output
 */
void drawLeftRight(fstream& paint, char direction, int numCharacters, bool boldStatus, bool down, bool printStatus){
    char c;
    //loop to move pointer
    for(int i = 0; i < numCharacters; i++){
        
        if(toupper(direction) == 'E')
            paint.seekp(1, ios::cur);
        else{
            paint.seekp(-1, ios::cur);
        }
        //if pen is down then draw
        if(down){
            //check if bold if bold print #
            if(boldStatus){
                paint.put('#');
                //move pointer back 1 to offset where # was drawn 
                paint.seekp(-1,ios::cur);
            }
            //if not bold print *
            else{
                //check if next character over is #
                c = paint.get();
                //move pointer back to current character
                paint.seekp(-1,ios::cur);
                //check if next character isn't a bold character
                if(c != '#'){
                    //if not print *
                    paint.put('*');
                    paint.seekp(-1,ios::cur);
                }
            }
        }
        else{
            if(toupper(direction) == 'W'){
                paint.seekp(3, ios::cur);
            }
        }
    }
    
    if(printStatus){
        printFile();
    }
    //move pointer back to where pointer was if it moves west
    if(toupper(direction) == 'W')
    {
        paint.seekp(-numCharacters, ios::cur);
        paint.seekp(1, ios::cur);
    }
}

/*
 * this function prints what the file has written at the moment to the console
 * returns:
 *      nothing
 * parameters:
 *      nothing
 */
void printFile(){
    //open ifstream to read characters
    string line;
    ifstream print("paint.txt");
    while(!print.eof()){
        //print each character
        getline(print, line);
        cout << line << endl;
    }
    cout << endl << endl;
}

int main(){
    string input;
    char direction, ch;
    int distance;
    
    ifstream commands("commands.txt");
    fstream paint("paint.txt", ios::ate | ios::in | ios::out);
    paint.seekp(ios::beg);
    
    //loop until end of file marker is reached
    //and get character
    while(getline(commands, input)){
        
        cout << input << endl;
        
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
        
        //gets the comma
        getCommands.get();
        
        //stores direction
        getCommands.get(direction);
                
        //get comma
        getCommands.get();
        
        //get all digits including 2 digit numbers
        getCommands >> distance;
        
        //check if p and b are in command
        while(getCommands.get(ch)){
            if(toupper(ch) == 'P'){
                printStatus = true;
            }
            if(toupper(ch) == 'B'){
                boldStatus = true;
            }
        }

        //if direction is N or S call drawUpDown
        if(toupper(direction) == 'N' || toupper(direction) == 'S'){
            drawUpDown(paint, direction, distance, boldStatus, down, printStatus);
        }
        //if direction is E or W call drawLeftRight
        if(toupper(direction) == 'E' || toupper(direction) == 'W'){
            drawLeftRight(paint, direction, distance, boldStatus, down, printStatus);
            //printFile();
        }
    }
    
    //print final canvas
    printFile();
    
    //close files
    commands.close();
    paint.close();
}
