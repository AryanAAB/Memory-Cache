#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

// Function Prototypes
pair<ll, ll> getMissHit(ll, ll, ll, const string &);    // Returns the number of hits and misses
double getHitRate(pair<ll, ll> &);          // Returns the hit rate
void print(ll, ll, ll, pair<ll, ll> &);     // Prints cache size, block size, num ways, hit rate and miss rate
void firstQ(ll, ll, ll);                    // First Question
void secondQ(bool);                         // Second Question
void thirdQ(bool);                          // Third Question
void fourthQ(bool);                         // Fourth Question


// CLass representing Cache Line
class Line
{
    private:
        ll tag;         // Tag of the line
        ll validBit;    // Valid bit (0 = invalid, 1 = valid)

    public:
        Line()
        {
            this->validBit = 0;       //initially validBit is 0 since no data present in the line
        }

        ll getTag() const
        {
            return this->tag;       // Returns the tag
        }

        void setTag(ll tag)
        {
            this->tag = tag;        // Sets the tag
            this->validBit = 1;     // Sets the valid bit to 1
        }

        ll getValidBit() const
        {
            return this->validBit;      // Returns the valid bit
        }

        void setValidBit()
        {
            this->validBit = 1;     // Sets the valid bit to 1
        }

        void resetValidBit()
        {
            this->validBit = 0;     // Resets the valid bit to 0
        }
}; 

// Class representing Cache
class Cache
{
    private:
        ll blockSize;               // Block size of the Cache
        ll cacheSize;               // Cache size of the Cache
        ll numWays;                 // Number of ways of the Cache
        ll sets;                    // Number of sets in the Cache
        vector<vector<Line>> LRU;   // Cache memory with LRU replacement policy
        ll numMisses, numHits;      // Number of misses and hits

    public:
        const static ll KILO_BYTE = 1024;   // 1 KB = 1024 Bytes

    public:
        
        Cache(ll blockSize, ll cacheSize, ll numWays)
        {   
            // Checking for invalid input values and throwing exception
            if(blockSize <= 0 || cacheSize <= 0 || numWays <= 0 
                || (blockSize & (blockSize-1))!=0 || (cacheSize & (cacheSize-1))!=0 || (numWays & (numWays-1)!=0))
            {
                throw invalid_argument("Received Invalid Input.");
            }
            
            // Setting the values of block size, cache size and number of ways
            this->blockSize=blockSize;
            this->cacheSize=cacheSize;
            this->numWays=numWays;

            // Calculating the number of sets
            this->sets = this->cacheSize * KILO_BYTE / ( this->numWays * this->blockSize );
            
            if(this->sets & (this->sets - 1) != 0)
            {
                throw invalid_argument("Received Invalid Input.");
            }

            // Initializing the Cache memory with LRU replacement policy
            for(ll i = 0; i < sets; i++)
            {
                LRU.push_back(vector<Line>());

                for(ll j = 0; j < numWays; j++)
                {
                    LRU[i].push_back(Line());
                }
            }
        
            this->numHits = this->numMisses = 0;    // Initially number of hits and misses are 0
        }

        // Getters for Cache parameters
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
        
        // Function to add data to the Cache
        void addData(ll address)
        {
            ll byteOffset = address & (blockSize - 1);      // Byte offset

            ll rest = address >> (ll)(log2(blockSize));     // Rest of the address

            ll index = rest & (sets - 1);                   // Index of the set

            ll tag = rest >> (ll)(log2(sets));              // Tag of the address

            // Checking if the data is already present in the Cache
            for(ll i = 0; i < LRU[index].size(); i++)
            {
                if(LRU[index][i].getValidBit() && LRU[index][i].getTag() == tag)
                {   
                    // If the data is present in the Cache, then move the data to the front
                    for (ll j = i; j>0; j--)
                    {
                        swap(LRU[index][j], LRU[index][j-1]);
                    }
                    
                    numHits++;      // Incrementing the number of hits
                    return;
                }
            }

            // If the data is not present in the Cache, then add the data and replace the least recently used data
            LRU[index][numWays - 1].setTag(tag);
            for (ll j = numWays-1; j>0; j--)
            {
                swap(LRU[index][j], LRU[index][j-1]);
            }

            numMisses++;        // Incrementing the number of misses
        }
};

