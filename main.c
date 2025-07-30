#include "libs/calc.h"
#include "libs/robot.h"
#include <math.h>
#include <raylib.h>

void safe_area(){
  for (int ki = 0; ki < 1000; ki++) {
    for (int kj = 0; kj < 1000; kj++) {
      double D1 = sqrt(pow(ki-B1.x,2)+pow(kj-B1.y,2));
      double D2 = sqrt(pow(ki-B2.x,2)+pow(kj-B2.y,2));
      if(D1 < (L1a+L1b) && D2<(L2a+L2b)){
        DrawCircle(ki, kj, 2, GreenCol);
      }
    }
  }
}

int main(){
  InitWindow(1000,1000,"SCARA");
  SetTargetFPS(60);


  int TARGETx=0;
  int TARGETy=0;

  double THETA_2 = 0.5;
  double THETA_1 = 0.3;

  struct Robot *rb1 = create_robot((Vector2){500,500}, 200, 200);

  SetWindowState(FLAG_WINDOW_RESIZABLE);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BlackCol);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      Vector2 ballPosition = GetMousePosition();
      //printf("%f\n", ballPosition.x);
      TARGETx = ballPosition.x;
      TARGETy = ballPosition.y;

    }

    DrawRectangle(TARGETx-5,TARGETy-5,10,10,GreenCol);
    draw_robot(rb1, THETA_1, THETA_2);
    THETA_1 += 0.02;
    THETA_2 += 0.01;


    EndDrawing();

    /*TARGETx += 1;
    TARGETy += 0.3;

    TARGET.x = 600 + TARGETx%100;
    TARGET.y = 500 + TARGETy%100;*/

  }

  //printf("\n\n\n%lf\n\n\n",forward_K2(theta_1, theta_2)) ;

}
