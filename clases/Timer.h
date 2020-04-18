#pragma once

class Timer
{
private:
    float max;
    float current;
public:
    //CANON
    Timer();
    Timer(float p_max);
    ~Timer();

    //FUNCTIONALITY
    float advance();
    float reset();

    //GET
    float getMax(){return max;}
    float getCurrent(){return current;}


    //SET
    void setMax(float p_max){max=p_max;}
};

