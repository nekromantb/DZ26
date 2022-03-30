#include "task3.h"
#include <iostream>


#define SCREENWIGHT 80
#define SCREENHEIGHT 60

class Coordinates
{
    double x = 0;
    double y = 0;

public:

    void setCoord(double inputX, double inputY)
    {
        x += inputX;
        y += inputY;
    }

    double getCoordX()
    {
        return x;
    }

    double getCoordY()
    {
        return y;
    }

};

class Window
{
    Coordinates LUcorner;
    double wight;
    double height;

public:

    void initialiseWindow()
    {
        while (1) {
            std::cout << "Enter coordinates of window(x: 0:"<< SCREENWIGHT << " ,y: 0:"<< SCREENHEIGHT<<")" << std::endl;
            double inputX, inputY;
            std::cin >> inputX >> inputY;
            if (inputX < 0 || inputX > SCREENWIGHT || inputY < 0 || inputY > SCREENHEIGHT) {
                std::cout << "Wrong input!" << std::endl;
                continue;
            } else {
                while(1) {
                    std::cout << "Enter wight(>0) and height(>0) of window" << std::endl;
                    double inputW, inputH;
                    std::cin >> inputW >> inputH;
                    if (inputW <= 0 || inputH <= 0) {
                        std::cout << "Wrong input!" << std::endl;
                        continue;
                    }
                    else
                    {
                        LUcorner.setCoord(inputX, inputY);
                        wight = inputW;
                        height = inputH;
                        break;
                    }
                }
                break;
            }
        }
    }

    void changeCoord()
    {
        while (1) {
            std::cout << "Enter vector of move for window(x, y)" << std::endl;
            double inputX, inputY;
            std::cin >> inputX >> inputY;
            if (inputX+LUcorner.getCoordX() < 0 || inputX+LUcorner.getCoordX() > SCREENWIGHT || inputY+LUcorner.getCoordY() < 0 || inputY+LUcorner.getCoordY() > SCREENHEIGHT) {
                std::cout << "Wrong input! Window is out of screen!" << std::endl;
                continue;
            } else {
                LUcorner.setCoord(inputX,inputY);
                std::cout << "New coordinates of window are: x: " << LUcorner.getCoordX() << " y: " << LUcorner.getCoordY() <<std::endl;
                break;
            }
        }
    }

    void resizeWindow()
    {
        while (1) {
            std::cout << "Enter new measurements of window(wight (>0) , height (>0))" << std::endl;
            double inputW, inputH;
            std::cin >> inputW >> inputH;
            if (inputW <= 0 || inputH <= 0) {
                std::cout << "Wrong input!" << std::endl;
                continue;
            } else {
                wight = inputW;
                height = inputH;
                std::cout << "New measurements of window are: wight: " << wight << " height: " << height<<std::endl;
                break;
            }
        }
    }

    Coordinates getCoordinatesWindow()
    {
        return LUcorner;
    }

    double getWightWindow()
    {
        return wight;
    }

    double getHeightWindow()
    {
        return height;
    }
};

class Screen
{
    Window window;
    double screenWight = SCREENWIGHT;
    double screenHeight = SCREENHEIGHT;

public:

    void initialiseScreen()
    {
        window.initialiseWindow();
    }

    void move()
    {
        window.changeCoord();
    }

    void resize()
    {
        window.resizeWindow();
    }

    void display()
    {
        for (int j =0 ; j< screenHeight; ++j)
        {
            for (int i =0 ; i <screenWight; ++i)
            {
                if (i+1 >= window.getCoordinatesWindow().getCoordX() && i+1 < window.getCoordinatesWindow().getCoordX()+window.getWightWindow() &&
                 j+1 >= window.getCoordinatesWindow().getCoordY() && j+1 < window.getCoordinatesWindow().getCoordX()+window.getHeightWindow())
                    std::cout << "1";
                else
                    std::cout << "0";
            }
            std::cout << std::endl;
        }
    }
};



void task3()
{
    std::cout << "WindowProg welcomes you!" <<std::endl;
    std::cout << "Commands are \"move\", \"resize\", \"display\", \"close\"" << std::endl;
    Screen* screen = new Screen();
    screen->initialiseScreen();
    std::cout << "Command:" <<std::endl;
    while (1)
    {
        std::string command;
        std::cin >> command;
        if (command == "move")
            screen->move();
        else if (command == "resize")
            screen->resize();
        else if (command == "display")
            screen->display();
        else if (command == "close")
            break;
        std::cout << "Command:" <<std::endl;
    }
    delete screen;
    screen = nullptr;
    delete screen;
}