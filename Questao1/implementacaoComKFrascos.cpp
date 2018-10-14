#include <bits/stdc++.h>
#include <ctime>
#include <ratio>
#include <chrono>
#include <cassert>

using namespace std;
using namespace std::chrono;

constexpr bool debug = false;

// Função auxiliar para impressão dos bits de um grupo
inline void imprimeGrupo(int tamanhoGrupo, unsigned int valorGrupo)
{
    deque<int> digs;
    while(valorGrupo > 0) 
    {
        digs.push_front(valorGrupo & 1u);
        valorGrupo >>= 1;
    }
    while((int) digs.size() < tamanhoGrupo)
    {
        digs.push_front(0);
    }
    for(const int& x : digs) cout << x;
    cout << endl;
}


/* Essa é a função que realiza o maior trabalho do algoritmo.
 * Dado que um determinado grupo de bits da resposta tem valor 011101010...
 * Vamos comecar da altura 0, e ir aumentando a altura um a um, até chegar na
 * altura de quebra
 * 
 * Observação importante: Não compilar o código com a flag -O2, porque senão
 * o compilador irá otimizar essa função para algumas operações de tempo 
 * constante. (Eu olhei no assembly)
 */
unsigned int resolveParaUmGrupo(unsigned int valorDoGrupo)
{
    unsigned int X = 0;
    while(X < valorDoGrupo) ++X;
    return X;
}




/* Essa funcao tem como papel coordenar a execução do algoritmo descrito para
 * K frascos. Ela irá quebrar os bits da altura total em grupos de 32 bits para
 * que possamos chamar a funcao resolverParaUmGrupo() descrita acima para cada
 * um dos grupos de bits individualmente
 */

string resolveComKFrascos(int numeroDeBits, int numeroDeFrascos, vector<bool> bits)
{
    // garantindo que nao teremos mais de 32 bits por grupo, o que tornaria a 
    // instancia grande demais para rodar no tempo esperado
    assert(numeroDeBits / numeroDeFrascos <= 32);
    
    
    // Imprimindo os bits da altura de quebra (parametro)//////////////////
    if(debug)
    {
        cout << "Altura de quebra recebida como parametro = ";
        for(int i = 0; i < numeroDeBits; ++i)
        {
            cout << (bits[i] ? '1' : '0');
        }
        cout << endl;
    }

    // Gerando as potencias de 2 necessarias///////////////////////////////
    vector<unsigned int> pot2(32);
    pot2[0] = 1u;
    for(int i = 1; i < 32; ++i) pot2[i] = (pot2[i - 1] << 1u); 
    ///////////////////////////////////////////////////////////////////////
    // Preenchendo os subgrupos ///////////////////////////////////////////
    int bitsPorGrupo = numeroDeBits / numeroDeFrascos;
    vector<unsigned int> grupo(numeroDeFrascos, 0);
    
    // So para representarmos a resposta da maneira mais conveniente
    // ( do menos significativo para o mais significativo )
    reverse(bits.begin(), bits.end());
    
    
    // Aqui estamos distribuindo os bits da resposta pelos K grupos de bits
    for(int i = 0; i < numeroDeBits; ++i)
    {
        if(bits[i] == true)
        {
            grupo[i / bitsPorGrupo] += pot2[i % bitsPorGrupo];
        }
    }

    vector<unsigned int> resposta(numeroDeFrascos, 0);
    
    // Resolvendo o problema para cada subgrupo //////////////////////////
    for(int frasco = 0; frasco < numeroDeFrascos; ++frasco)
    {
        resposta[frasco] = resolveParaUmGrupo(grupo[frasco]);
    }
    //////////////////////////////////////////////////////////////////////
    
    // Aqui realizamos a juncao da resposta dos subproblemas
    string resultado; 
    for(int frasco = numeroDeFrascos - 1; frasco >= 0; --frasco)
    {
        for(unsigned int i = 0; i < 32; ++i)
        {
            resultado += '0' + !!(resposta[frasco] & (1u << i) );
        }
    }
    //////////////////////////////////////////////////////////////////////
    return resultado;
}

constexpr array<int, 5> numFrascos       = {1, 2, 4, 8, 16};
constexpr array<int, 5> tamanhoDeBits    = {32, 64, 128, 192, 256};

/* Observacoes gerais
 * 1 - Optei por nao rodar para instancias onde frascos * 2 ^ ( N / frascos ) > 2^32... Pois não iria acabar em um tempo razoavel!
 * 2 - É MUITO IMPORTANTE não compilar com a flag -O2, se não ele otimiza o código e o tempo de CPU não vai estar "honesto", porque ele não vai fazer todas as operacoes
 */



// Na main esta a logica de chamar todas as combinacoes numFrascos X tamanhoDeBits que rodam em um tempo razoável
int main()
{
    string pathPrefix = "instancias/bignum_";
    for(int i = 1; i <= 1; ++i)
    {
        for(const int F : numFrascos)
        {
            ofstream out("tempos/usando" + to_string(F) + "Frascos" + "0" + to_string(i) + ".csv"); 
            out << "Tamanho da Instancia," << "Tempo de CPU Total" << endl;
            for(const int B : tamanhoDeBits)
            {
                string pathSuffix = to_string(B) + "_0" + to_string(i) + ".dat";                
                ifstream in(pathPrefix + pathSuffix);
                int dummy, numInstancias;
                in >> dummy >> numInstancias;
                vector< vector< bool > > testes;
                for(int i = 0; i < numInstancias; ++i)
                {
                    string s;
                    in >> s;
                    vector<bool> b;
                    for(const char& c : s) 
                    {
                        if(c == '1') b.push_back(true);
                        else b.push_back(false);
                    }
                    testes.push_back(b);
                }
                if(B / F > 32) continue;
                high_resolution_clock::time_point inicio = high_resolution_clock::now();
                unsigned long long total = 0;
                for(vector<bool> bits : testes)
                { 
                    string x = resolveComKFrascos(B, F, bits);
                    // imprimir resposta encontrada -> Só se nao estiver fazendo benchmark!!
                    // cout << x << endl; 
                }
                high_resolution_clock::time_point fim = high_resolution_clock::now();
                duration<double> time_span = duration_cast< duration<double> >(fim - inicio);
                out << B << "," << time_span.count() << endl; 
                in.close();
            }
            out.close();
        }
    }
    return 0;
}

