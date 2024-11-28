// #include<bits/stdc++.h>
#include<iostream>

#include<thread>
using namespace std; 

void func_1()
{
    // std::cout<< "Beauty is only Skin-Deep" << endl;
    std::cout<< "Thread Join execution" << endl;
}
class Fctor{
    public:
    void operator()(string& msg){
        // for(int i=0;i>-10;i--)
        // {
        //     cout<<"from t1 "<<i <<endl;
        // }
        cout<<"t1 says: "<<msg<<endl;
        msg = "Msg changed";
    }
};

int main()
{
    // func_1();
    // Fctor fct;
    // std::thread t1(fct); //t1 starts running 
    cout<<"Number of Threads which can be run concurrently = "<<std::thread::hardware_concurrency()<<endl;
    cout<<"Parent (main) Thread ID:"<<std::this_thread::get_id()<<endl;
    string s = "Message String"; 
    // std::thread t1((Fctor()),s); // pass by val
    std::thread t1((Fctor()),std::ref(s));
    cout<<"Child Thread T1 ID:"<<t1.get_id()<<endl;

    std::thread t2 = std::move(t1);
    // t1.join();
    t2.join();

    cout<<"from main: "<<s<<endl;
    
    
    // try{
       
    //     cout<<"from main: "<<s<<endl;
    // }
    // catch(...){
    //     t1.join();
    //     throw;
    // }
    // t1.join();
    return 0;
}