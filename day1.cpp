#include <iostream>
#include <vector>
#include <memory> 
#include <fstream>
#include <string>

int safe_modulo(int a, int m) {
    return ((a % m) + m) % m;
}

int main(){
    std::ifstream file("day1.txt"); 
    std::string turn; 
    int max = 100; //max value on the dial
    int pos = 50;
    int numZeros = 0; 
    while(std::getline(file, turn)){
        char direction = turn[0]; 
        int clicks = std::stoi(turn.substr(1)); 
        for(int i = 0; i<clicks; ++i){
            if(direction == 'L'){
                pos -=1;
            }else if (direction == 'R'){
                pos +=1; 
            }
            if(pos >= max){
                pos = 0; 
            }   
            if(pos < 0){
                pos = max - 1;
            }
            if(pos == 0){
                numZeros++; 
            }
        }
    }
    std::cout << "The password is: " << numZeros <<std::endl; 
}
