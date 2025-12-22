#include <iostream>
#include <vector>
#include <memory> 
#include <fstream>
#include <string> 
#include <sstream>
#include <regex>

bool contains_duplicate(long long i){
    std::string s = std::to_string(i); 

    int length = s.length(); 

    if(length % 2 ==1) return 0; 

    size_t midpoint = length / 2; 

    std::string start = s.substr(0, midpoint); 
    std::string end = s.substr(midpoint); 

    return start == end; 
}

bool contains_duplicate_at_least_once(long long i){
    std::string s = std::to_string(i); 
    int length = s.length(); 

    std::regex string_regex(R"(^(.+)\1+$)"); 
    return std::regex_match(s, string_regex);
}

int main(){
    std::ifstream file("day2.txt");  
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

    long long sum = 0; 
    for(std::string& range : data){
        if (range.empty()) continue; 
        int dash = range.find('-');  
        long long start = std::stoll(range.substr(0, dash)); 
        long long end = std::stoll(range.substr(dash + 1)); 

        for(long long i = start; i<=end; i++){
            if(contains_duplicate_at_least_once(i)){
                sum+=i; 
            }
        }
    }
    std::cout << "The sum of the invalid duplicates is: " << sum << std::endl; 
}

