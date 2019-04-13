#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class lru{
    private:
    int capacity;
    int countFaults;
    int now;
    vector<int> pages;
    vector<int> timeCount;
    int sz;
    void checkOverFlow(){
        if(now + 5 ==  (1<<30)){
            int timeMin = *min_element(timeCount.begin(),timeCount.end());
            for(int i = 0; i<sz; i++){
                timeCount[i]-=timeMin;
            }
            now-=timeMin;
        }
    }
    public:
    lru(int cap){
        capacity = cap;
        countFaults = 0;
        sz = 0;
        now = 0;
        pages.resize(capacity);
        timeCount.resize(capacity);
    }
    void access(int page){
        now++;
        int minCountIndex = 0;
        for(int i=0;i<sz;i++){
            if(pages[i] == page){
                timeCount[i] = now;
                this->checkOverFlow();
                return;
            }
            else if(timeCount[i]<timeCount[minCountIndex]){
                minCountIndex = i;
            }
        }
        countFaults++;
        if(sz<capacity){
            pages[sz] = page;
            timeCount[sz] = now;
            sz++;
        }
        else{
            pages[minCountIndex] = page;
            timeCount[minCountIndex] = now;
        }
        this->checkOverFlow();
    }
    int getCountOfFaults(){
        return countFaults;
    }
    //useful to debug
    /*
    void printCounter(){
        for(int i = 0; i<sz; i++){
            cout<<pages[i] << "   " << timeCount[i] << endl;;
        }    
    }
    */
    
};
int main(){
    lru l(4);
    int v[10]={3,1,4,2,5,2,1,2,3,4};
    for(int i = 0;i<10;i++){
        l.access(v[i]);
        //l.printCounter();
        cout<<l.getCountOfFaults()<<endl;
    }
    

    return 0;
}