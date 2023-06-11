#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

void ispisiPoruku(string poruka, bool ispisiKrov = true, bool ispisiPod = true)
{
    if (ispisiKrov)
    {
        cout << "+---------------------------------+" << endl;
        cout << "|";
    }
    else
    {
        cout << "|";
    }
    bool front = true;

    for (int i = poruka.length(); i < 33; i++)
    {
        if (front)
        {
            poruka = " " + poruka;
        }
        else
        {
            poruka = poruka + " ";
        }
        front = !front;
    }
    cout << poruka.c_str();

    if (ispisiPod)
    {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl;
    }
    else
    {
        cout << "|" << endl;
    }
}

void vjesalo(int brojPokusaja = 0)
{
    if (brojPokusaja >= 1)
        ispisiPoruku("|", false, false);
    else
        ispisiPoruku("", false, false);

    if (brojPokusaja >= 2)
        ispisiPoruku("|", false, false);
    else
        ispisiPoruku("", false, false);

    if (brojPokusaja >= 3)
        ispisiPoruku("O", false, false);
    else
        ispisiPoruku("", false, false);

    if (brojPokusaja == 4)
        ispisiPoruku("/  ", false, false);

    if (brojPokusaja == 5)
        ispisiPoruku("/| ", false, false);

    if (brojPokusaja >= 6)
        ispisiPoruku("/|\\", false, false);
    else
        ispisiPoruku("", false, false);

    if (brojPokusaja >= 7)
        ispisiPoruku("|", false, false);
    else
        ispisiPoruku("", false, false);

    if (brojPokusaja == 8)
        ispisiPoruku("/", false, false);

    if (brojPokusaja >= 9)
        ispisiPoruku("/ \\", false, false);
    else
        ispisiPoruku("", false, false);
}
bool funkcija(string rijec, string pokusaj)
{
    bool pobjeda = true;
    string s;
    for (int i = 0; i < rijec.length(); i++)
    {
        if (pokusaj.find(rijec[i]) == string::npos)
        {
            pobjeda = false;
            s += "_ ";
        }
        else
        {
            s += rijec[i];
            s += " ";
        }
    }
    ispisiPoruku(s, false);
    return pobjeda;
}
string ucitajRijec(string put)
{
    string rijec;
    vector<string> v;
    ifstream citac(put);
    if (citac.is_open())
    {
        while (std::getline(citac, rijec))
            v.push_back(rijec);

        int randomLine = rand() % v.size();

        rijec = v.at(randomLine);
        citac.close();
    }
    return rijec;
}
int preostaloPokusaja(string rijec, string pogodeno)
{
    int greska = 0;
    for (int i = 0; i < pogodeno.length(); i++)
    {
        if (rijec.find(pogodeno[i]) == string::npos)
            greska++;
    }
    return greska;
}
int main()
{
    fstream rez;
    int rezultat;
    srand(time(0));
    string p;
    string rijecZaPogodit;
    rijecZaPogodit = ucitajRijec("words.txt");
    int po = 0;
    bool pobjeda = false;
    do
    {
        system("cls");
        ispisiPoruku("VJESALO");
        vjesalo(po);
        ispisiPoruku("Guess the word");
        pobjeda = funkcija(rijecZaPogodit, p);
        ispisiPoruku("Rezultat", false, false);
        rez.open("rezultat.bin",ios::binary|ios::in);
        rez.read((char*)&rezultat,sizeof(rezultat));
        rez.close();
        stringstream ss;
        ss << rezultat;
        string str = ss.str();
        ispisiPoruku(str, false, true);
        int rezultat = stoi(str);
        if (pobjeda)
            break;

        char x;
        cout << ">"; cin >> x;

        if (p.find(x) == string::npos)
            p += x;

        po = preostaloPokusaja(rijecZaPogodit, p);
    } while (po < 10);

    ispisiPoruku("Resetirati rezultat?(Y/N)", true, true);
    char a;
    cout << ">"; cin >> a;
    if(a=='Y'||'y')
    {
        rez.open("rezultat.bin",ios::binary|ios::in);
        rez.read((char*)&rezultat,sizeof(rezultat));
        rez.close();
        rezultat=-1;
        rez.open("rezultat.bin",ios::binary|ios::out);
        rez.write((char*)&rezultat,sizeof(rezultat));
    }

    if (pobjeda)
    {
        ispisiPoruku("POBJEDIO SI!");
        rez.open("rezultat.bin",ios::binary|ios::in);
        rez.read((char*)&rezultat,sizeof(rezultat));
        rez.close();
        rezultat++;
        rez.open("rezultat.bin",ios::binary|ios::out);
        rez.write((char*)&rezultat,sizeof(rezultat));
        rez.close();
    }
    else
        ispisiPoruku("IZGUBIO SI");

    system("pause");
    getchar();
    return 0;
}
