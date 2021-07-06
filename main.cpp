
//THE ASSIGNMENT TOOK 10 HOURS
#include <iostream>
#include <fstream>
using namespace std;



class Sokoban{            //Sokoban class defined
private:
   char mgame_map[6][8];  // game map is defined as a 6x8 char array
   int player_row,player_column;  //player location is stored as integers
public:
    Sokoban(char game_map[6][8]);
   Sokoban(const Sokoban &otherSokoban);
    Sokoban& operator=(const Sokoban &anotherSokoban);
    Sokoban();
    bool move_up();
   bool move_down();
    bool move_left();
    bool move_right();
   bool is_solved();
   void print_puzzle();

};

using namespace std;
template <class T2>
class node{                //define a linked list node with public next ,prev pointers and data
public:
    node<T2> *next,*prev;
    T2 data;
    node(T2 item);      //nodes are constructed with a given item as their data
};

template <class T2>
class linked_list{      //doubly linked list defined which has the same methods as the stackqueue
private:
    node<T2> *head,*tail;
public:
    linked_list();
    void push_front(T2 item);
    T2 pop_front();
    T2 pop_rear();
    bool is_empty();
};



int main()
{

char key,prev_key;
    Sokoban s,current_sokoban; //s is defined as the main sokoban that will evolve throughout the game
    linked_list<Sokoban> stackqueue; //stackqueue is now defined as a linked list
    s.print_puzzle();       //initial state of the map is printed
    stackqueue.push_front(s);   //initial state of the map is pushed into the linked list

while(!s.is_solved())  //game loop. continues until the game is solved
{
    cin>>key;
  switch (key){           //depending on the key, related movement is performed and after each movement, new state of the map is pushed into the stackqueue
        case 'w':if(s.move_up()) {stackqueue.push_front(s);s.print_puzzle();}break;
        case 's':if(s.move_down()){stackqueue.push_front(s);s.print_puzzle();}break;
        case 'a':if(s.move_left()) {stackqueue.push_front(s);s.print_puzzle();}break;
        case 'd':if(s.move_right()) {stackqueue.push_front(s);s.print_puzzle();}break;
        case 'z':        //to undo last move, last state of sokoban is popped out, previous state is also popped out to print the puzzle then pushed back in
            if(prev_key=='z'){
                cout<<"\nCan't undo twice\n";break;}  //if z is pressed twice error message is displayed
            stackqueue.pop_front();
            s=stackqueue.pop_front();
            s.print_puzzle();
            stackqueue.push_front(s);
            break;
        case 'r':           //the chronological order of the states of the map is from rear to the front in the list so when r is entered stakcqueue pops all the elemnts from rear to the front and displays  them
            while(!stackqueue.is_empty()){
                current_sokoban=stackqueue.pop_rear();
                current_sokoban.print_puzzle();
            }
            exit(1); //pressing r also finishes the game
            break;
   }
   prev_key=key; //previous input stored


}
cout<<"\n\nCongratulations, the game is solved!";




}





//LINKED LIST METHODS-----------------------------------------------------------------

template <class T2>
node<T2>::node(T2 item):data(item){} //node constructed by setting the data,pointers are not null but that's no harm

template <class T2>
linked_list<T2>::linked_list(){
    Sokoban dummy;
    head= new node<T2>(dummy);     //when linked list is constructed, head and tail are allocated as node pointers
    tail= new node<T2>(dummy);
    head->next=tail;
    tail->prev=head;     //tail is initialized as the next node of the head
}

template <class T2>
void linked_list<T2>::push_front(T2 item){  //all the nodes that are pushed from front are fit between the head and tail,head will always remain the at the beginning and tail at the end of the list
    node<T2> *new_node= new node<T2>(item); // a node is allocated with the passed item that will be added to the front
    node<T2> *temp=head->next;
    new_node->prev=head;      //new node is inserted to the next of the head
    temp->prev=new_node;
    head->next=new_node;
    new_node->next=temp;
}

template <class T2>
T2 linked_list<T2>::pop_front(){    //pops the node next to the head
    node<T2> *front_node=head->next; //front_node points the node to be removed
    node<T2> *temp=front_node->next;  //temp points to the next of the front_node
    head->next=temp;                 //front_node is removed and head is connected to the temp
    temp->prev=head;
    front_node->next=NULL;
    front_node->prev=NULL;
    return front_node->data;  //data inside the removed node is returned
}

template <class T2>
T2 linked_list<T2>::pop_rear(){    //pops the node prev to the tail
    node<T2> *rear_node=tail->prev;  //rear_node points the node to be removed
    node<T2> *temp=rear_node->prev;  //temp points the prev of the removed node
    tail->prev=temp;
    temp->next=tail;             //node is removed and its prev is connected to the tail
    rear_node->next=NULL;
    rear_node->prev=NULL;
    return rear_node->data; // data inside the removed node is returned
}
template <class T2>
bool linked_list<T2>::is_empty(){
    return head->next==tail;
}


// SOKOBAN METHODS------------------------------------------------------------------

