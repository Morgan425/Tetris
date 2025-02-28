#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <ctime>
#include <format>


/// execute command: g++ -std=c++20 -o tetris Tetris.cpp -lsfml-graphics -lsfml-window -lsfml-system



sf::RenderWindow window;

std::vector<char> Names = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};

std::vector<sf::Texture> Minos_Textures(7); // = {I_mino, J_mino, L_mino, O_mino, S_mino, T_mino, Z_mino};
sf::Texture &I_mino = Minos_Textures[0];
sf::Texture &J_mino = Minos_Textures[1];
sf::Texture &L_mino = Minos_Textures[2];
sf::Texture &O_mino = Minos_Textures[3];
sf::Texture &S_mino = Minos_Textures[4];
sf::Texture &T_mino = Minos_Textures[5];
sf::Texture &Z_mino = Minos_Textures[6];

std::vector<std::vector<sf::Texture>> Textures(7, std::vector<sf::Texture>(4));

sf::Texture &I_Piece_0 = Textures[0][0];
sf::Texture &I_Piece_1 = Textures[0][1];
sf::Texture &I_Piece_2 = Textures[0][2];
sf::Texture &I_Piece_3 = Textures[0][3];

sf::Texture &J_Piece_0 = Textures[1][0];
sf::Texture &J_Piece_1 = Textures[1][1];
sf::Texture &J_Piece_2 = Textures[1][2];
sf::Texture &J_Piece_3 = Textures[1][3];

sf::Texture &L_Piece_0 = Textures[2][0];
sf::Texture &L_Piece_1 = Textures[2][1];
sf::Texture &L_Piece_2 = Textures[2][2];
sf::Texture &L_Piece_3 = Textures[2][3];

sf::Texture &O_Piece_0 = Textures[3][0];
sf::Texture &O_Piece_1 = Textures[3][1];
sf::Texture &O_Piece_2 = Textures[3][2];
sf::Texture &O_Piece_3 = Textures[3][3];

sf::Texture &S_Piece_0 = Textures[4][0];
sf::Texture &S_Piece_1 = Textures[4][1];
sf::Texture &S_Piece_2 = Textures[4][2];
sf::Texture &S_Piece_3 = Textures[4][3];

sf::Texture &T_Piece_0 = Textures[5][0];
sf::Texture &T_Piece_1 = Textures[5][1];
sf::Texture &T_Piece_2 = Textures[5][2];
sf::Texture &T_Piece_3 = Textures[5][3];

sf::Texture &Z_Piece_0 = Textures[6][0];
sf::Texture &Z_Piece_1 = Textures[6][1];
sf::Texture &Z_Piece_2 = Textures[6][2];
sf::Texture &Z_Piece_3 = Textures[6][3];

std::vector<std::vector<int>> I_shape{{4, 4, 5, 6, 7}, {4, 2, 6, 10, 14}, {4, 8, 9, 10, 11}, {4, 1, 5, 9, 13}};
std::vector<std::vector<int>> J_shape{{3, 0, 3, 4, 5}, {3, 1, 2, 4, 7}, {3, 3, 4, 5, 8}, {3, 1, 4, 6, 7}};
std::vector<std::vector<int>> L_shape{{3, 2, 3, 4, 5}, {3, 1, 4, 7, 8}, {3, 3, 4, 5, 6}, {3, 0, 1, 4, 7}};
std::vector<std::vector<int>> O_shape{{2, 0, 1, 2, 3}, {2, 0, 1, 2, 3}, {2, 0, 1, 2, 3}, {2, 0, 1, 2, 3}};
std::vector<std::vector<int>> S_shape{{3, 1, 2, 3, 4}, {3, 1, 4, 5, 8}, {3, 4, 5, 6, 7}, {3, 0, 3, 4, 7}};
std::vector<std::vector<int>> T_shape{{3, 1, 3, 4, 5}, {3, 1, 4, 5, 7}, {3, 3, 4, 5, 7}, {3, 1, 3, 4, 7}};
std::vector<std::vector<int>> Z_shape{{3, 0, 1, 4, 5}, {3, 2, 4, 5, 7}, {3, 3, 4, 7, 8}, {3, 1, 3, 4, 6}};
std::vector<std::vector<std::vector<int>>> Shapes{I_shape, J_shape, L_shape, O_shape, S_shape, T_shape, Z_shape};



