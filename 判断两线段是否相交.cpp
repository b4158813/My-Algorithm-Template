// 点结构体
struct Point
{
    double x,y;
};
// 线段结构体
struct Line
{
    Point ps,pe;
};

// 求叉积：CA x CB
inline double mult(Point c,Point a,Point b){return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);}

// 判断 AB和CD 是否有交点
inline bool intersect(Point a,Point b,Point c,Point d){
    //判投影
    if(max(a.x,b.x)<min(c.x,d.x)) return false;
    if(max(a.y,b.y)<min(c.y,d.y)) return false;
    if(max(c.x,d.x)<min(a.x,b.x)) return false;
    if(max(c.y,d.y)<min(a.y,b.y)) return false;
    //判叉积
    if(mult(a,c,b)*mult(a,b,d)<0) return false;
    if(mult(c,a,d)*mult(c,d,b)<0) return false;
    return true;
}