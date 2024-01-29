#include <iostream>
#include <vector>

using namespace std;

class COOMatrix {
private:
    int rownum,colnum;
    vector<int> row,col,values;

public:
    COOMatrix(int x,int y){
        rownum = x;
        colnum = y;

        row = {};
        col = {};
        values = {};
    }

    int get(int x,int y){
        if ((x<rownum)&&(y<colnum)){
            for(size_t i=0;i<row.size();i++){
                if (row[i]==x){
                    if (col[i]==y){
                        return values[i];
                    }
                }
            }
        }
        //In case there is no element in this representation
        return -1;
    }

    void set(int x,int y,int value){
        //in case the data being added exceeds the matrix's size
        if(rownum < x+1) rownum=x+1;
        if (colnum < y+1) colnum=y+1;

        bool checkifexisting=false;

        //Check if index of value that is a bout to be set exists.If it does,only modify value
        //if not,make a new insertion

        for (size_t i=0;i < row.size();i++){
            if ((row[i]==x)&&(col[i]==y)){
                checkifexisting=true;
                cout<<"test"<<'\n';
                values[i]=value;
            }
        }

        if (!checkifexisting){
            row.push_back(x);
            col.push_back(y);
            values.push_back(value);
        }
    }

    void printthis(){
        cout<<"Matrix x length:"<<rownum<<"\nMatrix y length:"<<colnum<<'\n';
        cout<<"row indexes: ";
        for (int value : row) {
            cout<<" "<<value<<",";
        }
        cout<<"\ncol indexes: ";
        for (int value : col) {
            cout<<" "<<value<<",";
        }
        cout<<"\n     values: ";
        for (int value : values) {
            cout<<" "<<value<<",";
        }
        cout<<"\n";
    }
    
    void printthis_matrix(){
        int matrix[rownum][colnum];
        
        for (int i=0;i<rownum;i++){
            for (int j=0;j<colnum;j++){
                matrix[i][j]=0;
            }
        }

        for(size_t i=0;i < row.size();i++){
            matrix[row[i]][col[i]]=values[i];
        }

        for (int i=0;i<rownum;i++){
            for (int j=0;j<colnum;j++){
                cout<<matrix[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

};

int main() {
    COOMatrix test(4,6);
    test.set(0,3,1);
    test.set(1,1,2);
    test.set(3,2,3);
    test.set(5,1,4);
    test.printthis();
    test.printthis_matrix();

    cout<<test.get(0,3)<<'\n';
    cout<<test.get(1,3)<<'\n';
    cout<<test.get(1,1)<<'\n';
};