void set_T_Position(sf::Sprite& sprite, int row, int col){
    col--;

    int x0 = 599;
    int y0 = 1202;

    int x = x0 + 50*col;
    int y = y0 - 50*row;

    sprite.setPosition(x, y);
}

void print_vect(std::vector<int> vect){
    std::cout << "{";
    for (int i = 0; i < vect.size(); i++){
        std::cout << vect[i] << ", ";
    }
    std::cout << "}" << std::endl;
}



class Matris{
    public:

    int n_rows;
    int n_cols;
    int bucket;
    std::vector<int> Vector;

    Matris(int n_rows, int n_cols, std::vector<int> Vector_arg, int bucket = 0): n_rows{n_rows}, n_cols{n_cols}, Vector{Vector_arg}, bucket{bucket}{

        if (Vector.size() != n_rows*n_cols){
            std::cout << "Error:Matrice_Size_Error: "<< Vector.size() << "!=" << n_rows*n_cols << std::endl;
            exit(1);
        }

        if (bucket > 0){
            std::vector<int> New_vector((n_rows + bucket) * (n_cols + 2*bucket), 0);
            for (int row = 1; row <= n_rows; row++){
                for (int col = 1; col <= n_cols; col ++){
                int new_row = row - 1 + bucket;
                int new_col = col - 1 + bucket;
                int new_index = new_row * (n_cols + 2*bucket) + new_col;
                New_vector[new_index] = 7;//Vector[(row - 1) * n_cols + col - 1];
                Vector = New_vector;
                }
            }
        }
    }


    int& operator[](std::pair<int,int> coords){
        int k = (coords.first - 1 + bucket) * (n_cols + 2*bucket) + (coords.second - 1 + bucket);
        return Vector[k];
    }

    Matris subMatris(int size, std::pair<int,int> anchor){
        int i = anchor.first - (size - 1);
        int j = anchor.second;
        std::vector<int> Sub_vector(size * size);

        for (int row = 0; row < size; row++){
            for (int col = 0; col < size; col++){
                Sub_vector[row * size + col] = this->operator[]({i + row, j + col});
            }
        }
        Matris submatris(size, size, Sub_vector);
        return submatris;
    }


    const void print(){
        std::cout << "{";
        for (int i = n_rows + bucket; i >= 1 - bucket; i--){
            std::cout << "{";
            for (int j = 1 - bucket; j<= n_cols + bucket; j++){
                std::cout << this->operator[](std::pair<int,int> {i, j}) << "; ";
            }
            std::cout << "}";
            if (i > 1 - bucket){
                std::cout << std::endl;
            }
        }
        std::cout << "}" << std::endl;
    }


    void clear_line(std::vector<int> rows, sf::RenderWindow& window){

        for (int l = 0; l < rows.size(); l++){
            int row = rows[l] - l;
            int start = (row - 1 + bucket) * (n_cols + 2*bucket) + 1;
            int end = (row  + bucket) * (n_cols + 2*bucket) + 1;
            std::move(Vector.begin() + end, Vector.end(), Vector.begin() + start);

            for (int k = 0; k < bucket; k++){
                Vector[(n_rows - 1 + bucket) * (n_cols + 2*bucket) + k] = 0;
            }

            for (int k = 0; k < n_cols; k++){
                Vector[(n_rows - 1 + bucket) * (n_cols + 2*bucket) + bucket + k] = 7;
            }

            for (int k = 0; k < bucket; k++){
                Vector[(n_rows - 1 + bucket) * (n_cols + 2*bucket) + bucket + n_cols] = 0;
            }
        }
        
    }





};




class Piece{
    public:
    int type;
    int orientation;
    std::pair<int, int> anchor;
    sf::Sprite sprite;
    std::vector<int> shape;
    char name;

    Piece(int type, int orientation, std::pair<int, int> anchor): type{type}, orientation{orientation}, anchor{anchor} {
        sprite.setTexture(Textures[type][orientation]);
        set_T_Position(sprite, anchor.first, anchor.second);
        shape = Shapes[type][orientation];
        name = Names[type];
    }

