/* Matrix quick power */
// (a1, a2, ...) * A = (a2, a3, ...) //
template <class T>
struct Matrix {
    vector<vector<T>> mat;
    int sz;
    Matrix(int n): sz(n) {
        mat.resize(n, vector<T>(n));
    }

    Matrix& operator*=(const Matrix& rhs) {
        Matrix<T> res(sz);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                for (int k = 0; k < sz; ++k) {
                    res.mat[i][j] += mat[i][k] * rhs.mat[k][j];
                }
            }
        }
        *this = std::move(res);
        return *this;
    }
};

template <class T>
Matrix<T> Mqpow(Matrix<T> a, Matrix<T> A, long long y) {
    while (y) {
        if (y & 1) a *= A;
        A *= A;
        y >>= 1;
    }
    return a;
}