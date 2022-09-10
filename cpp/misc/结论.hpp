// 三角形外心公式
ansx = ((y2 - y1) * (y3 * y3 - y1 * y1 + x3 * x3 - x1 * x1) - (y3 - y1) * (y2 * y2 - y1 * y1 + x2 * x2 - x1 * x1)) / (2.0 * ((x3 - x1) * (y2 - y1) - (x2 - x1) * (y3 - y1)));
ansy = ((x2 - x1) * (x3 * x3 - x1 * x1 + y3 * y3 - y1 * y1) - (x3 - x1) * (x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1)) / (2.0 * ((y3 - y1) * (x2 - x1) - (y2 - y1) * (x3 - x1)));
printf("%.3lf %.3lf", ansx, ansy);

// 勾股奇偶构造公式 a^2 + b^2 = c^2 已知a求b,c
int x, b, c;
if (a & 1) {
    x = (a - 1) >> 1;
    b = x * x + (x + 1) * (x + 1) - 1;
    c = x * x + (x + 1) * (x + 1);
} else {
    x = a >> 1;
    b = x * x - 1;
    c = x * x + 1;
}
