#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define R 400


typedef struct Weight {
    float mass;
    float theta;
} Weight;

void update(Weight *weights){
    weights[0].mass = 50;
    weights[1].mass = 50;
    weights[2].mass = 110;
    
    weights[0].theta = 190 * -(PI/180);
    weights[1].theta = 340 * -(PI/180);
    weights[2].theta = 360 * -(PI/180);
    
    for(int i = 0; i < 3; i++){
        printf("Mass of weight %d : ", i);
        scanf("%f", &weights[i].mass);
        printf("Angle of weight %d : ", i);
        scanf("%f", &weights[i].theta);
        weights[i].theta *= (-PI/180);
    }
}

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    
    Weight weights[4] = {};
    /*for(int i = 0; i < 4; i++){
        printf("Mass %d: ", i)
        scanf("%f", &weights[i] -> mass);
        printf("Theta %d: ", i)
        scanf("%f", &weights[i] -> theta);   
    }*/
    
    update(weights);
    //weights[3].theta = 290 * -(PI/180);
    
    
    float xTotal = 0.0;
    float yTotal = 0.0;
    for(int i = 0; i < 3; i++)
    {
        xTotal += weights[i].mass * cosf(-weights[i].theta);
        yTotal += weights[i].mass * sinf(-weights[i].theta);
    }     
    //xTotal = -xTotal;
    //yTotal = -yTotal;
   
    
   printf("R_x: %f \n", xTotal);
   printf("R_y: %f \n", yTotal);
    
        
    
    weights[3].mass = sqrt(pow(xTotal,2) + pow(yTotal,2));
    
    
    
    //printf("RAD: %f ", (1/tanf(yTotal/xTotal)));
    
    weights[3].theta = -(atanf(yTotal/xTotal));
     weights[3].theta -= PI;
    
    //printf("BEFORE ADD: %f ", weights[3].theta);
    
    if(xTotal > 0){
        if(yTotal < 0){
            weights[3].theta += 2*PI;
        }
    } else {
        weights[3].theta += PI;
    }
    
   // weights[3].theta += PI/2;
 //  weights[3].theta = weights[3].theta * (180/PI);
 //weights[3].theta += 1;
  //weights[3].theta = -1 * weights[3].theta;
 
 
 
 //((3/4) * PI) - weights[3].theta - ((3/4) * PI);
 
    
    printf("R mass: %f \n", weights[3].mass);
    printf("R theta - : %f \n", weights[3].theta);
    
    
   /* if(xTotal > 0){
        if(yTotal < 0){
            printf("---- %f", ((1/tanf(xTotal/xTotal)) * -(180/PI)) - 360);
        }
    } else {
        printf("---- %f", ((1/tanf(xTotal/xTotal)) * -(180/PI)) - 180);
    }*/
    
    
    
    /*float Rec2Polar(float x, float y){
        
        
    }
    
    float polar2Rec(float radius, float theta){
        
    }
    */
    
    
    
    
    
    /*float masses[4] = {};
    scanf("%f", &masses[0]);
    scanf("%f", &masses[1]);
    scanf("%f", &masses[2]);*/
    
   /* float thetas[4] = {};
    thetas[0] = 0.0;
    thetas[1] = 100.0;
    thetas[2] = 170;*/
    
    
    
    //thetas[3] = ;
    
    //Write the code to make the 4th mass cause an equilibrium
    
    
    

    InitWindow(screenWidth, screenHeight, "Force Table");

    Vector2 agentPos = { screenWidth/2, screenHeight/2 };


    SetTargetFPS(60);  
    while (!WindowShouldClose())    
    {
        
        
        
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
                DrawCircleLines(screenHeight/2, screenHeight/2, R, RED);
                
               // R * cosf(theta)
                //R * sinf(theta)

            
                
                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                agentPos = GetMousePosition();
                }
                
            
            
                /*DrawLineV((Vector2){screenWidth/2, screenHeight}, agentPos, BLACK);
                DrawLineV((Vector2){0, screenHeight/2}, agentPos, BLACK);
                DrawLineV((Vector2){screenWidth, screenHeight/2}, agentPos, BLACK);*/
                
              for(int i = 0; i< 4; i++){
                  DrawLineV((Vector2){ R*cosf(weights[i].theta) + screenWidth/2, R*sinf(weights[i].theta) + screenHeight/2}, agentPos, BLACK);
              }
               
                
               
                DrawCircleV(agentPos, 50, BLUE);
                
                for(int i = 0; i < 4; i++){
                    char thetaDisplay[30];
                    char massDisplay[30];
                    
                    sprintf(thetaDisplay, "%f", weights[i].theta * -(180/PI));
                    sprintf(massDisplay, "%f", weights[i].mass);
               
                    
                    DrawCircleV((Vector2){ R*cosf(weights[i].theta) + screenWidth/2, R*sinf(weights[i].theta) + screenHeight/2}, weights[i].mass, BLACK);
                    
                    //DrawCircleLines(R*cosf(weights[i].theta) + screenWidth/2, R*sinf(weights[i].theta) + screenHeight/2, weights[i].mass, BLUE);
                    //DrawCircleV((Vector2){ R*cosf(weights[2].theta), R*sinf(weights[2].theta)}, weights[2].mass, BLACK);
                    DrawText(thetaDisplay, (R*cosf(weights[i].theta) + screenWidth/2),  (R*sinf(weights[i].theta) + screenHeight/2 - 40), 20, RED);
                    DrawText(massDisplay, (R*cosf(weights[i].theta) + screenWidth/2),  (R*sinf(weights[i].theta) + screenHeight/2 + 40), 20, BLUE);
                    
                }
                
                 //DrawCircleV((Vector2){ R*cosf(xTotal), R*sinf(yTotal) + screenHeight/2}, weights[3].mass, RED);
                
                if(agentPos.x > screenWidth/2){
                    agentPos.x -= 0.6;
                }
                if(agentPos.x < screenWidth/2){
                    agentPos.x += 0.6;
                }
                
                if(agentPos.y > screenHeight/2){
                    agentPos.y -= 0.6;
                }
                
                if(agentPos.y < screenHeight/2){
                    agentPos.y += 0.6;
                }
                
                
                /*
                DrawCircleV((Vector2){ screenWidth/2, 0}, masses[0], BLACK);
                DrawCircleV((Vector2){ screenWidth/2, screenHeight}, masses[1], BLACK);
                DrawCircleV((Vector2){ 0, screenHeight/2}, masses[2], BLACK);
                DrawCircleV((Vector2){ screenWidth, screenHeight/2}, masses[3], BLACK);*/
            
        
            
        EndDrawing();
    }
    CloseWindow();       

    return 0;
}


