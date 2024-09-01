#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

class Line
{
    private:
        ll tag;
        ll validBit;

    public:
        Line()
        {
            this->validBit = 0;       //initially validBit is 0 since no data present in the cache
        }

        ll getTag() const
        {
            return this->tag;
        }

        void setTag(ll tag)
        {
            this->tag = tag;
            this->validBit = 1;
        }

        ll getValidBit() const
        {
            return this->validBit;
        }

        void setValidBit()
        {
            this->validBit = 1;
        }

        void resetValidBit()
        {
            this->validBit = 0;
        }
}; 

class Cache
{
    private:
        ll blockSize;
        ll cacheSize;
        ll numWays;
        ll sets;
        vector<vector<Line>> LRU;
        ll numMisses, numHits;

    public:
        const static ll KILO_BYTE = 1024;

    public:
        
        Cache(ll blockSize, ll cacheSize, ll numWays)
        {
            if(blockSize <= 0 || cacheSize <= 0 || numWays <= 0 
                || (blockSize & (blockSize-1))!=0 || (cacheSize & (cacheSize-1))!=0 || (numWays & (numWays-1)!=0))
            {
                throw invalid_argument("Received Invalid Input.");
            }
            
            this->blockSize=blockSize;
            this->cacheSize=cacheSize;
            this->numWays=numWays;

            this->sets = this->cacheSize * KILO_BYTE / ( this->numWays * this->blockSize );
            
            if(this->sets & (this->sets - 1) != 0)
            {
                throw invalid_argument("Received Invalid Input.");
            }

            for(ll i = 0; i < sets; i++)
            {
                LRU.push_back(vector<Line>());

                for(ll j = 0; j < numWays; j++)
                {
                    LRU[i].push_back(Line());
                }
            }
        
            this->numHits = this->numMisses = 0;
        }

        ll getBlockSize() const
        {
            return this->blockSize;
        }

        ll getCacheSize() const
        {
            return this->cacheSize;
        }

        ll getnumWays() const
        {
            return this->numWays;
        }

        ll getSets() const
        {
            return this->sets;
        }

        ll getNumHits() const
        {
            return this->numHits;
        }

        ll getNumMisses() const
        {
            return this->numMisses;
        }
        
        void addData(ll address)
        {
            ll byteOffset = address & (blockSize - 1);

            ll rest = address >> (ll)(log2(blockSize));

            ll index = rest & (sets - 1);

            ll tag = rest >> (ll)(log2(sets));

            for(ll i = 0; i < LRU[index].size(); i++)
            {
                if(LRU[index][i].getValidBit() && LRU[index][i].getTag() == tag)
                {
                    for (ll j = i; j>0; j--)
                    {
                        swap(LRU[index][j], LRU[index][j-1]);
                    }
                    
                    numHits++;
                    return;
                }
            }

            LRU[index][numWays - 1].setTag(tag);
            for (ll j = numWays-1; j>0; j--)
            {
                swap(LRU[index][j], LRU[index][j-1]);
            }

            numMisses++;
        }
};

const vector<string> fileNames = {"gcc.trace", "gzip.trace", "mcf.trace", "swim.trace", "twolf.trace"};

pair<ll, ll> getMissHit(ll blockSize, ll cacheSize, ll ways, const string & fileName)
{
    Cache c(blockSize, cacheSize, ways);

    ifstream file("traces/" + fileName);
    string line;
    vector<string> address; // Vector to store the middle strings

    while (getline(file, line)) 
    {
        istringstream iss(line);
        string first, middle, last;

        // Extract the three strings
        if (iss >> first >> middle >> last) 
        {
            address.push_back(middle); // Store the middle string in the vector
        }
    }

    for(string s : address)
    {
        c.addData(stoll(s.substr(2), nullptr, 16));
    }

    return make_pair(c.getNumHits(), c.getNumMisses());
}

double getHitRate(pair<ll, ll> & p)
{
    return 1.0 * p.first / (p.first + p.second);
}

void firstQ(ll blockSize, ll cacheSize, ll ways)
{
    for(int i = 0; i < fileNames.size(); i++)
    {
        auto p = getMissHit(blockSize, cacheSize, ways, fileNames[i]);

        cout << fileNames[i] << endl;
        cout << "\tHit Rate: "<< 1.0 * p.first / (p.first + p.second) << endl;
        cout << "\tMiss Rate: "<< 1.0 * p.second / (p.first + p.second) << endl;
        cout << endl;
    }
}

void secondQ()
{
    for(int i = 0; i < fileNames.size(); i++)
    {
        cout << fileNames[i] << endl;
        for(ll j = 128; j <= 4096; j *= 2)
        {
            auto p = getMissHit(4, j, 4, fileNames[i]);

            cout << getHitRate(p) << "," << (1-getHitRate(p)) << "," << j << "," << "4,4" << endl;
        }
    }

}

void thirdQ()
{
    for(int i = 0; i < fileNames.size(); i++)
    {
        cout << fileNames[i] << endl;
        for(ll j = 1; j <= 128; j *= 2)
        {
            auto p = getMissHit(j, 1024, 4, fileNames[i]);

            cout << getHitRate(p) << "," << (1-getHitRate(p)) << "," << 1024 << "," << j << ",4" << endl;
        }
    }
}

void fourthQ()
{
    for(int i = 0; i < fileNames.size(); i++)
    {
        cout << fileNames[i] << endl;
        for(ll j = 1; j <= 64; j *= 2)
        {
            auto p = getMissHit(4, 1024, j, fileNames[i]);

            cout << getHitRate(p) << "," << (1-getHitRate(p)) << "," << 1024 << ",4," << j << endl;
        }
    }
}

int main()
{
    cout << fixed;
    cout << setprecision(10);

    //firstQ(4, 1024, 4);
    // cout << endl;
    // secondQ();
    // cout << endl;
    // thirdQ();
    // cout << endl;
    fourthQ();
}