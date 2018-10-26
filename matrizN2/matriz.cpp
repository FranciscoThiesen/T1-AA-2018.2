#include <bits/stdc++.h>
#include <cassert>

using namespace std;

/* Lembrar de fazer testes com diferentes maxMatrixValue, porque o
 * Poggi comentou que o algoritmo era sensível a variações nos
 * tamanhos dos valores das matrizes
 */



/* Definicao da struct matriz que sera utilizada para a realizacao
 * dos testes de complexidade do algoritmo n^2 versus o n^3
 */
struct matrix 
{
    int N; // Dimensao da matriz quadrada N x N
    vector<vector<long long> > mat; // Essa eh a matriz propriamente dita
    int maxMatrixValue; // Esse eh o maior valor permitido no preenchimento da matriz com valores aleatorios
    

    /* Construtor a struct matriz. Recebe a dimensao e um segundo
     * parametro opcional que eh o valor maximo permitido na matrix.
     */
    matrix(int _N, int _maxMatrixValue = numeric_limits<int>::max() ) 
    {
        N = _N;
        maxMatrixValue = _maxMatrixValue;
        mat.assign( N, vector<long long>(N) );
    }
    
    /* Essa funcao serve pra ler os valores da matriz na mao
     * provavelmente nao sera muito usada, talvez na hora de ler de
     * um determinado arquivo seja mais util
     */
    void readMat()
    {
        assert(N > 0);
        for(int i = 0; i < N; ++i) for(int j = 0; j < N; ++j) cin >> mat[i][j];
    }

    /* Essa funcao serve para preencher a matriz com valores
     * aleatorios num intervalo (1, maxMatrixValue). Provavelmente
     * sera bastante usada para realizar os testes de corretude e
     * complexidade
     */
    void fillRandomMat()
    {
        assert(N > 0);
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> dis(1, maxMatrixValue);
        for(int i = 0; i < N; ++i) for(int j = 0; j < N; ++j) mat[i][j] = (long long) dis(generator); 
    }

};


/* Funcao que faz o produto de matrizes da forma pedestre O(n^3) */
inline matrix slowProduct(const matrix& M1, const matrix& M2)
{
    assert(M1.N == M2.N);
    int dimension = M1.N;
    matrix result(dimension);
    for(int i = 0; i < dimension; ++i)
    {
        for(int j = 0; j < dimension; ++j)
        {
            for(int k = 0; k < dimension; ++k)
            {
                result.mat[i][j] += (M1.mat[i][k] * M2.mat[k][j]); 
            }
        }
    }
    return result;
}

/* Funcao que faz o produto em "O(n^2)" */
inline matrix fastProduct(const matrix& M1, const matrix& M2)
{
    assert(M1.N == M2.N);
    long long dim = M1.N;
    
    /* Para tentar melhorar a legibilidade do codigo,
     * utilizarei a mesma notacao de variaveis do paper
     */

    long long a = 0, b = 0;
    for(int i = 0; i < dim; ++i)
    {
        for(int j = 0; j < dim; ++j)
        {
            a = max(M1.mat[i][j], a);
            b = max(M2.mat[i][j], b);
        }
    }
    long long x = (dim - 1) * a * b + 1;
    
    // Vamos agora calcular os bk's, utilizando o metodo de horner
    vector<long long> B(dim, 0);
    for(int k = 0; k < dim; ++k)
    {
        //metodo de horner
        long long xPot = 1;
        for(int j = 0; j < dim; ++j)
        {
            B[k] += (M2.mat[k][j] * xPot);
            xPot *= x;
        }
    }

    // Vamos agora calcular os ci's
    vector<long long> C(dim, 0);
    for(int i = 0; i < dim; ++i)
    {
        for(int k = 0; k < dim; ++k)
        {
            C[i] += (M1.mat[i][k] * B[k]);
        }
    }


    vector<vector<long long > > c(dim, vector<long long>(dim, 0) );
    vector<vector<long long > > q(dim, vector<long long>(dim, 0) );
    for(int i = 0; i < dim; ++i)
    {
        q[i][0] = C[i] / x; // divisao inteira
        c[i][0] = C[i] % x;
        
        for(int j = 1; j < dim - 2; ++j)
        {
            // qi(j-1) = qij x + cij ?
            q[i][j] = q[i][j - 1] / x;
            c[i][j] = q[i][j - 1] % x;
        }
        c[i][dim - 1] = q[i][dim - 3] / x;
        c[i][dim - 2] = q[i][dim - 3] % x;
    }
    
    // Em tese ja encotramos a resposta, falta atribuir a o tipo
    // matrix
    matrix result(dim);
    for(int i = 0; i < dim; ++i) for(int j = 0; j < dim; ++j) result.mat[i][j] = c[i][j];
    return result;
}

/* Instrucoes de uso
 * 1 - Para testar o programa com outras dimensoes da matriz, eh necessario 
 * alterar os parametros testSize e maxValue.
 * Apos alterar os valores, eh necessario compilar o codigo com 
 * g++ matriz.cpp -std=c++14 -O2 -o matriz
 * e depois rode o executável com ./matriz
 */


int main()
{
    constexpr int testSize = 11; // constante que define o tamanho da matriz a ser testada
    constexpr int maxValue = 2;  // constante que define o valor maximo permitido para um valor da matriz
    
    matrix M1(testSize, maxValue), M2(testSize, maxValue);
    
    M1.fillRandomMat();
    M2.fillRandomMat();
    
    matrix lento = slowProduct(M1, M2);
    matrix rapido = fastProduct(M1, M2); 
    
    if(lento.mat == rapido.mat) cout << " deu certo! " << endl;
    else 
    {
        cout << "resultados diferentes " << endl;
        cout << " imprimindo pedestre " << endl;
        for(int i = 0; i < testSize; ++i)
        {
            for(int j = 0; j < testSize; ++j)
            {
                cout << lento.mat[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << "imprimindo o rapido" << endl;
        for(int i = 0; i < testSize; ++i)
        {
            for(int j = 0; j < testSize; ++j)
            {
                cout << rapido.mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
