#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

ifstream f("input.txt");

vector < vector < pair < int, char > > > v;
vector < int > traseu;
int n, m, init, nrFinale, q;
bool gasit, eFinala[1000];

void DFS( int stare, char *s )
{
    //cout << "Stare: " << stare << endl << "s = " << s << endl << endl;
    if( gasit )
        return;
    if( strcmp( s, "" ) == 0 && eFinala[ stare ] )
    {
        gasit = true;
        return;
    }
    for( int i = 0; i < v[stare].size(); ++i )
        if( s[0] == v[stare][i].second || v[stare][i].second == '#' )
        {
            traseu.push_back( v[stare][i].first );
            if( s[0] == v[stare][i].second )
                DFS( v[stare][i].first, s + 1 );
            else
                DFS( v[stare][i].first, s );
            if( gasit )
                return;
            traseu.pop_back();
        }
}

void citireLambdaNFA()
{
    f >> n >> m;
    v.resize( n );
    for( int i = 0; i < m; ++i )
    {
        int x, y;
        char z;
        f >> x >> y >> z;
        v[x].push_back( make_pair( y, z ) );
    }
    f >> init >> nrFinale;
    for( int i = 0; i < nrFinale; ++i )
    {
        int x;
        f >> x;
        eFinala[x] = true;
    }
}

int main()
{
    citireLambdaNFA();
    f >> q;
    for( int i = 0; i < q; ++i )
    {
        char s[256];
        f >> s;
        traseu.clear();
        gasit = false;
        if( strcmp( s, "#" ) == 0 )
            gasit = true;
        DFS( init, s );
        if( gasit )
        {
            cout << "DA\nTraseu: " << init << " ";
            for( int i = 0; i < traseu.size(); ++i )
                cout << traseu[i] << " ";
            cout << endl;
        }
        else
            cout << "NU\n";
    }
    f.close();
    return 0;
}