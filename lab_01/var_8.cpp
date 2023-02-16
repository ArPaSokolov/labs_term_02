/*Создайте класс MyText, который позволит создавать анимированный вывод текста.
Класс должен содержать строку text, переменную ShowTime,
которая указывает время вывода всей строки на экран и метод AnimationText(),
которые выводит текст на экран.*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <chrono>
#include <time.h>
using namespace std;

class MyText //класс
{
private: // модификатор доступа
    string theText; //поле
    float ShowTime; //поле

public: // модификатор доступа

    MyText()
    {
        theText = "";
    }

    void AnimationText() // метод
    {
        //текст
        sf::Text text;
        string  theString;
        cout << "Enter the string: ";
        getline(cin, theString);
        text.setString(theString);

        // шрифт
        sf::Font font;
        font.loadFromFile("Orpheus.ttf");
        text.setFont(font);

        // размер в пикселях
        text.setCharacterSize(100);

        // цвет
        text.setFillColor(sf::Color(222, 184, 135));

        // стиль
        text.setStyle(sf::Text::Bold);

        // задержка
        cout << "Enter the time: ";
        cin >> ShowTime;
        cout << "The delay: " << (ShowTime / (theString.length() - 1) * 1.000) << " seconds" << endl;
        int count = 0; // счетчик
        clock_t tStart = 0; // таймер

        // окно
        int Width = theString.length() * 54;
        int Height = 150;
        sf::RenderWindow window(sf::VideoMode(Width, Height), "Text animation");

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                    window.close();
            }

            // анимация слова по частям
            if (count < theString.length())
            {
                theText += theString[count]; // добавляем букву к ранее анимированой
                cout << theText << endl; // дублирую в консоль
                count++;

                // текст
                text.setString(theText);
                
                // анимируем текст
                window.draw(text);
                window.display();

                if (count == 1) // после первой анимации
                {
                    tStart = clock(); // начинется счетчик времени
                }
                if (count == theString.length()) // если последняя буква анимирована
                {
                    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC); // выводим время
                    count++;
                }
                std::this_thread::sleep_for((ShowTime / (theString.length() - 1)) * 1000ms);

                window.clear();
            }
        }
    }
   
    ~MyText()
    {

    }
};

int main()
{
    MyText myText; // обЪект

    myText.AnimationText(); // анимация

    return 0;
}