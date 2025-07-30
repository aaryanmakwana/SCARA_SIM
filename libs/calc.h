#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define L1a 290.00
#define L1b 290.00
#define L2a 290.00
#define L2b 290.00
#define deg2rad 0.01745329

#define a_1 (L2.x)
#define b_1 (L2.y)
#define c (L2b)
#define j (pow(L1.x,2) + pow(L1.y,2) - pow(L2.x,2) - pow(L2.y,2))
#define k (2*(L1.x-L2.x))
#define l (2*(L1.y-L2.y))


struct position{
  double x;
  double y;
};

struct position L1;
struct position L2;
struct position B1;
struct position EF1;
struct position EF2;
struct position B2;

double THETA_1 = 10.0*deg2rad;
double PHI_1 = -10.0*deg2rad;
double THETA_2 = 0.0;

void checkTheta(double THETA_1, double PHI_1) {
  L1.x = B1.x + cos(THETA_1)*L1a;
  L1.y = B1.y + sin(THETA_1)*L1a;
  L2.x = B2.x + cos(PHI_1)*L2a;
  L2.y = B2.y + sin(PHI_1)*L2a;

  double D = sqrt(pow(L1.x-L2.x,2)+pow(L1.y-L2.y,2));

  while(D > (L2b+L1b)){
    THETA_1 -= 1;
    PHI_1 -= 1;
    D = sqrt(pow(L1.x-L2.x,2)+pow(L1.y-L2.y,2));
  }
}

double forward_K2(double THETA_1, double PHI_1){

    L1.x = B1.x + cos(THETA_1)*L1a;
    L1.y = B1.y + sin(THETA_1)*L1a;
    L2.x = B2.x + cos(PHI_1)*L2a;
    L2.y = B2.y + sin(PHI_1)*L2a;
    double D = sqrt(pow(L1.x-L2.x,2)+pow(L1.y-L2.y,2));

    double theta_arm = acos(( (L2.x-L1.x)*(B1.x-L1.x)+(B1.y-L1.y)*(L2.y-L1.y) )/( D*sqrt(pow(B1.x-L1.x,2)+pow(B1.y-L1.y,2)) ));
    double theta_transform = acos(D/(2*L1b));

    return 3.14159 - (theta_arm+theta_transform - THETA_1);
}

void forward_K(double THETA_1, double PHI_1){
  checkTheta(THETA_1, PHI_1);

  L1.x = B1.x + cos(THETA_1)*L1a;
  L1.y = B1.y + sin(THETA_1)*L1a;
  L2.x = B2.x + cos(PHI_1)*L2a;
  L2.y = B2.y + sin(PHI_1)*L2a;

  EF1.x = ((2*a_1 + (2*b_1 *k)/l) + sqrt((pow((2*a_1 + (2*b_1 *k)/l),2) - 4*(1-pow((k/l),2))*(pow(c,2)-pow(a_1,2)-pow(b_1 ,2)-pow(j/l,2)+(2*b_1 *j/l)))))/(2*(1-pow(k/l,2)));

  EF1.y = (j + k*EF1.x)/l;

  EF2.x = ((2*a_1 + (2*b_1 *k)/l) - sqrt((pow((2*a_1 + (2*b_1 *k)/l),2) - 4*(1-pow((k/l),2))*(pow(c,2)-pow(a_1,2)-pow(b_1 ,2)-pow(j/l,2)+(2*b_1 *j/l)))))/(2*(1-pow(k/l,2)));

  EF2.y = (j + k*EF2.x)/l;

/*
  printf("EndFactor1 : [ %lf , %lf ]\n",EF1.x, EF1.y);
  printf("EndFactor2 : [ %lf , %lf ]\n",EF2.x, EF2.y);
  printf("L1 : [ %lf , %lf ]\n",L1.x, L1.y);
  printf("L2 : [ %lf , %lf ]\n",L2.x, L2.y);
*/

}

void reverse_K(double x, double y){
  double delta_theta = atan((y-B2.y)/(x-B2.x));
  double sigma_theta = acos(0.5*((y-B2.y)/(L1a*sin(delta_theta))));

  //THETA_1 = delta_theta+sigma_theta;
  PHI_1 = sigma_theta+delta_theta;

  delta_theta = atan((y-B1.y)/(x-B1.x));
  sigma_theta = acos(0.5*((y-B1.y)/(L1a*sin(delta_theta))));

  THETA_1 = sigma_theta+delta_theta;
  //THETA_2 = sigma_theta-delta_theta;

}
