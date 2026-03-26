#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//   STRUCTURES
struct Flight {
    string flightID;       // Unique ID of the flight
    string fromCity;       // Departure city
    string toCity;         // Arrival city
    int seatsAvailable;    // Number of seats left
    int farePerSeat;       // Cost per seat
};
struct Booking {
    string username;       // Passenger who booked
    string flightID;       // Flight booked
    int bookedSeats;       // Number of seats booked
    int totalFare;         // Total cost of booking
};
//   GLOBAL VARIABLES 
string cityList[] = { "Karachi", "Lahore", "Islamabad", "Peshawar", "Quetta",
                      "Multan", "Faisalabad", "Sialkot", "Hyderabad", "Sukkur",
                      "Gwadar", "Bahawalpur", "Skardu", "Gilgit", "Chitral" };
int totalCities = 15;
/* =========================
   UTILITY FUNCTIONS
   ========================= */
   // Select city from menu
string selectCity() {
    int choice;
    while (true) {
        cout << "\nSelect City:\n";
        for (int i = 0; i < totalCities; i++)
            cout << i + 1 << ". " << cityList[i] << endl;
        cout << "Enter choice: ";
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        if (choice >= 1 && choice <= totalCities)
            return cityList[choice - 1];

        cout << "Invalid choice! Try again.\n";
    }
}
// Pause console until user presses Enter
void pauseConsole() {
    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}
/* =========================
   FILE INITIALIZATION
   ========================= */
void initializeFiles() {
    ifstream checkUsers("users.txt");
    if (!checkUsers.good())
        ofstream("users.txt").close();
    checkUsers.close();

    ifstream checkFlights("flights.txt");
    if (!checkFlights.good())
        ofstream("flights.txt").close();
    checkFlights.close();

    ifstream checkBookings("bookings.txt");
    if (!checkBookings.good())
        ofstream("bookings.txt").close();
    checkBookings.close();
    ifstream checkAdmins("admins.txt");
    if (!checkAdmins.good())
    {
        ofstream admins("admins.txt");
        admins << "admin admin123\n";
        admins.close();
    }
    checkAdmins.close();
}
/* =========================
   LOGIN & CHECK FUNCTIONS
   ========================= */
