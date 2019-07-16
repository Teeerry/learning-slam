#include <iostream>
#include <ctime>
#include <Eigen/Core>  // Eigen 部分
#include <Eigen/Dense> // 稠密矩阵的代数运算
using namespace std;

#define MATRIX_SIZE 50

/********************************************
 * 本程序演示Eigen的基本类型的使用
 * *****************************************/

int main(int argc, char** argv)
{
    Eigen::Matrix<float,2,3> matrix_23;
    Eigen::Vector3d v_3d;
    Eigen::Matrix<float,3,1> vd_3d;

    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero();
    Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> matrix_dynamic;
    Eigen::MatrixXd matrix_x;

    matrix_23 << 1, 2, 3, 4, 5, 6;
    cout<< matrix_23<<endl;

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
            cout<<matrix_23(i,j)<<"\t";
        cout<<endl;
    }
    
    v_3d << 3, 2, 1;
    vd_3d << 4, 5, 6;
    Eigen::Matrix<double,2,1> result = matrix_23.cast<double>() * v_3d;
    cout << result << endl;

    // Eigen::Matrix<double,2,1> result2 = matrix_23 * vd_3d;
    // cout << result2 << endl;

    // 四则运算直接用+-*/
    // 下面为其他矩阵运算
    matrix_33  = Eigen::Matrix3d::Random();
    cout << matrix_33 << endl;

    cout << matrix_33.transpose() << endl;
    cout << matrix_33.sum() << endl;
    cout << matrix_33.trace() << endl;
    cout << 10*matrix_33 <<endl;
    cout << matrix_33.inverse() << endl;
    cout << matrix_33.determinant() << endl;

    // 特征值
    //实对称矩阵可以保证对角化成功
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver
        (matrix_33.transpose()*matrix_33);
    cout << "Eigen values = \n"<< eigen_solver.eigenvalues()<<endl;
    cout << "Eigen vectors = \n"<< eigen_solver.eigenvectors()<<endl;

    // 解方程
    // 求解matrix_NN * x = v_Nd这个方程
    // N 由前面的宏定义
    // 直接求解最直接,但是求逆运算量大
    
    Eigen::Matrix<double,MATRIX_SIZE,MATRIX_SIZE> matrix_NN;
    matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE,MATRIX_SIZE);
    Eigen::Matrix<double,MATRIX_SIZE,1> v_Nd;
    v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE,1);

    clock_t time_stt = clock(); // start
    

    // 直接求逆
    Eigen::Matrix<double,MATRIX_SIZE,1> x = matrix_NN.inverse()*v_Nd;
    cout << "time use in normal inverse is " << 1000*(clock()-time_stt)/
        (double)CLOCKS_PER_SEC << "ms" <<endl;

    // 通常用矩阵分解的方式求
    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time use in Qr decomposition is " << 1000*(clock()-time_stt)/
        (double)CLOCKS_PER_SEC << "ms" <<endl;

    return 0;

}
