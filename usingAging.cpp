#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class lru{
    private:
	    int capacity;
	    int count_faults;
	    vector<int> pages;
	    vector<unsigned int> page_counter;
	    vector<bool> page_accessed;
    public:
	    lru(int cap){
		capacity = cap;
		count_faults = 0;
		pages.resize(capacity, 0);
		page_counter.resize(capacity, 0);
		page_accessed.resize(capacity, false);
	    }


	    void update_page_counter(){
	    	for(int i=0; i<capacity; i++){
		    if(page_counter[i] == (((unsigned int)1)<<31)){
		    	page_counter[i] = 0;
		    }
		    page_counter[i] = (page_counter[i]>>1);
		    page_counter[i] += (((unsigned int)page_accessed[i])<<30);
		}
	    }

	    void reset_page_counter(){
	    	for(int i=0; i<capacity; i++){
		    page_accessed[i] = 0;
		}
	    }

	    void access(vector<int> access_pages){
		reset_page_counter();
		for(int i=0; i<access_pages.size(); i++){
	            bool found = false;
		    for(int j=0; j<capacity; j++){
		    	if(access_pages[i] == pages[j]){
			    found = true;
			    page_accessed[j] = true;
			    break;
			}
		    }
		    if(found == false){
			count_faults++;
		    	int min_ele_index = min_element(page_counter.begin(), page_counter.end()) - page_counter.begin();
			page_counter[min_ele_index] = (((unsigned int)1)<<31);
			pages[min_ele_index] = access_pages[i];
			page_accessed[min_ele_index] = true;
		    }
		}
		update_page_counter();
	    }

	    int getCountOfFaults(){
		return count_faults;
	    }
};

int main(){
    lru l(4);
    int v[10]={3,1,4,2,5,2,1,2,3,4};
    vector<int> page_access_slot;
    for(int i = 0;i<10;i++){
	page_access_slot.push_back(v[i]); //vector used to generalize the concept
	l.access(page_access_slot);
	page_access_slot.clear();
        cout<<l.getCountOfFaults()<<endl;
    }
    

    return 0;
}
