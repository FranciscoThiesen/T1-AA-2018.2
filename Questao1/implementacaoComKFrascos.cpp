#include <bits/stdc++.h>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;
using namespace std::chrono;

inline void imprimeGrupo(int tamanhoGrupo, unsigned long long valorGrupo)
{
    deque<int> digs;
    while(valorGrupo > 0) 
    {
        digs.push_front(valorGrupo & 1ULL);
        valorGrupo >>= 1;
    }
    while((int) digs.size() < tamanhoGrupo)
    {
        digs.push_front(0);
    }
    for(const int& x : digs) cout << x;
    cout << endl;
}

// É necessário tomar cuidado com as flags, para que o GCC nao otimize essa funcao
inline unsigned long long resolveParaUmGrupo(unsigned long long valorDoGrupo)
{
    unsigned long long X = 0;
    while(X < valorDoGrupo) ++X;
    return X;
}


pair<bool, unsigned long long> resolveComKFrascos(int numeroDeBits, int numeroDeFrascos, vector<bool> bits)
{
    // Vou separar o inteiro de X bits, em K inteiros de X / K bits e resolver pra cada inteiro separadamente
    // A ideia de separar o numero em K inteiros tem a intencao de fazer cada inteiro ser < 2^64, e com isso podemos
    // Usar o tipo unsigned long long ao inves de usar bitsets
    cout << numeroDeBits << " " << numeroDeFrascos << " " << (int) bits.size() << endl;
    if(numeroDeBits / numeroDeFrascos > 32)
    {
        // Se tiver mais de 64 bits em cada grupo, o algoritmo vai levar uma quantidade enorme de segundos
        // Vou me restringir a analisar os casos que devem rodar em alguns segundos
        return make_pair(false, 0);
    }
    // Estamos assumindo que o numero de bits máximo da instância é divisível pelo número de frascos
    unsigned long long totalComparacoes = 0;
    
    // Vamos imprimir o inteiro recebido///////////////////////////////////
    cout << "Inteiro recebido " << endl;
    for(int i = 0; i < numeroDeBits; ++i) {
        if(bits[i]) cout << 1;
        else cout << 0;
    }
    cout << endl;
    /////////////////////////////////////////////////////////////////////// 
    
    // Gerando as potencias de 2 necessarias///////////////////////////////
    vector<unsigned long long> pot2(32);
    pot2[0] = 1ULL;
    for(int i = 1; i < 32; ++i) pot2[i] = (pot2[i - 1] * 2ULL); 
    ///////////////////////////////////////////////////////////////////////
    
    // Preenchendo os subgrupos ///////////////////////////////////////////
    int bitsPorGrupo = numeroDeBits / numeroDeFrascos;
    vector<unsigned long long> grupo(numeroDeFrascos, 0);
    reverse(bits.begin(), bits.end() );
    for(int i = 0; i < numeroDeBits; ++i)
    {
        if(bits[i] == true)
        {
            grupo[i / bitsPorGrupo] += pot2[i % 32];
        }
    }
    //////////////////////////////////////////////////////////////////////

    // Imprimindo os SubGrupos
    for(int frasco = 0; frasco < numeroDeFrascos; ++frasco)
    {
        cout << "Imprimindo o grupo " << frasco + 1 << endl;
        imprimeGrupo(bitsPorGrupo, grupo[frasco] );
    }
    //////////////////////////////////////////////////////////////////////
    
    // Resolvendo o problema para cada subgrupo //////////////////////////
    for(int frasco = 0; frasco < numeroDeFrascos; ++frasco)
    {
        totalComparacoes += resolveParaUmGrupo(grupo[frasco]);
    }
    //////////////////////////////////////////////////////////////////////
    
    return make_pair(true, totalComparacoes);
}

constexpr array<int, 5> numFrascos       = {1, 2, 4, 8, 16};
constexpr array<int, 5> tamanhoDeBits    = {32, 64, 128, 196, 256};

int main()
{
    string pathPrefix = "instancias/bignum_";
    for(int i = 1; i <= 2; ++i)
    {
        for(const int F : numFrascos)
        {
            ofstream out("tempos/usando" + to_string(F) + "Frascos.csv"); 
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
                cout << numInstancias << endl;
                // quick-check
                auto ans = resolveComKFrascos(B, F, testes[0]);
                if(ans.first == false)
                {
                    in.close();
                    break;
                }
                high_resolution_clock::time_point inicio = high_resolution_clock::now();
                unsigned long long total = 0;
                for(vector<bool> bits : testes)
                { 
                    auto x = resolveComKFrascos(B, F, bits);
                    total += x.second; 
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









