#include<iostream>
#include<thread>
#include<string>
#include<mutex>
using namespace std;    

std::mutex mut;

class LogFile{
    std::mutex m_mutex;
    ofstream f;
    public:
    LogFile(){
        f.open("log.txt");
    } // Need destructor to close file
    void shared_print(string id, int value){
        std::lock_guard<mutex> locker(m_mutex);
        f << "From "<<id<<": "<<value<<endl;
    }
    // Never return f to the outside world 
    // Below code not to be followed 
    ofstream& getStream() {return f;} 

    // Never pass f as an argument to user provided function
    // Below code not to be followed
    void processf(void fun(ofstream&)){ 
        fun(f);  // resource f is accessible freely without mutex permission, so avoid such stuff
    } 
}

class stack{
    int* _data;
    std::mutex _mu;
    public:
    void pop(); //pops off the item on the top of the stack
    int& top(); // returns the item on top
};

void funtion_2(stack& st){
    int v = st.top();
    st.pop();
    //process(v);
}

/* 
Avoiding Data Race:
1. Use mutex to syncrhonize data access
2. Never leak a handle of data to outside
3. Design interface appropriately
*/



void shared_print(string msg, int id){
    std::lock_guard<std::mutex> guard(mu); // RAII
    //mut.lock();
    cout<<msg<<id<<endl;
    //mut.unlock();

    // The Resource cout is not completely under the protection of mu, other threads can access it, 
    // as it is an global resource, so other thread can still use it without going through the lock
    // To protect the resource completely a mutex must be bundled together with the resource it is 
    // protecting 
}
void function_1(LogFile& log){
    for(int i=0;i>-10;i--)
    // cout<<"From t1: "<<i<<endl;
    log.shared_print(string("From t1: "),i);
}

int main(){

    LogFile log;
    std::thread t1(function_1,std::ref(log));

    for(int i=0;i<10;i++)
    // cout<< "From main: "<<i<<endl;
    log.shared_print(string("From Main: "),i);

    t1.join();
    return 0;
}