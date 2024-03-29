#include "raylib.h"
//Credit: I am using the Raylib.com C Library 
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//^ standard libs credit

#define R 400



typedef struct Weight {
    float mass;
    float theta;
} Weight;

//Function to get user input
bool update(Weight *weights, bool first)
{  
    char *new;
    if(first == false){
         new = "new ";
    } else {new = "";}
    
    for(int i = 0; i < 3; i++){
        char term;
        
        printf("Mass of %sweight #%d (Grams): ", new, i+1);
        if(scanf("%f%c", &weights[i].mass, &term) != 2 || term != '\n'){
            printf("invalid\n");
            return false;
        }
        
        printf("Angle of %sweight #%d (Degrees) : ", new, i+1);
        if(scanf("%f%c", &weights[i].theta, &term) != 2 || term != '\n'){
            printf("invalid\n");
            return false;
        }
        
        weights[i].theta *= (-PI/180);
    }
    return true;
}

//Function to compute the 4th weight values
void calculateFourth(Weight *weights){
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
}

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    
    Weight weights[4] = {};
  
    
    bool inputSuccess = update(weights, true);
    if(inputSuccess != true){
        printf("Please relaunch the program");
        CloseWindow();  
    }
    
    
    
    calculateFourth(weights);

    
   
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

    float durationDisplaced = 0.0;
    float offRadius = 0.0;

	//Game loop
    SetTargetFPS(60);  
    while (!WindowShouldClose())    
    {
        
         if(IsKeyDown(KEY_UP)){
             bool inputSuccess = update(weights, false);
             
             if(inputSuccess != true){
                 printf("Please relaunch the program");
                 CloseWindow();  
             }
             
             calculateFourth(weights);
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
                     float offAngle = atanf( (agentPos.y - screenHeight/2) / (agentPos.x - screenWidth/2) );
                     if(offRadius == 0.0){
                        offRadius = sqrt(  pow((agentPos.x - screenWidth/2),2) + pow((agentPos.y - screenHeight/2),2)  );
                        }
                    durationDisplaced += 1;
                  
                    
                    
                   
                       if(agentPos.x > screenWidth/2){
                            agentPos.x -= fabs(5 * cosf(offAngle));
                        }
                        if(agentPos.x < screenWidth/2){
                            agentPos.x += fabs(5 * cosf(offAngle));
                        }
                        
                        if(agentPos.y > screenHeight/2){
                            agentPos.y -= fabs(5 * sinf(offAngle));
                        }
                        
                        if(agentPos.y < screenHeight/2){
                            agentPos.y += fabs(5 * sinf(offAngle));
                        }
                      
                        
                }
                
                /*

				---
				
				float motion(float m, float a, float b, float w, float x){
					    return ((a) * exp((-(b)*(x))/(2*(m)))   *  cosf(sqrt(  pow((w), 2) - pow((b) / (4 * (m)), 2)  ) * (x))); 
					    } //a is equal to the displaced radius
					    
				}
				---

                if(agentPos.x != screenWidth/2 || agentPos.y != screenHeight/2){
                    durationDisplaced += .1;
                    float offAngle = atanf( (agentPos.y - screenHeight/2) / (agentPos.x - screenWidth/2) );
                       
                       if(offAngle > 0){
                            if(offAngle < 0){
                                offAngle += 2*PI;
                            }
                        } else {
                            offAngle += PI;
                        }
                    
                    if(offRadius == 0.0){
                        offRadius = sqrt(  pow((agentPos.x - screenWidth/2),2) + pow((agentPos.y - screenHeight/2),2)  );
                    }
                    
                   
                        //agentPos.x = (offRadius - 0.0001) * cosf(offAngle);
                    
                   //     agentPos.y = (offRadius - 0.0001) * sinf(offAngle);

                    
                    
                    if(agentPos.x > screenWidth/2){
                        agentPos.x -= (motion(40, offRadius, .5, 40, durationDisplaced)) * cosf(offAngle);
                    }
                    if(agentPos.x < screenWidth/2){
                        agentPos.x += (motion(40, offRadius, .5, 40, durationDisplaced)) * cosf(offAngle);
                    }
                    
                    if(agentPos.y > screenHeight/2){
                        agentPos.y -= (motion(40, offRadius, .5, 40, durationDisplaced)) * sinf(offAngle);
                    }
                    
                    if(agentPos.y < screenHeight/2){
                        agentPos.y += (motion(40, offRadius, .5, 40, durationDisplaced)) * sinf(offAngle);
                    }

                    //returnSpeed += 0.05;
                    
                    
                } else {
                    offRadius = 0.0;
                }
                */
                
                
                 
        DrawText("Up key to update values", 10, screenHeight - 60, 20, BLACK);
            
        EndDrawing();
    }
    
    CloseWindow();       

    return 0;
}


