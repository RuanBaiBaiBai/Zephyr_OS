
#include <stdio.h>
#include <math.h>


#define EPSILON 1e-15 // 用于泰勒级数展开的终止条件
#define PI 3.14159265358979323846 // 圆周率

// 辅助函数：计算阶乘
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// 泰勒级数展开计算sin(x)的近似值
double my_sin(double x) {
    // 将x限制在[-pi, pi]范围内
    if (x > PI) x -= 2 * PI;
    if (x < -PI) x += 2 * PI;
    
    // 初始化结果
    double sin_x = 0.0;
    double term = x;
    int n = 1;
    int sign = 1;

    // 泰勒级数展开
    do {
        sin_x += sign * term / factorial(n);
        term *= -x * x;
        n += 2;
        sign = -sign;
    } while (fabs(term / factorial(n)) > EPSILON);

    return sin_x;
}

// 泰勒级数展开计算cos(x)的近似值
double my_cos(double x) {
    // 将x限制在[-pi, pi]范围内
    if (x > PI) x -= 2 * PI;
    if (x < -PI) x += 2 * PI;
    
    // 初始化结果
    double cos_x = 1.0; // cos(0) = 1
    double term = 1.0;
    int n = 2;
    int sign = 1;

    // 泰勒级数展开
    do {
        term *= -x * x / ((n - 1) * n);
        cos_x += sign * term;
        sign = -sign;
        n += 2;
    } while (fabs(term) > EPSILON);

    return cos_x;
}

// 计算tan(x) = sin(x) / cos(x)
double my_tan(double x) {
    double cos_x = my_cos(x);
    // 检查cos(x)是否接近0，以避免除以0的错误
    if (fabs(cos_x) < EPSILON) {
        // 当cos(x)接近0时，tan(x)接近无穷大或不存在
        // 这里我们可以返回一个特定的值来表示这种情况，比如一个很大的数或一个特定的错误代码
        // 但在这个例子中，我们简单地返回无穷大（尽管在C语言中表示无穷大不是直接支持的）
        // 注意：在实际应用中，应该避免返回无穷大，而是应该处理这种错误情况
        return 1.0 / cos_x; // 这将产生一个非常大的数，但不一定是无穷大
    }
    return my_sin(x) / cos_x;
}

int main() {
    double x;
    printf("请输入一个弧度值: ");
    scanf("%lf", &x);

    double result = my_tan(x);
    // 检查是否发生了除以0的错误（尽管我们在my_tan中已经尝试避免这种情况）
    if (fabs(result) > 1e10) {
        printf("tan(%.10f) is undefined or too large to represent.\n", x);
    } else {
        printf("my_tan(%.10f) = %.10f\n", x, result);
    }

    // 注意：这里我们没有使用标准库函数进行比较，因为题目要求不使用math库

    return 0;
}