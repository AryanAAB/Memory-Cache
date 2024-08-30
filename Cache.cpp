#include <bits/stdc++.h>
#include<vector>
using namespace std;

class Line
{
    private:
        int tag;
        int validBit;
        
    public:
        Line(int tag)
        {
            this->tag = tag;
            this->validBit = 0;       //initially validBit is 0 since no data present in the cache
        }

        int getTag() const
        {
            return this->tag;
        }

        int getValidBit() const
        {
            return this->validBit;
        }

        int setValidBit()
        {
            this->validBit = 1;
        }

        int resetValidBit()
        {
            this->validBit = 0;
        }
};

class Set
{
    
};

class Way
{
    private:
        vector<Line> lines;
        int numLines;
        int indexBits;
    
    public:
        Way(int numLines)
        {
            this->numLines=numLines;

            this->lines = vector<Line>(this->numLines);     //creating a vector of lines of having numLines as the number of lines.

            this->indexBits = (int)log2(this->numLines);         //this gives us the number of bits for index.
        }

        bool lineFree(int address)
        {
            int index = address & (1 << (this->indexBits + 1) - 1);
            int tag = address >> (this->indexBits);

            !this->lines[index].getValidBit();
        }
};  

class Cache
{
    private:
        int blockSize;
        int cacheSize;
        int ways;
        int sets;

    public:
        const static int KILO_BYTE = 1024;

    public:
        
        Cache(int blockSize, int cacheSize, int ways)
        {
            if(blockSize <= 0 || cacheSize <= 0 || ways <= 0 
                || (this->blockSize & (this->blockSize-1))!=0 || (this->cacheSize & (this->cacheSize-1))!=0 || (this->ways & (this->ways-1)!=0))
            {
                throw invalid_argument("Received Invalid Input.");
            }
            
            this->blockSize=blockSize;
            this->cacheSize=cacheSize;
            this->ways=ways;

            this->sets = this->cacheSize * KILO_BYTE / ( this->ways * this->blockSize );
            
            if(this->sets & (this->sets - 1) != 0)
            {
                throw invalid_argument("Received Invalid Input.");
            }
        }

        int getBlockSize() const
        {
            return this->blockSize;
        }

        int getCacheSize() const
        {
            return this->cacheSize;
        }

        int getWays() const
        {
            return this->ways;
        }

        int getSets() const
        {
            return this->sets;
        }
};

            