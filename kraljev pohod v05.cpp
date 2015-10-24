#include <iostream>
#include <iomanip>
#include <windows.h>


using namespace std;
const int ver[]={-1,-2,-2,-1,1,2,2,1};
const int hor[]={2,1,-1,-2,-2,-1,1,2};

int row,col,npos;
int board[8][8],nextij[8][8][8],accessible[8][8];
	  
class KingTour {
unsigned int chessBoard[8][8];          //sahovska ploca
unsigned int kingLocation[2];           //trenutna pozicija kralja
unsigned int freePosition[8];           //slobodne pozicije na sahovskoj ploci


public:       
//Popunjavanje ploce sa jedinicama (1 - slobodno polje, 2 - trenutacno se nalazi kralj, 0 - polje na kojemu je bio)		  
void newBoard(){
     for (int i=0; i<8; i++){
         for (int j=0; j<8; j++){
             chessBoard[i][j]=1;
         }
     }
}

//Ispis podataka o autoru programa na zaslon
void printInformation(){
     cout<<endl;
     cout<<"                        Kraljev Pohod  v 0.5"<<endl;
     cout<<"              Izradio: ing. Zeljko Radicevic, ETFOS, 2011."<<endl;
     cout<<"                  e-mail: zeljko.radicevic@gmail.com"<<endl;
}    

/*Ispis ploce na zaslon. Na polja na koja moze stati kralj
upisuju se adrese, polja na kojima je bio ostaju prazna,
polje na kojemu se nalazi ima oznaku K
*/            
void printBoard(){
         string num = "   S   0       1       2       3       4       5       6       7";
           string hor = " +-------+-------+-------+-------+-------+-------+-------+-------+";
           
           cout<<endl;
           cout<<num<<endl;
           cout<<" R"<<hor<<endl;
           
          for (int z=0; z<8;z++){   //Petlja za pomak po redovima
          
              for (int j = 0; j < 3; j++){ // Petlja za ispis redaka kocke
                  if (j != 1) {
                     cout<<"   ";           
                     } else {
                       cout<<" "<<z<<" ";   // U srednjem redu kocke ispiši redni broj kocke (redak)
                       }             
                          
           for (int i=0; i<9;i++){ //Petlja za pomak po stupcima
            
               if(chessBoard[z][i] == 1 && j == 1 && i <= 7){  //Polje na koje moze doci kralj, ispisuje se njegova numericka lokacija
               cout<<"|   "<<z<<i<<"  ";
               } else if (chessBoard[z][i] == 0 && j == 1 && i <= 7){  //Polje na kojemu je kralj bio, ostaje prazno
                      cout<<"|       ";
               } else if    (chessBoard[z][i] == 2 && i <= 7 && j == 1){
                      cout<<"|###K###";
               }else if (chessBoard[z][i] == 2 && i <= 7) {  //Polje na kojemu se trenutaèno nalazi kralj, ima oznaku K (King)
                      cout<<"|#######";        
               } else {
                 cout<<"|       ";
               }
               }
               cout<<endl; 
               }  
           cout<<"  "<<hor<<endl;
           }  
}  

//Pomak kralja po ploci, i pohrana trenutne lokacije u vektor - kingLocation               
void shiftKing(unsigned int rc){
     unsigned int r = rc/10;   // izdvajanje reda
     unsigned int c = rc%10;   // izdvajanje stupca
     chessBoard[r][c]=2;
     kingLocation[0]=r;
     kingLocation[1]=c;
     }

/*Provjera polja na koja moze stati kralj u 8 smjerova, 
Na polja na koja moze stati adresa se upisuje u vektor freePosition,
a na polja na koja ne moze u vektor se upisuje broj sto
*/
void checkFreePosition(){
unsigned int k_row = kingLocation[0]; //skracivanje imena varijable
unsigned int k_col = kingLocation[1]; //skracivanje imena varijable

if((k_row-2)<8 && (k_col+1)<8 && chessBoard[k_row-2][k_col+1] == 1 ){
   freePosition[0]= (k_row-2)*10 + (k_col+1);       
   } else {
          freePosition[0]= 100;
          } 

if((k_row-1)<8 && (k_col+2)<8 && chessBoard[k_row-1][k_col+2] == 1 ){
   freePosition[1]= (k_row-1)*10 + (k_col+2);     
   } else {
          freePosition[1]= 100;
          }  

if((k_row+1)<8 && (k_col+2)<8 && chessBoard[k_row+1][k_col+2] == 1 ){
   freePosition[2]= (k_row+1)*10 + (k_col+2);    
   } else {
          freePosition[2]= 100;
          }

if((k_row+2)<8 && (k_col+1)<8 && chessBoard[k_row+2][k_col+1] == 1 ){
   freePosition[3]= (k_row+2)*10 + (k_col+1);     
   } else {
          freePosition[3]= 100;
          }

if((k_row+2)<8 && (k_col-1)<8 && chessBoard[k_row+2][k_col-1] == 1 ){
   freePosition[4]= (k_row+2)*10 + (k_col-1);     
   } else {
          freePosition[4]= 100;
          }          

if((k_row+1)<8 && (k_col-2)<8 && chessBoard[k_row+1][k_col-2] == 1 ){
   freePosition[5]= (k_row+1)*10 + (k_col-2);     
   } else {
          freePosition[5]= 100;
          }            

if((k_row-1)<8 && (k_col-2)<8 && chessBoard[k_row-1][k_col-2] == 1 ){
   freePosition[6]= (k_row-1)*10 + (k_col-2);      
   } else {
          freePosition[6]= 100;
          }

if((k_row-2)<8 && (k_col-1)<8 && chessBoard[k_row-2][k_col-1] == 1 ){
   freePosition[7]= (k_row-2)*10 + (k_col-1);
   } else {
          freePosition[7]= 100;
          }           
}

//Cisti polje na kojemu je kralj prethodno bio tj. upisuje 0 na tu adresu
void clean(){
     chessBoard[kingLocation[0]][kingLocation[1]] = 0;  
}

/*Ispis adresa polja na koja kralj moze ici
te vraca informaciju o broju polja na koja se moze ici (0-8)
*/
unsigned int showFreePosition(){
cout<<endl<<"Mozete na polja: ";
unsigned int brojac = 0;

     for (int i=0; i<8; i++){
        if (freePosition[i] != 100){
        
          if (freePosition[i] < 10){
            cout<<"0"<<freePosition[i]<<" ";
          } else {   
          cout<<freePosition[i]<<" ";
          }
       
          brojac++;
                }         
     }
         cout<<endl<<endl;
         return brojac;          
}

//Provjera dali je uneseni potez ispravan
bool checkMove(unsigned int cm){
     bool flag = 0;
     for (int i=0; i<8; i++){
         if (cm == freePosition[i] && cm != 100){  //ako je moguce napraviti potez vrati jedan
                flag = 1;
                } 
         }
         return flag;
}

//Obrisi sve sa zaslona     
void clearScreen(){
     system("CLS");
}
};


