#include "calc.h"
#include <raylib.h>

Color BackCol = {229,222,211,255};
Color WhiteCol = {255,255,255,255};
Color BlackCol = {14,17,17,255};
Color GreenCol = {14,170,17,80};

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

  B2.x = 250.0;
  B2.y = 650.0;
  B1.x = 250.0;
  B1.y = 350.0;
  double THETA_2 = 0;

  struct position EF;
  struct position TARGET;

  TARGET.x = 600;
  TARGET.y = 500;

  int TARGETx=0;
  int TARGETy=0;

  SetWindowState(FLAG_WINDOW_RESIZABLE);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BlackCol);
    reverse_K(TARGET.x, TARGET.y);
    THETA_2 = forward_K2(THETA_1, PHI_1);
    //safe_area();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      Vector2 ballPosition = GetMousePosition();
      //printf("%f\n", ballPosition.x);
      TARGET.x = ballPosition.x;
      TARGET.y = ballPosition.y;
    }


    DrawCircleLines(L1.x, L1.y, L1b, DARKBLUE);
    DrawCircleLines(L2.x, L2.y, L2b, DARKBLUE);
    DrawCircleLines(B1.x, B1.y, L1a, BackCol);
    DrawCircleLines(B2.x, B2.y, L2a, BackCol);

    DrawCircle(B1.x, B1.y, 20, WhiteCol);
    DrawCircle(B2.x, B2.y, 20, WhiteCol);
    DrawRectangle(L1.x-5,L1.y-5,10,10,WhiteCol);
    DrawRectangle(L2.x-5,L2.y-5,10,10,WhiteCol);
    DrawRectangle(EF.x-5,EF.y-5,10,10,BackCol);
    DrawRectangle(TARGET.x-5,TARGET.y-5,10,10,GreenCol);

    DrawLine(B1.x, B1.y, L1.x, L1.y, WhiteCol);
    DrawLine(B2.x, B2.y, L2.x, L2.y, WhiteCol);
    EF.x = L1.x+L1b*cos(THETA_2);
    EF.y = L1.y+L1b*sin(THETA_2);
    DrawLine(L1.x,L1.y,EF.x,EF.y,WhiteCol);
    DrawLine(L2.x,L2.y,EF.x,EF.y,WhiteCol);
    EndDrawing();

    /*TARGETx += 1;
    TARGETy += 0.3;

    TARGET.x = 600 + TARGETx%100;
    TARGET.y = 500 + TARGETy%100;*/

  }

  //printf("\n\n\n%lf\n\n\n",forward_K2(theta_1, theta_2)) ;

}
