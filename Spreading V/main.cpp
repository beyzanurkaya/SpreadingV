//BEYZA NUR KAYA
//1306170038

#include <fstream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

int turnCount = 0;
int gunSayisi = 0;

int infectedCount = 0;

bool startsWith(string mainStr, string toMatch){
    if(mainStr.find(toMatch) == 0)
        return true;
    else
        return false;
}



    int entityCount = 0, normalCounter = 0, deadCounter = 0, recoveredCounter = 0;
    string id;
    string gates;
    int xCoordination, yCoordination;
    int infectedCoordinationX, infectedCoordinationY;
    vector <int> xInfectedStartingCoordination;
    vector <int> yInfectedStartingCoordination;
    vector <int> xNormalStartingCoordination;
    vector <int> yNormalStartingCoordination;
    bool isInfected;
    vector<string> firstSitutaion;
    
    //string theSitutaion;
       
    void getInfectedEntityCoordination(string coordinations){ //infected entitylerin koordinati
        vector<string> coordination;
        stringstream ss(coordinations);
        const char delim = 'x';
        string s;
        while (getline(ss, s, delim)) {
            coordination.push_back(s);
        }
           
        string x = coordination[0];
        string y = coordination[1];
           
        infectedCoordinationX  = atoi(x.c_str());
        infectedCoordinationY  = atoi(y.c_str());
        
        xInfectedStartingCoordination.push_back(infectedCoordinationX);
        yInfectedStartingCoordination.push_back(infectedCoordinationY);
        
    }
   void getNormalEntityCoordination(string coordinations){ //normal entitylerin koordinati

        vector<string> coordination;
        stringstream ss(coordinations);
        const char delim = 'x';
        string s;
        while (getline(ss, s, delim)) {
            coordination.push_back(s);
        }
        
        string x = coordination[0];
        string y = coordination[1];
        
        xCoordination  = atoi(x.c_str());
        yCoordination  = atoi(y.c_str());
       
       xNormalStartingCoordination.push_back(xCoordination);
       yNormalStartingCoordination.push_back(yCoordination);

    }
    string checkGates(string gate){ //ilk durumdaki gate kontolu yapildi.
        gates = gate;
        int A=0,B=0,C=0,D=0;
        int i;
        for(i=0;gate[i]!='\0';i++){
            if(gate[i]=='A'){
                A++;
            }else if (gate[i]=='B'){
                B++;
            }else if (gate[i] == 'C'){
                C++;
            }else if (gate[i] == 'D'){
                D++;
            }
        }
        int result = A+B+C+D;
        if (A != 0 || B != 0 ) {
            if (result >= 3) {
                return "mightDie"; //bu hasta olebilir
            }else{
                return "getBetter"; //bu hasta iyilesebilir
            }
        }else{
            return "cantGetSick"; //hasta olamaz
        }
    }
    void initializeEntity(string str){ //entitynin bilgilerini analiz etme
        vector<string> entityIdenty;
        stringstream ss(str);
        const char delim = ' ';
        string s;
        while (getline(ss, s, delim)) {
            entityIdenty.push_back(s);
         }
         string id = entityIdenty[1];
         string gates = entityIdenty[2];
         string coord = entityIdenty[3];
         if (entityIdenty[4] == "infected") {
             isInfected = true;
             infectedCount++;
             getInfectedEntityCoordination(coord); //infected olan entitynin koordinatlarini belirleme
             firstSitutaion.push_back(checkGates(gates));
         }else{
             isInfected = false;
             getNormalEntityCoordination(coord); //normal olan entitynin koordinatlarini belirleme
             firstSitutaion.push_back(checkGates(gates)); //gatelerden gelen ilk durum
         }
         
    }



    
    int sizeInt = 0;
    vector<int> xCoord;
    vector<int> yCoord;
    vector<vector <int>> xTurnList;
    vector<vector <int>> yTurnList;
    vector<vector <int>> afterTurnX;
    vector<vector <int>> afterTurnY;

    int xCoordinations,yCoordinations;
    
    void TurnSayisi(){
      ifstream oku("/Users/beyzanurkaya/Desktop/input.txt");
        string data;
        oku >> data;
        while(oku){
            if(data == "size" ){
                oku >> data;
                sizeInt = atoi(data.c_str());
                
            }else if (data == "turn_count"){
                oku >> data;
                gunSayisi = atoi(data.c_str());
                //cout << gunSayisi << endl;
            }
            oku >> data;
        }
    }

    void getTurnCoordinations(string coord){
        string number;
        vector<string> turn;
        istringstream koordinat(coord);
        koordinat >> number;
        koordinat >> number;
        string word;
        while (koordinat >> word) {
        stringstream ss(word);
        const char delim = 'x';
        string s;
        while (getline(ss, s, delim)) {
            turn.push_back(s);
        }
            
        string x = turn[0];
        string y = turn[1];
               
        xCoordinations  = atoi(x.c_str());
        yCoordinations  = atoi(y.c_str());
        xCoord.push_back(xCoordinations);
        yCoord.push_back(yCoordinations);
        
        turn.clear();
        }
    }
    void infectedOtherEntity(){
        
        for (int i = 0; i < entityCount; i++) {
            for (int j = 0; j<infectedCount; j++) {
                if (i == j) {
                    continue;
                }
                else{
                    int distanceX = abs(xNormalStartingCoordination[i] - xInfectedStartingCoordination[i]);
                    int distanceY = abs(yNormalStartingCoordination[i] - yInfectedStartingCoordination[i]);
                    if ((distanceX <= 3 || distanceY <= 3) && turnCount >= 3  ) {
                        if (firstSitutaion[i] == "mightDie" || firstSitutaion[i] == "getBetter") {
                            firstSitutaion[i] = "infected";
                            infectedCount++;
                        }
                    }
                }
            }
        }
    }
    
    void infectedDays(){
        TurnSayisi();
        int infectedDay = 0;
        for (int i = 0; i < gunSayisi; i++) {
            if (firstSitutaion[i] == "infected") {
            infectedDay++;
            }
        }
        for (int j = 0; j < gunSayisi; j++) {
            if (infectedDay >= 14 && firstSitutaion[j] == "mightDie") {
                firstSitutaion[j] = "Dead";
                deadCounter++;
            }else if(infectedDay >= 30 && firstSitutaion[j] == "getBetter"){
                firstSitutaion[j] = "Recovered";
                recoveredCounter++;
            }
        }
        
    }
    
    void writingTurns(int turn){
        ofstream turnText;
        turnText.open ("turn.txt");
        turnText << "TURN " << turn << ":\n" << endl;
        for (int i = 0; i <= sizeInt + 2; i++) {
            for (int j = 0; j <= sizeInt + 2; j++) {
                if ((i > 0 && i < sizeInt + 2) && (j > 0 && j < sizeInt + 2)) {
                    for (int x = 0; x < entityCount; x++) {
                        if ((xNormalStartingCoordination[x] == i && yNormalStartingCoordination[x] == j) && firstSitutaion[i] == "cantGetSick") {
                            turnText << "o";
                        } else if ((xInfectedStartingCoordination[x] == i && yInfectedStartingCoordination[x] == j)) {
                            turnText << "x";
                        } else if ((xNormalStartingCoordination[x] == i && yNormalStartingCoordination[x] == j) && firstSitutaion[i] == "Dead"){
                            turnText << "d";
                        }
                    }
                    turnText << " ";
                }
                else{
                    turnText << "-";
                }
            }
            turnText << endl;
        }
    }
    void writingOutput(){
        ofstream outputText;
        outputText.open ("output.txt");
        outputText << "Normal: " << normalCounter << endl << "Infected: " << infectedCount << endl << "Dead: " << deadCounter << endl <<  "Recovered: " << recoveredCounter << endl;
          for (int i = 0; i < 5; i++) {
              outputText << "entity " << i+1 << endl;
              for (int j = 0 ; j < afterTurnX[i].size(); j++) {
                  for (int a = 0 ; j < afterTurnY.size(); j++) {
                      for (int b = 0 ; j < afterTurnY[b].size(); j++) {
                          outputText << afterTurnX[i][j] << "x" << afterTurnY[a][b];
                      }
                  }
              }
              outputText << endl;
          }
          
       
    }
    void turnEntities(){
        int currentCount = 0;
        while (currentCount < turnCount ) {
            for (int  i = 0; i < entityCount; i++) {
                if (currentCount < 14 || ( currentCount >= 14 && firstSitutaion[i] != "GoingToDie")) {
                    afterTurnX.push_back(xTurnList[i]);
                    afterTurnY.push_back(yTurnList[i]);
                }
            }
        }
        currentCount++;
        infectedOtherEntity();
        infectedDays();
        //writingTurns(currentCount);
        //writingOutput();
    }
    

void entityAndTurnRead(){
    
    
    
    string satir = "";
    ifstream dosyaOku("/Users/beyzanurkaya/Desktop/input.txt");
    if (dosyaOku.is_open()){
         while (getline(dosyaOku, satir) ){
             //cout << satir << endl;
             if (startsWith(satir, "entity")) {
                 entityCount++;
                 initializeEntity(satir);
                 gunSayisi = 0;
             }else if (startsWith(satir, "turn ")){
                 turnCount++;
                 getTurnCoordinations(satir);
                 gunSayisi = 0;
                 xTurnList.push_back(xCoord); //tum xleriburda sakla
                 yTurnList.push_back(yCoord); //tum yleri burda sakla
                 xCoord.clear();
                 yCoord.clear();
             }
         }
         dosyaOku.close();
     }
    turnEntities();
}



int main() {
    
    entityAndTurnRead();
    cout << entityCount;
    return 0;
}
