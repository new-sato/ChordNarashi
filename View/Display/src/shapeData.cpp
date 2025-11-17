#include "shapeData.hpp"

Rectangle::Rectangle(
    double x_arg,
    double y_arg,
    double v_arg,
    double h_arg,
    int r,
    int g,
    int b
):
    x(x_arg),
    y(y_arg),
    vertical_length(v_arg),
    horizontal_length(h_arg),
    red(r),
    green(g),
    blue(b)
{
}
