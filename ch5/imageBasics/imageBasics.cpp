#include<iostream>
#include<chrono>
using namespace std;

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
    cv::Mat image;
    image = cv::imread(argv[1]);
    // 判断图像文件是否正确读取
    if (image.data == nullptr)
    {
        cerr<<"文件"<<argv[1]<<"不存在."<<endl;
        return 0;
    }

    // 如果文件正确读取,打印图像信息
    cout <<"图像宽为:"<<image.cols<<",高为:"<<image.rows<<",通道数为:"<<image.channels()<<endl;
    cv::imshow("image",image);
    cv::waitKey(0);

    // 判断image类型
    if(image.type() != CV_8UC1 && image.type() != CV_8UC3 )
    {
        cout <<"请输入一张彩色图片或者灰度图像"<<endl;
        return 0;
    }

    // 遍历图像,下面的方法可以用于随机访问
    // 使用std::chrono 给算法计时
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (size_t y=0; y<image.rows;y++)
    {
        for(size_t x=0; x<image.cols;x++)
        {
            // 访问位于x,y处的元素
            // 用cv::Mat::ptr 获得图像的行指针
            unsigned char* row_ptr = image.ptr<unsigned char> (y);
            unsigned char* data_ptr = &row_ptr[x*image.channels()];
            // 输出每个通道的值
            for(int c = 0; c<image.channels();c++)
            {
                unsigned char data = data_ptr[c];
            }
        }
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
    cout<<"遍历图像用时: "<<time_used.count()<<"秒."<<endl;

    // 关于 cv::Mat 的拷贝
    // 直接赋值并不会拷贝数据
    cv::Mat image_clone = image.clone();
    image_clone(cv::Rect(0,0,100,100)).setTo(255);
    cv::imshow("image",image);
    cv::imshow("image_clone",image_clone);
    cv::waitKey(0);

    cv::destroyAllWindows();
    return 0;
}