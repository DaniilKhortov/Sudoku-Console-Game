//Бібліотеки
#include <iostream>
#include<cstdlib>
#include <ctime>
#include <string>
#include <Windows.h> //Бібліотека, що необхідна тільки для windows
using namespace std;

class Game{
private:    
    static const int length = 9;//Константа
    int sudoku[length][length]; //Масив відповіді сітки судоку
    int unsolvedSudoku[length][length]; // Масив нерозв`язаної сітки судоку

    //Оголошення методів
    void shuffle(int *array);
    void write( int *array, int horizon);
    bool squareTest( int vertical); 
    bool verticalTest(int *array); 
    void sudokuGenerator();
    void sudokuHide();
public:
    //Оголошення методів
    void sudokuShow();
    bool writeSudoku();
    bool answerSudoku();
    bool winningCheck();
    void createNewGame();
};

void Game::sudokuShow(){ 
    int i, j; 
    for( i = 0; i < length; i++) { 
        if(i%3==0) 
            cout << "----------------------\n"; 
        cout << "|";     
        for(j=0; j<length; j++){ 
            if(unsolvedSudoku[i][j]==0){ 
                cout<<"- "; 
            }else { 
                cout<<unsolvedSudoku[i][j]<<" "; 
            }     
            if((j+1)%3 == 0) 
                cout << "|"; 
        } 
        cout << endl; 
    } 
    cout << "----------------------\n"; 
}

bool Game::winningCheck(){
  for(int i=0; i<length; i++){
    for(int j=0; j<length; j++){
        if(unsolvedSudoku[i][j]==0){
            return false;
        }
    }    
  }
  return true;
}

bool Game::answerSudoku(){
  for(int i=0; i<length; i++){
    for(int j=0; j<length; j++){
        if(unsolvedSudoku[i][j]!=0){
            if(sudoku[i][j]!= unsolvedSudoku[i][j])
               unsolvedSudoku[i][j]=0;
        }
    }    
  }
  return true;
}

void Game::sudokuHide(){
    int counter = 20;
    while(counter !=0){
        int i = (rand()%length); 
        int j = (rand()%length); 
        if(unsolvedSudoku[i][j] != 0){
            unsolvedSudoku[i][j]=0;
            unsolvedSudoku[j][i]=0;
            counter--;
        }
    }
}

bool Game::writeSudoku() {
    int row, column, value; 
    try {
        char rowChar, columnChar, valueChar;
        cin >> rowChar >> columnChar >> valueChar;
        row = rowChar - '0'; 
        column = columnChar - '0'; 
        value = valueChar - '0'; 

        if (row > 0 && row <= length && column > 0 && column <= length && value > 0 && value <= length) {
            if (unsolvedSudoku[row - 1][column - 1] == 0) {
                unsolvedSudoku[row - 1][column - 1] = value;
                return true;
            } else if(unsolvedSudoku[row - 1][column - 1] != 0){
                cout << "B клітинці вже є число!" << endl;
                return false;
            }else{
                cout << "Число за межами сітки судоку!" << endl;
                return false; 
            }
        } else {
            throw 10;
        }
    } catch (int i) {
        cout << "Некоректний ввід!" << endl;
        return false;
    }
}


void Game::shuffle(int *array){ 
    for(int i = 0; i<length-1; i++){ 
        int j = i+rand() / (RAND_MAX / (length-i)+1); 
        int temp = array[j]; 
        array[j] = array[i]; 
        array[i] = temp; 
    } 
    
} 


bool Game::verticalTest( int *array){ 
    for(int i = 0; i<length; i++){ 
        for(int j = 0; j<length; j++){ 
            if(array[i] == sudoku[j][i]){ 
                return true; 
            } 
        } 
         
    } 
    return false; 
} 
 
bool Game::squareTest( int vertical) {
    int binAr[9] = {0};

    for (int k = 0; k < 3; k++) {
        for (int i = vertical; i < vertical + 3; i++) {
            for (int j = k * 3; j < k * 3 + 3; j++) {
                binAr[sudoku[i][j] - 1] = 1;
            }
        }
        
        for (int t = 0; t < length; t++) {
            if (binAr[t] == 0) {
                return true;
            }
        }
        fill(binAr, binAr + length, 0); 
    }

    return false;
}
 
