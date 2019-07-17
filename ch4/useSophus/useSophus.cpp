#include<iostream>
#include<cmath>
#include<Eigen/Core>
#include<Eigen/Geometry>
#include"sophus/so3.h"
#include"sophus/se3.h"

using namespace std;
int main(int argc, char** argv)
{
    // 沿着Z轴旋转90度的旋转矩阵
    Eigen::Matrix3d R = Eigen::AngleAxisd(M_PI/2,Eigen::Vector3d(0,0,1)).toRotationMatrix();
    // SO(3) 可以直接从旋转矩阵构造
    Sophus::SO3 SO3_R(R);
    // 也可以从旋转向量构造
    Sophus::SO3 SO3_v(0,0,M_PI/2);
    // 或者四元数构造
    Eigen::Quaterniond q(R);
    Sophus::SO3 SO3_q(q);
    // 上面的构造方式等价
    // 输出结果
    cout << "SO(3) from matrix: "<< SO3_R<<endl;
    cout << "SO(3) from vector: "<< SO3_v<<endl;
    cout << "SO(3) from quaterniond: "<< SO3_q<<endl;

    // 使用对数映射获得他们的李代数
    Eigen::Vector3d so3 = SO3_R.log();
    cout << "SO(3) = "<<so3.transpose()<<endl;
    // hat 为向量到反对称矩阵
    cout << "SO(3) hat = "<<Sophus::SO3::hat(so3)<<endl;
    // vee 为反对称到向量
    cout << "SO(3) hat vee = "<<Sophus::SO3::vee(Sophus::SO3::hat(so3)).transpose()<<endl;

    // 增量扰动模型的更新
    Eigen::Vector3d update_so3(1e-4,0,0);
    Sophus::SO3 SO3_updated = Sophus::SO3::exp(update_so3)*SO3_R; // 左乘更新
    cout << "SO(3) updated = "<<SO3_updated<<endl;
    /***********************************************************************/

    // 对SE(3)进行操作
    Eigen::Vector3d t(1,0,0); // 沿着X轴平移1
    Sophus::SE3 SE3_Rt(R,t);  // 从R,t构造SE(3)
    Sophus::SE3 SE3_qt(q,t);  // 从q,t构造SE(3)
    cout << "SE3 from R,t = "<< SE3_Rt<<endl;
    cout << "SE3 from q,t = "<< SE3_qt<<endl;
    // 李代数se(3)是一个六维向量,方便起见先typedef一下
    typedef Eigen::Matrix<double,6,1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout << "se3 = "<<se3.transpose()<<endl;
    // hat and vee 
    cout << "se3 hat = "<<endl<<Sophus::SE3::hat(se3)<<endl;
    cout << "se3 hat vee = "<<Sophus::SE3::vee(Sophus::SE3::hat(se3)).transpose()<<endl;

    // 更新
    Vector6d update_se3;
    update_se3.setZero();
    update_se3(0,0)=1e-4d;
    Sophus::SE3 SE3_updated = Sophus::SE3::exp(update_se3)*SE3_Rt;
    cout<<"SE3 updated = "<<endl<<SE3_updated.matrix()<<endl;

    return 0;
}