/***************************   START  SIMULACIJA   **************************/
void possible()
{
	int npos;
	for(int r=0;r<=7;r++)
	{

		for(int c=0;c<=7;c++)
		{
			npos = 0;

			for(int i=0;i<=7;i++)
			{
				if(((r+ver[i] >=0) && (r+ver[i] <=7))&&((c+hor[i] >=0) && (c+hor[i] <=7))&&(board[r+ver[i]][c+hor[i]] == 0))
				{

					nextij[r][c][npos] = i;
					npos++;
				}
			}
			accessible[r][c] = npos;
		}
	}

}
void exits(int l)
{

	int min = accessible[row+ver[nextij[row][col][0]]][col+hor[nextij[row][col][0]]];
	int r = row+ver[nextij[row][col][0]],c=col+hor[nextij[row][col][0]];

	for(int i=1;i < accessible[row][col];i++)
		if(min >= accessible[row+ver[nextij[row][col][i]]][col+hor[nextij[row][col][i]]])
		{
			min =accessible[row+ver[nextij[row][col][i]]][col+hor[nextij[row][col][i]]];
			r = row + ver[nextij[row][col][i]];
			c = col + hor[nextij[row][col][i]];
		}

		board[r][c]=l;
		row = r;
		col = c;

}

/***************************    KRAJ SIMULACIJA   **************************/


