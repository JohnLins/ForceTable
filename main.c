#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define R 400


typedef struct Weight {
    float mass;
    float theta;
} Weight;

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    float x = 0.0f;
    
    Weight weights[4] = {};
    /*for(int i = 0; i < 4; i++){
        printf("Mass %d: ", i)
        scanf("%f", &weights[i] -> mass);
        printf("Theta %d: ", i)
        scanf("%f", &weights[i] -> theta);   
    }*/
    
    weights[0].mass = 50;
    weights[1].mass = 10;
    weights[2].mass = 50;
    //weights[3].mass = 80;
    
    weights[0].theta = 10 * -(PI/180);
    weights[1].theta = 80 * -(PI/180);
    weights[2].theta = 190 * -(PI/180);
    //weights[3].theta = 290 * -(PI/180);
    
    
    float xTotal = 0.0;
    float yTotal = 0.0;
    for(int i = 0; i < 3; i++)
    {
        xTotal += weights[i].mass * cosf(weights[i].theta);
        yTotal += weights[i].mass * sinf(weights[i].theta);
    }     

        
    printf("R_x: %f \n", xTotal);
    printf("R_y: %f \n", yTotal);
    
    
    printf("R mass: %f \n", sqrt(pow(xTotal,2) + pow(yTotal,2)));
    printf("R theta - : %f \n", 1/tanf(xTotal/xTotal) );
    
    weights[3].mass = sqrt(pow(xTotal,2) + pow(yTotal,2));
    weights[3].theta = 1/tanf(xTotal/xTotal) * -(PI/180);
    
    if(xTotal > 0){
        if(yTotal < 0){
            weights[3].theta = weights[3].theta + 360.0;
        }
    } else {
        weights[3].theta = weights[3].theta + 180.0;
    }
    
    
    
    
    
    
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

    Vector2 agentPos = { screenWidth/2 + 4, screenHeight/2 + 4};


    SetTargetFPS(60);  
    while (!WindowShouldClose())    
    {
        
        
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
                DrawCircleLines(screenHeight/2, screenHeight/2, R, RED);
                
               // R * cosf(theta)
                //R * sinf(theta)

            
                x++;
                agentPos.x = screenWidth/2 + 20;
                agentPos.y = screenHeight/2 + 20;
                
            
            
                for(int i = 0; i < 4; i++){
                    DrawLineV((Vector2){ R*cosf(weights[i].theta) + screenWidth/2, R*sinf(weights[i].theta) + screenHeight/2}, agentPos, BLACK);
                }
                /*DrawLineV((Vector2){screenWidth/2, screenHeight}, agentPos, BLACK);
                DrawLineV((Vector2){0, screenHeight/2}, agentPos, BLACK);
                DrawLineV((Vector2){screenWidth, screenHeight/2}, agentPos, BLACK);*/
                
              
               
                
               
                DrawCircleV(agentPos, 50, BLUE);
                
                for(int i = 0; i < 4; i++){
                    DrawCircleV((Vector2){ R*cosf(weights[i].theta) + screenWidth/2, R*sinf(weights[i].theta) + screenHeight/2}, weights[i].mass, BLACK);
                    //DrawCircleV((Vector2){ R*cosf(weights[2].theta), R*sinf(weights[2].theta)}, weights[2].mass, BLACK);
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


