#include<stack>
#include<iostream>
#include<cstdlib>
#include<stdio.h>
#include<cstdlib>
#include<bits/stdc++.h>
#include<string>
#include<ctime>
#include<algorithm>
using namespace std;
int score=0;
int counter = 1;
char **maze;
static int lives= 3;
int player_count=0;
vector<class player> leader;
class Graph // The class
{
    public:   // Access specifier
        int nodes; // Attribute (int variable)
        vector<int>*adj;
        int sp;
        int lp;

    Graph(int n)
    {
        sp=0;
        this->nodes=n;
        adj=new vector<int>[n*n];
    }
    void redef_graph(int n1)
    {
        sp=0;
        nodes=n1;
            adj=new vector<int>[nodes*nodes];

    }
    void init()
    {
        adj=new vector<int>[nodes*nodes];
    }

    void checkEdge()
    {
        for(int i=0;i<nodes;i++)
        {
            for(int j=0;j<nodes;j++)
            {
                edge(i,j);
            }
        }
    }

    void add_edge(int org,int dest)
    {
        adj[org].push_back(dest);
    }

    void edge(int i,int j) 
    {
        if(maze[i][j]!='X') //adding obsticals
        {
            if(i>0 && maze[i-1][j]!='X') //adding obsticals
            {
                add_edge((i*nodes)+j,(i-1)*nodes+j);
            }
            if(i<nodes-1 && maze[i+1][j]!='X') //adding obsticals
            {
                add_edge((i*nodes)+j,(i+1)*nodes+j);
            }
            if(j>0 && maze[i][j-1]!='X') //adding obsticals
            {
                add_edge((i*nodes)+j,(i*nodes)+(j-1));
            }
            if(j<nodes-1 && maze[i][j+1]!='X') //adding obsticals
            {
                add_edge((i*nodes)+j,(i*nodes)+(j+1));
            }
        }
    }

