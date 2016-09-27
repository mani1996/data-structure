#include <vector>
#include <map>
using namespace std;

class Heap{
	vector<int> ele;
	map<int,int> pos;
	static int infinity;

	bool compare(int v1,int v2){
		// This is for maxHeap
		return v1 > v2;
		// For minHeap, use "return v1 < v2;"
	}

	void swap(int index1,int index2){
		ele[index1] = ele[index1] + ele[index2] - (ele[index2] = ele[index1]);
		pos[ele[index1]] = index1;
		pos[ele[index2]] = index2;
	}

	void siftUp(int index){
		if(index>0 && compare(ele[index],ele[index/2])){
			swap(index,index/2);
			siftUp(index/2);
		}
	}

	void siftDown(int index){
		int v1 = ((2*index+1 < ele.size())?ele[2*index+1]:infinity);
		int v2 = ((2*index+2 < ele.size())?ele[2*index+2]:infinity);
		int v3 = (compare(v1,v2)?v1:v2);

		if(v3 < ele[index]){
			if(v1==v3){
				swap(index,2*index+1);
				index = 2*index+1;
			}
			else{
				swap(index,2*index+2);
				index = 2*index+2;
			}
			siftDown(index);
		}
	}

	public:
	Heap(){}

	void insert(int v){
		ele.push_back(v);
		pos[v] = ele.size()-1;
		siftUp(ele.size()-1);
	}

	void del(int v){
		if(pos.find(v) != pos.end()){
			int index = pos[v];
			swap(index,ele.size()-1);
			pos.erase(ele.back());
			ele.pop_back();
			siftDown(index);
		}
	}

	int top() const{ return ele[0];}
	int size() const{ return ele.size();}
};

int Heap::infinity = 1000000001;

int main(){
	
}