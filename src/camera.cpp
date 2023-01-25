#include "camera.h"

Camera::Camera()
{
    x = 0;
    y = 0;
}

Camera::~Camera()
{

}

void Camera::GetRelativePosition(int xin, int yin, int* xout, int* yout)
{    
    *xout = xin - x;
    *yout = yin - y;
}

void Camera::SetPos(int xdest, int ydest)
{
    x = xdest;
    y = ydest;
}

void Camera::MoveIP(int xoff, int yoff)
{
    x += xoff;
    y += yoff;
}