    int minEdgeBFS(int u, int v)
    { //board logic for avoiding X as an obstical 
        vector<bool> visited(nodes*nodes, false);
        vector<int> distance(nodes*nodes, 0);
        queue <int> Q;
        distance[u] = 0;
        Q.push(u);
        visited[u] = true;
        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for (int i=0; i<adj[x].size(); i++)
            {
                if (visited[adj[x][i]])
                    continue;
                distance[adj[x][i]] = distance[x] + 1;
                Q.push(adj[x][i]);
                visited[adj[x][i]] = 1;
            }
        }
        return distance[v];
    }
};
class mazegame // The class
{
public:   // Access specifier
   string player;  // Attribute (string variable)
    stack<pair<int,int> > S;
    int n , steps; // Attribute (int variable)
    void randomObstruction(double percent)
    {

        int c=(percent*n*n); // Attribute (int variable)
        while(c>0)
        {
            int i=rand()%n; // Attribute (int variable)
            int j=rand()%n; // Attribute (int variable)
            if(maze[i][j]!='X' && maze[i][j]!='#' && (i!=0 || j!=0))
            {
                maze[i][j]='X';
                c--;
            }
        }
    }
    mazegame(int n , string name)
    {
        this->n=n;
        player = name;
        steps=0;
        maze = new char * [n];
        for (int i = 0; i < n; ++i )
            maze[i] = new char [n];

        for(int i=0;i<n;i++)
        {
          for(int j=0;j<n;j++)
             maze[i][j]=' ';
        }

        maze[0][0]='@';
        maze[n-1][n-1]='#';
    }
    void redefine(int n1)
    {
        n=n1;
        steps=0;
        maze = new char * [n];
        for (int i = 0; i < n; ++i )
            maze[i] = new char [n];

        for(int i=0;i<n;i++)
        {
          for(int j=0;j<n;j++)
             maze[i][j]=' ';
        }
        maze[0][0]='@';
        maze[n-1][n-1]='#';
    }
 void drawMaze()
 {

       system("clear");
       cout<<"\n\n\t\t\t\t\t\t\t LEVEL "<<counter<<"\n\n";
     int i,j=0; // Attribute (int variable)
     cout<<"\n\n\n";
     for(i=0;i<n;i++)
     {
         cout<<"\t   "<<(i+1)<<"  ";
     }
     cout<<"\n";
    for(i=0;i<n;i++)
     {
         cout<<"\t  ___  ";
     }
     cout<<"\n";
     while(j<n)
     {
        for(i=0;i<n;i++)
        {
            if(maze[i][j]!=' ')
                printf("\t| _%c_ |",maze[i][j]);
            else
                cout<<"\t| ___ |";
        }
        cout<<"\n";
        j++;
     }
    cout<<"\n\n\n\n\n";
 }
 int move(int x,int y)
 {
     pair<int,int> K;
     char ch;
     int termin=0; // Attribute (int variable)
     do
     { //Game controll define
         cout<<"\nUP....'W'";
         cout<<"\nLEFT....'A'";
         cout<<"\nDOWN....'S'";
         cout<<"\nRIGHT....'D'";
         cout<<"\nUNDO....'U'";
         cout<<"\nQUIT....'Q'";
         cout<<"\n\t\t\t\t Your Lives:- "<<lives;
         cout<<"\nEnter Your Move:- ";
         //system("stty raw");
         ch=getchar();
         //system("stty cooked");
         switch(ch)
         { //stage start
         case 'W': //stage 1
             {
                 if(y>0 && maze[x][y-1]!='X'&& maze[x][y-1]!='#')
                   {
                     maze[x][y]='_';
                     if(!S.empty())
                     {  K=S.top();}
                     S.push(make_pair(x,y));
                     y-=1;
                     if((K.first==x)&&(K.second==y))
                     {  lives--;}
                     maze[x][y] = '@';
                     steps++;
                   }
                else if(maze[x][y-1]=='#')
                    {
                        cout<<"\n\t\t\tHURRAY!! Level Cleared !!";
                        y-=1;
                        break;
                    }
                else
                    cout<<"\nCan't Move up";
                if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    exit(0);
                }
                break;
             }
         case 'A': //stage 2
             {
                 if(x>0 && maze[x-1][y]!='X'&& maze[x-1][y]!='#')
                    {
                        maze[x][y]='_';
                        if(!S.empty())
                        {  K=S.top();}
                        S.push(make_pair(x,y));
                        x-=1;
                         if((K.first==x)&&(K.second==y))
                     {  lives--;}
                        maze[x][y] = '@';
                        steps++;
                    }
                else if(maze[x-1][y]=='#')
                   {
                       cout<<"\n\t\t\tHURRAY!! Level Cleared !!";
                       x-=1;
                       break;
                   }
                else
                    cout<<"\nCan't Move left";
                if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    exit(0);
                }
                break;
             }
        case 'S': //stage 3
             {
                 if(y>=0 && y+1<n && maze[x][y+1]!='X' && maze[x][y+1]!='#')
                    {
                        maze[x][y]='_';
                        if(!S.empty())
                        {  K=S.top();}
                        S.push(make_pair(x,y));
                        y+=1;
                         if((K.first==x)&&(K.second==y))
                     {  lives--;}
                        maze[x][y] = '@';
                        steps++;
                    }
                else if(maze[x][y+1]=='#')
                    {
                        cout<<"\n\t\t\tHURRAY!! Level Cleared !!";
                        y+=1;
                        break;
                    }
                else
                    cout<<"\nCan't Move Down";

                if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    exit(0);
                }
                break;
             }