    Piece(const Piece& p){
        this->type = p.type;
        this->orientation=p.orientation;
        sprite.setTexture(Textures[p.type][p.orientation]);
        this->anchor = p.anchor;
        set_T_Position(sprite, anchor.first, anchor.second);
        shape = Shapes[type][orientation];
        name = Names[type];
    }

    void updt(){
        sprite.setTexture(Textures[type][orientation]);
        set_T_Position(sprite, anchor.first, anchor.second);
        shape = Shapes[type][orientation];
    }


    void draw(sf::RenderWindow& window){

        window.draw(this->sprite);
        // std::cout << "Drawing sprite at position: " << sprite.getPosition().x << ", " << sprite.getPosition().y << std::endl;
    }


    void rotate_right(){

        if (orientation == 3){ 
            orientation = 0;
            }
        else{
            orientation++;
        }
        this->updt();
    }

    void rotate_left(){

        if (orientation == 0){ 
            orientation = 3;
            }
        else{
            orientation--;
        }
        this->updt();
    }

    void move_left(){
        anchor.second--;
        this->updt();
    }

    void move_right(){
        anchor.second++;
        this->updt();
    }

    void move_down(){
        anchor.first--;
        this->updt();
    }


    bool is_position_possible(Matris sub_stack, std::pair<int,int> anchor){
        int size = this->shape[0];
        for (int k = 1; k < 5; k++){
            int i = this->shape[k];
            int row = size - i/size;
            int col = i % size + 1;
            if (sub_stack[{row, col}] < 7){
                return false;
            }            
        }
        return true;
    }

    bool can_move_left(Matris& stack){
        int size = this->shape[0];
        auto sub_stack = stack.subMatris(size, {this->anchor.first, this->anchor.second - 1});
        return this->is_position_possible(sub_stack, {this->anchor.first, this->anchor.second - 1});
    }

    bool can_move_right(Matris& stack){
        int size = this->shape[0];
        auto sub_stack = stack.subMatris(size, {this->anchor.first, this->anchor.second + 1});
        return this->is_position_possible(sub_stack, {this->anchor.first, this->anchor.second + 1});
    }

    bool can_move_down(Matris& stack){
        int size = this->shape[0];
        auto sub_stack = stack.subMatris(size, {this->anchor.first - 1, this->anchor.second});
        return this->is_position_possible(sub_stack, {this->anchor.first - 1, this->anchor.second});
    }


    bool can_rotate_right(Matris& stack){
        this->rotate_right();
        int size = this->shape[0];
        auto sub_stack = stack.subMatris(size, this->anchor);
        auto r = this->is_position_possible(sub_stack, this->anchor);
        this->rotate_left();
        return r;
    }

    bool can_rotate_left(Matris& stack){
        this->rotate_left();
        int size = this->shape[0];
        auto sub_stack = stack.subMatris(size, this->anchor);
        auto r = this->is_position_possible(sub_stack, this->anchor);
        this->rotate_right();
        return r;
    }






    void add_to_stack(Matris& stack){
        int size = this->shape[0];
        for (int k = 1; k < 5; k++){
            int i = this->shape[k];
            int row =  -i/size;
            int col = i % size;
            stack[{this->anchor.first + row, this->anchor.second + col}] = this->type;
        }
    }


    const sf::Sprite& getSprite() const {
        return sprite;
    }


};









void draw_stack(Matris& matrix, sf::RenderWindow& window, std::vector<sf::Texture>& Minos_Textures, int bucket = 0){
    int top = 0;
    if (bucket > 0){
        top = 4;
    }
    sf::Sprite mino;
    for (int row = 1 - bucket; row <= 20 + top; ++row){
        for (int col = 1 - bucket; col <= 10 + bucket; ++col){
            int type = matrix[{row, col}];
            if (type <7){
                mino.setTexture(Minos_Textures[type]);
                set_T_Position(mino, row, col);
                window.draw(mino);
                }
        }
    }
}


Piece Spawn_Falling_Piece(int type){
    std::pair<int,int> anchor = {22,4};
    if (type == 3){
        anchor = {22,5};
    }

    Piece new_piece(type, 0, anchor);
    return new_piece;
}





sf::Text Create_text(std::string message, int x, int y, const sf::Font& font, int size = 50, sf::Color color = sf::Color::White){
    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(sf::Text::Bold);
    text.setPosition(x, y);
    return text;
}