// Vector to store the file names
const vector<string> fileNames = {"gcc.trace", "gzip.trace", "mcf.trace", "swim.trace", "twolf.trace"};

// Function to get the number of hits and misses
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

    // Add the data to the Cache
    for(string s : address)
    {
        c.addData(stoll(s.substr(2), nullptr, 16));
    }

    return make_pair(c.getNumHits(), c.getNumMisses());     // Return the number of hits and misses
}

// Function to get the hit rate
double getHitRate(pair<ll, ll> & p)
{
    return 1.0 * p.first / (p.first + p.second);    // Return the hit rate
}

// Function to print cache size, block size, num ways, hit rate and miss rate
void print(ll cacheSize, ll blockSize, ll ways, pair<ll, ll> & p)
{
    cout << "\tCache Size: " << cacheSize << "KB, Block Size: " << blockSize << "B, Num Ways: " << ways << endl;
    cout << "\t\tHit Rate : " << getHitRate(p) << endl;
    cout << "\t\tMiss Rate: " << (1-getHitRate(p)) << endl;
    cout << endl;
}

// Function to answer the first question
void firstQ(ll blockSize, ll cacheSize, ll ways)
{
    for(int i = 0; i < fileNames.size(); i++)
    {
        auto p = getMissHit(blockSize, cacheSize, ways, fileNames[i]);

        cout << fileNames[i] << endl;
        print(cacheSize, blockSize, ways, p);
    }
}

// Function to answer the second question
void secondQ(bool toPrint)
{
    for(int i = 0; i < fileNames.size(); i++)
    {
        cout << fileNames[i] << endl;
        for(ll j = 128; j <= 4096; j *= 2)
        {
            auto p = getMissHit(4, j, 4, fileNames[i]);

            if(toPrint)
                print(4, j, 4, p);
            else
                cout << getHitRate(p) << "," << (1-getHitRate(p)) << "," << j << "," << "4,4" << endl;
        }
    }

}

// Function to answer the third question
void thirdQ(bool toPrint)
{
    for(int i = 0; i < fileNames.size(); i++)
    {
        cout << fileNames[i] << endl;
        for(ll j = 1; j <= 128; j *= 2)
        {
            auto p = getMissHit(j, 1024, 4, fileNames[i]);

            if(toPrint)
                print(j, 1024, 4, p);
            else
                cout << getHitRate(p) << "," << (1-getHitRate(p)) << "," << 1024 << "," << j << ",4" << endl;
        }
    }
}

// Function to answer the fourth question
void fourthQ(bool toPrint)
{
    for(int i = 0; i < fileNames.size(); i++)
    {
        cout << fileNames[i] << endl;
        for(ll j = 1; j <= 64; j *= 2)
        {
            auto p = getMissHit(4, 1024, j, fileNames[i]);
            
            if(toPrint)
                print(4, 1024, j, p);
            else
                cout << getHitRate(p) << "," << (1-getHitRate(p)) << "," << 1024 << ",4," << j << endl;
        }
    }
}

int main(int argc, char *argv[])
{
    cout << fixed;              
    cout << setprecision(20);   // Set precision to 20 decimal places

    // If no command line arguments are provided, then answer all the questions
    if(argc == 1)
    {
        cout << "Question 1" << endl << endl;
        firstQ(4, 1024, 4);
        cout << endl << "Question 2" << endl << endl;
        secondQ(true);
        cout << endl << "Question 3" << endl << endl;
        thirdQ(true);
        cout << endl << "Question 4" << endl << endl;
        fourthQ(true);
        cout << endl;
    }
    // If first argument is 1, then answer the first question
    else if(strcmp(argv[1], "1") == 0)
    {
        firstQ(4, 1024, 4);
    }
    // If first argument is 2, then answer the second question
    else if(strcmp(argv[1], "2") == 0)
    {
        secondQ(false);
    }
    // If first argument is 3, then answer the third question
    else if(strcmp(argv[1], "3") == 0)
    {
        thirdQ(false);
    }
    // If first argument is 4, then answer the fourth question
    else if(strcmp(argv[1], "4") == 0)
    {
        fourthQ(false);
    }
    // If wrong input is provided, then throw exception
    else
    {
        throw invalid_argument("Wrong input provided.");
    }
}