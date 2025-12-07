#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <math.h>

struct Scara{
    Vector2 origin;
    Vector2 end;
    double Theta1;
    double Theta2;
    double l1;
    double l2;
};

Color BaigeCol = {229,222,211,255};
Color WhiteCol = {255,255,255,255};
Color BlackCol = {14,17,17,255};
Color GreenCol = {14,170,17,80};

struct Scara* createScara(Vector2 origin, double l1, double l2){
    struct Scara* rb = (struct Scara*)malloc(sizeof(struct Scara));
    rb->origin = origin;
    //rb->end = {rb->origin.x + l1 + l2, rb->origin.y};
    rb->Theta1 = 0;
    rb->Theta2 = 0;
    rb->l1 = l1;
    rb->l2 = l2;
    return rb;
}

bool moveScara(struct Scara* rb, Vector2 target){
    double X = target.x - rb->origin.x;
    double Y = target.y - rb->origin.y;
    double Theta = atan2(Y, X);
    double l = sqrt(X*X + Y*Y);
    printf("[Theta1 : %lf\tTheta2 : %lf]\t", rb->Theta1, rb->Theta2);
    printf("target : [%lf  ,  %lf]\n", target.x, target.y);

    double T2 = acos( (rb->l2 * l /2) + sqrt((2 * l * l * rb->l2 * rb->l2) - 4*((rb->l1 * rb->l1) - (rb->l2 * rb->l2) - (l*l))) );
    double T1 = asin(rb->l2 * sin(T2) / rb->l1);

    rb->Theta1 = Theta - T1;
    rb->Theta2 = Theta + T2;

    printf("[Theta1:%lf\tTheta2:%lf]", rb->Theta1, rb->Theta2);
    return true;

    printf("[Theta1 : %lf\tTheta2 : %lf]\t", rb->Theta1, rb->Theta2);
    printf("target : [%lf  ,  %lf]\n", target.x, target.y);


}

bool drawScara(struct Scara * rb){

    int pos_x = (int)rb->origin.x;
    int pos_y = (int)rb->origin.y;
    int pos_x2 = pos_x + (rb->l1 * cos(rb->Theta1));
    int pos_y2 = pos_y + (rb->l1 * sin(rb->Theta1));
    int pos_x3 = pos_x2 + (rb->l2 * cos(rb->Theta2));
    int pos_y3 = pos_y2 + (rb->l2 * sin(rb->Theta2));

    DrawCircle(pos_x, pos_y, 20, WhiteCol);
    DrawCircle(pos_x2, pos_y2, 20, WhiteCol);
    DrawCircle(pos_x3, pos_y3, 20, WhiteCol);
    DrawLine(pos_x, pos_y,pos_x2, pos_y2, WhiteCol);
    DrawLine(pos_x2, pos_y2, pos_x3, pos_y3, WhiteCol);

    return true;
}

void safeAreaScara(struct Scara* rb){
    DrawCircle(rb->origin.x, rb->origin.y, (rb->l1 + rb->l2), GreenCol);
}
