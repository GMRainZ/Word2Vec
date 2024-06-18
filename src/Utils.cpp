#include"Utils.hpp"




namespace Utils::Config
{
    int word_dimension=300;//词汇量

    int embedding_dimension=117;//词嵌入的维数

    double learning_rate=0.001;

    //int word_num=10000;
    int epochs=1e2;

    int n_gram=3;
}
void Utils::vector_minus(const std::vector<double>&x1,const std::vector<double>&x2,
        std::vector<double>&x)
{
    const int n=x1.size();
    for(int i=0;i<n;++i)x[i]=x1[i]-x2[i];
}


// 计算两个向量的乘积
double Utils::vector_mutiple(const std::vector<double>&x1,const std::vector<double>&x2)
{
    // 获取向量x1的长度
    const int n=x1.size();
    // 定义返回值ans
    double ans=0.;
    // 遍历向量x1和x2
    for(int i=0;i<n;++i)ans+=x1[i]*x2[i];

    // 返回计算结果
    return ans;
}

void Utils::vector_multiple_matrix(const std::vector<double>&src,
    const std::vector<std::vector<double>>&matrix,std::vector<double>&dst)
{
    const int row=matrix.size(),col=matrix[0].size();
    int i;
    for(i=0;i<row;++i)
    {
        dst[i]=vector_mutiple(src,matrix[i]);
    }
}
void Utils::vectors2matrix(const std::vector<double>&x1,const std::vector<double>&x2,
    std::vector<std::vector<double>>&matrix)
{
    const int row=x1.size(),col=x2.size();
    int i,j;

    for(i=0;i<row;++i)
    {
        for(j=0;j<col;++j)
        {
            matrix[i][j]=x1[i]*x2[j];
        }
    }

}
void Utils::transpose(const std::vector<std::vector<double>>&src,
    std::vector<std::vector<double>>&dst)
{

    const int row=src.size(),col=src[0].size();

    int i,j;
    for(i=0;i<row;++i)
    {
        for(j=0;j<col;++j)
        {
            dst[j][i]=src[i][j];
        }
    }
}

void Utils::matrix_multiple_number(const std::vector<std::vector<double>> &matrix, 
    const double x,std::vector<std::vector<double>>&dst)
{
    const int row=matrix.size(),col=matrix[0].size();

    int i,j;
    for(i=0;i<row;++i)
    {
        for(j=0;j<col;++j)
        {
            dst[i][j]=matrix[i][j]*x;
        }
    }
}


void Utils::matrix_minus(const std::vector<std::vector<double>>&matrix1,const std::vector<std::vector<double>>&matrix2,
        std::vector<std::vector<double>>&dst)
{
    const int row=matrix1.size();
    for(int i=0;i<row;++i)
    {
        vector_minus(matrix1[i],matrix2[i],dst[i]);
    }
}
void Utils::getTrainData(std::vector<std::string>&trainData)
{
    std::string trainSetPath=DATA_DIR;

    // printf("%s\n",DATA_DIR);

    trainSetPath+="/train_content.txt";


    std::ifstream ifs(trainSetPath);

    std::string t;
    int cnt=0;
    while(!ifs.eof())
    {
        ifs>>t;

        printf("%s\n",t.c_str());

        if(t[0]=='\"')t.erase(0);
        if(t.back()=='\"')t.erase(t.size()-1);

        if(isdigit(t[0]))continue;

        trainData.emplace_back(t);
        if(++cnt>Config::word_dimension)break;
    }
}

void Utils::getTestData(std::vector<std::string>&testData)
{
    std::string trainSetPath=DATA_DIR;
    trainSetPath+="/test_content.txt";

    std::ifstream ifs(trainSetPath);

    std::string t;
    while(!ifs.eof())
    {
        ifs>>t;
        if(t[0]=='\"')t.erase(0);
        if(t.back()=='\"')t.erase(t.size()-1);

        if(isdigit(t[0]))continue;

        testData.emplace_back(t);
    }
}