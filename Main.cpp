
#include <iostream>;
#include <fstream>;


using namespace std;


//HeapSort class implementation

class HeapSort {
	
public:
	int countNum=0;
	int countPosition=0;
	int data=0;
	int arraySize=0;
	int* HeapArray;
	int dataIndex = 0;
	int parentIndex = 0;
	int lastItem = 0;


public:
	HeapSort() {
		arraySize = 0;
		
	}

	HeapSort(int count) {
		countNum = count;
		arraySize = count+1; 
		HeapArray = new int[arraySize]; //dymanically allocate 1-D array
		HeapArray[0] = 0;  //initialize heapAry[0] to 0;
	}


	~HeapSort() {
		delete[] HeapArray;
	}



	void buildHeap(int data, ofstream &outFile,ifstream &inFile) {
		
		while (inFile >> data) {
			
			//if not full, insert
			if (isHeapFull() == false) {

				insertOneDataItem(data);
			}//if

			//printout for debugging
			printHeap(outFile);
		}

		inFile.close();


	}

	void deleteHeap(ofstream &outFile,ofstream &outFile2) {

		//if not empty, delete the root
		while (isHeapEmpty() == false) {

			//remove root
			int root = DeleteRoot();
			outFile2 << "the deleted root is :" << root << endl;
			

			//remove the last item from the last level
			lastItem = HeapArray[countPosition];//store the last item
			
			countPosition--;//reduce the lastItem's index 

			
			//change the arraysize
			arraySize--;
			HeapArray[0] = arraySize;

			//put the last item in the root position
			HeapArray[1] = lastItem;
			//cout << "Put last item in the first position" << HeapArray[1] << endl;

         
			//bubbble down 
			bubbleDown(lastItem);

			//cout << "out of bubble down loop" << endl;
			printHeap(outFile);

		}
		
	
		

	
	
	}

	void insertOneDataItem(int data) {
		
		   //size++
			countPosition=countPosition+1;

			//put the data in the last level with the rule
			HeapArray[countPosition] = data;

			//increase the size recorder 
			HeapArray[0] = countPosition;

			//bubble up
			bubbleUp(data,countPosition);
		

	}

	int DeleteRoot() {
		int temp = HeapArray[1];
		HeapArray[1] = NULL;
		return temp;
	}

	void bubbleUp(int data,int countPosition) {
		//caculate parent&child node index
		dataIndex =countPosition;
		parentIndex = countPosition / 2;
		

		//while data<its parent&not root, keep swaping 

		while (data < HeapArray[parentIndex] && dataIndex!= 0) {
			

			int temp = HeapArray[parentIndex];
			HeapArray[parentIndex] = data;
			HeapArray[dataIndex] = temp;

			//caculate new parent and child index after swap
			dataIndex = parentIndex;
			parentIndex = dataIndex / 2;
			
		
		}



	}

	void bubbleDown(int lastItem) {
		int data = lastItem;
		int Increase_Position =1;
		int left_child_Index = Increase_Position * 2;
		int right_child_Index = Increase_Position * 2 + 1;
		int smallest_child_index;

        //find the smaller kid
		if (HeapArray[left_child_Index] > HeapArray[right_child_Index]) {
			smallest_child_index = right_child_Index;

		}
		else {
		
			smallest_child_index = left_child_Index;
		}
		//cout << "This is before bubbleDown While loop";

		//smallest_child_index*2<=countPosition)
		while (HeapArray[smallest_child_index]< data&&smallest_child_index * 2 <= countPosition) {
			//cout << "This is inside bubbleDown While loop";
			//swap
			int temp = HeapArray[smallest_child_index];
			HeapArray[smallest_child_index] = data;
			HeapArray[Increase_Position] = temp;

			//data at new position
			Increase_Position = smallest_child_index;

			left_child_Index = Increase_Position * 2;
			right_child_Index = Increase_Position * 2 + 1;

			//find the smaller kid
			if (HeapArray[left_child_Index] > HeapArray[right_child_Index]) {
				smallest_child_index = right_child_Index;

			}
			else {

				smallest_child_index = left_child_Index;
			}




		}
	
	
	}

	bool isHeapEmpty() {

		if (HeapArray[0] <= 1) {
			return true;
		}
		
		else { return false; }

	}

	bool isHeapFull() {
		//if the first cell's number equal to count num
		if (HeapArray[0] == countNum) {
			return true;
		}

		else { return false; }
	}

	void printHeap(ofstream &outFile) {
		//print to outfile 1 from [0]-[9]

		//find out the minumn size between 10 and arraysize
		int minium;
		if ((countPosition) - 9 < 0) { minium = countPosition; }
		else { minium = 9; }

		for (int i = 0; i <=minium; i++) {
			
			outFile <<HeapArray[i]<<endl;
			
		}

		
		outFile << "------------------" << endl;
		
	}


	
};

//main class 

int main(int argc, char *argv[]) {

	int data;
	int count=0;
	ifstream inFile;
	ofstream outFile;
	ofstream outFile2;

	//open file 
	inFile.open(argv[1]);
	outFile.open(argv[2]);
	outFile2.open(argv[3]);

	//read data from inFile
	
	while (inFile >> data) {
		//cout << "Main" << data;
		count++;
	}//while

	 //close file
	inFile.close();

	//create an instance of HeapSort Class & Dynamically allocate array
	HeapSort heapsort(count);

	//open file
	inFile.open(argv[1]);

    heapsort.buildHeap(data,outFile,inFile);

	
	heapsort.deleteHeap(outFile,outFile2);
		

   //close file when done
	inFile.close();

	//close outFile 1&2
	outFile.close();
	outFile2.close();


	//cin.get();
	return 0;

}