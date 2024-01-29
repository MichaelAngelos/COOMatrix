#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class COOMatrix {
private:
    T typeofvalues;
    size_t rownum,colnum;
    vector<size_t> row,col;
    vector<T> values;

    size_t get_row_data(size_t x){
        return row[x];
    }
    size_t get_col_data(size_t y){
        return col[y];
    }
    T get_values_data(size_t index){
        return values[index];
    }

public:
    COOMatrix(int x, int y){
        rownum = x;
        colnum = y;

        row = {};
        col = {};
        values={};
    }
    
    size_t get_row_num() {
        return rownum;
    };
    size_t get_col_num(){
        return colnum;
    };
    size_t get_length_of_data(){
        return row.size();
    };

    T get(size_t x,size_t y){
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
        return T();
    }

    void set(int x,int y,T value){

        //There is no point to pollute sparse-matrix data by inserting
        //a value that is the type's default constructor.
        //get function always returns it if an element is not found,after all
        if (value!=T()){
            //in case the data being added exceeds the matrix's size,expand matrix
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
    }

    bool append(COOMatrix appending_matrix,bool appendbelowrows){

        //the boolean appendbelowrows serves as an option to either
        //append along rows or along columns.Because the processes
        //are similar,they are defined in the same function
        
        if (appendbelowrows==true){
            //check if matrices are suitable for appending
            if (appending_matrix.colnum==this->colnum){
                
                //increase appendee's row size by the sum of total rows and keep
                //current so we can properly add data
                size_t previous_row_size=this->rownum;
                this->rownum=this->rownum + appending_matrix.rownum;

                for(size_t i=0; i < appending_matrix.get_length_of_data();i++){
                    //push the appending data down so it is added after current data
                    //and add other data normally
                    row.push_back(appending_matrix.get_row_data(i)+previous_row_size);
                    col.push_back(appending_matrix.get_col_data(i));
                    values.push_back(appending_matrix.get_values_data(i));
                }

                //return true if appending is successful
                return true;
            }
            //return false if matrices are not suitable for appending
            else return false;
        }
        else{
            if (appending_matrix.rownum==this->rownum){
                //increase appendee's column size by the sum of the total columns and keep
                //current so we can properly add data
                size_t previous_column_size=this->colnum;
                this->colnum=this->colnum + appending_matrix.colnum;

                for(size_t i=0; i < appending_matrix.get_length_of_data();i++){
                    //push the appending data right so it is added after current data
                    //and add other data normally
                    row.push_back(appending_matrix.get_row_data(i));
                    col.push_back(appending_matrix.get_col_data(i)+previous_column_size);
                    values.push_back(appending_matrix.get_values_data(i));
                }
                //return true if appending is successful
                return true;
            }
            //return false if matrices are not suitable for appending
            else return false;
        }
    }

    void printthis(){
        cout<<"Matrix row size:"<<rownum<<"\nMatrix column size:"<<colnum<<'\n';
        cout<<"row indexes: ";
        for (int value : row) {
            cout<<" "<<value<<",";
        }
        cout<<"\ncol indexes: ";
        for (int value : col) {
            cout<<" "<<value<<",";
        }
        cout<<"\n     values: ";
        for (T value : values) {
            cout<<" "<<value<<",";
        }
        cout<<"\n";
    }
    
    void printthis_matrix(){
        //Print the data in the form of a matrix
        T matrix[rownum][colnum];
        
        //For any non-existent data,display the type's constructor.
        //Not suitable for string type but who keeps text in matrix form anyway
        for (size_t i=0;i<rownum;i++){
            for (size_t j=0;j<colnum;j++){
                matrix[i][j]=T();
            }
        }
        
        //populate the matrix with existing data
        for(size_t i=0;i < row.size();i++){
            matrix[row[i]][col[i]]=values[i];
        }

        //display matrix data
        for (size_t i=0;i<rownum;i++){
            for (size_t j=0;j<colnum;j++){
                cout<<matrix[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

};

int main() {
    COOMatrix<int> test(4,6);
    test.set(0,3,3);
    test.set(1,1,2);
    test.set(3,2,5);
    test.set(5,1,8);
    test.printthis();
    test.printthis_matrix();

    COOMatrix<int> test2(3,3);
    test2.set(0,1,2);
    test2.set(1,0,1);
    test2.set(2,1,4);
    test2.printthis();
    test2.printthis_matrix();
    COOMatrix<int> test3(3,3);
    test3.set(2,2,5);
    test3.set(0,1,2);
    test3.set(0,0,1);
    test3.printthis();
    test3.printthis_matrix();
    test2.append(test3,1);
    test2.printthis();
    test2.printthis_matrix();

    cout<<test2.get(0,1)<<'\n';
    cout<<test2.get(1,3)<<'\n';
    cout<<test2.get(5,2)<<'\n';
};