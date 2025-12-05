#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define dTHETA1_Y -(robot->link_1_length * sin(robot->theta1))
#define dTHETA1_X (robot->link_1_length * cos(robot->theta1))
#define dTHETA2_Y -(robot->link_2_length * sin(robot->theta1))
#define dTHETA2_X (robot->link_2_length * cos(robot->theta1))

Color BaigeCol = {229,222,211,255};
Color WhiteCol = {255,255,255,255};
Color BlackCol = {14,17,17,255};
Color GreenCol = {14,170,17,80};

struct Robot {
    Vector2 origin;
    double link_1_length;
    double link_2_length;
    double theta1;
    double theta2;
    double endF[2];
};

bool draw_robot(struct Robot * robot, double theta1, double theta2){
    robot->theta1 = theta1;
    robot->theta2 = theta2;

    int pos_x = (int)robot->origin.x;
    int pos_y = (int)robot->origin.y;
    int pos_x2 = pos_x + (robot->link_1_length * cos(theta1));
    int pos_y2 = pos_y + (robot->link_1_length * sin(theta1));
    int pos_x3 = pos_x2 + (robot->link_2_length * cos(theta2));
    int pos_y3 = pos_y2 + (robot->link_2_length * sin(theta2));

    DrawCircle(pos_x, pos_y, 20, WhiteCol);
    DrawCircle(pos_x2, pos_y2, 20, WhiteCol);
    DrawCircle(pos_x3, pos_y3, 20, WhiteCol);
    DrawLine(pos_x, pos_y,pos_x2, pos_y2, WhiteCol);
    DrawLine(pos_x2, pos_y2, pos_x3, pos_y3, WhiteCol);
    //DrawRectangle(pos_x-5,pos_y-5,robot->link_1_length,10,GreenCol);
    //DrawRectangle(pos_x2-5,pos_y2-5,robot->link_2_length,10,GreenCol);

    //printf("%d\t%d\n", pos_x,pos_y);
    //printf("%d\t%d\n", pos_x2,pos_y2);
    //printf("%d\t%d\n\n", pos_x3,pos_y3);

    return true;
}

bool render_robot(struct Robot * robot){
    int pos_x = (int)robot->origin.x;
    int pos_y = (int)robot->origin.y;
    int pos_x2 = pos_x + (robot->link_1_length * cos(robot->theta1));
    int pos_y2 = pos_y + (robot->link_1_length * sin(robot->theta1));
    int pos_x3 = pos_x2 + (robot->link_2_length * cos(robot->theta2));
    int pos_y3 = pos_y2 + (robot->link_2_length * sin(robot->theta2));

    DrawCircle(pos_x, pos_y, 20, WhiteCol);
    DrawCircle(pos_x2, pos_y2, 20, WhiteCol);
    DrawCircle(pos_x3, pos_y3, 20, WhiteCol);
    DrawLine(pos_x, pos_y,pos_x2, pos_y2, WhiteCol);
    DrawLine(pos_x2, pos_y2, pos_x3, pos_y3, WhiteCol);

    return true;
}


struct Robot * create_robot(Vector2 origin, double link_1_length, double link_2_length){
    struct Robot * robot = malloc(sizeof(struct Robot));
    robot->origin = origin;
    robot->link_1_length = link_1_length;
    robot->link_2_length = link_2_length;
    robot->theta1 = 0;
    robot->theta2 = 0;
    printf("robot created!\n");
    printf("%lf\n", robot->link_1_length);
    printf("%lf\n", robot->link_1_length);

    return robot;
}

void predict_theta(double TARGETx, double TARGETy, struct Robot * robot, double* theta_1, double* theta_2){
    double dY = TARGETy - robot->endF[1];
    double dX = TARGETx - robot->endF[0];
    *theta_1 += (dTHETA1_X * dX) + (dTHETA1_Y * dY);
    *theta_2 += (dTHETA2_X * dX) + (dTHETA2_Y * dY);
    //robot->theta1 = *theta_1;
    //robot->theta2 = *theta_2;
}

void go_up(struct Robot* rb){
    rb->theta1 += 0.02;
    rb->theta2 -= 0.02;
}

void go_down(struct Robot* rb){
    rb->theta1 -= 0.02;
    rb->theta2 += 0.02;
}

void go_left(struct Robot* rb){
    rb->theta1 += 0.02;
    rb->theta2 -= 0.02;
}

void go_right(struct Robot* rb){
    rb->theta1 -= 0.02;
    rb->theta2 += 0.02;
}
