#include <iostream>
#include <string>
#include <vector>
#include <cctype>

class Achievement {
private:
    std::string title;
    std::string description;
    int scoreValue;

public:
    Achievement(const std::string& title, const std::string& description, int scoreValue)
        : title(title), description(description), scoreValue(scoreValue) {}

    // Accessors
    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    int getScoreValue() const { return scoreValue; }

    // Destructor for cleanup
    ~Achievement() {
        std::cout << "Deleting Achievement: " << getTitle() << std::endl;
    }
};

class Game {
private:
    std::string name;
    std::string publisher;
    std::string developer;
    std::vector<Achievement*> achievements;

public:
    Game(const std::string& name, const std::string& publisher, const std::string& developer)
        : name(name), publisher(publisher), developer(developer) {}

    // Accessors
    std::string getName() const { return name; }
    std::string getPublisher() const { return publisher; }
    std::string getDeveloper() const { return developer; }
    const std::vector<Achievement*>& getAchievements() const { return achievements; }

    // Mutators
    void addAchievement(Achievement* achievement) {
        achievements.push_back(achievement);
    }

    // Destructor for cleanup
    ~Game() {
        for (Achievement* achievement : achievements) {
            delete achievement;
        }
        std::cout << "Deleting Game: " << getName() << std::endl;
    }
};

class Platform {
private:
    std::string name;
    std::string manufacturer;
    std::vector<Game*> games;

public:
    Platform(const std::string& name, const std::string& manufacturer)
        : name(name), manufacturer(manufacturer) {}

    // Accessors
    std::string getName() const { return name; }
    std::string getManufacturer() const { return manufacturer; }
    const std::vector<Game*>& getGames() const { return games; }

    // Mutators
    void addGame(Game* game) {
        games.push_back(game);
    }

    // Destructor for cleanup
    ~Platform() {
        for (Game* game : games) {
            delete game;
        }
        std::cout << "Deleting Platform: " << getName() << std::endl;
    }
};

class AchievaApp {
private:
    std::vector<Platform*> platforms;

public:
    // Menu functions
    void showMainMenu();
    void createPlatform();
    void createGame(Platform* platform);
    void createAchievement(Game* game);
    void viewAllSettings();
    void printAchievaArt();

    // Accessor for platforms
    const std::vector<Platform*>& getPlatforms() const {
        return platforms;
    }

    // Destructor for cleanup
    ~AchievaApp() {
        for (Platform* platform : platforms) {
            delete platform;
        }
        std::cout << "Deleting AchievaApp" << std::endl;
    }

    void run() {
        printAchievaArt();
        showMainMenu();
    }
};

// Function prototypes
int parseScore(const std::string& scoreStr);

