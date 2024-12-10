#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

template <typename T> class DSU {
protected:
    std::vector<int> parent;
    std::vector<int> ranks;
    int DSU_size;
public:
    DSU(){
        DSU_size = 0;
    }
    DSU (const int num){
        DSU_size = num;
        for (int i = 0; i < DSU_size; i++){
            parent.push_back(i);
            ranks.push_back(i);
        }
    }

    int get_root_number(int num){
        if (parent[num] == num)
            return  num;
        else 
            return get_root_number(parent[num]);
    }
    bool  is_root(int num) {
        return (get_root_number(num) == num) ? true : false;
    }
    bool not_root(int num){
        return !is_root(num);
    }
    void merge(int tree_A, int tree_B){
        int tree_A_root = get_root_number(tree_A);
        int tree_B_root = get_root_number(tree_B);
        if (tree_A_root == tree_B_root)
            return;
        if (ranks[tree_A_root] < ranks[tree_B_root])
            parent[tree_A_root] = tree_B_root;
        else if (ranks[tree_A_root] > ranks[tree_B_root])
            parent[tree_B_root] = tree_A_root;
        else { 
            parent[tree_A_root] = tree_B_root;
            ranks[tree_B_root]++; 
        }
    }
    std::vector<int> calculate_component_numbers(){
        std::vector<int> components;
        std::vector<std::pair<int,int>> trees;
        int current_comp = 0;
        for (int i = 0; i < DSU_size; i++) {
            if (is_root(i)) {
                trees.push_back(std::pair<int,int>(i, ++current_comp));
            }
        }
        for (int i = 0; i < DSU_size; i++) {
            int tmp = get_root_number(i);
            int it = 0; 
            for (int j = 0; j < trees.size(); j++)
                if (trees[j].first == tmp) {
                    it = j;
                    break;
                }
            components.push_back(trees[it].second);

        }
    return components;
    }
};

template <typename T> class DSU_path_compression: public DSU<T>{
public:
    DSU_path_compression(){
        DSU_size = 0;
    }
    DSU_path_compression (const int num){
        DSU_size = num;
        for (int i = 0; i < DSU_size; i++){
            parent.push_back(i);
            ranks.push_back(i);
        }
    }
    int get_root_number(int num){
        return (parent[num] == num) ? num : (parent[num] = get_root_number(parent[num]));
    }
    void merge(int tree_A, int tree_B) {
        int tree_A_root = get_root_number(tree_A);
        int tree_B_root = get_root_number(tree_B);
        if (tree_A_root == tree_B_root)
            throw("error: trying to merge tree with itself");
        
        if (ranks[tree_A_root] < ranks[tree_B_root])
            parent[tree_A_root] = tree_B_root;
        else if (ranks[tree_A_root] > ranks[tree_B_root])
            parent[tree_B_root] = tree_A_root;
        else { 
            parent[tree_A_root] = tree_B_root;
            ranks[tree_B_root]++; 
        }
    }
};

std::vector<int> RAM_algorithm(DSU<int> dsu, std::vector<std::pair<int, int>> E);

std::vector<std::pair<int, int>> pseudo_random_edges(const int n, const int amount);