        case 'D': //stage 4
             {
                 if(x>=0 && x+1<n && maze[x+1][y]!='X' && maze[x+1][y]!='#')
                    {
                        maze[x][y]='_';
                        if(!S.empty())
                        {  K=S.top();}
                        S.push(make_pair(x,y));
                        x+=1;
                         if((K.first==x)&&(K.second==y))
                     {  lives--;}
                        maze[x][y] = '@';
                        steps++;
                    }
                else if(maze[x+1][y]=='#')
                    {
                        cout<<"\n\t\t\tHURRAY!! Level Cleared !!";
                        x+=1;
                        break;
                    }
                else
                    cout<<"\nCan't Move Right";

                    if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    exit(0);
                }
                break;
             }
        case 'U': //stage 5
            {
                int i,j; // Attribute (int variable)
                if(S.empty()==true)
                    {   cout<<"\nUNDO NOT POSSIBLE";
                        break;

                    }
                    else
                    {
                        pair<int,int> P=S.top();
                        i=P.first;
                        j=P.second;
                        S.pop();
                        maze[x][y] = '_';
                        maze[i][j] = '@';
                        x=i;
                        y=j;
                        steps--;
                    }
                if(lives==0)
                {
                    cout<<"\n"<<player<<" Your Steps are:- "<<steps;
                    int count_player=0; // Attribute (int variable)
                }
                else
                    lives--;
                break;
            }
        case 'Q': //stage calculations
            {
                cout<<"\n"<<player<<" Your Steps are:- "<<steps; //steps counter
                termin=1;
                int count_player=0; // Attribute (int variable)
            }
        }
        //system("clear");
        if(termin==0)
        {

        drawMaze(); //board draw

        }
        else
        {
            break;
        }
        }while(maze[x][y]!='#' && termin==0); //pasenger placement

        return(termin);

    }
   void scoreBoard(int shortest , double percent) //Score board display
    {
            int longest = (n*n)-(percent*n*n); // Attribute (int variable)
            int avg = (longest+shortest)/2;  // Attribute (int variable)
            int count=0; // Attribute (int variable)
            if((steps+1)>avg)
               {
                 score += 40;
               }
            else if((steps+1) == avg)
            {
                score+=50;
            }
            else if((steps+1)<avg)
            {
                if((steps+1)==shortest)
                    score+=100;
                else
                { //score board append display
                    count = (steps+1)-shortest;
                    if(count==1)
                        score+=95;
                    else if(count==2)
                        score+=90;
                    else if(count==3)
                        score+=85;
                    else if(count==4)
                        score+=80;
                     else if(count==5)
                        score+=75;
                     else if(count==6)
                        score+=70;
                     else if(count==7)
                        score+=65;
                     else if(count==8)
                        score+=60;
                     else if(count==9)
                        score+=55;
                    else
                        score+=50;

                }
            }
    }
 };
