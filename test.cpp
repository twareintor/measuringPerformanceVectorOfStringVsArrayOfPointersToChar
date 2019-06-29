//Permanent link: http://rextester.com/PJPV98211
//g++  5.4.0
//clang 3.8.0
//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64
//Measuring performance vector of strings vs. array of pointers to char const
//code by Twareintor (2018) - Claudiu Ciutacu

#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#define NITEMS 0x1000

#define NTRIALS 0x10

void (*pfn[2])();

void test01()
{
    std::vector<std::string> v(NITEMS);
    for(int i=0; i<NITEMS; i++)
        v.push_back(std::move(std::string("the quick brown fox jumps over the lazy dog")));
}

void test02()
{
    char** const sz = new char*[NITEMS];
    for(int i=0; i<NITEMS; i++)
        sz[i] = "the quick brown fox jumps over the lazy dog";
    delete[] sz;
}

int main()
{
    std::cout << "Hello, world!\n";
    // 
    unsigned long resCnt[2][NTRIALS];
    pfn[0] = &test01;
    pfn[1] = &test02;
    auto t0 = std::chrono::high_resolution_clock::now();
    auto t1 = t0;     
    for(int i=0; i<NTRIALS; i++)
    {
        // calling the two functions alternatively every loop
        t0 = std::chrono::high_resolution_clock::now();
        pfn[0==i%2](); 
        t1 = std::chrono::high_resolution_clock::now();     
        resCnt[0==i%2][i] = (t1-t0).count();
        t0 = std::chrono::high_resolution_clock::now();
        pfn[0!=i%2]();
        t1 = std::chrono::high_resolution_clock::now();     
        resCnt[0!=i%2][i] = (t1-t0).count();
    }
    for(int j=0; j<2; j++)
    {
        for(int i=0; i<NTRIALS; i++)
            std::cout<<resCnt[j][i]<<"\t";
        std::cout<<std::endl;
    }
    //
    std::cout<<"Game Over!\n";
}



/************

On Wednesday, August 29, 2018, 2:00:53 PM GMT+2, Ciutacu wrote:


//Permanent link: http://rextester.com/JAVF34423
//g++  5.4.0
//clang 3.8.0
//Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x64
//Measuring performance vector of strings vs. array of pointers to char
//code by Twareintor (2018) - Claudiu Ciutacu

#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#define NITEMS 0x1000

#define NTRIALS 0x10

void (*pfn[2])();

void test01()
{
    std::vector<std::string> v(NITEMS);
    for(int i=0; i<NITEMS; i++)
        v.push_back(std::move(std::string("the quick brown fox jumps over the lazy dog")));
}

void test02()
{
    char** sz = new char*[NITEMS];
    for(int i=0; i<NITEMS; i++)
        sz[i] = "the quick brown fox jumps over the lazy dog";
    delete[] sz;
}

int main()
{
    std::cout << "Hello, world!\n";
    // 
    unsigned long resCnt[2][NTRIALS];
    pfn[0] = &test01;
    pfn[1] = &test02;
    auto t0 = std::chrono::high_resolution_clock::now();
    auto t1 = t0;     
    for(int i=0; i<NTRIALS; i++)
    {
        // calling the two functions alternatively every loop
        t0 = std::chrono::high_resolution_clock::now();
        pfn[0==i%2](); 
        t1 = std::chrono::high_resolution_clock::now();     
        resCnt[0==i%2][i] = (t1-t0).count();
        t0 = std::chrono::high_resolution_clock::now();
        pfn[0!=i%2]();
        t1 = std::chrono::high_resolution_clock::now();     
        resCnt[0!=i%2][i] = (t1-t0).count();
    }
    for(int j=0; j<2; j++)
    {
        for(int i=0; i<NTRIALS; i++)
            std::cout<<resCnt[j][i]<<"\t";
        std::cout<<std::endl;
    }
    //
    std::cout<<"Game Over!\n";
}

*****************/