Sokoban::Sokoban(char game_map[6][8]){   //the constructor that initializes from a char array
for(int i=0; i<6; ++i)
    for(int j=0; j<8; ++j)
        mgame_map[i][j]=game_map[i][j];
}
Sokoban::Sokoban(const Sokoban &othersokoban){  // copy constructor defined
    for(int i=0; i<6; ++i)
        for(int j=0; j<8; ++j)
            mgame_map[i][j]=othersokoban.mgame_map[i][j];
    player_row=othersokoban.player_row;
    player_column=othersokoban.player_column;


}
Sokoban& Sokoban::operator=(const Sokoban &anothersokoban){ //copy assignment op. defined
    for(int i=0; i<6; ++i)
        for(int j=0; j<8; ++j)
            mgame_map[i][j]=anothersokoban.mgame_map[i][j];
    player_row=anothersokoban.player_row;
    player_column=anothersokoban.player_column;
}

Sokoban::Sokoban(){                     // the constructor that initializes from file
string path = "Sample_puzzle.txt";
char dummy;
ifstream file;
file.open(path);
for(int i=0; i<6; ++i){
 for(int j=0; j<8; ++j){
 file >> noskipws >> mgame_map[i][j];    // characters in file assigned to game_map one by one
   if (mgame_map[i][j]=='@'||mgame_map[i][j]=='+'){    //locate the player
    player_row=i;
    player_column=j;}
 }
 file >> noskipws >> dummy;
}
file.close();
}

bool Sokoban::move_down(){
    bool move_valid;                      // boolean variable that takes 1 if the move is valid
    char current_block=mgame_map[player_row][player_column];
    char next_block=mgame_map[player_row+1][player_column];
    char two_next_block=mgame_map[player_row+2][player_column];

    if(next_block==' '||next_block=='.')   // checks the case if the below block is a space or a target
    {
        move_valid=true;
        if(current_block=='+')           // if the player is on a target, when it moves the block becomes a '.',if it is on space block becomes space
            mgame_map[player_row][player_column]='.';
        else
            mgame_map[player_row][player_column]=' ';
        if(next_block=='.')                // if the below block is a target, when the player moves onto it, it is shown as '+'
            mgame_map[player_row+1][player_column]='+';
        else                                // if the below block is free space, when the player moves onto it, it is whown as '@'
            mgame_map[player_row+1][player_column]='@';
        player_row++;
    }

    else if (next_block=='$'||next_block=='*'){  //if there is a box below,the box behind the box is checked
        if(two_next_block==' '||two_next_block=='.')   // if the block behind the box is movable into, the box and player moves, otherwise not
        {
            move_valid= true;
            if (current_block=='+')
                mgame_map[player_row][player_column]='.';
            else
                mgame_map[player_row][player_column]=' ';

            if (next_block=='*')            //if the box at the next block is on target, when it is moved, the player moves there and shown by '+'
                mgame_map[player_row+1][player_column]='+';
            else                            // if the box at the next block is on empty space, when it is moved , the player moves there and shown by '@'
                mgame_map[player_row+1][player_column]='@';

            if(two_next_block==' ')        //finally the block behind the box is checked, if it is empty when the block is moved there it is shown as '$'
              mgame_map[player_row+2][player_column]='$';
            else                          // if the block is a target, when the block moves there, it is shown as '*'
                mgame_map[player_row+2][player_column]='*';
            player_row++;
        }
        else
        move_valid=false;
    }
    else
        move_valid=false;

   return move_valid;
}

bool Sokoban::move_up(){
    bool move_valid;                      // boolean variable that takes 1 if the move is valid
    char current_block=mgame_map[player_row][player_column];
    char next_block=mgame_map[player_row-1][player_column];
    char two_next_block=mgame_map[player_row-2][player_column];

    if(next_block==' '||next_block=='.')   // checks the case if the above block is a space or a target
    {
        move_valid=true;
        if(current_block=='+')           // if the player is on a target, when it moves the block becomes a '.',if it is on space block becomes space
            mgame_map[player_row][player_column]='.';
        else
            mgame_map[player_row][player_column]=' ';
        if(next_block=='.')                // if the above block is a target, when the player moves onto it, it is shown as '+'
            mgame_map[player_row-1][player_column]='+';
        else                                // if the above block is free space, when the player moves onto it, it is shown as '@'
            mgame_map[player_row-1][player_column]='@';
        player_row--;
    }

    else if (next_block=='$'||next_block=='*'){  //if there is a box above,the box behind the box is checked
        if(two_next_block==' '||two_next_block=='.')   // if the block behind the box is movable into, the box and player moves, otherwise not
        {
            move_valid= true;
            if (current_block=='+')
                mgame_map[player_row][player_column]='.';
            else
                mgame_map[player_row][player_column]=' ';

            if (next_block=='*')            //if the box at the next block is on target, when it is moved, the player moves there and shown by '+'
                mgame_map[player_row-1][player_column]='+';
            else                            // if the box at the next block is on empty space, when it is moved , the player moves there and shown by '@'
                mgame_map[player_row-1][player_column]='@';

            if(two_next_block==' ')        //finally the block behind the box is checked, if it is empty when the block is moved there it is shown as '$'
              mgame_map[player_row-2][player_column]='$';
            else                          // if the block is a target, when the block moves there, it is shown as '*'
                mgame_map[player_row-2][player_column]='*';
            player_row--;
        }
        else
        move_valid=false;
    }
    else
        move_valid=false;

   return move_valid;
}

