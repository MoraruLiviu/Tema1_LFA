#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;
stack <int> s;
void traseu()
{
    while(!s.empty())
    {
        int nod = s.top();
        s.pop();
        traseu();
        cout << nod << " ";
    }
}


int lambda_NFA(int stanga, int dreapta, int pozitie, int stari, string cuvant, char matrix[100][100])
{
    int i;
    int k = 0;
    s.push(stanga);
    for(i = 0; i < stari; i++)
    {
        if(matrix[stanga][i] == cuvant[pozitie])
        {
            lambda_NFA(i, dreapta, pozitie +1, stari, cuvant, matrix);
            k = 1;
        }
        else if(matrix[stanga][i] == '#')
        {
            lambda_NFA(i, dreapta, pozitie, stari, cuvant, matrix);
            k = 1;

        }
    }

    if(k)
    {
        if(s.size() == cuvant.length() + 1)
            return 1;
        else
            s.pop();
    }
    else
    {
        s.pop();
    }

    if(s.empty())
        return 0;
}

int main()
{
    int nr_stari;
    int nr_tranzitii;
    char matrix[100][100];
    int stanga, dreapta, nr_cuvinte, stare_initiala, nr_stari_finale;
    char caracter, cuvant[100];

    ifstream input("input.in");

    input >> nr_stari >> nr_tranzitii;
    for(int i = 0; i < nr_tranzitii; i++)
    {
        input >> stanga >> dreapta >> caracter;
        matrix[stanga][dreapta] = caracter;
    }

    input >> stare_initiala;
    input >> nr_stari_finale;
    vector <int> stari_finale(nr_stari_finale);
    for(int i = 0; i < nr_stari_finale; i++)
        input >> stari_finale[i];

    input >> nr_cuvinte;
    for(int i = 0; i < nr_cuvinte; i++)
    {
        input >> cuvant;

        int verif = 0;
        int k;
        for(int j = 0; j < nr_stari_finale; j++)
        {
            k = j;
            if(lambda_NFA(stare_initiala, stari_finale[j], 0, nr_stari, cuvant, matrix))
                verif = 1;
        }

        if(verif)
        {
            cout << "DA" << endl;
            cout << "Traseu: ";
            traseu();
            cout << stari_finale[k] << endl;
        }
        else
            cout << "NU" << endl;

    }

    return 0;

}