void Game::write( int *array, int horizon){ 
    shuffle(array); 
    while(verticalTest(array)){ 
        shuffle(array); 
    } 
    for(int i=0; i<length; i++){ 
        sudoku[horizon][i]=array[i]; 
    } 
}  


void Game::sudokuGenerator() {
    for (int i = 0; i < length; i++) { 
        for (int j = 0; j < length; j++){ 
            sudoku[i][j] = {0}; 
        }    
    } 
 
    srand((unsigned)time(0)); 
    int arr[length] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
    do { 
        write(arr, 0); 
        write(arr, 1); 
        write(arr, 2); 
    } 
    while (squareTest(0)); 
 
    do { 
        write( arr, 3); 
        write( arr, 4); 
        write( arr, 5); 
    } 
    while (squareTest(3));  
 
    do { 
        write( arr, 6); 
        write( arr, 7); 
        write( arr, 8); 
    } 
    while (squareTest(6)); 

}

void Game::createNewGame(){
    
    sudokuGenerator();

    //Зберігаємо вказівник згенерованої відповіді у масив відповіді сітки судоку та масив нерозв`язаної сітки судоку
    for(int i = 0; i<length; i++){
        for(int j = 0; j<length; j++){
            unsolvedSudoku[i][j]=sudoku[i][j];
        }
    } 
    //генеруємо задачу
    sudokuHide();
}

//Головний метод main
int main() {
    //Підключення UTF8 для windows
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    //Початок гри
    cout<<"Запрошуємо y Судоку. Хочете зіграти?"<<endl;
    cout<<"1-Так\n2-Hi"<<endl;
    bool umova = false; //Булева змінна для виходу з циклу
    string temp; //Змінна для користувацького вводу
    while(!umova){
        cout<<"Ваш вибір: ";
        try{
            cin>> temp;
            if(temp!="1" && temp!="2"){//Якщо користувач не вводить 1 або 2, то сприймається ввід за вийняток
                throw 10;
                break;
            }else{ 
                if(temp=="1"){
                    //Вихід з циклу
                    umova = true;
                }else if(temp=="2"){
                    cout<<"Зустрінимось наступного разу!"<<endl;
                    return 0;
                }
        }
            
        }catch(int i){
            cout<<"Некоректна команда!"<<endl;
        }
    }
    
    Game play = Game();
    //Генерація нової задачі
    play.createNewGame();

    while(umova){
        //вивід сітки судоку та меню
        play.sudokuShow();
        cout<<"Можливі дії:"<<endl;
        cout<<"1.Вписати число в сітку судоку."<<endl;
        cout<<"2.Перевірити відповідь."<<endl;
        cout<<"3.Почати новий судоку."<<endl;
        cout<<"4.Вийти з гри."<<endl;
        try{
            cout<<"Ваш вибір: ";
            cin>> temp;
            if(temp!="1" && temp !="2" && temp !="3" && temp !="4"){//Якщо користувач не вводить 1, 2, 3 або 4 то сприймається ввід за вийняток
                throw 10;

            }else{
                if(temp=="1"){
                        cout<<"Введіть число через пробіли від 1 до 9:\n(рядок) (стовпчик) (число)"<<endl;
                        //Введення нового числа в судоку
                        if(!play.writeSudoku()){
                            cout<<"Спробуй ще!\n";
                        }
                }else if(temp=="2"){
                        //Перевірка користувацької відповіді на помилки. Очистка неправильнихх чисел
                        if(play.answerSudoku()){
                            cout<<"Перевірка успішна!"<<endl;
                                //Перевірка повної користувацької відповіді із правильною
                                if(play.winningCheck()){
                                    cout<<"Вітаю, ви вирішили судоку!!!"<<endl;
                                        return 0;
                                } 
                        }else{
                            cout<<"Тут були помилки."<<endl;
                        }
                }else if(temp=="3"){
                       //Генерація нової задачі
                       play.createNewGame();
                }else if(temp == "4"){
                        cout<<"Зустрінимось наступного разу!"<<endl;
                        return 0;
                }
        
            }
        }catch(int i){
            cout<<"Некоректна команда!"<<endl;
        }
    }
}

