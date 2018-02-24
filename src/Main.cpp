#include <iostream>
#include <fstream>
using namespace std;
class ImageProcessing{
public:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMinVal;
	int newMaxVal;
	int ** zeroframedary;
	int neighborary[5];
	int Rowcounter=1;
	int Colcounter=1;
	int neighborAry_counter=0;
	ImageProcessing(int numrows,int numcols,int minval,int maxval){
		this->numRows=numrows;
		this->numCols=numcols;
		this->minVal=minval;
		this->maxVal=maxval;
		newMinVal=0;
		newMaxVal=0;
		//create 2d dynamic array
		zeroframedary = new int*[numRows+2];
		for(int l = 0; l < numRows+2; l++)
		{
			zeroframedary[l] = new int[numCols+2];
		}
		// initlize to zero
		for(int m = 0; m < numRows+2; m++)
		{
			for(int n = 0; n < numCols+2; n++)
			{
				zeroframedary[m][n] = 0;
			}
		}
	}
	//destructors
	~ImageProcessing(){
		for(int i = 0; i < numRows+2; ++i) {
			delete[] zeroframedary[i];
		}
		delete[] zeroframedary;
	}
	void load_image(int input_value){
		if(Colcounter<numCols){
			zeroframedary[Rowcounter][Colcounter++]=input_value;
		}
		else{
			zeroframedary[Rowcounter++][Colcounter]=input_value;
			Colcounter=1;
		}
	}
	void firstPassDistance(){
		for(int i=1;i<numRows+1;i++){
			for(int j=1;j<numCols+1;j++){
				if(zeroframedary[i][j]>0){
					load_Into_neighbor_pass1(i,j);
					zeroframedary[i][j]=findmin()+1;
				}
			}
		}
	}
	void secondPassDistance(){
		for(int i=numRows+1;i>1;i--){
			for(int j=numCols+1;j>1;j--){
				if(zeroframedary[i][j]>0){
					load_Into_neighbor_pass2(i,j);
					int min=999;
					for(int index=0;index<5;index++){
						if((min>neighborary[index])){
							min=neighborary[index];
						}
					}
					zeroframedary[i][j]=zeroframedary[i][j] < min ? zeroframedary[i][j]+1:min+1;
				}
			}
		}
	}
	void load_Into_neighbor_pass1(int row ,int col){
		neighborary[4]=zeroframedary[row][col];
		row=row-1;
		col=col-1;
		for(int j=0;j<3;j++){
			neighborary[neighborAry_counter++]=zeroframedary[row][col++];
		}
		neighborary[neighborAry_counter++]=zeroframedary[row+1][col-3];
		neighborAry_counter=0;
	}
	void load_Into_neighbor_pass2(int row,int col){
		neighborary[4]=zeroframedary[row][col];
		//i =row, j =col
		neighborary[neighborAry_counter++]=zeroframedary[row++][col+1];
		col=col-1;
		for(int j=0;j<3;j++){
			neighborary[neighborAry_counter++]=zeroframedary[row][col++];
		}
		neighborAry_counter=0;
	}
	int findmin(){
		int min=999;
		for(int index=0;index<4;index++){
			if((min>neighborary[index])){
				min=neighborary[index];
			}
		}
		return min;
	}
};
int main(int argc, char **argv) {
	ifstream inFile;
	ofstream outFile2;
	ofstream outFile1;

	inFile.open(argv[1]);
	outFile2.open(argv[3]);
	outFile1.open(argv[2]);

	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	inFile >> numRows >> numCols >> minVal >> maxVal;
	ImageProcessing * image=new ImageProcessing(numRows,numCols,minVal,maxVal);
	outFile2<< image->numRows<<" "<< image->numCols<<" "<<image->minVal<<" "<<image->maxVal<<" "<<endl;;

	while(!inFile.eof())
	{
		int mychar;
		inFile>>mychar;
		image->load_image(mychar);
	}
	image->firstPassDistance();
	outFile2<<" This is the result of pass-1"<<endl;

	for(int i=0;i<numRows+2;i++){
		for(int j=0;j<numCols+2;j++){
			if(image->zeroframedary[i][j]>0){
				outFile2<<image->zeroframedary[i][j]<< " ";
			}
			else{
				outFile2<<"  ";
			}
		}
		outFile2<<endl;
	}
	image->secondPassDistance();
	outFile2<<" This is the result of pass-2"<<endl;
	for(int i=0;i<numRows+2;i++){
		for(int j=0;j<numCols+2;j++){
			if(image->zeroframedary[i][j]>0){
				outFile2<<image->zeroframedary[i][j]<< " ";
			}
			else{
				outFile2<<"  ";
			}

		}
		outFile2<<endl;
	}
	minVal=999;
	maxVal=0;
	for(int i=1;i<numRows+1;i++){
		for(int j=1;j<numCols+1;j++)
		{
			if(image->zeroframedary[i][j]>maxVal){
				maxVal=image->zeroframedary[i][j];
			}
			else if(image->zeroframedary[i][j]<minVal){
				minVal=image->zeroframedary[i][j];
			}
		}
	}
outFile1<< image->numRows<<" "<< image->numCols<<" "<<minVal<<" "<<maxVal<<" "<<endl;
	for(int i=1;i<numRows+1;i++){
		for(int j=1;j<numCols+1;j++){
			if(image->zeroframedary[i][j]>0){
				outFile1<<image->zeroframedary[i][j]<< " ";
			}
			else{
				outFile1<<"  ";
			}
		}
		outFile1<<endl;
	}
	outFile2.close();
	outFile1.close();
	return 0;
}
