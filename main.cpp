#include <iostream>
#include<cstdlib>
#include<string>
using namespace std;
int is_connected(char **row_ptr, int x_1, int y_1, int x_2, int y_2);                     //completed
void assign_values(char **row_ptr, char a, int position_row, int position_column);
bool validate_move(int current_position, int new_position);
void Display(char **row_ptr, int row, int column);
void initialiaze_board(char **row_ptr);
int validate_coordinates(string a, int coordinates[]);
int menu_option();
class Goats{
private:
    int goat_x;
    int goat_y;
    int id;
public:
    static int goat_id;
    static int eaten_goat_count;
    Goats(){
        id = goat_id;
        goat_id++;
    }
    void set_position(char** row_ptr, int x, int y){
        if(row_ptr[x][y] == '0'){
            row_ptr[x][y] = 'G' ;   
            goat_x = x;
            goat_y = y;
        }        
    }
    int get_x(){
        return goat_x;
    }
    int get_y(){
        return goat_y;
    }
    //....................................................................................................................................//
    int move(char **row_ptr, int x_final, int y_final){
        //0 for successful execution of the move
        //-1 for invalid move
        if(is_connected(row_ptr, goat_x, goat_y, x_final,y_final)){
            if(row_ptr[x_final][y_final] == '0'){
                //update goat's position from goat_x, goat_y to x_final, y_final and erase goat from the previous point
                row_ptr[goat_x][goat_y] = '0';          //free up initial space
                goat_x = x_final;                       //update to the new position
                goat_y = y_final;
                row_ptr[goat_x][goat_y] = 'G';
                return 0;
            }
            else{
                return -1;
            }
        }
        else{
            return -1;     //goat is asked to go between two unconnected points
        }
    }
    //....................................................................................................................................//
    // void eaten(char **row_ptr){
    //     row_ptr[goat_x][goat_y] = '0';
    // }
};
class Tiger{
private:
    int tiger_x;
    int tiger_y;
    int id;
public:
    static int tiger_id;
    Tiger(){
        id = tiger_id;
        tiger_id++;
    }
    void set_position(char ** row_ptr, int x, int y){            //set position
        tiger_x = x;
        tiger_y = y;
        row_ptr[x][y] = 'T';                                    // put T on the board
    }
    int get_x_tiger(){
        return tiger_x;
    }
    int get_y_tiger(){
        return tiger_y;
    }
    int get_id(){
        return id;
    }
//................................................................................................................................//
    int is_valid(char ** row_ptr, int x_final, int y_final){
        //1 - tiger moves normally, 2- tiger eats,          valid moves
        //rest are invalid
        // 3 - invalid, 1 step move. asked to go to a point which already has something, ....
        //4 - points are not connected 5-either no goat in between or something occupies the last step in 2 move
        double distance = sqrt(pow((x_final - tiger_x),2)+pow((y_final - tiger_y),2) );
        int return_value = -1;
        if((distance == 1 || distance == sqrt(2))){
            if(is_connected(row_ptr,tiger_x,tiger_y,x_final, y_final)){
                if(row_ptr[x_final][y_final] == '0'){           //valid move normal move
                    return_value = 1;
                }
                else{
                    return_value = 3;
                }
            }
            else{//asked to move to an unconnected point 
            return_value = 4;
            }
        }
        if ((distance == 2 || distance == sqrt(8))){                //tiger moves 2 steps
            int mid_x, mid_y;                       //find the midpoint
            mid_x = (tiger_x+ x_final)/2;
            mid_y = (tiger_y + y_final)/2;
            if(row_ptr[mid_x][mid_y] == 'G' && row_ptr[x_final][y_final] == '0'){       //if there is a goat in between and empty space at last
                return_value = 2;
            }
            else{
                return_value = 5;
            }
        }
        return return_value;
    }
//................................................................................................................................//
    void move(char ** row_ptr, int x_final, int y_final){
        int validity_type = is_valid(row_ptr, x_final, y_final);
        if(validity_type == 1){
            row_ptr[tiger_x][tiger_y] = '0';        //initial position is freed
            tiger_x = x_final;                      // position of tiger is updated
            tiger_y = y_final;
            this->set_position(row_ptr,tiger_x, tiger_y);
        }
        else if(validity_type == 2){
            int mid_x, mid_y;
            mid_x = (tiger_x+ x_final)/2;
            mid_y = (tiger_y + y_final)/2;
            row_ptr[mid_x][mid_y] = '0';
            Goats:: eaten_goat_count++;              //the number of eaten goats is increased
            row_ptr[tiger_x][tiger_y] = '0';        // since tiger moves to new position, previous position is empty
            tiger_x = x_final;                      // position of tiger is updated
            tiger_y = y_final;
            this->set_position(row_ptr,tiger_x, tiger_y);
        }
        else{
            cout <<"Invalid move. Enter a valid move."<<endl;
        }
    }
//....................................................................................................................................//
    bool is_restricted(char** row_ptr){            //false/0 =  not restricted........true/1 = restricted
        bool restrict = true;
        for(int i= 0 ; i < 5; i++){
            for(int j = 0; j< 5; j++){
                    if(this-> is_valid(row_ptr, i,j)== 1 || this-> is_valid(row_ptr,i,j)==2) {         //i,j are the final position
                        restrict =  false;
                        break;
                    }
            }
            if(restrict == false){
                break;
            }
        }
        return restrict;
    }
//....................................................................................................................................//
};
int Goats:: goat_id = 0;
int Goats:: eaten_goat_count = 0;
int Tiger:: tiger_id = 0;
void first_20_moves(Tiger t[], Goats g[], char **row_ptr);
void remaining_moves(Tiger t[], Goats g[], char **row_ptr);
//....................................................................................................................................//
int main() {
    int user_choice;
    cout<<".................................................................................................................................."<<endl<<endl;
    cout<<"                                         Welcome to Baghchal"<<endl<<endl;
    cout<<"Baghchal is a 2 player game between Tigers and Goats."<<endl<<endl;
    cout<<"There are 4 Tigers and 20 Goats. 4 Tigers start from the corners of the board."<<endl<<endl;
    cout<<"The game is played in turns. The Goats move first and the Tigers move next. "<<endl<<endl;
    cout<<"The aim of the Tiger is to eat Goats and the aim of the Goats is to restrict the Tiger so they have no valid moves."<<endl<<endl;
    cout<<"For the first 20 moves, the Goats can just be assigned on the board while the Tiger can be moved."<<endl<<endl;
    cout<<"For the Tiger to move, enter the coordinates of the tiger you wish to move. First enter the rows then the column."<<endl<<endl;
    cout<<"Then enter the coordinates you wish to move the selected tiger to."<<endl<<endl;
    cout<<"After all the goats are put on the board, the goats can be moved between the points that are joined by lines."<<endl<<endl;
    cout<<"The Tigers can eat the goat by jumping over the goat in a straight line to the point just behind the goat if the point is empty."<<endl<<endl;
    cout<<"The Tigers can win the match if 5 goats are eaten."<<endl<<endl;
    cout<<"The Goats can win the match if all 4 tigers have no valid moves (All Tigers are restricted)"<<endl<<endl;
    cout<<"NOTE: WHILE ENTERING THE COORDINATES, ENTER THEM IN THE SAME LINE TO AVOID ERRORS."<<endl<<endl;
    cout<<"Any formatting such as (1,2) or 1 2 or [1,2] etc. are acceptable for the input of coordinates."<<endl<<endl;
    cout<<"...................................................................................................................................."<<endl<<endl;
        user_choice = menu_option();
        system("clear");
        if(user_choice == 1){
            Tiger t[4];
            Goats G[20];
            char **row_ptr;
            row_ptr = new char *[5];
            initialiaze_board(row_ptr);
            first_20_moves(t, G, row_ptr);
            remaining_moves(t, G, row_ptr);
            for(int i = 0; i<5; i++){
                delete [] row_ptr[i];
            }
            delete [] row_ptr;
        }
        else if(user_choice == 3){
            cout<<"Exiting the Game......"<<endl;
        }
    return 0;
}

