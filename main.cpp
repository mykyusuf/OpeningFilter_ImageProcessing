#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class Morphology{
    
    int numRowsIMG, numColsIMG, minValIMG, maxValIMG;
    int numRowsSE, numColsSE, minValSE, maxValSE;
    int rowOrigin, colOrigin;
    
    int** zeroFramedAry;
    int** morphFramedAry;
    int** structEleAry;
    int** tempFramedAry;
    
    int rowFrameSize, colFrameSize;
    
    public:
    Morphology(ifstream& infile1, ifstream& infile2){
        
        infile1>>numRowsIMG>>numColsIMG>>minValIMG>>maxValIMG;
        infile2>>numRowsSE>>numColsSE>>minValSE>>maxValSE>>rowOrigin>>colOrigin;
        
        
        rowFrameSize = numRowsSE-1;
        colFrameSize = numColsSE-1;
        
        zeroFrame(infile1);
        morphFrame();
        
        structEle(infile2);
        
        
        consolePrintIMG();
        
        consolePrintSE();
        
        
    }
    
    void consolePrintIMG(){
        cout<<"IMAGE: "<<endl;
        cout<<numRowsIMG<<" "<<numColsIMG<<" "<<minValIMG<<" "<<maxValIMG<<endl;
        
        for(int i=rowFrameSize; i<numRowsIMG+rowFrameSize; i++ ){
            for(int j=colFrameSize; j<numColsIMG+colFrameSize; j++){
                
                cout<<zeroFramedAry[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    
    void consolePrintSE(){
        cout<<"Structuring Element:"<<endl;
        cout<<numRowsSE<<" "<<numColsSE<<" "<<minValSE<<" "<<maxValSE<<endl;
        cout<<rowOrigin<<" "<<colOrigin<<endl;
        
        for(int i=0; i<numRowsSE; i++ ){
            for(int j=0; j<numColsSE; j++){
                cout<<structEleAry[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    
    void consolePrintMorph(){
        
        
        cout<<numRowsIMG<<" "<<numColsIMG<<" "<<minValIMG<<" "<<maxValIMG<<endl;
        
        for(int i=rowFrameSize; i<numRowsIMG+rowFrameSize; i++ ){
            for(int j=colFrameSize; j<numColsIMG+colFrameSize; j++){
                cout<<morphFramedAry[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
        
    }
    
    void zeroFrame(ifstream& infile1){
        
        zeroFramedAry = new int*[numRowsIMG+(2*rowFrameSize)];
        for(int r = 0; r<(numRowsIMG+(2*rowFrameSize)); r++){
            zeroFramedAry[r] = new int[numColsIMG+(2*colFrameSize)];
        }
        
        for(int k = 0; k<numRowsIMG+(2*rowFrameSize); k++){
            for(int l =0; l<rowFrameSize; l++){
                
                zeroFramedAry[k][l]=0;
                zeroFramedAry[k][numColsIMG+(colFrameSize*2)-1-l]=0;
            }
        }
        
        
        
        for(int j = 0; j<=numColsIMG+(2*colFrameSize); j++){
            for(int m = 0; m<colFrameSize; m++){
                zeroFramedAry[m][j]=0;
                zeroFramedAry[numRowsIMG+(rowFrameSize*2)-1-m][j]= 0;
            }
        }
        
        int data;
        for(int r=rowFrameSize; r<numRowsIMG+rowFrameSize; r++){
            for(int c=colFrameSize; c<numColsIMG+colFrameSize; c++){
                infile1>>data;
                zeroFramedAry[r][c]=data;
            }
        }
        
    }
    
    void morphFrame(){
        
        morphFramedAry = new int*[numRowsIMG+(2*rowFrameSize)];
        for(int r = 0; r<(numRowsIMG+(2*rowFrameSize)); r++){
            morphFramedAry[r] = new int[numColsIMG+(2*colFrameSize)];
        }
        
        for(int i=0; i<(numRowsIMG+ (2*rowFrameSize)); i++){
            for(int j=0; j<(numColsIMG+(2*colFrameSize)); j++){
                morphFramedAry[i][j]=0;
            }
        }
        
        tempFramedAry = new int*[numRowsIMG+(2*rowFrameSize)];
        for(int r = 0; r<(numRowsIMG+(2*rowFrameSize)); r++){
            tempFramedAry[r] = new int[numColsIMG+(2*colFrameSize)];
        }
        
        for(int i=0; i<(numRowsIMG+ (2*rowFrameSize)); i++){
            for(int j=0; j<(numColsIMG+(2*colFrameSize)); j++){
                tempFramedAry[i][j]=0;
            }
        }
    }
    
    void structEle(ifstream& infile2){
        
        structEleAry = new int*[numRowsSE];
        for(int r=0; r<(numRowsSE); r++){
            structEleAry[r] = new int[numColsSE];
        }
        
        int data;
        for(int r=0; r<numRowsSE; r++){
            for(int c=0; c<numColsSE; c++){
                infile2>>data;
                structEleAry[r][c]=data;
            }
        }
        
    }

    void ErosionO(){
        
        for(int currentRow = rowFrameSize; currentRow<numRowsIMG+rowFrameSize; currentRow++){
            for(int currentCol = colFrameSize; currentCol<numColsIMG+colFrameSize; currentCol++){
                
                if(zeroFramedAry[currentRow][currentCol]==structEleAry[rowOrigin][colOrigin]){

                    int flag = 1;
                    
                    int rowStart = (currentRow-rowOrigin);
                    int rowEnd = (rowStart+numRowsSE);
                    int colStart = (currentCol-colOrigin);
                    int colEnd = (colStart + numColsSE);
                    
                    int seRow;
                    int seCol;
                    
                    for(int i = rowStart; i< rowEnd; i++){
                        for(int j = colStart; j< colEnd; j++){
                            
                            seRow =  (numRowsSE-(rowEnd-i));
                            seCol =  (numColsSE-(colEnd-j));
                            
                            
                            if(structEleAry[seRow][seCol]==1){
                                
                                if(zeroFramedAry[i][j] != structEleAry[seRow][seCol]){
                                    flag=0;
                                }
                            }
                            
                            
                            
                        }
                    }
                    
                    tempFramedAry[currentRow][currentCol] = flag;
                    
                }
                
            }
        }
        
        
        
        
        
    }

    
    //Dilation for Opening-  no zeroframing needed AND we create morphAry, working with temp
    void DilationO(){
      
        for(int currentRow = rowFrameSize; currentRow<numRowsIMG+rowFrameSize; currentRow++){
            for(int currentCol = colFrameSize; currentCol<numColsIMG+colFrameSize; currentCol++){
                
                if(tempFramedAry[currentRow][currentCol]==structEleAry[rowOrigin][colOrigin]){
                    
                    int rowStart = (currentRow-rowOrigin);
                    int rowEnd = (rowStart+numRowsSE);
                    int colStart = (currentCol-colOrigin);
                    int colEnd = (colStart + numColsSE);
                    
                    int seRow;
                    int seCol;
                    
                    for(int i = rowStart; i< rowEnd; i++){
                        for(int j = colStart; j< colEnd; j++){
                            
                            seRow =  (numRowsSE-(rowEnd-i));
                            seCol =  (numColsSE-(colEnd-j));
                            
                            if(structEleAry[seRow][seCol]==1){
                                morphFramedAry[i][j] = structEleAry[seRow][seCol];
                            }
                            
                            
                        
                            
                        }
                    }
                    
                }
                
            }
        }
        
    }

    void printAll(ofstream& outfile){
        
        for(int i=rowFrameSize; i<numRowsIMG+rowFrameSize; i++ ){
            for(int j=colFrameSize; j<numColsIMG+colFrameSize; j++){
                outfile<<morphFramedAry[i][j]<<" ";
            }
            outfile<<endl;
        }
        
    }
    
    void morphFrameZERO(){
        
        for(int i=0; i<(numRowsIMG+(2*rowFrameSize)); i++){
            for(int j=0; j<(numColsIMG+(2*colFrameSize)); j++){
                morphFramedAry[i][j]=0;
            }
        }
        
    }
    
    
    void Opening(ofstream& outfile){
        
        morphFrameZERO();
        
        ErosionO();
        DilationO();
        
        cout<<"Opening Result "<<endl;
        consolePrintMorph();
        
        printAll(outfile);
        
    }
    
    
};



int main(int argc, char* argv[]){
    
    system("python helper.py");

    ifstream infile1, infile2;
    infile1.open("imageB.txt");
    infile2.open("structureElement.txt");

    
    ofstream outfile1;
    outfile1.open("output.txt");
    
    Morphology morph(infile1, infile2);
    
    morph.Opening(outfile1);
    
    infile1.close();
    infile2.close();
    outfile1.close();
    
    system("python helper2.py");

}
