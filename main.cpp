#include <iostream>
#include <algorithm>
#include <cmath>
#include <ctime>

#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>

#define DEBUG
#define CALCU_TIME(start, end) \
    std::cout << "Spend Time::" <<(double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
#define SHOW_POINT(point) \
    std::cout << "(" << point.x() << ", " << point.y() << ")" << std::endl;

static const int WIDTH  = 700;
static const int HEIGHT = 700;

std::vector<Eigen::Vector3f> frameBuffer;

void putPixel(const Eigen::Vector2i& point) {
    int index = (HEIGHT - point.y())*WIDTH + point.x();
    frameBuffer[index] = Eigen::Vector3f(255.0f, 255.0f, 255.0f);
}

void draw() {
    int key = -1;
    while(key != 27) {
        cv::Mat image(WIDTH, HEIGHT, CV_32FC3, frameBuffer.data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("Image", image);

        key = cv::waitKey(10);
    }
}

void Bresenham(const Eigen::Vector2f& begin, const Eigen::Vector2f& end)
{
    float x0 = begin.x();
    float y0 = begin.y();
    float x1 = end.x();
    float y1 = end.y();

    // 确保计算方向为正向
    if(x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dX = (int)fabs(x1 - x0);
    int dY = (int)fabs(y1 - y0);
    int delta = dX - 2 * dY;

    int dStepUp = 2 * (dX - dY);
    int dStepDown = -2 * dY;

    int x = (int)x0, y = (int)y0;

    for(int i = x; i != (int)x1; i++) {
        putPixel(Eigen::Vector2i(i, y));
        SHOW_POINT(Eigen::Vector2i(i, y));
        if(delta < 0) {
            y += 1;
            delta += dStepUp;
        } else {
            delta += dStepDown;
        }
    }
}

void DDA(Eigen::Vector2f begin, Eigen::Vector2f end)
{
    float x0 = begin.x();
    float y0 = begin.y();
    float x1 = end.x();
    float y1 = end.y();

    float dx = fabs(x1 - x0);
    float dy = fabs(y1 - y0);

    // 选择最大截距方向为步长方向
    float step = std::max(dx, dy);

    // 若step选择的移动方向为x轴，则deltaX = dx / dx = 1，即默认在x方向进行步长为1的移动
    // 同理deltaY = 1
    float deltaX = dx / step;
    float deltaY = dy / step;

    float x = x0, y = y0;
    putPixel(Eigen::Vector2i(x, y));
    SHOW_POINT(Eigen::Vector2i(x, y));

    for(int i = 0 ; i < (int)step ; i++) {
        x += deltaX;
        y += deltaY;
        putPixel(Eigen::Vector2i(x, y));
        SHOW_POINT(Eigen::Vector2i(x, y));
    }
}

int main() {
    frameBuffer.resize(WIDTH * HEIGHT);
    std::fill(frameBuffer.begin(), frameBuffer.end(), Eigen::Vector3f{0, 0, 0});

    auto point = Eigen::Vector2f(700, 700);

    clock_t startTime, endTime;
    startTime = clock();

    //Bresenham(Eigen::Vector2f(0, 0), point);
    DDA(Eigen::Vector2f(0, 0), point);

    endTime = clock();
    CALCU_TIME(startTime, endTime);

    draw();

    return 0;
}
