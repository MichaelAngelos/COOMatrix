#include <vector>
#include <iostream>

template <typename T>
class COOMatrix {
private:
    T typeofvalues;
    size_t rownum, colnum;
    std::vector<size_t> row, col;
    std::vector<T> values;

public:
    // Constructor with initial values for values
    COOMatrix(int x, int y, const std::vector<T>& initialValues)
        : rownum(x), colnum(y), row{}, col{}, values(initialValues) {
        // Additional initialization if needed
    }
};

int main() {
    std::vector<int> initialValues = {1, 2, 3, 4, 5};
    COOMatrix<int> matrix(3, 4, initialValues);
    // Do something with the matrix...
    return 0;
}
