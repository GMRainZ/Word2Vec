#pragma once

#include"Utils.hpp"
#include<unordered_map>
#include<iostream>
#include<algorithm>


class Word2Vec
{
private:
    /* data */
    //两个哈希表
    std::unordered_map<std::string,int>word2index;
    std::unordered_map<int,std::string>index2word;

    //两个变换矩阵
    std::vector<std::vector<double>>w1,w2;

    //一个词汇表
    std::vector<std::vector<double>>one_hot;

    void fit();
    void softmax(std::vector<double>&);

    
public:
    Word2Vec(/* args */);
    ~Word2Vec();


    void train();
    void save_matrix();
};