int randint(int n){
    std::time_t time = std::time(nullptr);
    return (rand() + time) % n;
}


void set_next_position(sf::Sprite& sprite, int next){
    sprite.setTexture(Textures[next][0]);
    sprite.setScale(1, 1);   
    int x = 1225;
    int y = 630;
    if (next == 0){
    sprite.setTexture(Textures[0][1]);
    sprite.setScale(0.75, 0.75);
    }
    else if (next == 3){
        x += 25;
        y += 25;
    }
    sprite.setPosition(x, y);
}



/// Fonction générée par Chat-GPT juste pour rescale la fenêtre en fonction de la taille d'écran

void scaleView(sf::RenderWindow& window, int resolution_ecran) {

    float scaleFactor = resolution_ecran / float(1440);
    std::cout << scaleFactor << std::endl;
    // Get the current window size
    sf::Vector2u currentSize = window.getSize();

    // Resize the window
    window.setSize(sf::Vector2u(currentSize.x * scaleFactor, currentSize.y * scaleFactor));

    // Create and apply a correctly scaled view
    sf::View view(sf::FloatRect(0, 0, currentSize.x, currentSize.y));
    view.setViewport(sf::FloatRect(0, 0, 1, 1)); // Ensure it fills the window
    window.setView(view);
}

/// utilisée ligne 573