class Levels // The class
{
    public:   // Access specifier
        double level(int size)
        {
            if(size==8)
                return(.15);
            if(size==9)
                return(.2);
            if(size==10)
                return(.3);
            if(size==11)
                return(.35);
            if(size==12)
                return(.3);
        }
};
class player // The class //leader logic board start
{
    public:   // Access specifier
    string pl_name;   // Attribute (string variable)
    int pl_score; // Attribute (int variable)
};
bool compare(player i1,player i2)
{
    return(i1.pl_score>i2.pl_score);
}
void add_player(string name,int sco,int count_player)
{
    player p1;
    p1.pl_name=name;
    p1.pl_score=sco;
    leader.push_back(p1);
    count_player++;
}
void update_player(string name,int sco,int count_player)
{
    for(int i=0;i<count_player;i++)
    {
        if(leader[i].pl_name==name)
        {
            leader[i].pl_name=sco;
            count_player++;
        }
    }
}
int find_pl(string name,int count_player)
{
    int temp=0; // Attribute (int variable)
    for(int i=0;i<count_player;i++)
    {
        if(leader[count_player].pl_name==name)
        {
            temp=1;
        }
    }
    return temp;
}
void create_leader()
{
    sort(leader.begin(),leader.end(),compare);
    ofstream m4("n1.txt");
    for(int i=0;i<player_count;i++)
    {
        m4<<leader[i].pl_name<<" "<<leader[i].pl_score<<"\n";
    }
    m4.close();
}
void get_player_count()
{
    ifstream m1("n1.txt"); //leader file create if not exist
    if(!m1.fail())
    {
    string n;   // Attribute (string variable)
     while(!m1.eof())
     {
         getline(m1,n);
         player_count++; //adde ntery in leader file
     }
    }
    m1.close(); 
}
int find_player(string n1,int score_of_pl,int count_player)
{
    string nam;   // Attribute (string variable)
    int score_p; // Attribute (int variable)
    ifstream m2("n1.txt"); //leader file append
    if(!m2.fail())
    {
    while(!m2.eof())
    {
        m2>>nam>>score_p; //score add
        if(nam!="")
        {
        add_player(nam,score_p,count_player);
        }
    }
    if(find_pl(n1,count_player)!=1)
    {
        add_player(n1,score_of_pl,count_player);
    }
    else if(find_pl(n1,count_player))
    {
        update_player(n1,score_of_pl,count_player);
    }
    m2.close();
    }
}
void show_leader() //leader board view
{
    int count_temp=1; // Attribute (int variable)
   cout<<"RANK"<<"         "<<"NAME"<<"           "<<"SCORE"<<"        "<<endl;
   for(int i=0;i<player_count;i++)
   {
       cout<<count_temp<<"         "<<leader[i].pl_name<<"     "<<leader[i].pl_score<<endl;
       count_temp++;
   }
} //leader logic board end
int main() //Game Discription
{
     srand(time(NULL));
     string name;   // Attribute (string variable)
     int n=8; // Attribute (int variable)
     double c;
     cout<<"********************************************** WELCOME TO CODE CAB!!!!**************************************************";
     cout<<"\n\t Enter your name CABBY! :- "<<endl;
     cin>>name;
     cout<<endl;
     getchar();
     system("clear");
     cout<<"HEY "<<name<<" "<<"YOU CAB IS @ IN THE GAME AND PASSENGER IS #"<<endl<<endl; //player name and taxi passenger explanation 
     cout<<"LET ME ELABORATE YOU THE RULES OF THE GAME :-"<<endl<<endl;
     cout<<"1) YOU HAVE 3 LIVES AND THEY REDUCE WHEN YOU TRY TO COPY YOUR PREVIOUS MOVE !!! \n2) THE GAME HAS 5 STAGES ... EACH STAGE HAS DIFFERENT POINTS...AND I BET YOU'LL ENJOY TILL THE LAST"<<endl;;
     cout<<"\n3)AVOID TAKING ROUTES FULL OF OBSTACLES AND GET TO THE PASSENGER ON TIME !!!!! \n ENJOY DRIVING CABBY!!!!!!"<<endl;;
     cout<<"\n PRESS ENTER TO PLAY"<<endl;
     getchar();
     int sp=0; // Attribute (int variable)
     int player_score=0; // Attribute (int variable)
     mazegame a(n,name);
     Levels l;
     Graph g(n) ;
     while(counter<=5)
     {
        int sp=0; // Attribute (int variable)
        char ch;
        c = l.level(n);
        while(sp==0)
        {
            a.redefine(n);
            g.redef_graph(n);
            a.randomObstruction(c);
            g.init();
            g.checkEdge();
            sp=g.minEdgeBFS(0,(n*n)-1);
             if(sp!=0)
             {
                a.drawMaze();
             }
        }
        char lo;
        int player_score; // Attribute (int variable)
        int temp=a.move(0,0); // Attribute (int variable)
        if(!temp)
        {
        a.scoreBoard(sp,c); //Player board
        cout<<"\nYour total Steps were:"<<(a.steps+1);
        cout<<"\nYour Score:"<<score;
        cout<<"\nMin steps were: "<<sp<<endl;
        cout<<"PRESS ENTER TO CONTINUE!!!!"<<endl;
        cin>>lo;
        }
        else if(temp)
        { //Steps calculator
         cout<<"\nYour Score: "<<0;
        cout<<"\nMin steps were: "<<sp<<endl;
        counter=6;
        getchar();
        cout<<"PRESS ENTER TO CONTINUE!!!!"<<endl;
        cin>>lo;
            break;
        }
        counter++;
        n++;
    }
    int count_player=0; // Attribute (int variable)
    get_player_count();
    //player players[player_count];
    find_player(a.player,score,count_player);
    create_leader();
    show_leader();
    return 0;
 }
