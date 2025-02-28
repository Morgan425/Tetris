#include <SFML/Graphics.hpp>


/// Pour compiler : 
/// g++ -o test test_install.cpp  -lsfml-graphics -lsfml-window -lsfml-system

sf::Texture texture_0;

class Piece{
    public:
    int type;
    int orientation;
    std::pair<int, int> anchor;
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<int> shape;
    char name;

    Piece(int type, int orientation, std::pair<int, int> anchor): type{type}, orientation{orientation}, anchor{anchor} {
        texture = texture_0;
        sprite.setTexture(texture);
        sprite.setPosition(anchor.first, anchor.second);
    }

    void draw(sf::RenderWindow& window){
        window.draw(this->sprite);
    // std::cout << "Drawing sprite at position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
    }
};






int main() {
    texture_0.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/I_Piece/I_Piece_0.png");
    // Créer une fenêtre de 800x600 pixels
    sf::RenderWindow window(sf::VideoMode(800, 600), "Validation SFML");


    Piece piece(0, 0, {375, 275});

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Effacer l'écran
        window.clear(sf::Color::Black);

        // Dessiner le cercle
        piece.draw(window);

        // Afficher le contenu
        window.display();
    }

    return 0;
}

