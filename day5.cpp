#include <iostream>
#include <vector>
#include <memory> 
#include <fstream>
#include <string>
#include <sstream>  
#include <unordered_set>
#include <algorithm>


void solve_part_one(std::string filename){
    std::ifstream file(filename); 

    std::vector<std::string> first_block; 
    std::vector<std::string> second_block; 

    std::string line; 
    int total = 0; 

    bool second = false; 
    while(std::getline(file, line)){
        if(line.empty()){
            second = true; 
            continue; 
        }
        if(!second){
            first_block.push_back(line); 
        }else{
            second_block.push_back(line);
        } 
    }
        for(std::string& id : second_block){
            long long item_num  = std::stoll(id); 
            for(std::string& span : first_block){
                size_t dash = span.find('-'); 
                long long lo = std::stoll(span.substr(0,dash)); 
                long long hi = std::stoll(span.substr(dash+1));
                if(item_num >=lo && item_num <= hi){
                    total++; 
                    break; 
                }
            } 
        }
    std::cout << "The total number of fresh goods is: " << total <<std::endl;
} 



void solve_part_two(std::string filename){
    std::ifstream file(filename); 
    std::vector<std::string> first_block; 

    std::string line; 
    std::vector<std::pair<long long, long long>> ranges; 
    std::vector<std::pair<long long, long long>> merged; 
    long long total = 0; 

    while(std::getline(file, line)){
        if(line.empty()){
            break; 
        }
        first_block.push_back(line);
        size_t dash = line.find('-'); 
        long long lo = std::stoll(line.substr(0,dash)); 
        long long hi = std::stoll(line.substr(dash+1));
        ranges.emplace_back(lo, hi); 
    } 
    std::sort(ranges.begin(), ranges.end()); 
    merged.push_back(ranges[0]);  
    for(size_t i = 1; i< ranges.size(); i++){
        auto& last = merged.back();  
        if(ranges[i].first <= last.second+1){
            last.second = std::max(last.second, ranges[i].second); 
        }else{
            merged.push_back(ranges[i]); 
        }

    } 
    for( auto& range : merged){
        total += range.second - range.first +1; 
    }
    std::cout << "The total number of fresh good id's is: " << total <<std::endl;
}


int main(){
    solve_part_one("day5.txt"); 
    solve_part_two("day5.txt"); 
}