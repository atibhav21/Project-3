//
//  main.cpp
//  Project 3
//
//  Created by Atibhav Mittal on 10/19/15.
//  Copyright © 2015 ati. All rights reserved.
//

#include "grid.h"
#include <string>
#include <cctype>
#include <iostream>
#include <cassert>
using namespace std;

bool isRouteWellFormed(string route)
{
    
    if(isdigit(route[0]))   // first characted in string cannot be a digit
    {
        return false;
    }
    for(size_t i = 0; i!=route.size(); i++) // checks for all other values in the string
    {
        if(!isdigit(route[i])) //if character is not a digit, check if its N,S,W,E in upper or lower case
        {
            switch(tolower(route[i]))
            {
                case 'n':
                case 's':
                case 'w':
                case 'e': break;
                    
                default: return false; //character at route[i] is not a direction or an integer
            }
        }
        
    }
    return true;
}

int navigateSegment(int r, int c, char dir, int maxSteps)
{
    int steps = -1;//steps start with -1 so that first iteration of loop gets steps to 0
    if( r>getRows() || r<=0 || c>getCols() || c<=0 || maxSteps<0) //invalid input
    {
        return -1;
    }
    else //input is valid
    {
        /*move in given direction maximum number of steps until maxSteps is reached or a wall is encountered or edge of grid is countered*/
        if(tolower(dir)=='n')
        {
            for(int i = r; i>=1 && !isWall(i,c) && steps < maxSteps;i--)
            {
                steps++;
            }
        }
        else if(tolower(dir)=='s')
        {
            for(int i =r; i<= getRows() && !isWall(i,c) && steps < maxSteps; i++)
            {
                steps++;
            }
        }
        else if(tolower(dir)=='w')
        {
            for(int j = c; j >= 1 && !isWall(r,j) && steps < maxSteps; j--)
            {
                steps++;
            }
        }
        else if(tolower(dir)=='e')
        {
            for(int j = c; j<= getCols() && !isWall(r, j) && steps < maxSteps; j++)
            {
                steps++;
            }
        }
        else //direction entered is invalid
        {
            return -1;
        }
    }
    return steps;
}

int convertStringToInteger(string s) //convert numerical value in string to an integer
{
    int num = 0;
    for(size_t i = 0; i<s.size(); i++)
    {
        int digit = (int) (s[i] - '0'); //character is converted to its integer value
        num = (num*10) + digit;
    }
    return num;
}

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)
{
    if(sr<0||sr>getRows()||sc<0||sc>getCols()||er<0||er>getRows()||ec<0||ec>getCols()|| !isRouteWellFormed(route) || isWall(sr,sc) || isWall(er, ec)) // invalid input
    {
       return 2;
    }
    int startRow = sr;
    int startCol = sc;
    nsteps = 0;
    for(size_t i = 0; i<route.size(); i++)
    {
        
        if(isalpha(route[i]))   //find direction to go in
        {
            char direction = route[i];
            int maxSteps = 1; //only one step in current direction
            if(i+1 != route.size() && isdigit(route[i+1])) //read number of steps taken in that direction
                                                           //only if last segment does not have just a direction
            {
                size_t j = i+1;
                string numberOfSteps = "";
                while(j!= route.size() && isdigit(route[j]))
                {
                    numberOfSteps += route[j];
                    j++;
                }
                i = j-1; //set i to next (character position - 1) so that i++ gets it to correct index
                maxSteps = convertStringToInteger(numberOfSteps);
                
            }
            int stepsTaken = navigateSegment(startRow, startCol, direction, maxSteps);
            if(stepsTaken<maxSteps)
            {
                nsteps += stepsTaken;
                return 3;
            }
            else{ //nsteps is equal to maxSteps
                if(tolower(direction)=='n')
                {
                    startRow -= stepsTaken;   //change starting row for next segment
                }
                if(tolower(direction)=='s')
                {
                    startRow += stepsTaken;
                }
                if(tolower(direction)=='e')
                {
                    startCol += stepsTaken;
                }
                if(tolower(direction)=='w')
                {
                    startCol -= stepsTaken;
                }
                nsteps += maxSteps;
            }
            
        }
    }
    if(startRow == er && startCol == ec)
    {
        return 0;   //ends at required position
    }
    return 1;
}

int main()
{
    setSize(5,12);
    setWall(4,3);
    setWall(2,7);
    setWall(5,7);
    
    assert(navigateSegment(0,4,'S',2) == -1);
    
}


