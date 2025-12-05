#include "libs/calc.h"
#include "libs/robot.h"
#include <raylib.h>

void safe_area(struct Robot* rb1){
    DrawCircle(rb1->origin.x, rb1->origin.y, (rb1->link_1_length + rb1->link_2_length), GreenCol);
}


int main(){
  InitWindow(1000,1000,"SCARA");
  SetTargetFPS(60);


  int TARGETx=0;
  int TARGETy=0;

  double THETA_2 = 0.5;
  double THETA_1 = 0.3;

  struct Robot *rb1 = create_robot((Vector2){500,500}, 200, 200);

  //SetWindowState(FLAG_WINDOW_RESIZABLE);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BlackCol);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
      Vector2 ballPosition = GetMousePosition();
      //printf("%f\n", ballPosition.x);
      TARGETx = ballPosition.x;
      TARGETy = ballPosition.y;
    }

    if(IsKeyDown(KEY_UP)){
        go_up(rb1);
    }
    if(IsKeyDown(KEY_DOWN)){
        go_down(rb1);
    }
    if(IsKeyDown(KEY_LEFT)){
        go_left(rb1);
    }
    if(IsKeyDown(KEY_RIGHT)){
        go_right(rb1);
    }

    safe_area(rb1);

    //predict_theta(TARGETx, TARGETy, rb1, &THETA_1, &THETA_2);

    //DrawRectangle(TARGETx-5,TARGETy-5,10,10,BaigeCol);
    //draw_robot(rb1, THETA_1, THETA_2);
    render_robot(rb1);

    EndDrawing();

    /*TARGETx += 1;
    TARGETy += 0.3;

    TARGET.x = 600 + TARGETx%100;
    TARGET.y = 500 + TARGETy%100;*/

  }

  //printf("\n\n\n%lf\n\n\n",forward_K2(theta_1, theta_2)) ;

}
