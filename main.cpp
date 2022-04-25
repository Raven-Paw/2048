#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

using std::cout;

int CELL_SIZE = 75;
int cell_array[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
int score = 0;
int largest_value = 2;
bool game = true;
bool move_trigger = true;

struct Position {int x, y;};

std::vector<Position> empty_cell;

// TO-DO
// fix the gameover trigger

// Color Pallete
sf::Color color_array[] = {
        sf::Color(187,173,160),  // background
        sf::Color(205,193,180),  // empty tile
        sf::Color(238,228,218),     // 2    
        sf::Color(238,225,201),     // 4   
        sf::Color(243,178,122),     // 8    
        sf::Color(246,150,100),     // 16  
        sf::Color(247,124,95),  // 32   
        sf::Color(247,95,59),   // 64    
        sf::Color(237,208,114), // 128 
        sf::Color(237,204,98),  // 256  
        sf::Color(237,201,80),  // 512  
        sf::Color(237,197,63)   // 1024 

    };

// Game Over trigger
void game_trigger(){
    int full_cell=0;
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){
            if(cell_array[y][x]!=0){
                full_cell++;
            }
        }
    }

    if(full_cell == 16){
        for (int y = 0; y < 4; y++){
            for (int x = 0; x < 4; x++){
                if(x!=3){
                    if(cell_array[y][x] == cell_array[y][x+1]){game=true; goto jump;}
                    else{game = false;}
                }
            }
        }

        for (int x = 0; x < 4; x++){
            for (int y = 0; y < 4; y++){
                if(y!=3){
                    if(cell_array[y][x] == cell_array[y+1][x]){game=true; goto jump;}
                    else{;game = false;}
                }
            }
        }
    }
    jump:
    if(!game){move_trigger = false;}

}

// Check any empty cell
void Check_empty_cell(){
    int count = 0;
    empty_cell.clear();
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if(cell_array[i][j] == 0){
                empty_cell.push_back({j,i});
                count++;
            }
        }
    }

}

// Add new cell
void fill(){
    if(empty_cell.size() != 0){
    int arr[2] = {2,4};

    int rnd = rand() % empty_cell.size();    // pick random index on empty_cell
    int num = rand() % 2;                    

    cell_array[ empty_cell[rnd].y][empty_cell[rnd].x ] = arr[num]; // pick value between(2,4)
    }
}

