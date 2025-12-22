#include <iostream>
#include <vector>
#include <memory> 
#include <fstream>
#include <string>
#include <sstream>



int find_largest_sub_num(std::string& input){

    int n = input.size(); 

    int max = input[n-1] - '0'; 

    int best_num = -1; 

    for(int i = n-2; i>=0; i--){
        int first = input[i] -'0'; 
        best_num = std::max(best_num, 10*first + max); 
        max = std::max(max, first); 
    }
    return best_num; 
}



long long find_largest_sub_num_12_digits(std::string& input, int k){
    int n = input.size(); 
    int remove = n-k; 

    std::string stack; 

    for(char c : input){
        while(!stack.empty() && remove > 0 && stack.back() < c){
            stack.pop_back(); 
            --remove; 
        }
        stack.push_back(c); 
    }
    stack.resize(k); 
    return std::stoll(stack); 


}

int main(){
    long long max = 0; 
    std::ifstream file("day3.txt");  
    std::string line; 
    std::vector<std::string> data; 
    while(std::getline(file, line)){
        std::stringstream iss(line); 
        std::string id; 
        while(std::getline(iss, id, ',')){
            if(!id.empty()){
                data.push_back(id);
            }  
        }  
    }
    for(std::string& val : data){
        max+= find_largest_sub_num_12_digits(val, 2); 
    }
    std::cout << "the sum is: " << max << std::endl; 
}