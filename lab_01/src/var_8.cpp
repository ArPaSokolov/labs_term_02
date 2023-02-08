/*Создайте класс MyText, который позволит создавать анимированный вывод текста.
Класс должен содержать строку text, переменную ShowTime, 
которая указывает время вывода всей строки на экран и метод AnimationText(), 
которые выводит текст на экран.*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
using namespace std;

class Animation
{
private:
    string text;
public:

};
int main()
{
    /*--------------------------------------------задаем окно------------------------------------------------------*/
    int Width = 1000;
    int Height = 1000;
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Text animation");


    /*------------------------------------------задаем текст-------------------------------------------------------*/
    


    /*--------------------------------------запускаем программу-----------------------------------------------------*/
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        


    /*-----------------------------------анимация текста--------------------------------------------------------*/
        
        //window.draw();//выводим спрайт на экран

        window.display();
        window.clear();

        // задержка
        /*std::this_thread::sleep_for(std::chrono::seconds(1));*/
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

	return 0;
}