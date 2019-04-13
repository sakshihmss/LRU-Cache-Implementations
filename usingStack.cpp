#include <iostream>
#include <stack>
using namespace std;
class lru{
    private:
    int capacity;
    int countFaults;
    stack<int> pages;
    public:
    lru(int cap){
        capacity = cap;
        countFaults = 0;
    }
    void access(int page){
        int num = pages.size();
        if(num == 0 && capacity == 0){
            countFaults++;
            return;
        }
        bool found = false;
        stack<int> tmp;
        while(!pages.empty() && (!found || capacity == 0)){
            if(pages.top() == page){
                found = 1;
            }
            else{
                tmp.push(pages.top());
            }
            pages.pop();
        }
        if(capacity == 0 && !found){
            if(!tmp.empty()){
                tmp.pop();
            }
        }
        while(!tmp.empty()){
            pages.push(tmp.top());
            tmp.pop();
        }
        pages.push(page);
        if(!found) countFaults++;
        if(!found && capacity>0) capacity--;
    }
    int getCountOfFaults(){
        return countFaults;
    }
    //useful to debug
    /*
    void printStack(){
        stack<int> tmp;
        while(!pages.empty()){
            tmp.push(pages.top());
            cout<<pages.top()<<"  "; 
            pages.pop();
        }
        cout<<endl;
        while(!tmp.empty()){
            pages.push(tmp.top());
            tmp.pop();
        }
    }
    */
};
int main(){
    lru l(4);
    int v[10]={3,1,4,2,5,2,1,2,3,4};
    for(int i = 0;i<10;i++){
        l.access(v[i]);
        //l.printStack();
        cout<<l.getCountOfFaults()<<endl;
    }
    

    return 0;
}
