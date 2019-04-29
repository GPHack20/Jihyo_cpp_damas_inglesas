#include<iostream>
#include<vector>
#include<list>
//#include "Pruebas.h"
// A simple C++ program to find 
// maximum score that 
// maximizing player can get. 
//#include<bits/stdc++.h> 
using namespace std; 
/*
// Returns the optimal value a maximizer can obtain. 
// depth is current depth in game tree. 
// nodeIndex is index of current node in scores[]. 
// isMax is true if current move is 
// of maximizer, else false 
// scores[] stores leaves of Game tree. 
// h is maximum height of Game tree 
int minimax(int depth, int nodeIndex, bool isMax, 
			int scores[], int h) 
{ 
	// Terminating condition. i.e 
	// leaf node is reached 
	if (depth == h) 
		return scores[nodeIndex]; 

	// If current move is maximizer, 
	// find the maximum attainable 
	// value 
	if (isMax) 
	return max(minimax(depth+1, nodeIndex*2, false, scores, h), 
			minimax(depth+1, nodeIndex*2 + 1, false, scores, h)); 

	// Else (If current move is Minimizer), find the minimum 
	// attainable value 
	else
		return min(minimax(depth+1, nodeIndex*2, true, scores, h), 
			minimax(depth+1, nodeIndex*2 + 1, true, scores, h)); 
} 

// A utility function to find Log n in base 2 
int log2(int n) 
{ 
return (n==1)? 0 : 1 + log2(n/2); 
} 
*/
class Point{
public:
    int x;
    int y;
    Point(int xx,int yy){
      x=xx;
      y=yy;
    }
};


// Driver code 
int main() 
{ 
	// The number of elements in scores must be 
	// a power of 2. 
	/*
	int scores[] = {3, 5, 2, 9, 12, 5, 23, 23}; 
	int n = sizeof(scores)/sizeof(scores[0]); 

	int h = log2(n); 
  cout<<"H: "<<h<<endl;
	int res = minimax(0, 0, true, scores, h); 
	cout << "The optimal value is : " << res << endl; */
	
	enum Type {EMPTY, WHITE, BLACK, WHITE_KING, BLACK_KING};
	vector<Type>cell(8);
    vector<vector<Type>>board(8,cell);
	for(int c=0;c<8;c++){
		for(int i=0;i<7;i++){
			board[c][i]=WHITE;
			cout<<(Type)board[c][i]<<" ";
		}
		cout<<"\n";
	}
	Type pi=(Type)1;
	cout<<"****"<<WHITE<<"****";
	if(!board[7][7]){
		cout<<"vacio"<<endl;
	}
	for(int c=0;c<8;c++){
		for(int i=0;i<8;i++){

		}
	}
	cout<<"Prueba"<<endl;
	return 0; 
} 
