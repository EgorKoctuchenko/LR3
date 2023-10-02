#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <filesystem>
#include <direct.h>
#include <clocale>
#include <sstream>
#include <windows.h>
#include <cmath>

// Глобальные переменные
std::string commanda = "";
sf::Text receivedText;
sf::Mutex mutex;
bool running = true;
char buffer[1024];
std::size_t received;

int mode = 0;
int this_mode = 0;
sf::Color this_color;

int mas_param[8];
std::string mas_param2[2];

char pathe1[MAX_PATH];

struct Command {
    std::string name;
    std::vector<std::string> params;
};


Command ParseCommand(const std::string& commandStr) {
    Command command;

    int number;

    std::string s_mode;

    std::istringstream ss(commandStr);
    std::string word;

    int j = 0;
    int i = 0;
    while (ss >> word) {
        if (word == "=")
        {
            break;
        }
        else {
            s_mode = word;
            std::cout << word << " === \n";
        }
    }
    std::cout << "s_mode " << s_mode;
    try {
        mode = std::stoi(s_mode);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    this_mode = mode;
    while (ss >> word) {
        switch (mode)
        {
            //clear display
            ///other
        case 5: case 10: case 15: case 20: case 24: case 30: case 36:
        case 40: case 44: case 48: case 53: case 57: case 58: case 61: case 62:
            command.params.push_back(word);
            try {
                number = std::stoi(word);
            }
            catch (const std::invalid_argument& e) {
                mas_param2[j] = word;
                std::cout << j + 1 << " param = " << mas_param2[j];
                j++;
                if (mode != 57)
                {
                    return command;
                }
                else {
                    mode++;
                }
            }
            break;

            ///
            ///numbers
        case 1: case 2: case 3: case 4: case 6: case 7: case 8: case 9: case 11: case 12:
        case 13: case 14: case 16: case 17: case 18: case 19: case 21: case 22: case 23:
        case 27: case 28: case 29: case 33: case 34:
        case 35: case 37: case 38: case 39: case 41: case 42: case 43: case 45: case 46:
        case 47: case 49: case 50: case 51: case 52: case 54: case 55: case 56: case 59:
        case 60:
            command.params.push_back(word);
            try {
                number = std::stoi(word);
            }
            catch (const std::invalid_argument& e) {
                return command;
            }
            std::cout << i + 1 << " param = " << number;
            mode++;
            mas_param[i] = number;
            i++;
            break;
            ///
        }
    }
    return command;

}
//Цвет
sf::Color MyCol()
{
    if ("red" == mas_param2[0])
    {
        return sf::Color (255, 0, 0);
    }
    else if ("blue" == mas_param2[0])
    {
        return sf::Color (0, 0, 255);
    }
    else if ("black" == mas_param2[0])
    {
        return sf::Color (0, 0, 0);
    }
    else if ("brown" == mas_param2[0])
    {
        return sf::Color (128, 64, 48);
    }
    else if ("green" == mas_param2[0])
    {
        return sf::Color (0, 255, 0);
    }
    else if ("white" == mas_param2[0])
    {
        return sf::Color (255, 255, 255);
    }
    else if ("cyan" == mas_param2[0])
    {
        return sf::Color (0, 255, 255);
    }
    else if ("yellow" == mas_param2[0])
    {
        return sf::Color (255, 255, 0);
    }
    else  if ("magenta" == mas_param2[0])
    {
        return sf::Color (255, 0, 255);
    }
    else  if ("gray" == mas_param2[0])
    {
        return sf::Color (80, 80, 80);
    }
    else if ("lightgray" == mas_param2[0])
    {
        return sf::Color (150, 150, 150);
    }
    else  if ("darkgray" == mas_param2[0])
    {
        return sf::Color (35, 35, 35);
    }
    else if ("orange" == mas_param2[0])
    {
        return sf::Color (255, 165, 0);
    }
    else if ("pink" == mas_param2[0])
    {
        return sf::Color (255, 192, 203);
    }
    else if ("purple" == mas_param2[0])
    {
        return sf::Color (128, 0, 128);
    }
    else {
        return sf::Color (255, 255, 255);
    }
}






// Функция для приема сообщений в отдельном потоке
void receiveMessages(sf::UdpSocket& socket) {
    while (running) {
        sf::IpAddress clientAddress;
        unsigned short clientPort;
        sf::Packet packet;

        // Пытаемся принять пакет от клиента
        if (socket.receive(buffer, sizeof(buffer), received, clientAddress, clientPort) == sf::Socket::Done) {
            std::string message(buffer);
            std::cout << "Получено сообщение от клиента (" << clientAddress << ":" << clientPort << "): " << message << std::endl;
            receivedText.setString("Your Command: " + message);
            ParseCommand(message);
            this_color = MyCol();

        }
        else {
            std::cerr << "Ошибка при приеме данных" << std::endl;
        }
    }
}

int main() {
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "");
    _getcwd(pathe1, MAX_PATH);
    std::string exep(pathe1);
    sf::UdpSocket socket;
    sf::RenderWindow serverWindow(sf::VideoMode(800, 600), "SFML UDP Сервер");
    unsigned short serverPort = 12345;

    if (socket.bind(serverPort) != sf::Socket::Done) {
        std::cerr << "Ошибка при привязке к порту " << serverPort << std::endl;
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile(exep + "\\font\\arial.ttf")) {
        std::cerr << "Ошибка при загрузке шрифта" << std::endl;
        return -1;
    }

    sf::RectangleShape rectangle;

    receivedText.setFont(font);
    receivedText.setCharacterSize(24);
    receivedText.setFillColor(sf::Color::White);
    receivedText.setPosition(20, 20);
    std::cout << "Сервер запущен. Ожидание команд..." << std::endl;
    sf::Color backgroundColor = sf::Color::Black;
    // Запускаем поток для приема сообщений
    std::thread receiveThread(receiveMessages, std::ref(socket));

    while (serverWindow.isOpen()) {
        sf::Event event;
        while (serverWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
                receiveThread.join(); // Дожидаемся завершения потока
                serverWindow.close();
            }
        }
        // Выводим текст на окно сервера
        serverWindow.clear(backgroundColor);
        mutex.lock();
        serverWindow.draw(receivedText);
        if (this_mode == 1)
        {

            sf::RectangleShape rectangle(sf::Vector2f(mas_param[2], mas_param[3]));
            rectangle.setPosition(mas_param[0], mas_param[1]);//Прямоугольник
            rectangle.setFillColor(sf::Color::Transparent); //Заливка без цвета
            rectangle.setOutlineColor(this_color);
            rectangle.setOutlineThickness(2.0f);
            serverWindow.draw(rectangle);
        }
        if(this_mode == 6)
        {
            sf::RectangleShape rectangle2(sf::Vector2f(mas_param[2], mas_param[3]));
            rectangle2.setPosition(mas_param[0], mas_param[1]);//Прямоугольник
            rectangle2.setFillColor(this_color); //Заливка цвета
            serverWindow.draw(rectangle2);
        }
        if (this_mode == 11)
        {
            //Элипс создание
            sf::ConvexShape ellipse;

            int numPoints = 100; //Кол-во точек
            ellipse.setPointCount(numPoints);

            float horizontalRadius = mas_param[2];
            float verticalRadius = mas_param[3];

            for (int i = 0; i < numPoints; ++i)
            {
                float angle = i * 2 * 3.14 / numPoints; 
                float x = horizontalRadius * std::cos(angle);
                float y = verticalRadius * std::sin(angle);

                ellipse.setPoint(i, sf::Vector2f(x, y));
            }
            //Ну и параметры :)
            ellipse.setPosition(mas_param[0], mas_param[1]);

            ellipse.setFillColor(sf::Color::Transparent);
            ellipse.setOutlineColor(this_color);
            ellipse.setOutlineThickness(2.0f);


            serverWindow.draw(ellipse);
        }
        if (this_mode == 16 )
        {
            //Заполненный эллипс
            sf::ConvexShape ellipse;

            int numPoints = 100;
            ellipse.setPointCount(numPoints);

            float horizontalRadius = mas_param[2];
            float verticalRadius = mas_param[3];

            for (int i = 0; i < numPoints; ++i)
            {
                float angle = i * 2 * 3.14 / numPoints;
                float x = horizontalRadius * std::cos(angle);
                float y = verticalRadius * std::sin(angle);

                ellipse.setPoint(i, sf::Vector2f(x, y));
            }

            ellipse.setPosition(mas_param[0], mas_param[1]);

            ellipse.setFillColor(this_color);
            ellipse.setOutlineColor(this_color);
            ellipse.setOutlineThickness(2.0f);


            serverWindow.draw(ellipse);
        }

        if (this_mode == 21)
        {
            sf::ConvexShape hexagon;
            hexagon.setPointCount(6); // Устанавливаем количество вершин (6 для шестиугольника)

            // Радиус шестиугольника
            float radius = mas_param[0];

            // Устанавливаем координаты вершин
            for (int i = 0; i < 6; ++i)
            {
                float angle = i * 2 * 3.14 / 6; // Угол между вершинами
                float x = radius * std::cos(angle);
                float y = radius * std::sin(angle);
                hexagon.setPoint(i, sf::Vector2f(x, y));
            }

            hexagon.setFillColor(sf::Color::Transparent); // Задаем цвет заливки
            hexagon.setOutlineColor(this_color); // Задаем цвет контура
            hexagon.setOutlineThickness(2); // Задаем толщину контура
            hexagon.setPosition(mas_param[1], mas_param[2]);
            serverWindow.draw(hexagon);
        }
        if (this_mode == 27)
        {
            sf::ConvexShape hexagon2;
            hexagon2.setPointCount(6); // Устанавливаем количество вершин (6 для шестиугольника)

            // Радиус шестиугольника
            float radius = mas_param[0];

            // Устанавливаем координаты вершин
            for (int i = 0; i < 6; ++i)
            {
                float angle = i * 2 * 3.14 / 6; // Угол между вершинами
                float x = radius * std::cos(angle);
                float y = radius * std::sin(angle);
                hexagon2.setPoint(i, sf::Vector2f(x, y));
            }

            hexagon2.setFillColor(this_color); // Задаем цвет заливки
            hexagon2.setOutlineColor(this_color); // Задаем цвет контура
            hexagon2.setOutlineThickness(2); // Задаем толщину контура
            hexagon2.setPosition(mas_param[1], mas_param[2]);
            serverWindow.draw(hexagon2);
        }
        if (this_mode == 33)
        {

            sf::RectangleShape square(sf::Vector2f(mas_param[2], mas_param[2]));
            square.setPosition(mas_param[0], mas_param[1]);//Квадрат
            square.setFillColor(sf::Color::Transparent); //Заливка без цвета
            square.setOutlineColor(this_color);
            square.setOutlineThickness(2.0f);
            serverWindow.draw(square);
        }
        if (this_mode == 37)
        {
            sf::RectangleShape square2(sf::Vector2f(mas_param[2], mas_param[2]));
            square2.setPosition(mas_param[0], mas_param[1]);//Квадрат
            square2.setFillColor(this_color); //Заливка цвета
            serverWindow.draw(square2);
        }
        if (this_mode == 41)
        {
            sf::CircleShape circle;
            float radius = mas_param[2];
            circle.setRadius(radius);

            circle.setPosition(mas_param[0], mas_param[1]);

            circle.setFillColor(sf::Color::Transparent); //Заливка без цвета
            circle.setOutlineColor(this_color);
            circle.setOutlineThickness(2.0f);
            serverWindow.draw(circle);
        }
        if (this_mode == 45)
        {
            sf::CircleShape circle2;
            float radius = mas_param[2];
            circle2.setRadius(radius);

            circle2.setPosition(mas_param[0], mas_param[1]);

            circle2.setFillColor(this_color); //Заливка без цвета
            serverWindow.draw(circle2);
        }
        if (this_mode == 49)
        {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(mas_param[0], mas_param[1]), this_color),    // начальная точка
                sf::Vertex(sf::Vector2f(mas_param[2], mas_param[3]), this_color)    // конечная точка
            };
            serverWindow.draw(line, 2, sf::Lines);
        }
        if (this_mode == 54)
        {
            sf::Text text2;
            text2.setPosition(mas_param[0], mas_param[1]);
            text2.setCharacterSize(mas_param[2]);
            text2.setFont(font);
            text2.setFillColor(this_color);
            text2.setString(mas_param2[1]);
            serverWindow.draw(text2);
        }
        if (this_mode == 59)
        {
            sf::Texture texture3;
            if (!texture3.loadFromFile(exep + "\\your_image\\" + mas_param2[0] + ".png")){
            //if (!texture3.loadFromFile(exep + "\\your_image\\" + mas_param2[0] + ".png")) {
                // Обработка ошибки загрузки текстуры
                std::cerr << "Ошибка загрузки текстуры!" << std::endl;
                return -1;
            }
            sf::Sprite sprite3(texture3);
            sprite3.setPosition(mas_param[0], mas_param[1]);
            serverWindow.draw(sprite3);
        }
        if (this_mode == 62) {
            backgroundColor = this_color;
        }
        mutex.unlock();
        serverWindow.display();
    }

    return 0;
}