bool loginAdmin(string& username) {
    system("cls");
    cout << "===== ADMIN LOGIN =====\n";
    string password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    string fileUsername, filePassword;
    ifstream file("admins.txt");
    while (file >> fileUsername >> filePassword) {
        if (fileUsername == username && filePassword == password)
            return true;
    }
    return false;
}
bool loginPassenger(string& username) {
    system("cls");
    cout << "===== PASSENGER LOGIN =====\n";
    string password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    string fileUsername, filePassword;
    ifstream file("users.txt");
    while (file >> fileUsername >> filePassword) {
        if (fileUsername == username && filePassword == password)
            return true;
    }
    return false;
}
bool flightsExist()
{
    ifstream file("flights.txt");
    return file.peek() != EOF;
}
// Check if username already exists
bool usernameExists(const string& username) {
    ifstream file("users.txt");
    string u, p;
    while (file >> u >> p) {
        if (u == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
// Check if flight ID already exists
bool flightIDExists(const string& flightID) {
    ifstream file("flights.txt");
    Flight f;
    while (file >> f.flightID >> f.fromCity >> f.toCity
        >> f.seatsAvailable >> f.farePerSeat) {
        if (f.flightID == flightID) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
/* =========================
   PASSENGER REGISTRATION
   ========================= */
void registerPassenger() {
    if (!flightsExist()) {
        cout << "No flights available! Cannot register passengers.\n";
        pauseConsole();
        return;
    }
    system("cls");
    cout << "===== PASSENGER REGISTRATION =====\n";
    string username, password;
    cout << "Enter Username: ";
    cin >> username;

    if (usernameExists(username)) {
        cout << "Username already exists! Try logging in.\n";
        pauseConsole();
        return;
    }
    cout << "Enter Password: ";
    cin >> password;
    ofstream outFile("users.txt", ios::app);
    outFile << username << " " << password << endl;
    outFile.close();
    cout << "Registration successful! You can now login.\n";
    pauseConsole();
}
/* =========================
   ADMIN FUNCTIONS
   ========================= */
void addPassenger() {
    if (!flightsExist()) {
        cout << "No flights available! Cannot add passengers.\n";
        pauseConsole();
        return;
    }
    system("cls");
    cout << "===== ADD PASSENGER =====\n";
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    if (usernameExists(username))
    {
        cout << "Username already exists!\n";
        pauseConsole();
        return;
    }
    cout << "Enter Password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();
    cout << "Passenger added successfully!\n";
    pauseConsole();
}
void removePassenger() {
    system("cls");
    cout << "===== REMOVE PASSENGER =====\n";
    string username, u, p;
    bool found = false;   // to check passenger existence
    cout << "Enter Passenger Username to Remove: ";
    cin >> username;

    ifstream inFile("users.txt");
    ofstream outFile("temp.txt");
    while (inFile >> u >> p) {
        if (u == username) {
            found = true;     // passenger found
            continue;        // skip writing → removed
        }
        outFile << u << " " << p << endl;
    }
    inFile.close();
    outFile.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
    if (found)
        cout << "Passenger removed successfully!\n";
    else
        cout << "Passenger does not exist!\n";
    pauseConsole();
}
bool adminUsernameExists(const string& username)
{
    ifstream file("admins.txt");
    string u, p;
    while (file >> u >> p)
    {
        if (u == username)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
void addAdmin()
{
    system("cls");
    cout << "===== ADD NEW ADMIN =====\n";
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    //  UNIQUE CHECK
    if (adminUsernameExists(username))
    {
        cout << "Admin username already exists!\n";
        pauseConsole();
        return;
    }
    cout << "Enter Password: ";
    cin >> password;
    ofstream file("admins.txt", ios::app);
    file << username << " " << password << endl;
    file.close();
    cout << "New admin added successfully!\n";
    pauseConsole();
}
void addFlight()
{
    system("cls");
    cout << "===== ADD FLIGHT =====\n";
    Flight newFlight;
    cout << "Flight ID: ";
    cin >> newFlight.flightID;
    if (flightIDExists(newFlight.flightID))
    {
        cout << "Flight ID already exists!\n";
        pauseConsole();
        return;
    }
    cout << "FROM: ";
    newFlight.fromCity = selectCity();
    cout << "TO: ";
    newFlight.toCity = selectCity();
    if (newFlight.toCity == newFlight.fromCity)
    {
        while (newFlight.toCity == newFlight.fromCity)
        {
            cout << "Error!! Please Select a Different Destination\n";
            newFlight.toCity = selectCity();
        }
    }
    cout << "Seats Available: ";
    cin >> newFlight.seatsAvailable;
    cout << "Fare per Seat: ";
    cin >> newFlight.farePerSeat;
    ofstream file("flights.txt", ios::app);
    file << newFlight.flightID << " " << newFlight.fromCity << " "
        << newFlight.toCity << " " << newFlight.seatsAvailable << " "
        << newFlight.farePerSeat << endl;
    file.close();
    cout << "Flight added successfully!\n";
    pauseConsole();
}
void removeFlight() {
    system("cls");
    cout << "===== REMOVE FLIGHT =====\n";
    string flightID;
    bool found = false;   // check if flight exists
    Flight f;
    cout << "Enter Flight ID to Remove: ";
    cin >> flightID;
    ifstream inFile("flights.txt");
    ofstream outFile("temp.txt");
    while (inFile >> f.flightID >> f.fromCity >> f.toCity
        >> f.seatsAvailable >> f.farePerSeat) {
        if (f.flightID == flightID) {
            found = true;     // flight found
            continue;        // skip writing → removed
        }
        outFile << f.flightID << " " << f.fromCity << " "
            << f.toCity << " " << f.seatsAvailable << " " << f.farePerSeat << endl;
    }
    inFile.close();
    outFile.close();
    remove("flights.txt");
    rename("temp.txt", "flights.txt");
    if (found)
        cout << "Flight removed successfully!\n";
    else
        cout << "Flight does not exist!\n";
    pauseConsole();
}
void viewFlights() {
    system("cls");
    cout << "===== AVAILABLE FLIGHTS =====\n";
    ifstream file("flights.txt");
    Flight f;
    if (file.peek() == EOF) {
        cout << "No flights available!\n";
        pauseConsole();
        return;
    }
    while (file >> f.flightID >> f.fromCity >> f.toCity >> f.seatsAvailable >> f.farePerSeat) {
        cout << "Flight ID: " << f.flightID
            << " | FROM: " << f.fromCity
            << " | TO: " << f.toCity
            << " | Seats: " << f.seatsAvailable
            << " | Fare: " << f.farePerSeat << endl;
    }
    file.close();
    pauseConsole();
}
/* =========================
   PASSENGER FUNCTIONS
   ========================= */
void bookFlight(string username) {
    if (!flightsExist()) {
        cout << "No flights available! Cannot book flights.\n";
        pauseConsole();
        return;
    }
    system("cls");
    cout << "===== BOOK FLIGHT =====\n";
    viewFlights();
    string flightID;
    int seats;
    cout << "\nEnter Flight ID: ";
    cin >> flightID;
    cout << "Seats to Book: ";
    cin >> seats;
    // Load flights into memory
    Flight flights[100];
    int flightCount = 0;
    ifstream inFile("flights.txt");
    while (inFile >> flights[flightCount].flightID >> flights[flightCount].fromCity
        >> flights[flightCount].toCity >> flights[flightCount].seatsAvailable
        >> flights[flightCount].farePerSeat)
        flightCount++;
    inFile.close();
    bool booked = false;
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightID == flightID && flights[i].seatsAvailable >= seats) {
            flights[i].seatsAvailable -= seats;
            // Save booking
            ofstream bookingsFile("bookings.txt", ios::app);
            bookingsFile << username << " " << flightID << " " << seats
                << " " << seats * flights[i].farePerSeat << endl;
            bookingsFile.close();

            booked = true;
            break;
        }
    }
    // Save updated flights
    ofstream outFile("flights.txt");
    for (int i = 0; i < flightCount; i++)
        outFile << flights[i].flightID << " " << flights[i].fromCity << " "
        << flights[i].toCity << " " << flights[i].seatsAvailable << " "
        << flights[i].farePerSeat << endl;
    outFile.close();

    cout << (booked ? "\nBooking successful!" : "\nBooking failed!");
    pauseConsole();
}
void viewBookings(string username) {
    system("cls");
    cout << "===== MY BOOKINGS =====\n";
    ifstream file("bookings.txt");
    Booking b;
    bool found = false;
    while (file >> b.username >> b.flightID >> b.bookedSeats >> b.totalFare) {
        if (b.username == username) {
            cout << "Flight ID: " << b.flightID
                << " | Seats: " << b.bookedSeats
                << " | Total: " << b.totalFare << endl;
            found = true;
        }
    }
    file.close();
    if (!found)
        cout << "No bookings found!\n";
    pauseConsole();
}
void cancelBooking(string username) {
    if (!flightsExist())
    {
        cout << "No flights available! Cannot cancel bookings.\n";
        pauseConsole();
        return;
    }
    system("cls");
    cout << "===== CANCEL BOOKING =====\n";
    string flightID;
    bool bookingFound = false;
    ifstream inFile("bookings.txt");
    Booking b;
    while (inFile >> b.username >> b.flightID >> b.bookedSeats >> b.totalFare) {
        if (b.username == username) {
            cout << "Flight ID: " << b.flightID
                << " | Seats: " << b.bookedSeats
                << " | Total: " << b.totalFare << endl;
            bookingFound = true;
        }
    }
    inFile.close();

    if (!bookingFound) {
        cout << "No bookings to cancel!\n";
        pauseConsole();
        return;
    }
    cout << "\nEnter Flight ID to cancel: ";
    cin >> flightID;
    int cancelledSeats = 0;
    ifstream bookingsIn("bookings.txt");
    ofstream tempOut("temp.txt");
    while (bookingsIn >> b.username >> b.flightID >> b.bookedSeats >> b.totalFare) {
        if (b.username == username && b.flightID == flightID) {
            cancelledSeats = b.bookedSeats;
        }
        else {
            tempOut << b.username << " " << b.flightID << " " << b.bookedSeats << " " << b.totalFare << endl;
        }
    }
    bookingsIn.close(); tempOut.close();
    remove("bookings.txt");
    rename("temp.txt", "bookings.txt");
    if (cancelledSeats > 0)
    {
        Flight flights[100];
        int flightCount = 0;
        ifstream flightsIn("flights.txt");
        string fid, from, to; int seats, fare;
        while (flightsIn >> fid >> from >> to >> seats >> fare) {
            flights[flightCount].flightID = fid;
            flights[flightCount].fromCity = from;
            flights[flightCount].toCity = to;
            flights[flightCount].seatsAvailable = seats;
            flights[flightCount].farePerSeat = fare;
            flightCount++;
        }
        flightsIn.close();
        for (int i = 0; i < flightCount; i++) {
            if (flights[i].flightID == flightID) flights[i].seatsAvailable += cancelledSeats;
        }
        ofstream flightsOut("flights.txt");
        for (int i = 0; i < flightCount; i++)
            flightsOut << flights[i].flightID << " " << flights[i].fromCity << " "
            << flights[i].toCity << " " << flights[i].seatsAvailable << " "
            << flights[i].farePerSeat << endl;
        flightsOut.close();
        cout << "\nBooking cancelled successfully!";
    }
    else {
        cout << "\nBooking not found!";
    }
    pauseConsole();
}
/* =========================
   DASHBOARDS
   ========================= */
void adminDashboard() {
    int choice;
    do {
        system("cls");
        cout << "\t       ===================================  ADMIN DASHBOARD   =================================    \n" << endl;
        cout << "\t____________________________________________________________________________________________________" << endl;
        cout << "\t\t\t\t\t" << endl;
        cout << "\t                                   | Press 1. Add Passenger                   |" << endl;
        cout << "\t                                   | Press 2. Remove Passenger                |" << endl;
        cout << "\t                                   | Press 3. Add Flight                      |" << endl;
        cout << "\t                                   | Press 4. Remove Flight                   |" << endl;
        cout << "\t                                   | Press 5. View Flights                    |" << endl;
        cout << "\t                                   | Press 6. Add Admin                       |" << endl;
        cout << "\t                                   | Press 0. Logout                          |" << endl;
        cout << "\t                                   |\t\t\t\t\              |" << endl;
        cout << "\t____________________________________________________________________________________________________" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: addPassenger(); break;
        case 2: removePassenger(); break;
        case 3: addFlight(); break;
        case 4: removeFlight(); break;
        case 5: viewFlights(); break;
        case 6: addAdmin(); break;
        case 0: cout << "Logging out...\n"; pauseConsole(); break;
        default: cout << "Invalid choice!\n"; pauseConsole();
        }
    } while (choice != 0);
}
void passengerDashboard(string username) {
    int choice;
    do {
        system("cls");
        cout << "\t      ===================================== PASSENGER PANEL ======================================\n" << endl;
        cout << "\t____________________________________________________________________________________________________" << endl;
        cout << "\t\t\t\t\t" << endl;
        cout << "\t                                   | Press 1. View Flights                     |" << endl;
        cout << "\t                                   | Press 2. Book flightd                     |" << endl;
        cout << "\t                                   | Press 3. View My Bookings                 |" << endl;
        cout << "\t                                   | Press 4. Cancel Booking                   |" << endl;
        cout << "\t                                   | Press 0. Logout                           |" << endl;
        cout << "\t                                   |\t\t\t\t\               |" << endl;
        cout << "\t____________________________________________________________________________________________________" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: viewFlights(); break;
        case 2: bookFlight(username); break;
        case 3: viewBookings(username); break;
        case 4: cancelBooking(username); break;
        case 0: cout << "Logging out...\n"; pauseConsole(); break;
        default: cout << "Invalid choice!\n"; pauseConsole();
        }
    } while (choice != 0);
}
/* =========================
   MAIN FUNCTION
   ========================= */
int main() {
    initializeFiles();
    int mainChoice;
    do {
        system("cls");
        cout << "\t                                  AIRLINE RESERVATION MANAGEMENT SYSTEM                     \n" << endl;
        cout << "\t       ===================================== MAIN MEUN ======================================\n" << endl;
        cout << "\t____________________________________________________________________________________________________" << endl;
        cout << "\t\t\t\t\t" << endl;
        cout << "\t                                  ||\t\t\t\t\            ||" << endl;
        cout << "\t                                  || Press 1. Admin Login                   ||" << endl;
        cout << "\t                                  || Press 2. Passenger Login               ||" << endl;
        cout << "\t                                  || Press 3. Register as Passenger         ||" << endl;
        cout << "\t                                  || Press 0.Exist                          ||" << endl;
        cout << "\t                                  ||\t\t\t\t\            ||" << endl;
        cout << "\t____________________________________________________________________________________________________\n" << endl;
        cout << "Enter Your  choice: ";
        cin >> mainChoice;
        cin.ignore();

        switch (mainChoice) {
        case 1: {
            string username;
            if (loginAdmin(username)) adminDashboard();
            else {
                cout << "Invalid Admin Login!\n"; pauseConsole();
            }
            break;
        }
        case 2: {
            if (!flightsExist())
            {
                cout << "No flights available! Cannot login as passenger.\n"; pauseConsole(); break;
            }
            string username;
            if (loginPassenger(username)) passengerDashboard(username);
            else
            {
                cout << "Invalid Passenger Login!\n"; pauseConsole();
            }
            break;
        }
        case 3: registerPassenger();
            break;
        case 0: cout << "Exiting Program...\n";
            break;
        default: cout << "Invalid choice!\n"; pauseConsole();
        }
    } while (mainChoice != 0);

    return 0;
}