// Show the whole display
void show_display(sf::RenderWindow& window, sf::Font font){
    sf::RectangleShape rect;
    sf::Text text;
    text.setFont(font);

    // Background
    rect.setSize(sf::Vector2f(310,310));
    rect.setPosition(sf::Vector2f(20,162));
    rect.setFillColor(color_array[0]);
    window.draw(rect);

    // Draw the rectangle of SCORE
    rect.setSize(sf::Vector2f(100,50));
    rect.setFillColor(sf::Color(187,173,160));
    rect.setPosition(sf::Vector2f(230,80));
    window.draw(rect);

    // print the word "SCORES"
    sf::Text score_t;
    score_t.setFont(font);
    score_t.setString("SCORE");
    score_t.setFillColor(sf::Color(119,110,101));
    score_t.setCharacterSize(10);
    score_t.setStyle(sf::Text::Bold);
    score_t.setPosition(sf::Vector2f(265, 83));
    window.draw(score_t);

    // Display the score
    sf::Text scores;
    scores.setFont(font);
    scores.setFillColor(sf::Color(255,255,255));
    scores.setCharacterSize(20);
    scores.setStyle(sf::Text::Bold);
    
    // change score position depending on the score
    if(score>99999){scores.setPosition(sf::Vector2f(242, 95));}
    else if(score>9999){scores.setPosition(sf::Vector2f(248, 95));}
    else if(score>999){scores.setPosition(sf::Vector2f(258, 95));}
    else if(score>99){scores.setPosition(sf::Vector2f(265, 95));}
    else if(score>9){scores.setPosition(sf::Vector2f(270, 95));}
    else{scores.setPosition(sf::Vector2f(277, 95));}

    scores.setString(std::to_string(score));    // print the score
    window.draw(scores);

    // Draw empty tiles
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){

            rect.setPosition(sf::Vector2f((x*CELL_SIZE)+25, (y*CELL_SIZE)+167));
            rect.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
            rect.setFillColor(color_array[1]);
            rect.setOutlineThickness(-3);
            rect.setOutlineColor(color_array[0]);
            window.draw(rect);

        }
    }

    // Draw the tiles
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){
            if(cell_array[y][x] != 0){
                int color;
                if(cell_array[y][x] > 1024){color = 10;}
                else{color = log2(cell_array[y][x]);}
                
                rect.setPosition(sf::Vector2f((x*CELL_SIZE)+25, (y*CELL_SIZE)+167));
                rect.setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
                rect.setFillColor(color_array[color+1]);
                // rect.setOutlineThickness(-3);
                // rect.setOutlineColor(color_array[0]);
                window.draw(rect);
            }
        }
    }

    // Print the Number on tiles
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){
            if(cell_array[y][x] != 0){
                
                // Change position depending on the number size
                if(cell_array[y][x] > 999){
                    text.setPosition(sf::Vector2f((x*CELL_SIZE)+35, (y*CELL_SIZE)+189));
                }
                else if(cell_array[y][x] > 99){
                    text.setPosition(sf::Vector2f((x*CELL_SIZE)+40, (y*CELL_SIZE)+189));
                }
                else if(cell_array[y][x] > 9){
                    text.setPosition(sf::Vector2f((x*CELL_SIZE)+45, (y*CELL_SIZE)+189));
                }
                else{
                    text.setPosition(sf::Vector2f((x*CELL_SIZE)+55, (y*CELL_SIZE)+189));
                }

                text.setFillColor(sf::Color(119,110,101));
                text.setString(std::to_string(cell_array[y][x]));
                text.setCharacterSize(25);
                window.draw(text);
            }
        }
    }

    // Show Gameover Screen
    if(!game){
        // Draw the orange tint rectangle
        rect.setSize(sf::Vector2f(310,310));
        rect.setPosition(sf::Vector2f(20,162));
        rect.setOutlineThickness(0);
        rect.setFillColor(sf::Color(243,178,122,150));
        window.draw(rect);

        // Print the "GameOver"
        text.setPosition(sf::Vector2f(100, 285));
        text.setFillColor(sf::Color(119,110,101));
        text.setString("Game Over");
        text.setCharacterSize(30);
        window.draw(text);

        // Rectangle New Game
        sf::RectangleShape newgame_r;
        newgame_r.setSize(sf::Vector2f(110,30));
        newgame_r.setPosition(sf::Vector2f(120,325));
        newgame_r.setFillColor(sf::Color(119,110,101));
        window.draw(newgame_r);

        // New Game
        text.setPosition(sf::Vector2f(130, 328));
        text.setFillColor(sf::Color(255,255,255));
        text.setString("New Game");
        text.setCharacterSize(18);
        window.draw(text);
    }

}

