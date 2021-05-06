//
// Created by Lanz on 2021/3/20.
//
#include <opencv2/opencv.hpp>

class Arm{
    bool m_bConstrain = true;
public:
    Arm(double x, double y, double angle_, double len_)
        : m_A(cv::Point2d(x, y)), m_Angle(angle_), m_Length(len_)
    {
        Init();
    }

    Arm(Arm* p, double angle_, double len_)
        : m_Parent(p), m_A(p->m_B), m_Angle(angle_), m_Length(len_)
    {
        Init();
    }

    void Init()
    {
        calculateB();
        m_ConstPoint = m_B;

        cv::RNG rng(cv::getTickCount());
        rng.next();
        m_Color = cv::Scalar(rng.uniform(100, 255), rng.uniform(100, 255), rng.uniform(100, 255));
    }

    void calculateB()
    {
        double dx = m_Length * cos(m_Angle);
        double dy = m_Length * sin(m_Angle);

        m_B.x = m_A.x + dx;
        m_B.y = m_A.y + dy;
    }

    void calculateA()
    {
        double dx = m_Length * cos(m_Angle);
        double dy = m_Length * sin(m_Angle);

        m_A.x = m_B.x - dx;
        m_A.y = m_B.y - dy;
    }

    void draw(const cv::Mat& m)
    {
        //calculateB();
        //if (m_Length == 50)
        line(m, m_A, m_B, m_Color, 12, cv::LINE_AA, 0);
    }
//
//    static double calculateMag(const double& x, const double& y)
//    {
//        return sqrt(pow(x, 2) + pow(y, 2));
//    }
//
//    void follow(const double& target_x, const double& target_y)
//    {
//        cv::Point2d new_p(target_x, target_y);
//        new_p -= m_A;
//        m_Angle = atan2(new_p.y,new_p.x);
//
//        calculateB();
//
//        double new_mag = calculateMag(new_p.x, new_p.y);
//
//        new_p *= m_Length/new_mag;
//        new_p *= -1;
//
//        m_A.x = target_x + new_p.x;
//        m_A.y = target_y + new_p.y;
//
//        if (m_Child != nullptr)
//            m_Child->follow(this);
//    }

    void follow(const double& target_x, const double& target_y)
    {
        cv::Point2d new_p(target_x, target_y);
        new_p -= m_A;
        m_Angle = atan2(new_p.y, new_p.x);

        m_B.x = target_x;
        m_B.y = target_y;
        calculateA();


        if (m_Child != nullptr)
            m_Child->follow(this);
    }

    void followInverse(const double& target_x, const double& target_y){

        m_A.x = target_x;
        m_A.y = target_y;
        calculateB();

        if(m_Parent != nullptr)
            m_Parent->followInverse(m_B.x, m_B.y);
    }

    void follow(Arm* const target)
    {
        if (target == nullptr)
            return;

        follow(target->m_A.x, target->m_A.y);

        if (m_bConstrain && m_Child == nullptr){
            this->followInverse(m_ConstPoint.x, m_ConstPoint.y);
        }
    }

    void setChild(Arm* const c)
    {
        m_Child = c;
    }

private:
    cv::Point2d m_A;
    cv::Point2d m_B;
    cv::Point2d m_ConstPoint;
    cv::Scalar m_Color;
    double m_Angle;
    double m_Length;
    Arm* m_Parent = nullptr;
    Arm* m_Child = nullptr;
};