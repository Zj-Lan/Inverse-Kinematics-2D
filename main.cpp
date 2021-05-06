//
// Created by Lanz on 2021/3/20.
//
#include "Arm.cpp"

static cv::Mat canvas;
static cv::Mat blank;
static std::vector<Arm*> vec_Arms;

void createArms()
{
    int N = 2;
    Arm* a1 = new Arm(500,300,20,50);
    vec_Arms.push_back(a1);

    for (int i = 0; i < N; ++i) {
        Arm* pArm = new Arm(vec_Arms.back(), 10*(i%2?-1:1), 100+i*10);
        //Arm* pArm = new Arm(vec_Arms.back(), 10*(i%2?-1:1), 5);
        vec_Arms.back()->setChild(pArm);
        vec_Arms.push_back(pArm);
    }
}

void drawArms(const cv::Mat& m)
{
    for(auto& arm: vec_Arms) arm->draw(m);
}

void on_mouse(int event, int x, int y, int flags, void* u)
{
    if (event == CV_EVENT_LBUTTONDOWN
        || (event == CV_EVENT_MOUSEMOVE && flags == CV_EVENT_FLAG_LBUTTON))
    {
        blank.copyTo(canvas);

        vec_Arms.front()->follow(x,y);
        drawArms(canvas);
    }
    imshow("IK", canvas);
}

int main()
{
    cv::namedWindow("IK");
    canvas = cv::Mat(768,1024, CV_8UC3, cv::Scalar(50,50,50));
    canvas.copyTo(blank);

    createArms();
    drawArms(canvas);

    cv::setMouseCallback("IK", on_mouse,nullptr);
    imshow("IK", canvas);
    cv::waitKey(0);

    return 0;
}
