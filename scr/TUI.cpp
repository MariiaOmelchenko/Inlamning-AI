#include <iostream>
#include "TUI.h"


TUI::TUI(DatabaseManager &dbManager) : db(dbManager) {
    initscr();             // Initialisera ncurses
    cbreak();              // Stäng av buffring för inmatning
    noecho();              // Stäng av eko för inmatning
    keypad(stdscr, TRUE);  // Aktivera tangentkombinationer som piltangenter
    curs_set(0);           // Dölj markören
    mainWin = stdscr;      // Använd standardfönstret
}

TUI::~TUI() {
    endwin(); // Avsluta ncurses
}

void TUI::run() {
    while (true) {
        displayMenu();
        int choice = wgetch(mainWin);

        switch (choice) {
            case '1':
                addContactMenu();
                break;
            case '2':
                searchContactMenu();
                break;
            case '3':
                listContactsMenu();
                break;
            case 'q': // Avsluta programmet
                return;
            default:
                mvprintw(LINES - 2, 0, "Ogiltigt val. Tryck på valfri tangent...");
                getch();
        }
    }
}

void TUI::displayMenu() {
    werase(mainWin);
    printCentered("=== Kontaktbok ===", 2);
    mvprintw(4, 2, "1. Lägg till kontakt");
    mvprintw(5, 2, "2. Sök kontakt");
    mvprintw(6, 2, "3. Lista alla kontakter");
    mvprintw(7, 2, "q. Avsluta");
    printCentered("Välj ett alternativ: ", 9);
    wrefresh(mainWin);
}

void TUI::addContactMenu() {
    werase(mainWin);
    printCentered("Lägg till ny kontakt", 2);

    // Ange namn
    mvprintw(4, 2, "Ange namn: ");
    char name[256];
    echo();
    getstr(name);
    noecho();

    // Ange telefonnummer
    mvprintw(6, 2, "Ange telefonnummer, separerade med kommatecken: ");
    char phones[256];
    echo();
    getstr(phones);
    noecho();

    // Ange e-postadresser
    mvprintw(8, 2, "Ange e-postadresser, separerade med kommatecken: ");
    char emails[256];
    echo();
    getstr(emails);
    noecho();

    // Dela upp strängar
    std::vector<std::string> phoneList, emailList;
    std::string temp;
    for (const char &c : std::string(phones)) {
        if (c == ',') {
            phoneList.push_back(temp);
            temp.clear();
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) phoneList.push_back(temp);

    temp.clear();
    for (const char &c : std::string(emails)) {
        if (c == ',') {
            emailList.push_back(temp);
            temp.clear();
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) emailList.push_back(temp);

    // Spara i databasen
    db.addContact(name, phoneList, emailList);

    mvprintw(LINES - 2, 0, "Kontakten har lagts till. Tryck på valfri tangent...");
    getch();
}

void TUI::searchContactMenu() {
    werase(mainWin);
    printCentered("Sök efter kontakt", 2);

    mvprintw(4, 2, "Ange namn, telefonnummer eller e-postadress: ");
    char query[256];
    echo();
    getstr(query);
    noecho();

    std::vector<std::string> results = db.searchContact(query);

    werase(mainWin);
    printCentered("Sökresultat", 2);
    for (size_t i = 0; i < results.size(); ++i) {
        mvprintw(4 + i, 2, results[i].c_str());
    }

    mvprintw(LINES - 2, 0, "Tryck på valfri tangent för att återgå...");
    getch();
}

void TUI::listContactsMenu() {
    werase(mainWin);
    printCentered("Lista alla kontakter", 2);

    db.listContacts();

    mvprintw(LINES - 2, 0, "Tryck på valfri tangent för att återgå...");
    getch();
}

void TUI::printCentered(const std::string &text, int row) {
    int col = (COLS - text.length()) / 2;
    mvprintw(row, col, "%s", text.c_str());
}
