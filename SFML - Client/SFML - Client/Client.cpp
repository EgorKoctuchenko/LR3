#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <clocale>
#include <filesystem>
#include <direct.h>
#include <Windows.h>

using namespace std;
// ����
char pathe1[MAX_PATH];

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(1251);

    setlocale(LC_ALL, "ru");
    // ��� ����� ��������?
    int mode = 0;
    int sec_mode = 0;

    // ���������� ���� � ������
    _getcwd(pathe1, MAX_PATH);
    std::string exep(pathe1);

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML UDP ������");

    sf::UdpSocket socket;

    // �������� ������
    sf::Texture buttonTexture1;
    if (!buttonTexture1.loadFromFile(exep + "\\butons\\rect.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button1(buttonTexture1);

    sf::Texture buttonTexture2;
    if (!buttonTexture2.loadFromFile(exep + "\\butons\\rect2.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button2(buttonTexture2);

    sf::Texture buttonTexture3;
    if (!buttonTexture3.loadFromFile(exep + "\\butons\\ellips.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button3(buttonTexture3);

    sf::Texture buttonTexture4;
    if (!buttonTexture4.loadFromFile(exep + "\\butons\\ellips2.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button4(buttonTexture4);

    sf::Texture buttonTexture5;
    if (!buttonTexture5.loadFromFile(exep + "\\butons\\hex.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button5(buttonTexture5);

    sf::Texture buttonTexture6;
    if (!buttonTexture6.loadFromFile(exep + "\\butons\\hex2.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button6(buttonTexture6);

    sf::Texture buttonTexture7;
    if (!buttonTexture7.loadFromFile(exep + "\\butons\\square.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button7(buttonTexture7);

    sf::Texture buttonTexture8;
    if (!buttonTexture8.loadFromFile(exep + "\\butons\\square2.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button8(buttonTexture8);

    sf::Texture buttonTexture9;
    if (!buttonTexture9.loadFromFile(exep + "\\butons\\circle.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button9(buttonTexture9);

    sf::Texture buttonTexture10;
    if (!buttonTexture10.loadFromFile(exep + "\\butons\\circle2.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button10(buttonTexture10);

    sf::Texture buttonTexture11;
    if (!buttonTexture11.loadFromFile(exep + "\\butons\\line.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button11(buttonTexture11);

    sf::Texture buttonTexture12;
    if (!buttonTexture12.loadFromFile(exep + "\\butons\\text.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button12(buttonTexture12);

    sf::Texture buttonTexture13;
    if (!buttonTexture13.loadFromFile(exep + "\\butons\\img.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button13(buttonTexture13);

    sf::Texture buttonTexture14;
    if (!buttonTexture14.loadFromFile(exep + "\\butons\\clear.png")) {
        std::cerr << "������ ��� �������� �������� ������" << std::endl;
        return -1;
    }
    sf::Sprite button14(buttonTexture14);

    // ���������������� ������ (�������)
    button1.setPosition(60, 655);
    button2.setPosition(195, 655);
    button3.setPosition(325, 655);
    button4.setPosition(460, 655);
    button5.setPosition(595, 655);
    button6.setPosition(730, 655);
    button7.setPosition(865, 655);
    
    button8.setPosition(60, 855);
    button9.setPosition(195, 855);
    button10.setPosition(325, 855);
    button11.setPosition(460, 855);
    button12.setPosition(595, 855);
    button13.setPosition(730, 855);
    button14.setPosition(865, 855);


    // IP-����� � ���� �������, � �������� �� ����� ������������
    sf::IpAddress serverAddress = "127.0.0.1";
    unsigned short serverPort = 12345;

    // ������� ���� ����� ��� ��������� � �����
    sf::RectangleShape inputBox(sf::Vector2f(500, 30));
    inputBox.setPosition(250, 500);
    inputBox.setFillColor(sf::Color::White);

    //�����
    sf::Font font;
    if (!font.loadFromFile(exep + "\\font\\arial.ttf")) {
        std::cerr << "������ ��� �������� ������" << std::endl;
        return -1;
    }
    
    //������ ��������
    sf::Text inputText;
    inputText.setFont(font); // ���������� ����� �� ���������
    inputText.setCharacterSize(20);
    inputText.setPosition(250, 500);
    inputText.setFillColor(sf::Color::Black);
    std::string currentText;

    //�����-����������
    sf::Text InfoT;
    InfoT.setFont(font);
    InfoT.setCharacterSize(36);
    InfoT.setFillColor(sf::Color::White);
    InfoT.setString("Your Parametrs");

    sf::Text InfoT2;
    InfoT2.setFont(font);
    InfoT2.setCharacterSize(36);
    InfoT2.setFillColor(sf::Color::White);
    InfoT2.setString("Your Choise: None");
    InfoT2.setPosition(50, 30);

    //���������� �����
    sf::FloatRect textBounds;
    textBounds = InfoT.getLocalBounds();
    InfoT.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    InfoT.setPosition(window.getSize().x / 2, 550);

    // �������� ���� ����������
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                // ���������, ���� �� ������� �� ������
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //�������������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 1;
                    sec_mode = 1;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //����������� �������������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 2;
                    sec_mode = 6;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button3.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 3;
                    sec_mode = 11;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button4.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //����������� ������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 4;
                    sec_mode = 16;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button5.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //����������� �������������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 5;
                    sec_mode = 21;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button6.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //����������� ����������� �������������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 6;
                    sec_mode = 27;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button7.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //�������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 7;
                    sec_mode = 33;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button8.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //����������� �������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 8;
                    sec_mode = 37;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button9.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //����
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 9;
                    sec_mode = 41;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button10.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //����������� ����
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 10;
                    sec_mode = 45;
                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button11.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //�����
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 11;
                    sec_mode = 49;
                    std::cout << sec_mode;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button12.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //�����
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 12;
                    sec_mode = 54;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button13.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //�����������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 13;
                    sec_mode = 59;

                }
                if (event.mouseButton.button == sf::Mouse::Left &&
                    button14.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    //��������
                    // ���������� ��������� �� ������
                    std::string message = currentText;
                    mode = 14;
                    sec_mode = 62;

                }
            }

            // ��������� ����� ������
            if (mode != 0) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 8 && !currentText.empty()) {  // Backspace
                        currentText.pop_back();
                    }
                    else if (event.text.unicode == 13) {  // Enter
                        // ���������� ��������� �� ������
                        if (!currentText.empty()) {
                            string buf = to_string(sec_mode);
                            std::string mesage = (buf + " = " + currentText);
                            sf::Packet packet;
                            if (socket.send(mesage.c_str(), mesage.size() + 1, serverAddress, serverPort) != sf::Socket::Done) {
                                std::cerr << "������ ��� �������� ������" << std::endl;
                            }
                            else {
                                std::cout << "��������� ������� ���������� �� ������: " << mesage << std::endl;
                            }
                            currentText.clear();  // ������� ������� �����
                        }
                    }
                    else if (event.text.unicode < 128) {
                        currentText += static_cast<char>(event.text.unicode);
                    }
                    inputText.setString(currentText);
                }
            }
        }

        switch (mode)
        {
        case 1:
            InfoT2.setString("Your Choise: Rectangle");
            break;
        case 2:
            InfoT2.setString("Your Choise: Filled Rectangle");
            break;
        case 3:
            InfoT2.setString("Your Choise: Ellipse");
            break;
        case 4:
            InfoT2.setString("Your Choise: Filled Ellipse");
            break;
        case 5:
            InfoT2.setString("Your Choise: Hexagon");
            break;
        case 6:
            InfoT2.setString("Your Choise: Filled Hexagon");
            break;
        case 7:
            InfoT2.setString("Your Choise: Square");
            break;
        case 8:
            InfoT2.setString("Your Choise: Filled Square");
            break;
        case 9:
            InfoT2.setString("Your Choise: Circle");
            break;
        case 10:
            InfoT2.setString("Your Choise: Filled Circle");
            break;
        case 11:
            InfoT2.setString("Your Choise: Line");
            break;
        case 12:
            InfoT2.setString("Your Choise: Text");
            break;
        case 13:
            InfoT2.setString("Your Choise: Image");
            break;
        case 14:
            InfoT2.setString("Your Choise: Clear");
            break;
        }

        // ������� ����
        window.clear();

        // ������ ������
        window.draw(InfoT2);
        window.draw(InfoT);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button4);
        window.draw(button5);
        window.draw(button6);
        window.draw(button7);
        window.draw(button8);
        window.draw(button9);
        window.draw(button10);
        window.draw(button11);
        window.draw(button12);
        window.draw(button13);
        window.draw(button14);

        window.draw(inputBox);
        window.draw(inputText);

        // ���������� ���������� ����
        window.display();
    }

    return 0;
}