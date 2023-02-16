/*Создайте класс MyText, который позволит создавать анимированный вывод текста.
Класс должен содержать строку text, переменную ShowTime,
которая указывает время вывода всей строки на экран и метод AnimationText(),
которые выводит текст на экран.*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <time.h>
using namespace std;

class MyText //класс
{
private: // модификатор доступа
    string theString; //поле
    string animatedString; //поле
    int count = 0; //поле
    float ShowTime; //поле

public: // модификатор доступа

    MyText()
    {
        theString = nullptr;
    }

    int GetCount()
    {
        return count;
    }

    int GetLength()
    {
        return theString.length();
    }

    string GetAnimatedString() // геттер
    {
        return animatedString;
    }

    float GetShowTime() // геттер
    {
        return ShowTime;
    }

    void SetTheString() // ввод строки
    {
        cout << "Enter the string:" << endl;
        cin >> theString;
    }

    void AnimationText() // анимация
    {
        int Number = theString.length();
        if (count < Number)
        {
            animatedString += theString[count];
            cout << animatedString << endl;
            count++;
        }
    }

    void ShowTimeCount() // задержка
    {
        float time;
        cout << "Enter the time:" << endl;
        cin >> time;
        float Number = theString.length();
        ShowTime = time / (Number - 1);
    }

    ~MyText()
    {

    }
};

int main()
{
    clock_t tStart = 0;
    bool flag = false;
    /*--------------------------------------------задаем окно------------------------------------------------------*/
    int Width = 1500;
    int Height = 1000;
    sf::RenderWindow window(sf::VideoMode(Width, Height), "Text animation");

    /*------------------------------------------задаем текст-------------------------------------------------------*/
    MyText myText; // обЪект

    //текст
    myText.SetTheString();
    myText.ShowTimeCount();

    sf::Text text;

    // шрифт
    sf::Font font;
    font.loadFromFile("DuskDemon.ttf");
    text.setFont(font);
    // размер в пикселях
    text.setCharacterSize(100);
    // цвет
    text.setFillColor(sf::Color::Red);
    // стиль
    text.setStyle(sf::Text::Bold);

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
        if (myText.GetCount() < myText.GetLength())
        {
            myText.AnimationText();
            text.setString(myText.GetAnimatedString());
            window.draw(text);
            if (flag == false)
            {
                tStart = clock();
                flag = true;
            }
            printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
        }

        window.display();
        window.clear();

        // задержка
        if (myText.GetCount() < myText.GetLength())
        {
            std::this_thread::sleep_for(myText.GetShowTime() * 1000ms);
            cout << "Delay: " << myText.GetShowTime() << endl;
        }
    }


    return 0;
}