#include <iostream>
#include "DatabaseManager.h"
#include "TUI.h"

int main() {
    DatabaseManager db("localhost", "root", "password", "ContactBook");
    if (!db.connect()) {
        std::cerr << "Failed to connect to the database." << std::endl;
        return 1;
    }

    TUI tui(db);
    tui.run(); 
    return 0;
}
