// #include<bits/stdc++.h>
#include<iostream>

#include<thread>
using namespace std; 

void func_1()
{
    // std::cout<< "Beauty is only Skin-Deep" << endl;
    std::cout<< "Thread Join execution" << endl;
}

int main()
{
    // func_1();
    std::thread t1(func_1); //t1 starts running 
    // t1.join(); // main thread waits for child thread t1 to finish
    t1.detach(); // t1 will run freely on its own -- daemon process 

    // once detached, thread cannot join again for concurrent prog

    if(t1.joinable())
    {
        t1.join();  // if above condition not checked, it will crash the program
    }


    return 0;
}