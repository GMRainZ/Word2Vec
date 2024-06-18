#include"Word2Vec.hpp"

#include<random>
#include<ctime>
#include<cmath>
//#include<fstream>

void Word2Vec::fit()//用于构建one_hot和映射哈希
{
    std::string trainSetPath=DATA_DIR;

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


        if(word2index.find(t)!=word2index.end())continue;

        word2index[t]=cnt;
        index2word[cnt]=t;

        one_hot[cnt][cnt]=1;

        if(++cnt>=Utils::word_dimension)break;
    }
}

Word2Vec::Word2Vec(/* args */)
    : w1(Utils::embedding_dimension, std::vector<double>(Utils::word_dimension)),
      w2(Utils::word_dimension, std::vector<double>(Utils::embedding_dimension)),
      one_hot(Utils::word_dimension, std::vector<double>(Utils::word_dimension))
{
    std::default_random_engine gen(time(0));
    std::uniform_real_distribution<> guass(-10,10);

    int i,j;
    for(i=0;i<Utils::word_dimension;++i)
    {
        for(j=0;j<Utils::embedding_dimension;++j)
        {
            w1[j][i]=guass(gen);
            w2[i][j]=guass(gen);
        }
    }


    
}

Word2Vec::~Word2Vec()
{
}


void Word2Vec::train()
{
    int i,j,k,forend;

    std::vector<double>hidden(Utils::embedding_dimension),
        output(Utils::word_dimension),G2(Utils::word_dimension),
        G1(Utils::embedding_dimension);

    std::vector<std::vector<double>>delta_w1(Utils::embedding_dimension, std::vector<double>(Utils::word_dimension)),
        delta_w2(Utils::word_dimension, std::vector<double>(Utils::embedding_dimension));
    
    auto w2_T=w1;
    for(i=0;i<Utils::epochs;++i)//每一次迭代
    {
        for(j=0;j<Utils::word_dimension;++j)//对于每一个词
        {
            //对于该词的上下文
            forend=std::min(Utils::word_dimension-1,j+Utils::n_gram);
            for(k=std::max(j-Utils::n_gram,0);k<=forend;++k)
            {
                Utils::vector_multiple_matrix(one_hot[k],w1,hidden);


                Utils::vector_multiple_matrix(hidden,w2,output);
                softmax(output);

                Utils::vector_minus(output,one_hot[k],G2);
                //delta_w2=hidden.T @ G2
                Utils::vectors2matrix(G2,hidden,delta_w2);
                //G1=G2@w2.T
                Utils::transpose(w2,w2_T);
                Utils::vector_multiple_matrix(G2,w2_T,G1);
                //delta_w1=oenhot[k].T@G1
                Utils::vectors2matrix(G1,one_hot[k],delta_w1);

                //update weight
                Utils::matrix_multiple_number(delta_w1,Utils::learning_rate,delta_w1);
                Utils::matrix_multiple_number(delta_w2,Utils::learning_rate,delta_w2);
            
                Utils::matrix_minus(w1,delta_w1,w1);
                Utils::matrix_minus(w2,delta_w2,w2);
            }
            //printf("this word sequence number is %d\n",j);
        }
        printf("iteration is %d\n",i);
    }

}

void Word2Vec::save_matrix()
{
    std::string save_path1=DATA_DIR,save_path2=DATA_DIR;
    save_path1+="/w1.txt",save_path2+="/w2.txt";
    std::ofstream ofs1(save_path1,std::ios_base::trunc),
        ofs2(save_path2,std::ios_base::trunc);

    int i,j;
    for(i=0;i<Utils::embedding_dimension;++i)
    {
        for(j=0;j<Utils::word_dimension;++j)
        {
            ofs1<<w1[i][j]<<' ';
        }
        ofs1<<'\n';
    }
    for(i=0;i<Utils::word_dimension;++i)
    {
        for(j=0;j<Utils::embedding_dimension;++j)
        {
            ofs2<<w2[i][j]<<' ';
        }
        ofs2<<'\n';
    }
}

// softmax函数用于计算softmax值
void Word2Vec::softmax(std::vector<double>&x)
{
    // 获取向量x的长度
    const int n=x.size();
    // 定义i
    int i;
    // 定义sum
    double sum=0.;
    // 遍历向量x
    for(i=0;i<n;++i)
        // 将x[i]取值为e的x[i]次方，并将结果累加到sum中
        x[i]=exp(x[i]),sum+=x[i];
    // 遍历向量x
    for(i=0;i<n;++i)
        // 将x[i]除以sum，得到softmax值
        x[i]/=sum;
}