//....................................................................................................................................//
int is_connected(char **row_ptr, int x_1, int y_1, int x_2, int y_2){           //enter the coordinates(x1,y1) and (x2,y2) and find out if they are connected in the board
    int connected = 0;
    double dist = sqrt(pow(x_2-x_1,2)+pow(y_2-y_1,2) );
    double sqrt2 = sqrt(2);
    if (abs(x_2-x_1)==0 && abs(y_2-y_1) == 1)       //horizontal connecting line
    {
        connected = 1;
    }
    else if (abs(x_2-x_1) == 1 && abs(y_2-y_1) == 0){       //vertical lines
        connected = 1;
    }
    else if(dist == sqrt2){         //slanted lines
        if(((x_1 == y_1) && (x_2 ==y_2))
           ||((x_1+y_1 ==4) &&(x_2+y_2 ==4))
           ||((x_1-y_1 ==2) && (x_2-y_2==2))
           ||((x_1+y_1 ==6)&&(x_2+y_2==6))
           ||((y_1-x_1==2) &&(y_2-x_2 ==2))
           || ((x_1+y_1==2) && (x_2+y_2==2)))
        {
            connected = 1;
        }
    }
    else {
        connected = 0;
    }
    return connected;
}

//....................................................................................................................................//
void Display(char **row_ptr, int row, int column){                     
    cout<< "  "<<" 0  " <<" 1  "<<" 2  "<<" 3 "<<"  4 "<<endl;
    int back_slash_start = 1; //  print( \) - backslash
    int row_back_slash_start = 1;     // if the row starts with" \ ==1, then at the end change it to / ==0")
    for(int i = 0; i<row; i++){
        cout<<" "<<i<<" ";
        for(int j = 0; j< column; j++){
            cout << *(*(row_ptr+i)+j);
            if(j!=column-1){
                cout<<"---";
            }
            if(i!=row-1){                   //to display vertical and slanted lines
                if(j == column-1){
                    cout<<endl;
                    for(int k= 0; k<5; k++){
                        if(k == 0){
                            cout<<"   ";
                        }
                        cout <<"|";
                        if(k!=column-1){
                           //check from here
                            if (back_slash_start == 1){
                                cout << " \\ ";
                                back_slash_start = 0;
                            }
                            else{
                                cout<<" / ";
                                back_slash_start = 1;
                            }
                        }
                    }
                    cout <<endl;
                }
            }
        }
        if(row_back_slash_start == 1){   //if the slash at the start was a back_slash, it needs to be a forward slash at the start of next line
            back_slash_start = 0;
            row_back_slash_start =0;
        }
        else{
            back_slash_start= 1;
            row_back_slash_start =1;
        }
    }
}

