#include <bits/stdc++.h>
using namespace std;
void printGrid(int Xr, int Xc, int sr, int sc) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (Xr==i && Xc==j) cout << "X ";
            else if (i==sr && j==sc) cout << "O ";
            else cout << ". ";
        }
        cout << "\n";
    }
}

int main(){
    srand(time(0));
    int points=0;
    int pointsBefore=0;

    for (int i=1;i<=3;i++){
        pointsBefore=points;
        int sr = rand() % 10;
        int sc = rand() % 10;
        int Xr=rand()%10;
        int Xc=rand()%10;
        while (Xr==sr && Xc==sc){
            Xr=rand()%10, Xc=rand()%10;
        }
        system("cls");
        
        cout<<"\n";
        printGrid(Xr,Xc,sr,sc);
        cout<<"grid "<<Xr<<" "<<Xc<<" set to X!";
    
        char dir;
        int steps=0;
        while (true){
            
            bool hitBoundary=false;
            cout<<"\nMove X using WASD, and press X for exiting";
            cin>>dir;
            switch(dir){
            
                case 'w':
                case 'W': if (Xr!=0)Xr--;
                      else hitBoundary=true;
                      break;
                case 's':
                case 'S': if (Xr!=9)Xr++;
                      else hitBoundary=true;
                      break;
                case 'a':
                case 'A': if (Xc!=0)Xc--;
                      else hitBoundary=true;
                      break;
                case 'd':
                case 'D': if (Xc!=9)Xc++;
                      else hitBoundary=true;
                      
                      break;
                default: exit(0);
                     
            }
            system("cls");
            if (Xr==sr && Xc==sc){
               printGrid(Xr,Xc,sr,sc);
                points+=10;
                cout << "\nPoints this round: " << points - pointsBefore;
                cout << "\nTotal points: " << points<<"\nPress any key to continue: ";
                cin>>dir;
                break;
            }
            else{
                printGrid(Xr,Xc,sr,sc);
        }
        if (hitBoundary){cout<<"\nYou are out of Bounds!";points-=5;}
        else steps++;
    }
    
}
cout<<"\nYou earned "<<points<< " points";
    return 0;

}