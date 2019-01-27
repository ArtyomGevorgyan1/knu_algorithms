#define MAGIC_CONST 1000

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <assert.h>

using std::string;
using std::vector;

// get parameters for liner hashing
struct Params {
    int a;
    int b;
    int p;
    int m;
    Params(int a, int b, int p, int  m) {
        this -> a = a;
        this -> b = b;
        this -> p = p;
        this -> m = m;
    }
    Params(){}
    bool operator == (Params& p) {
        return this -> a == p.a
                && this -> b == p.b
                && this -> m == p.m
                && this -> p == p.p;
    }
};

Params goodParams[] =
{
    Params(7, 3, 107, 31),
    Params(1, 0, 31, 31),
    Params(101, 1, 97,31),
    Params(3, 2, 1187,31)
};

Params getRandomParam() {
    return goodParams[std::rand() % 4];
}

int getHIndex(Params p) {
    for (int i = 0; i < 4; i++) {
        if (goodParams[i] == p) return i;
    }
    return -1;
}

class H {
public :
    H(vector <string> c) :
        firstHFInd(-1),

        theSet(c)
    {
        for (int i = 0; i < MAGIC_CONST; i++) {
            secondHFIng[i] = -1;
        }
        buildFunctions();
    }
    ~H();
private:
    void buildFunctions() {


        bool good(false);

        Params optParams;

        //  надо выбрать оптимальную по памяти функцию



        while (!good) {

            Params t = getRandomParam();
            optParams = t;

            int cnt[t.m];
            for (int i = 0; i < t.m; i++) cnt[i] = 0;

            for (unsigned int i = 0; i < theSet.size(); i++) {
                int hf(0);
                for (unsigned int j = 0; j  < theSet[i].size(); j++) {
                    hf += ((t.a * ((int)theSet[i][j]) + t.p) % t.p) % t.m;
                    cnt[hf]++;
                }
            }

            unsigned int overhead(0);

            for (int i = 0; i < t.m; i++) {

                if (cnt[i] >= 1) {
                    overhead += cnt[i] * cnt[i];
                }

            }

            if (overhead <= 4 * theSet.size()) {
                good = true;
            }

        }

        firstHFInd = getHIndex(optParams);
        vector <string> cnt[optParams.m];

        for (unsigned int i = 0; i < theSet.size(); i++) {
            int hf(0);
            for (unsigned int j = 0; j  < theSet[i].size(); j++) {
                hf += ((optParams.a * ((int)theSet[i][j]) + optParams.p) % optParams.p) % optParams.m;
                cnt[hf].push_back(theSet[i]);
            }
        }

        for (int i = 0; i < optParams.m; i++) {
            if (cnt[i].size() >= 1) {
                bool good = false;
                while (!good) {
                    Params tt = getRandomParam();
                    int temp[cnt[i].size()];
                    for (size_t j = 0; j < cnt[i].size(); j++) temp[j] = 0;
                    for (size_t j = 0; j < cnt[i].size(); j++) {
                        int hf(0);
                        vector <string> *f = cnt;

                        //test
                        assert(typeid(string) == typeid(*f));

                        string tempString = f -> at(j);
                        for (size_t k = 0; k < tempString.size(); k++) {
                            hf += ((tt.a * ((int)tempString[k]) + tt.p) % tt.p) % tt.m;
                        }
                        temp[hf]++;
                    }

                    int oks(0);
                    for (int j = 0; j < tt.m; j++) {
                        if (temp[tt.m] < 1) oks++;
                    }

                    if (oks == (int)cnt[i].size()) {good = true; secondHFIng[i] = getHIndex(tt);}
                }
            }
        }

    }
    int firstHFInd;
    int secondHFIng[MAGIC_CONST];
    vector <string> theSet;
};

int main() {

    return 0;
}
