#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Box {
	int sum;
	int w;
	int h;
	// z = 1
};

int main(){
	int S, N;
	
	ifstream file("valija.in");
	file >> S >> N;
	
	vector<Box> boxes;
	boxes.resize(N);
	for(int i = 0; i < N; i++) {
		file >> boxes[i].w >> boxes[i].h;
		boxes[i].sum = boxes[i].w + boxes[i].h;
	}
	
	sort(boxes.begin(), boxes.end(), [](const Box& box1, const Box& box2) {
		return box1.sum < box2.sum;
	});
	
	int maxW = 0, maxH = 0;
	int count = 0;
	for(Box& box : boxes) {
		int newW = max(maxW, box.w);
		int newH = max(maxH, box.h);

		int newWRot = max(maxW, box.h);
		int newHRot = max(maxH, box.w);
		
		if(newW + newH > newWRot + newHRot){
			newW = newWRot;
			newH = newHRot;
		}

		int newSum = newW + newH + count + 1;
		
		if(newSum <= S) {
			count++;
			maxW = newW;
			maxH = newH;
		} else
			break;
		
		//cout << maxW << " "<< maxH << " -- " << newSum << endl;
	}
	
	cout << count << endl;
	
	ofstream ofile("valija.out");
	ofile << count;
	ofile.close();
	
	/*
	// Generate stress test case
	ofile << 1500 << " " << 200000 << endl;
	for(int i = 0; i < 200000; i++){
		int r1 = 1 + (std::rand() % 1000);
		int r2 = 1 + (std::rand() % 1000);
		ofile << r1 << " " << r2 << endl;
	}
	*/
	
	return 0;
}