// All about movement
void move_mechanics(int dir){
    int move_cell[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    int movecell = 0; 

    switch(dir){
        case 1: // Moving Left
            for(int y=0; y<4; y++){
                for(int x=0; x<4; x++){

                    if(cell_array[y][x] != 0){

                        for(int x2=0; x2<4; x2++){
                            if(x2==x){
                                break;
                            }
                            if((cell_array[y][x] == cell_array[y][x2] && move_cell[y][x2] == 0) && (cell_array[y][x2+1] == 0 || x2+1 == x)){ // same value, cell is untouch, next cell is empty or it is the same position 
                                cell_array[y][x2] += cell_array[y][x];  // Add them together
                                score += cell_array[y][x2];
                                cell_array[y][x] = 0;
                                move_cell[y][x2] = 1;
                                if(cell_array[y][x2] > largest_value){largest_value = cell_array[y][x2];}
                                movecell++;
                                break;
                            }

                            else if(cell_array[y][x2] == 0){ // If the cell is empty
                                cell_array[y][x2] = cell_array[y][x];  // Assign the value to that empty cell
                                cell_array[y][x] = 0;
                                movecell++;
                                break;
                            }
                        }

                    }

                }
            }
            
        break;

        case 2: // Moving Right
            for(int y=0; y<4; y++){
                for(int x=3; x>-1; x--){

                    if(cell_array[y][x] != 0){

                        for(int x2=3; x2>-1; x2--){
                            if(x2==x){
                                break;
                            }
                            if((cell_array[y][x] == cell_array[y][x2] && move_cell[y][x2] == 0) && (cell_array[y][x2-1] == 0 || x2-1 == x)){ // same value, cell is untouch, next cell is empty or it is the same position 
                                cell_array[y][x2] += cell_array[y][x];  // Add them together
                                score += cell_array[y][x2];
                                cell_array[y][x] = 0;
                                move_cell[y][x2] = 1;
                                if(cell_array[y][x2] > largest_value){largest_value = cell_array[y][x2];}
                                movecell++;
                                break;
                            }

                            else if(cell_array[y][x2] == 0){ // If the cell is empty
                                cell_array[y][x2] = cell_array[y][x];  // Assign the value to that empty cell
                                cell_array[y][x] = 0;
                                movecell++;
                                break;
                            }
                        }

                    }

                }
            }
        break;

        case 3: // Moving Up
            for(int x=0; x<4; x++){
                for(int y=0; y<4; y++){

                    if(cell_array[y][x] != 0){

                        for(int y2=0; y2<4; y2++){
                            if(y2==y){
                                break;
                            }
                            
                            if((cell_array[y][x] == cell_array[y2][x] && move_cell[y2][x] == 0) && (cell_array[y2+1][x] == 0 || y2+1 == y)){ // same value, cell is untouch, next cell is empty or it is the same position 
                                cell_array[y2][x] += cell_array[y][x];  // Add them together
                                score += cell_array[y2][x];
                                cell_array[y][x] = 0;
                                move_cell[y2][x] = 1;
                                if(cell_array[y2][x] > largest_value){largest_value = cell_array[y2][x];}
                                movecell++;
                                break;
                            }

                            else if(cell_array[y2][x] == 0){ // If the cell is empty
                                cell_array[y2][x] = cell_array[y][x];  // Assign the value to that empty cell
                                cell_array[y][x] = 0;
                                movecell++;
                                break;
                            }
                        }

                    }

                }
            }
        break;

        case 4: // Moving Down
            for(int x=0; x<4; x++){
                for(int y=3; y>-1; y--){

                    if(cell_array[y][x] != 0){

                        for(int y2=3; y2>-1; y2--){
                            if(y2==y){
                                break;
                            }
                            
                            if((cell_array[y][x] == cell_array[y2][x] && move_cell[y2][x] == 0) && (cell_array[y2-1][x] == 0 || y2-1 == y)){ // same value, cell is untouch, next cell is empty or it is the same position 
                                cell_array[y2][x] += cell_array[y][x];  // Add them together
                                score += cell_array[y2][x];
                                cell_array[y][x] = 0;
                                move_cell[y2][x] = 1;
                                if(cell_array[y2][x] > largest_value){largest_value = cell_array[y2][x];}
                                movecell++;
                                break;
                            }

                            else if(cell_array[y2][x] == 0){ // If the cell is empty
                                cell_array[y2][x] = cell_array[y][x];  // Assign the value to that empty cell
                                cell_array[y][x] = 0;
                                movecell++;
                                break;
                            }
                        }

                    }

                }
            }
        break;
    }
    if(movecell>0){
        Check_empty_cell();
        fill();
    }
    if(largest_value == 2048){cout<<"You reach 2048!";}
    game_trigger();
    
}

// Reset the game
void game_reset(){
    //reset everything
    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 4; x++){
            cell_array[y][x] = 0;
        }
    }
    score = 0;
    game = true;
    move_trigger = true;

    // Assign random numbers
    int count=0;
    while(count<2){
        int rndx = rand() % 4;
        int rndy = rand() % 4;

        if(cell_array[rndy][rndx] == 0){
            cell_array[rndy][rndx] = 2;
            count++;
        }
    }


}

int main()
{
    srand(time(0));

    const int width = 350, height = 625;

    sf::Font font;
    font.loadFromFile("font/ClearSans-Bold.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString("2048");
    text.setFillColor(sf::Color(119,110,101));
    text.setCharacterSize(53);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(25, 70));


    sf::RenderWindow window(sf::VideoMode(width, height), "2048");
    
    // assign 2 random numbers on the cell_array
    int count=0;
    while(count<2){
        int rndx = rand() % 4;
        int rndy = rand() % 4;

        if(cell_array[rndy][rndx] == 0){
            cell_array[rndy][rndx] = 2;
            count++;
        }
    }
    

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

                switch(event.type){
                    case sf::Event::KeyReleased:
                        if(move_trigger){
                            switch(event.key.code){
                                case sf::Keyboard::Left:
                                    move_mechanics(1);
                                break;
                                case sf::Keyboard::Right:
                                    move_mechanics(2);
                                break;
                                case sf::Keyboard::Up:
                                    move_mechanics(3);
                                break;
                                case sf::Keyboard::Down:
                                    move_mechanics(4);
                                break;
                            }
                        }
                    break;

                    case sf::Event::MouseButtonReleased:
                        switch(event.mouseButton.button){
                            case sf::Mouse::Left:
                                int x = sf::Mouse::getPosition(window).x;
                                int y = sf::Mouse::getPosition(window).y;
                                if((x>120 && x<231) && (y>325 && y<355)){game_reset();}
                                
                            break;
                        }
                    break;
                }
        }

        window.clear(sf::Color(250,248,239));
        window.draw(text);
        show_display(window, font);
        window.display();
    }

    return 0;
}