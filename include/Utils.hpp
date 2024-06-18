#pragma once

#include<vector>
#include<string>
#include<fstream>


namespace Utils
{
    //获取词表
    void getTrainData(std::vector<std::string>&trainData);
    void getTestData(std::vector<std::string>&testData);
    double vector_mutiple(const std::vector<double>&,const std::vector<double>&);

    void vector_multiple_matrix(const std::vector<double>&,const std::vector<std::vector<double>>&,
    std::vector<double>&);
    void vector_minus(const std::vector<double>&,const std::vector<double>&,
        std::vector<double>&);

    void vectors2matrix(const std::vector<double>&,const std::vector<double>&,
        std::vector<std::vector<double>>&);

    void transpose(const std::vector<std::vector<double>>&,std::vector<std::vector<double>>&);

    void matrix_multiple_number(const std::vector<std::vector<double>>&,
        const double,std::vector<std::vector<double>>&);

    void matrix_minus(const std::vector<std::vector<double>>&,const std::vector<std::vector<double>>&,
        std::vector<std::vector<double>>&);
    inline 
    namespace Config
    {
        extern int word_dimension;//词向量维数

        extern int embedding_dimension;//词嵌入的维数

        extern double learning_rate;

        // extern int word_num;//词汇的个数

        extern int epochs;//迭代次数
        extern int n_gram;//上下文
    }
}