//Glavni program
int main()
{
unsigned int x;      //pocetna pozicija kralja   
unsigned int next;  // sljedece polje
unsigned int y = 0; //brojac slobodnih polja
unsigned int z = 1; //brojac napravljenih poteza
unsigned int j = 0;
int choice = -1;
int count = 1;
int xx;



KingTour kt;                 //kreiraj objekt
kt.printInformation();       //ispisi podatke o autoru programa    

//Ispisi izbornik na zaslon i trazi unos
do {
    cout<<endl<<"1 - Igra kraljev pohod"<<endl<<"2 - Simulacija kraljevog pohoda"<<endl<<"0 - Izlaz"<<endl<<endl;
    cout<<"Unesite vas odabir: ";
    cin>>choice;
    }while(choice < 0 || choice >2);

switch (choice){
       //Ako je unesena nula izadji iz programa
       case 0:           
       system("PAUSE");
       return EXIT_SUCCESS;
       break;
       
       //Ako je unesen jedan obavi sve potrebne akcije kako bi se mogli igrati
       case 1:
       kt.clearScreen();        //ocisti zaslon
       kt.printInformation();   //ispisi podatke o autoru programa
       kt.newBoard();           //kreiraj novu praznu plocu
       kt.printBoard();         //ispisi praznu plocu na zaslon
       
       //Traziti od korisnika da unese pocetnu poziciju kralja sve dok ne unese broj od 00 do 77
                 do{
                    cout<<endl<<"Unesite pocetnu poziciju kralja (npr. 52): ";
                    cin>>x;
                 } while (x < 0 || x > 77);
       
       kt.shiftKing(x);         //staviti kralja na pocetnu poziciju
       kt.checkFreePosition();  //provjeri polja na koja kralj moze ici
       kt.clearScreen();        //ocisti zaslon
       kt.printInformation();   //ispisi podatke o autoru programa
       kt.printBoard();         //prikazi plocu sa ucrtanim kraljem na zaslon
       
                                do{
                                   y = kt.showFreePosition();  //preuzmi broj polja na koja kralj moze stati i pohrani u varijablu y
                                   if (y == 0){                //ako nema vise slobodnih mjesta, prekinu do-while petlju
                                   break;  
                                   }                                   
                                 z++;      //povecaj broj poteza za jedan
                                           
                                           
                                           //Traziti od korisnika unos sljedece pozicije kralja sve dok ne unese polje na koje kralj moze stati
                                           do{
                                              cout<<"Unesite #"<<z<<" poziciju kralja: ";
                                              cin>>next;
                                              j = kt.checkMove(next); //provjeri dali se na uneseno polje moze stati                                             
                                           } while (j == 0);
                                 
                                 kt.clean();                //na polje na kojemu je kralj bio upisi nulu
                                 kt.shiftKing(next);        //pomaci kralja na uneseno polje
                                 kt.checkFreePosition();    //provjeri sljedece slobodne pozicije na koje moze kralj stati
                                 kt.clearScreen();          //ocisti zaslon
                                 kt.printInformation();     //ispisi podatke o autoru programa
                                 kt.printBoard();           //ispisi plocu na zaslon             
                                } while (y > 0);
       
       //ako se ploca ne obidje u 64 poteza (na svako polje stanemo jednom) dobijemo informaciju o kraju igre
             if(z != 64){
                  cout<<"          KRAJ IGRE!!!!              "<<endl;
                  cout<<"Nazalost niste uspjeli doci do kraja."<<endl;
                  cout<<"Odmorite konja pa pokusajte ponovno!"<<endl<<endl;     
             } else {
                     cout<<"BRAVO!!! USPJESNO STE STIGLI DO KRALJEVNE!!!"<<endl<<"CESTITAMO!!!"<<endl<<endl;
                    }
       
       system("PAUSE");
       return EXIT_SUCCESS;       
       break;     
       
       //Ako je unesen broj dva traziti unos pocetne pozicije kralja i dalje prikazati simulaciju obilaska
       case 2:
       
	int count = 1;
 //Traziti od korisnika da unese pocetnu poziciju kralja sve dok ne unese broj od 00 do 77
           do{
              cout<<endl<<"Unesite pocetnu poziciju kralja (npr. 52): ";
              cin>>xx;
             } while (xx < 0 || xx > 77);

               row = xx / 10;
               col = xx % 10;

	board[row][col]=count;   //postavi kralja na pocetnu poziciju, koristi pomocnu plocu - board


	while(count!=64)
	{
		count++;
		possible();
		exits(count);
	}

KingTour kt2;        //kreiraj objekt
kt2.newBoard();      //kreiraj novu praznu plocu
int position[64];        //pozicije kralja

//Obilazak ploce
for(int i = 0; i < 64; i++){
   for(int j = 0; j<8; j++){
       for (int k = 0; k < 8; k++){
           if(board[j][k] == i+1){
              position[i] = (j*10) + k;     //pretvaranje dvodimenzionalne kordinate u jednodimenzionalnu
              kt2.clearScreen();         //ocisti zaslon
              kt2.shiftKing(position[i]);   //pomici kralja prema redosljedu (1-64)            
              kt2.printInformation();    //ispisi podatke o autoru programa
              kt2.printBoard();          //ispisi plocu sa ucrtanim kraljme
              kt2.clean();               //ocisti polje na kojemu se nalazio kralj
              cout<<endl<<"Trenutna pozicija kralja: ";
              if (position[i] < 10){
                 cout<<"0"<<position[i]<<endl;          //ako je adresa polja manja od 10 dodaj ispred nulu             
              } else {
                cout<<position[i]<<endl;                //inace ispisi adresu
              }
              Sleep(1000);                           //cekaj 1000 milisekundi
           }       
        }
    }
}

cout<<endl<<"Ploca je obidjena sljedecim redosljedom:"<<endl<<endl;
for (int i = 0; i < 64; i++){
    cout<<"#"<<i+1<<": ";
    if (position[i] < 10){
        cout<<"0"<<position[i]<<endl;                
    } else {
           cout<<position[i]<<endl;
           }
}
	
       system("PAUSE");
       return EXIT_SUCCESS;
       break;
       }
}