bool Sokoban::move_right(){
    bool move_valid;                      // boolean variable that takes 1 if the move is valid
    char current_block=mgame_map[player_row][player_column];
    char next_block=mgame_map[player_row][player_column+1];
    char two_next_block=mgame_map[player_row][player_column+2];

    if(next_block==' '||next_block=='.')   // checks the case if the right block is a space or a target
    {
        move_valid=true;
        if(current_block=='+')           // if the player is on a target, when it moves the block becomes a '.',if it is on space block becomes space
            mgame_map[player_row][player_column]='.';
        else
            mgame_map[player_row][player_column]=' ';
        if(next_block=='.')                // if the right block is a target, when the player moves onto it, it is shown as '+'
            mgame_map[player_row][player_column+1]='+';
        else                                // if the right block is free space, when the player moves onto it, it is whown as '@'
            mgame_map[player_row][player_column+1]='@';
        player_column++;
    }

    else if (next_block=='$'||next_block=='*'){  //if there is a box on the right,the box behind the box is checked
        if(two_next_block==' '||two_next_block=='.')   // if the block behind the box is movable into, the box and player moves, otherwise not
        {
            move_valid= true;
            if (current_block=='+')
                mgame_map[player_row][player_column]='.';
            else
                mgame_map[player_row][player_column]=' ';

            if (next_block=='*')            //if the box at the next block is on target, when it is moved, the player moves there and shown by '+'
                mgame_map[player_row][player_column+1]='+';
            else                            // if the box at the next block is on empty space, when it is moved , the player moves there and shown by '@'
                mgame_map[player_row][player_column+1]='@';

            if(two_next_block==' ')        //finally the block behind the box is checked, if it is empty when the block is moved there it is shown as '$'
              mgame_map[player_row][player_column+2]='$';
            else                          // if the block is a target, when the block moves there, it is shown as '*'
              mgame_map[player_row][player_column+2]='*';
            player_column++;
        }
        else
        move_valid=false;
    }
    else
        move_valid=false;

   return move_valid;
}

bool Sokoban::move_left(){
    bool move_valid;                      // boolean variable that takes 1 if the move is valid
    char current_block=mgame_map[player_row][player_column];
    char next_block=mgame_map[player_row][player_column-1];
    char two_next_block=mgame_map[player_row][player_column-2];

    if(next_block==' '||next_block=='.')   // checks the case if the left block is a space or a target
    {
        move_valid=true;
        if(current_block=='+')           // if the player is on a target, when it moves the block becomes a '.',if it is on space block becomes space
            mgame_map[player_row][player_column]='.';
        else
            mgame_map[player_row][player_column]=' ';
        if(next_block=='.')                // if the left block is a target, when the player moves onto it, it is shown as '+'
            mgame_map[player_row][player_column-1]='+';
        else                                // if the left block is free space, when the player moves onto it, it is whown as '@'
            mgame_map[player_row][player_column-1]='@';
        player_column--;
    }

    else if (next_block=='$'||next_block=='*'){  //if there is a box on the left,the box behind the box is checked
        if(two_next_block==' '||two_next_block=='.')   // if the block behind the box is movable into, the box and player moves, otherwise not
        {
            move_valid= true;
            if (current_block=='+')
                mgame_map[player_row][player_column]='.';
            else
                mgame_map[player_row][player_column]=' ';

            if (next_block=='*')            //if the box at the next block is on target, when it is moved, the player moves there and shown by '+'
                mgame_map[player_row][player_column-1]='+';
            else                            // if the box at the next block is on empty space, when it is moved , the player moves there and shown by '@'
                mgame_map[player_row][player_column-1]='@';

            if(two_next_block==' ')        //finally the block behind the box is checked, if it is empty when the block is moved there it is shown as '$'
              mgame_map[player_row][player_column-2]='$';
            else                          // if the block is a target, when the block moves there, it is shown as '*'
              mgame_map[player_row][player_column-2]='*';
            player_column--;
        }
        else
        move_valid=false;
    }
    else
        move_valid=false;

   return move_valid;
}



bool Sokoban::is_solved(){   // swipes the map to check if there is any boxes out of target left. If there isn't, the game is solved and 1 is returned.
for(int i=0; i<6; ++i)
 for(int j=0; j<8; ++j)
    if(mgame_map[i][j]=='$')
        return 0;
cout<<"Game solved";
 return 1;
}

void Sokoban::print_puzzle(){   //prints the puzzle as a 6x8 map on the console
for(int i=0; i<6; ++i){
 for(int j=0; j<8; ++j)
    cout<<mgame_map[i][j];
    cout<<endl;
}
cout<<endl;
}




