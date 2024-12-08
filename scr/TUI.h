#ifndef TUI_H
#define TUI_H

#include "DatabaseManager.h"
#include <ncurses.h>
#include <string>
#include <vector>

class TUI {
private:
    DatabaseManager &db; // Referens till databasens manager
    WINDOW *mainWin;     // Huvudfönster för gränssnittet

    // Privata metoder
    void displayMenu();                 // Visa huvudmenyn
    void addContactMenu();              // Meny för att lägga till en kontakt
    void searchContactMenu();           // Meny för att söka efter kontakter
    void listContactsMenu();            // Meny för att visa alla kontakter
    void printCentered(const std::string &text, int row); // Skriva text centrerad

public:
    explicit TUI(DatabaseManager &dbManager);
    ~TUI();

    void run(); // Huvudloopen för TUI
};

#endif
