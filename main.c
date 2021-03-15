#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define R 400


typedef struct Weight {
    float mass;
    float theta;
} Weight;

void update(Weight *weights)
{
   
    for(int i = 0; i < 3; i++){
        printf("Mass of weight %d (Grams): ", i+1);
        scanf("%f", &weights[i].mass);
        printf("Angle of weight %d (Degrees) : ", i+1);
        scanf("%f", &weights[i].theta);
        weights[i].theta *= (-PI/180);
    }
    
}

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    
    Weight weights[4] = {};
  
    
    update(weights);
    
    
    float xTotal = 0.0;
    float yTotal = 0.0;
    for(int i = 0; i < 3; i++)
    {
        xTotal += weights[i].mass * cosf(-weights[i].theta);
        yTotal += weights[i].mass * sinf(-weights[i].theta);
    }     
   
    
   printf("R_x: %f \n", xTotal);
   printf("R_y: %f \n", yTotal);
    
        
    
    weights[3].mass = sqrt(pow(xTotal,2) + pow(yTotal,2));
    
    
    
    weights[3].theta = -(atanf(yTotal/xTotal));
    weights[3].theta -= PI;
    
    
    if(xTotal > 0){
        if(yTotal < 0){
            weights[3].theta += 2*PI;
        }
    } else {
        weights[3].theta += PI;
    }
    
    
    printf("R mass: %f \n", weights[3].mass);
    printf("R theta: %f \n", weights[3].theta);
    

    
   
    InitWindow(screenWidth, screenHeight, "Force Table");

    Vector2 agentPos = { screenWidth/2, screenHeight/2 };
    
    
    //sizeRatio
    float largestWeight = 0;
    
    for(int i = 0; i < 4; i++){
        if(weights[i].mass > largestWeight){
            largestWeight = weights[i].mass;
        }
    }
    
    
    float sizeRatio = (largestWeight / 60);


    SetTargetFPS(60);  
    while (!WindowShouldClose())    
    {
        
         if(IsKeyDown(KEY_UP)){
             update(weights);
          }
        
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
                DrawCircleLines(screenHeight/2, screenHeight/2, R, RED);
            
            
                
                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                    agentPos = GetMousePosition();
                }
                
            
                
              for(int i = 0; i< 4; i++){
                  DrawLineV((Vector2){ R*cosf(weights[i].theta) + screenWidth/2, R*sinf(weights[i].theta) + screenHeight/2}, agentPos, BLACK);
              }
               
                
               
                DrawCircleV(agentPos, 50, BLUE);
                
                DrawCircleV((Vector2){ R*cosf(weights[3].theta) + screenWidth/2, R*sinf(weights[3].theta) + screenHeight/2}, weights[3].mass/sizeRatio, PURPLE);
               
                for(int i = 0; i < 4; i++){
                    char thetaDisplay[30];
                    char massDisplay[30];
                    
                    sprintf(thetaDisplay, "%f", weights[i].theta * -(180/PI));
                    sprintf(massDisplay, "%f", weights[i].mass);
                    
                    strcat(thetaDisplay, " Degrees ");
                    strcat(massDisplay, " Grams ");
               
                    if(i != 3){
                        DrawCircleV((Vector2){ R*cosf(weights[i].theta) + screenWidth/2, R*sinf(weights[i].theta) + screenHeight/2}, weights[i].mass/sizeRatio, BLACK);
                    }
                    DrawText(thetaDisplay, (R*cosf(weights[i].theta) + screenWidth/2),  (R*sinf(weights[i].theta) + screenHeight/2 - 40), 20, RED);
                    DrawText(massDisplay, (R*cosf(weights[i].theta) + screenWidth/2),  (R*sinf(weights[i].theta) + screenHeight/2 + 40), 20, BLUE);
                    
                }
                
                
               
                if(agentPos.x != screenWidth/2 || agentPos.y != screenHeight/2){
                    
                    if(agentPos.x > screenWidth/2){
                        agentPos.x -= 1;
                    }
                    if(agentPos.x < screenWidth/2){
                        agentPos.x += 1;
                    }
                    
                    if(agentPos.y > screenHeight/2){
                        agentPos.y -= 1;
                    }
                    
                    if(agentPos.y < screenHeight/2){
                        agentPos.y += 1;
                    }
                        
                }
                
                
                 
        DrawText("Up key to update values", 10, screenHeight - 60, 20, BLACK);
            
        EndDrawing();
    }
    
    CloseWindow();       

    return 0;
}