//....................................................................................................................................//
void initialiaze_board(char **row_ptr){
    for(int i = 0; i<5; i++){
        row_ptr[i] = new char [5];
        for(int j = 0; j<5; j++){
            *(*(row_ptr+i)+j) = '0';
        }
    }
}

//....................................................................................................................................//
int Select_Tiger(Tiger t[], int x, int y){          //select tiger from coordinates
    int val =-1;
    for(int i=0;i<4; i++){                  //4 is the number of tigers
        if(t[i].get_x_tiger() ==x &&t[i].get_y_tiger() == y){
            val = i;
            break;
        }
    }
    return val;
}
//....................................................................................................................................//
int Select_Goat(Goats g[], int x, int y){
    int val =-1;
    for(int i=0;i<20; i++){                  //20 is the number of goats
        if(g[i].get_x() ==x && g[i].get_y() == y){
            val = i;
            break;
        }
    }
    return val;
}
//....................................................................................................................................//
void first_20_moves(Tiger t[], Goats g[], char **row_ptr){
   // assign tigers to the corners of the board
    t[0].set_position(row_ptr,0,0);
    t[1].set_position(row_ptr,0,4);
    t[2].set_position(row_ptr,4,0);
    t[3].set_position(row_ptr,4,4);
    Display(row_ptr, 5, 5) ;             //replace 5,5 later
    cout<<endl;
    int tig_x, tig_y, gt_x, gt_y, tig_fin_x, tig_fin_y;
    int tig_select, tig_validate;
    //place the goats on the board
    bool error_checker = true;  
    string a11; 
    for(int i = 0; i<20; i++){
        cout <<"Goat Turn: "<<endl;
        int valid_goat_input = 0;
       do{      string a1;
                int validate1;
            do{
                cout<<"Enter the coordinate where you want to place the goat: "<<endl;
                if (error_checker == true){
                    getline(cin, a11); 
                    error_checker = false;  
                }
                getline(cin, a1);
                int coordinates[]={0,0};
                validate1 = validate_coordinates(a1,coordinates);
                    if(validate1 !=1){
                    cout<<"Invalid Input. Enter valid coordinates. "<<endl;
                    }
                    else{
                        gt_x = coordinates[0];
                        gt_y = coordinates[1];
                    }
            }while(validate1!=1);
            if(row_ptr[gt_x][gt_y] == '0'){
                g[i].set_position(row_ptr,gt_x,gt_y);
                valid_goat_input = 1;
            }
            else{
                cout <<"Enter a free coordinate to position your goat"<<endl;
            }
        }while(valid_goat_input == 0);
        cout<<endl;
        system("clear");
        int dead_goats;
        dead_goats =  Goats:: eaten_goat_count;
        cout<<endl<<"Total number of goats used = "<<i+1<<endl<<endl;
        cout<<"Number of dead goats = "<<dead_goats<<endl<<endl;
        //check if all the tigers are restricted or not
        int restricted_tiger_count = 0;
        for(int l = 0; l<4;l++){
            if(t[l].is_restricted(row_ptr)){              
                restricted_tiger_count ++;
            }
            if(restricted_tiger_count == 4){    //goats have won the match
                cout<< "restricted tiger count  = "<< restricted_tiger_count<<endl;
                cout <<"Goats have won the match"<<endl;
                exit(0);
            }
        }
        cout<< "restricted tiger count  = "<< restricted_tiger_count<<endl<<endl;
        Display(row_ptr, 5,5);              //replace 5,5 later with appropriate variables
        cout<< endl;
        //take in input for tiger move
        cout<<endl<<endl<<"Tiger Turn: "<<endl;
        do{
            string a2;
            int validate2 = -1;
            do{
                cout<<"Enter the coordinate of the tiger you want to move: "<<endl;
                getline(cin, a2);
                int coordinates[]={0,0};
                validate2 = validate_coordinates(a2,coordinates);
                if(validate2 !=1){
                cout<<"Invalid Input. Enter valid coordinates. "<<endl;
                }
                else{
                    tig_x = coordinates[0];
                    tig_y = coordinates[1];
                }
            }while(validate2!=1);
            tig_select = Select_Tiger(t,tig_x,tig_y);
            if(tig_select == -1){
                cout<<"Invalid input of coordinates"<<endl;
            }
            else{
                cout<<endl;
            }
        }while(tig_select==-1);
        do{
            string a3;
            int validate3=-1;
            do{
                cout<<"Enter the coordinate of the point you want the tiger to move to: "<<endl;
                getline(cin, a3);
                int coordinates[]={0,0};
                validate3 = validate_coordinates(a3,coordinates);
                if(validate3 !=1){
                cout<<"Invalid Input. Enter valid coordinates. "<<endl;
                }
                else{
                    tig_fin_x = coordinates[0];
                    tig_fin_y = coordinates[1];
                }
            }while(validate3!=1);
            tig_validate = t[tig_select].is_valid(row_ptr,tig_fin_x,tig_fin_y);    
            if(tig_validate ==1 || tig_validate ==2){
                t[tig_select].move(row_ptr,tig_fin_x,tig_fin_y);        
            }
            else{
                cout<<"Invalid move. Enter valid coordinates again."<<endl;
            }
        }while(!(tig_validate==1 || tig_validate==2));         
        system("clear");
        dead_goats =  Goats:: eaten_goat_count;
        cout<<endl<<"Total number of goats used = "<<i+1<<endl<<endl;
        cout<<"Number of dead goats = "<<dead_goats<<endl<<endl;
        Display(row_ptr, 5,5);              //replace 5,5 later with appropriate variables
        cout<< endl;
        if(dead_goats == 5){
            cout<<"The tiger has won the match";
            exit(0);                                
        }
        
    }
}
void remaining_moves(Tiger t[], Goats g[], char **row_ptr){
    system("clear");
    cout<<"first 20 moves completed. now you can move the goats"<<endl;
    string a;
    int validate;
    int tig_x, tig_y, gt_x, gt_y, tig_fin_x, tig_fin_y,goat_fin_x, goat_fin_y;
    int tig_select, tig_validate, goat_validate;            
    int goat_select;
    int check_value = -1;           //check value = 1 = goats won 2 =tiger won
    while(check_value== -1){
        int dead_goats1;
        dead_goats1 =  Goats:: eaten_goat_count;
        cout<<"Number of dead goats = "<<dead_goats1<<endl<<endl;
        Display(row_ptr, 5, 5) ;             //replace 5,5 later
        cout<<endl;
        cout <<"Goat Turn: "<<endl;
        int valid_goat_input = 0;                   //check if this is needed or not
        //select which goat you want to move
        do{
            do{
                cout<<"Enter the coordinate of the goat you want to move: "<<endl;
                getline(cin, a);
                int coordinates[]={0,0};
                validate = validate_coordinates(a,coordinates);
                if(validate !=1){
                cout<<"Invalid Input. Enter valid coordinates. "<<endl;
                }
                else{
                    gt_x = coordinates[0];
                    gt_y = coordinates[1];
                }
            }while(validate!=1);
            goat_select = Select_Goat(g,gt_x,gt_y);
            if(goat_select == -1){
                cout<<"Invalid input of coordinates"<<endl;
            }
            else{
                cout<<endl;
            }
        }while(goat_select==-1);
         do{
            do{
                cout<<"Enter the coordinate of the point you want the goat to move to: "<<endl;
                getline(cin, a);
                int coordinates[]={0,0};
                validate = validate_coordinates(a,coordinates);
                if(validate !=1){
                cout<<"Invalid Input. Enter valid coordinates. "<<endl;
                }
                else{
                    goat_fin_x = coordinates[0];
                    goat_fin_y = coordinates[1];
                }
            }while(validate!=1);
            goat_validate = g[goat_select].move(row_ptr,goat_fin_x,goat_fin_y);
            if(goat_validate == -1){
                cout<<"Invalid Move. Enter valid coordinates again"<<endl;
            }
        }while(goat_validate==-1);
       
        cout<<endl;
        system("clear");
        int dead_goats;
        dead_goats =  Goats:: eaten_goat_count;
        cout<<"Number of dead goats = "<<dead_goats<<endl<<endl;
        //tiger restriction check
        int restricted_tiger_count = 0;
        for(int l = 0; l<4;l++){
            if(t[l].is_restricted(row_ptr)){           
                restricted_tiger_count ++;
            }
            if(restricted_tiger_count == 4){    //goats have won the match
                cout<<endl<< "restricted tiger count  = "<< restricted_tiger_count<<endl<<endl;
                cout <<"Goats have won the match"<<endl;
                //check_value = 1;
                exit(0);
            }
        }
        cout<<endl<< "restricted tiger count  = "<< restricted_tiger_count<<endl<<endl;
        Display(row_ptr, 5,5);              //replace 5,5 later with appropriate variables
        cout<< endl;
        //take in input for tiger move
        cout<<endl<<endl<<"Tiger Turn: "<<endl;
        do{
            do{
                cout<<"Enter the coordinate of the tiger you want to move: "<<endl;
                getline(cin, a);
                int coordinates[]={0,0};
                validate = validate_coordinates(a,coordinates);
                if(validate !=1){
                cout<<"Invalid Input. Enter valid coordinates. "<<endl;
                }
                else{
                    tig_x = coordinates[0];
                    tig_y = coordinates[1];
                }
            }while(validate!=1);
            tig_select = Select_Tiger(t,tig_x,tig_y);
            if(tig_select == -1){
                cout<<"Invalid input of coordinates"<<endl;
            }
            else{
                cout<<endl;
            }
        }while(tig_select==-1);
        do{
            do{
                cout<<"Enter the coordinate of the point you want the tiger to move to: "<<endl;
                getline(cin, a);
                int coordinates[]={0,0};
                validate = validate_coordinates(a,coordinates);
                if(validate !=1){
                cout<<"Invalid Input. Enter valid coordinates. "<<endl;
                }
                else{
                    tig_fin_x = coordinates[0];
                    tig_fin_y = coordinates[1];
                }
            }while(validate!=1);
            tig_validate = t[tig_select].is_valid(row_ptr,tig_fin_x,tig_fin_y);   
            if(tig_validate ==1 || tig_validate ==2){
                t[tig_select].move(row_ptr,tig_fin_x,tig_fin_y);        // is valid funciton is called inside .move function also
            }
            else{
                cout<<"Invalid move. Enter valid coordinates again."<<endl;
            }
        }while(!(tig_validate==1 || tig_validate==2));          
        system("clear");
        dead_goats =  Goats:: eaten_goat_count;
        cout<<"Number of dead goats = "<<dead_goats<<endl;
        Display(row_ptr, 5,5);              //replace 5,5 later with appropriate variables
        cout<< endl;
        system("clear");
        if(dead_goats == 5){
            cout<<" The tiger has won the match";
            //check_value = 2;
            exit(0);                               
        }
    }
}
int menu_option(){
   
    int option;
    do{
        cout<<"Select one of the following options:"<<endl
        <<"1) Play Game"<<endl
        <<"2) Help Menu"<<endl
        <<"3) Exit"<<endl;
        cin>> option;
        if(!(option==1 || option==2 || option==3)){
            cout<<"Invalid Choice of Input. Choose the valid Option"<<endl;
        }
        if (option== 2){
            system("clear");
             cout<<".................................................................................................................................."<<endl<<endl;
    cout<<"Baghchal is a 2 player game between Tigers and Goats."<<endl<<endl;
    cout<<"There are 4 Tigers and 20 Goats. 4 Tigers start from the corners of the board."<<endl<<endl;
    cout<<"The game is played in turns. The Goats move first and the Tigers move next. "<<endl<<endl;
    cout<<"The aim of the Tiger is to eat Goats and the aim of the Goats is to restrict the Tiger so they have no valid moves."<<endl<<endl;
    cout<<"For the first 20 moves, the Goats can just be assigned on the board while the Tiger can be moved."<<endl<<endl;
    cout<<"For the Tiger to move, enter the coordinates of the tiger you wish to move. First enter the rows then the column."<<endl<<endl;
    cout<<"Then enter the coordinates you wish to move the selected tiger to."<<endl<<endl;
    cout<<"After all the goats are put on the board, the goats can be moved between the points that are joined by lines."<<endl<<endl;
    cout<<"The Tigers can eat the goat by jumping over the goat in a straight line to the point just behind the goat if the point is empty."<<endl<<endl;
    cout<<"The Tigers can win the match if 5 goats are eaten."<<endl<<endl;
    cout<<"The Goats can win the match if all 4 tigers have no valid moves (All Tigers are restricted)"<<endl<<endl;
    cout<<"NOTE: WHILE ENTERING THE COORDINATES, ENTER THEM IN THE SAME LINE TO AVOID ERRORS."<<endl<<endl;
    cout<<"Any formatting such as (1,2) or 1 2 or [1,2] etc. are acceptable for the input of coordinates."<<endl<<endl;
    cout<<"...................................................................................................................................."<<endl<<endl;
      //xcout<<"..................................................................................................................................."<<endl<<endl;
        }
    }while(!(option==1 || option==3));
    return option;
}
int validate_coordinates(string a, int coordinates[]){
    int i = 0;
    int j = 0;
    while(a[i]!='\0'){        
        if(a[i]>='0'  && a[i]<='4'){           
            coordinates[j] = a[i] - '0';
            j++;
        }
        i++;
    }
    if(j == 2){
        return 1;       //correct input;
    }
    else{
        return 0;   //not correct input;
    }
}