int main() {


    I_mino.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/I_Piece/I_mino.png");
    J_mino.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/J_Piece/J_mino.png");
    L_mino.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/L_Piece/L_mino.png");
    O_mino.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/O_Piece/O_mino.png");
    S_mino.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/S_Piece/S_mino.png");
    T_mino.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/T_Piece/T_mino.png");
    Z_mino.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/Z_Piece/Z_mino.png");
    std::vector<sf::Texture> Minos_Textures = {I_mino, J_mino, L_mino, O_mino, S_mino, T_mino, Z_mino};

    I_Piece_0.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/I_Piece/I_Piece_0.png");
    I_Piece_1.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/I_Piece/I_Piece_1.png");
    I_Piece_2.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/I_Piece/I_Piece_2.png");
    I_Piece_3.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/I_Piece/I_Piece_3.png");

    J_Piece_0.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/J_Piece/J_Piece_0.png");
    J_Piece_1.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/J_Piece/J_Piece_1.png");
    J_Piece_2.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/J_Piece/J_Piece_2.png");
    J_Piece_3.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/J_Piece/J_Piece_3.png");

    L_Piece_0.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/L_Piece/L_Piece_0.png");
    L_Piece_1.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/L_Piece/L_Piece_1.png");
    L_Piece_2.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/L_Piece/L_Piece_2.png");
    L_Piece_3.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/L_Piece/L_Piece_3.png");

    O_Piece_0.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/O_Piece/O_Piece_0.png");
    O_Piece_1.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/O_Piece/O_Piece_1.png");
    O_Piece_2.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/O_Piece/O_Piece_2.png");
    O_Piece_3.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/O_Piece/O_Piece_3.png");

    S_Piece_0.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/S_Piece/S_Piece_0.png");
    S_Piece_1.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/S_Piece/S_Piece_1.png");
    S_Piece_2.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/S_Piece/S_Piece_2.png");
    S_Piece_3.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/S_Piece/S_Piece_3.png");

    T_Piece_0.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/T_Piece/T_Piece_0.png");
    T_Piece_1.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/T_Piece/T_Piece_1.png");
    T_Piece_2.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/T_Piece/T_Piece_2.png");
    T_Piece_3.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/T_Piece/T_Piece_3.png");

    Z_Piece_0.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/Z_Piece/Z_Piece_0.png");
    Z_Piece_1.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/Z_Piece/Z_Piece_1.png");
    Z_Piece_2.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/Z_Piece/Z_Piece_2.png");
    Z_Piece_3.loadFromFile("/home/morgan425/Tetris/Tetris_Pieces/Z_Piece/Z_Piece_3.png");

    std::vector<sf::Texture> I_Piece = {I_Piece_0, I_Piece_1, I_Piece_2, I_Piece_3};
    std::vector<sf::Texture> J_Piece = {J_Piece_0, J_Piece_1, J_Piece_2, J_Piece_3};
    std::vector<sf::Texture> L_Piece = {L_Piece_0, L_Piece_1, L_Piece_2, L_Piece_3};
    std::vector<sf::Texture> O_Piece = {O_Piece_0, O_Piece_1, O_Piece_2, O_Piece_3};
    std::vector<sf::Texture> S_Piece = {S_Piece_0, S_Piece_1, S_Piece_2, S_Piece_3};
    std::vector<sf::Texture> T_Piece = {T_Piece_0, T_Piece_1, T_Piece_2, T_Piece_3};
    std::vector<sf::Texture> Z_Piece = {Z_Piece_0, Z_Piece_1, Z_Piece_2, Z_Piece_3};

    std::vector<std::vector<sf::Texture>> Textures = {I_Piece, J_Piece, L_Piece, O_Piece, S_Piece, T_Piece, Z_Piece};
    

    std::vector<double> Speeds = {1.2, 1.4, 1.6, 1.8, 2, 2.5, 3.3, 4.5, 7.5, 10, 12, 12, 12, 15, 15, 15,  20, 20, 20, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 60};
    std::vector<int> score_per_finishes = {40, 100, 300, 1200};

    sf::Font font;
    if (!font.loadFromFile("/home/morgan425/Tetris/nintendo-nes-font.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    sf::Font font_stats;
    if (!font_stats.loadFromFile("/home/morgan425/Tetris/NintendoNESFont_stats.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    auto level_txt      = Create_text("LEVEL",      1203, 890, font);
    auto next_txt       = Create_text("NEXT",       1203, 545, font);
    auto Tetris_txt     = Create_text("TETRIS",     150,  96,  font);
    auto statistics_txt = Create_text("STATISTICS", 120,  342, font_stats, 40);
    auto score_txt      = Create_text("SCORE",      1203, 248, font);
    auto top_txt        = Create_text("TOP",        1203, 90,  font);
    auto lines_txt      = Create_text("LINES-",     640,  45,  font);

    int Score = 0;
    int Top = 0;
    int Lines = 0;
    int Level = 0;
    std::vector<int> Statistics {0,0,0,0,0,0,0};

    

    auto score_number   = Create_text(std::format("{:06}", Score), 1203, 300, font);
    auto top_number     = Create_text(std::format("{:06}", Top),   1203, 140, font);
    auto level_number   = Create_text(std::format("{:02}", Level), 1303, 950, font);
    auto lines_number   = Create_text(std::format("{:03}", Lines), 960,  45,  font);

    std::vector<sf::Text> Statistics_number(7);
    for (int type = 0; type < 7; type++){
        Statistics_number[type] = Create_text(std::format("{:03}", Statistics[type]), 300,  485 + type * 100,  font, 50, sf::Color::Red);
    }


    sf::Texture bg_Texture;
    bg_Texture.loadFromFile("/home/morgan425/Tetris/Tetris_background.png");
    sf::Sprite bg;
    bg.setTexture(bg_Texture);

    sf::Texture bg_top_Texture;
    bg_top_Texture.loadFromFile("/home/morgan425/Tetris/Tetris_top.png");
    sf::Sprite bg_top;
    bg_top.setTexture(bg_top_Texture);
    bg_top.setPosition(599, 0);

    std::vector<sf::Sprite> Statistics_sprite(7);

    for (int type = 0; type < 7; type++){
        Statistics_sprite[type].setTexture(Textures[type][0]);
        Statistics_sprite[type].setPosition(140, 475 + type * 100);
        Statistics_sprite[type].setScale(0.7, 0.7);
    }
    Statistics_sprite[0].setPosition(127, 460);
    Statistics_sprite[3].setPosition(153, 475 + 3 * 100);

    // Créer une fenêtre
    sf::RenderWindow window(sf::VideoMode(1600, 1250), "Tetris", sf::Style::Close);

    // Put screen resolution here
    scaleView(window, 1080);

    std::vector<int> stack(240, 7);
    Matris Stack(24, 10, stack, 3);

    int Falling_type = randint(7);
    auto Falling_Piece = Spawn_Falling_Piece(Falling_type);
    Falling_Piece.draw(window);

    int next = randint(7);
    sf::Sprite next_sprite;
    next_sprite.setTexture(Textures[next][0]);
    next_sprite.setPosition(1203, 700);
    set_next_position(next_sprite, next);

    int soft_drop = 0;

    std::time_t chrono = std::time(nullptr);

    bool game_over = false;

    // sf::Music music;
    // if (!music.openFromFile("/home/morgan425/Tetris/03.-A-Type-Music-_Korobeiniki_.wav")) {
    //    std::cerr << "Error loading music file!" << std::endl;
    //    return -1;
    // }
    // music.setLoop(true);
    // music.play();
    // bool is_unmute = false;

    // Boucle principale
    while (window.isOpen()) {

        for (int col = 1; col<= 10; col++){
            if (Stack[{21, col}] < 7){
                game_over = true;
            }
        }
        if(game_over){
            break;
        }
    

        std::time_t time = std::time(nullptr);
        auto delta_time = difftime(time, chrono);
        if (difftime(time, chrono) > 1 / Speeds[Level]){

            if (Falling_Piece.can_move_down(Stack)){
                Falling_Piece.move_down();
            }
            else{
                Score += soft_drop;
                soft_drop = 0;
                Falling_Piece.add_to_stack(Stack);
                Falling_Piece = Spawn_Falling_Piece(next);
                Statistics[next] += 1;
                Statistics_number[next].setString(std::format("{:03}", Statistics[next]));
                next = randint(7);
                set_next_position(next_sprite, next);

                std::vector<int> Finished_lines = {};

                for (int row = 1; row <= 20; row++){
                    int c = 0;
                    for(int col = 1; col <= 10; col++){
                        if (Stack[{row, col}] > 6){
                            break;
                        }
                        c++;
                    }
                    if (c == 10){
                        Finished_lines.push_back(row);
                    }
                }
                int number = Finished_lines.size();
                if (number > 0){
                    Score += score_per_finishes[number - 1] * (Level + 1);
                    Lines += number;
                    Level = Lines / 10;

                    Stack.clear_line(Finished_lines, window);
                }
            }
            chrono = std::time(nullptr);
        }

        score_number.setString(std::format("{:06}", Score));
        level_number.setString(std::format("{:02}", Level));
        lines_number.setString(std::format("{:03}", Lines));

        window.clear();

        window.draw(bg);

        draw_stack(Stack, window, Minos_Textures);

        Falling_Piece.draw(window);
        window.draw(bg_top);

        window.draw(level_txt);
        window.draw(next_txt);
        window.draw(statistics_txt);
        window.draw(top_txt);
        window.draw(score_txt);
        window.draw(Tetris_txt);
        window.draw(lines_txt);

        window.draw(lines_number);
        window.draw(top_number);
        window.draw(score_number);
        window.draw(level_number);

        for (int type = 0; type < 7; type++){
            window.draw(Statistics_sprite[type]);
        }

        window.draw(next_sprite);

        for (int type = 0; type < 7; type++){
            window.draw(Statistics_number[type]);
        }

        
        std::time_t time_event = std::time(nullptr);

        sf::Event event;
        while (window.pollEvent(event) && difftime(time_event, chrono) < 1 / Speeds[Level]) {
            std::time_t time = std::time(nullptr);
            
        auto delta_time = difftime(time, chrono);
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
                if (event.key.code == sf::Keyboard::Q && Falling_Piece.can_rotate_left(Stack)){
                    Falling_Piece.rotate_left();
                }

                else if ((event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Space) && Falling_Piece.can_rotate_right(Stack)){
                    Falling_Piece.rotate_right();
                }

                else if (event.key.code == sf::Keyboard::Right && Falling_Piece.can_move_right(Stack)){
                    Falling_Piece.move_right();
                }

                else if (event.key.code == sf::Keyboard::Left && Falling_Piece.can_move_left(Stack)){
                    Falling_Piece.move_left();
                }

                else if (event.key.code == sf::Keyboard::Down && Falling_Piece.can_move_down(Stack)){
                    Falling_Piece.move_down();
                    soft_drop++;
                }
            }

            // else if (event.type == sf::Event::KeyReleased){
            //    if (event.key.code == sf::Keyboard::M){
            //        is_unmute = !is_unmute;
            //        if(is_unmute){
            //            music.pause();
            //        }
            //        else{
            //            music.play();
            //        }
            //    }
            // }

        }

        window.display();
    }

    return 0;
}
    