// Function implementations
void AchievaApp::showMainMenu() {
    while (true) {
        std::cout << "\n1. Create Platform\n"
            << "2. View All Settings\n"
            << "3. Exit\n"
            << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();  // Ignore newline character left in the buffer

        switch (choice) {
        case 1:
            createPlatform();
            break;
        case 2:
            viewAllSettings();
            break;
        case 3:
            std::cout << "Exiting Achieva. Goodbye!\n";
            return;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void AchievaApp::createPlatform() {
    std::string name, manufacturer;
    std::cout << "\nEnter platform name: ";
    std::getline(std::cin, name);
    std::cout << "Enter platform manufacturer: ";
    std::getline(std::cin, manufacturer);

    platforms.push_back(new Platform(name, manufacturer));

    Platform* newPlatform = platforms.back();
    std::cout << "\nPlatform '" << newPlatform->getName() << "' created successfully.\n";

    createGame(newPlatform);
}

void AchievaApp::createGame(Platform* platform) {
    std::string name, publisher, developer;
    std::cout << "\nEnter game name: ";
    std::getline(std::cin, name);
    std::cout << "Enter game publisher: ";
    std::getline(std::cin, publisher);
    std::cout << "Enter game developer: ";
    std::getline(std::cin, developer);

    platform->addGame(new Game(name, publisher, developer));

    Game* newGame = platform->getGames().back();
    std::cout << "\nGame '" << newGame->getName() << "' created successfully.\n";

    createAchievement(newGame);
}

void AchievaApp::createAchievement(Game* game) {
    std::string title, description, scoreStr;

    std::cout << "\nEnter achievement title: ";
    std::getline(std::cin, title);
    std::cout << "Enter achievement description: ";
    std::getline(std::cin, description);
    std::cout << "Enter achievement score (with optional 'G'): ";
    std::getline(std::cin, scoreStr);

    int score = parseScore(scoreStr);

    game->addAchievement(new Achievement(title, description, score));

    Achievement* newAchievement = game->getAchievements().back();
    std::cout << "\nAchievement '" << newAchievement->getTitle() << "' created successfully.\n";
}

int parseScore(const std::string& scoreStr) {
    // Check if the score string contains 'G' and extract the numeric part
    size_t pos = scoreStr.find('G');
    if (pos != std::string::npos) {
        std::string numericPart = scoreStr.substr(0, pos);
        if (!numericPart.empty()) {
            for (char c : numericPart) {
                if (!std::isdigit(c)) {
                    std::cout << "Invalid score format. Using default score of 0.\n";
                    return 0;
                }
            }
            return std::stoi(numericPart);
        }
    }

    // If 'G' is not present or the format is invalid, use default score of 0
    std::cout << "Invalid score format. Using default score of 0.\n";
    return 0;
}

void AchievaApp::viewAllSettings() {
    std::cout << "\n--- All Settings ---\n";
    for (Platform* platform : platforms) {
        std::cout << "Platform: " << platform->getName() << " (Manufacturer: " << platform->getManufacturer() << ")\n";
        for (Game* game : platform->getGames()) {
            std::cout << "  Game: " << game->getName() << " (Publisher: " << game->getPublisher()
                << ", Developer: " << game->getDeveloper() << ")\n";
            for (Achievement* achievement : game->getAchievements()) {
                std::cout << "    Achievement: " << achievement->getTitle() << " (Description: "
                    << achievement->getDescription() << ", Score: " << achievement->getScoreValue() << ")\n";
            }
        }
    }
}

void AchievaApp::printAchievaArt() {
    std::cout << R"(
                                              @@@@@@@@                                              
                                       @@@@@@@@@@@@@@@@@@@@@@@                                      
                                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                 
                              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                              
                            @@@@@@@@@@@  =====         ++++   @@@@@@@@@@@                           
                         @@@@@@@@@@*==========         +++++++++ @@@@@@@@@@                         
                       @@@@@@@@@ =============         ++++++++++++ @@@@@@@@@                       
                      @@@@@@@@================         +++++++++++++++ @@@@@@@@                     
                    @@@@@@@@=================          +++++++++++++++++ @@@@@@@                    
                   @@@@@@@==============                    ++++++++++++++ @@@@@@@                  
                  @@@@@@%===========                            +++++++++++ @@@@@@@                 
                 @@@@@@===========                                +++++++++++@@@@@@@                
                @@@@@@==========                                    ++++++++++ @@@@@@               
               @@@@@@==========                                      ++++++++++@@@@@@               
               @@@@@+=========    ++++++====================++++++     +++++++++@@@@@@              
              @@@@@%========      ==+***+==================+***+==      ++++++++ @@@@@              
             @@@@@@=========       ==+  +==================+  +==       +++++++++@@@@@@             
             @@@@@ ========         ==+  ==================   ==         ++++++++ @@@@@             
            @@@@@@                  ===   ================   ==+                  @@@@@@            
            @@@@@@                   +===  ==============  ===+                   @@@@@@            
            @@@@@@                     +===+============+===+                     @@@@@@            
            @@@@@@                        +==============*                        @@@@@@            
            @@@@@@                            ========+                           @@@@@@            
            @@@@@@+++++++++                    =======                   ++++++++ @@@@@@            
             @@@@@ ++++++++                    ======                    ++++++++*@@@@@             
             @@@@@@+++++++++                   ======+                  +++++++++@@@@@@             
              @@@@@ ++++++++                  *=======                  ++++++++%@@@@@              
              @@@@@@+++++++++                 ========                 ++++++++*@@@@@@              
               @@@@@@++++++++++               =========              ++++++++++@@@@@@               
               @@@@@@ ++++++++++             +=========             ++++++++++@@@@@@                
                @@@@@@@+++++++++++          +===========          +++++++++++@@@@@@                 
                 @@@@@@@*+++++++++++         ===========        +++++++++++#@@@@@@                  
                  @@@@@@@ +++++++++++++                      +++++++++++++@@@@@@@                   
                    @@@@@@@ ++++++++++++++++            ++++++++++++++++@@@@@@@@                    
                     @@@@@@@@ ++++++++++++++++        ++++++++++++++++%@@@@@@@                      
                       @@@@@@@@  +++++++++++++        +++++++++++++ @@@@@@@@@                       
                         @@@@@@@@@@ ++++++++++        ++++++++++ @@@@@@@@@@                         
                           @@@@@@@@@@@  ++++++        ++++++ @@@@@@@@@@@                            
                              @@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@                              
                                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                 
                                      @@@@@@@@@@@@@@@@@@@@@@@@                                      
                                             @@@@@@@@@            achieva by @sutnex                                  
)";
}

int main() {
    AchievaApp achievaApp;
    achievaApp.run();

    // No need to manually clean up memory, as the destructors will be called when variables go out of scope.

    return 0;
}
