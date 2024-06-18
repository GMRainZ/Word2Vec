#include"Word2Vec.hpp"

int main()
{
    Word2Vec w2v;

    w2v.train();
    w2v.save_matrix();

    return 0;
}