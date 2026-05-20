#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {
protected:
    string name, phone;

public:
    void inputPerson() {
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter phone: ";
        getline(cin, phone);
    }

    virtual void show() = 0;
};

class Customer : public Person {
    string cnic;

public:
    void inputCustomer() {
        inputPerson();
        cout << "Enter CNIC: ";
        getline(cin, cnic);
    }

    string getName() { return name; }
    string getPhone() { return phone; }
    string getCnic() { return cnic; }

    void show() {
        cout << "Name  : " << name << endl;
        cout << "Phone : " << phone << endl;
        cout << "CNIC  : " << cnic << endl;
    }
};

class EventPackage {
public:
    virtual string getName() = 0;
    virtual int getPricePerGuest() = 0;
    virtual int getDecorationCharges() = 0;

    virtual void showPackage() {
        cout << getName()
             << " | Per Guest: Rs. " << getPricePerGuest()
             << " | Decoration: Rs. " << getDecorationCharges() << endl;
    }

    virtual ~EventPackage() { }
};

class BasicPackage : public EventPackage {
public:
    string getName() { return "Basic Package"; }
    int getPricePerGuest() { return 800; }
    int getDecorationCharges() { return 20000; }
};

class PremiumPackage : public EventPackage {
public:
    string getName() { return "Premium Package"; }
    int getPricePerGuest() { return 1200; }
    int getDecorationCharges() { return 40000; }
};

class RoyalPackage : public EventPackage {
public:
    string getName() { return "Royal Package"; }
    int getPricePerGuest() { return 1800; }
    int getDecorationCharges() { return 70000; }
};

class Hall {
    int id, capacity, rent;
    string name;

public:
    Hall() {
        id = capacity = rent = 0;
        name = "";
    }

    Hall(int hallId, string hallName, int hallCapacity, int hallRent) {
        id = hallId;
        name = hallName;
        capacity = hallCapacity;
        rent = hallRent;
    }

    string getName() { return name; }
    int getCapacity() { return capacity; }
    int getRent() { return rent; }

    void showHall() {
        cout << id << ". " << name
             << " | Capacity: " << capacity
             << " | Rent: Rs. " << rent << endl;
    }
};

class Booking {
    int bookingId, guests, totalBill, paidAmount;
    Customer customer;
    Hall hall;
    string date, packageName;

public:
    Booking() {
        bookingId = guests = totalBill = paidAmount = 0;
    }

    Booking(int id, Customer c, Hall h, string eventDate,
            int totalGuests, string pkgName, int bill, int paid) {
        bookingId = id;
        customer = c;
        hall = h;
        date = eventDate;
        guests = totalGuests;
        packageName = pkgName;
        totalBill = bill;
        paidAmount = paid;
    }

    int getBookingId() {
        return bookingId;
    }

    int getBalance() {
        return totalBill - paidAmount;
    }

    void addPayment(int amount) {
        if (amount <= 0) {
            cout << "Payment amount valid nahi hai." << endl;
        } else if (amount > getBalance()) {
            cout << "Payment balance se zyada nahi ho sakti." << endl;
        } else {
            paidAmount = paidAmount + amount;
            cout << "Payment added successfully." << endl;
        }
    }

    void showBooking() {
        cout << "\n----- Booking Details -----" << endl;
        cout << "Booking ID : " << bookingId << endl;
        customer.show();
        cout << "Hall       : " << hall.getName() << endl;
        cout << "Date       : " << date << endl;
        cout << "Guests     : " << guests << endl;
        cout << "Package    : " << packageName << endl;
        cout << "Total Bill : Rs. " << totalBill << endl;
        cout << "Paid       : Rs. " << paidAmount << endl;
        cout << "Balance    : Rs. " << getBalance() << endl;
    }

    void writeToFile(ofstream& file) {
        file << "Booking ID : " << bookingId << endl;
        file << "Name       : " << customer.getName() << endl;
        file << "Phone      : " << customer.getPhone() << endl;
        file << "CNIC       : " << customer.getCnic() << endl;
        file << "Hall       : " << hall.getName() << endl;
        file << "Date       : " << date << endl;
        file << "Guests     : " << guests << endl;
        file << "Package    : " << packageName << endl;
        file << "Total Bill : Rs. " << totalBill << endl;
        file << "Paid       : Rs. " << paidAmount << endl;
        file << "Balance    : Rs. " << getBalance() << endl;
        file << "-----------------------------" << endl;
    }
};

class MarriageHallSystem {
    Hall halls[3];
    Booking bookings[50];
    int nextBookingId, totalBookings;

    EventPackage* createPackage(int choice) {
        if (choice == 1) return new BasicPackage();
        if (choice == 2) return new PremiumPackage();
        if (choice == 3) return new RoyalPackage();
        return 0;
    }

    void saveAllBookings() {
        ofstream file("marriage_bookings.txt");

        if (!file) {
            cout << "File open nahi ho saki." << endl;
            return;
        }

        for (int i = 0; i < totalBookings; i++) {
            bookings[i].writeToFile(file);
        }

        file.close();
    }

public:
    MarriageHallSystem() {
        halls[0] = Hall(1, "Pearl Marriage Hall", 300, 100000);
        halls[1] = Hall(2, "Royal Palace Hall", 500, 180000);
        halls[2] = Hall(3, "Grand Banquet Hall", 700, 250000);
        nextBookingId = 1;
        totalBookings = 0;
    }

    void showHalls() {
        cout << "\nAvailable Halls" << endl;
        for (int i = 0; i < 3; i++) halls[i].showHall();
    }

    void showPackages() {
        BasicPackage basic;
        PremiumPackage premium;
        RoyalPackage royal;

        EventPackage* package;
        cout << "\nAvailable Packages" << endl;

        package = &basic;
        cout << "1. ";
        package->showPackage();

        package = &premium;
        cout << "2. ";
        package->showPackage();

        package = &royal;
        cout << "3. ";
        package->showPackage();
    }

    void bookHall() {
        int hallChoice, packageChoice, guests, advancePayment;
        string date;

        if (totalBookings >= 50) {
            cout << "Booking limit full ho gayi." << endl;
            return;
        }

        showHalls();
        cout << "\nSelect hall: ";
        cin >> hallChoice;
        cin.ignore(1000, '\n');

        if (hallChoice < 1 || hallChoice > 3) {
            cout << "Invalid hall." << endl;
            return;
        }

        Customer customer;
        cout << "\nEnter Customer Details" << endl;
        customer.inputCustomer();

        cout << "Enter event date: ";
        getline(cin, date);

        cout << "Enter guests: ";
        cin >> guests;
        cin.ignore(1000, '\n');

        Hall selectedHall = halls[hallChoice - 1];
        if (guests > selectedHall.getCapacity()) {
            cout << "Guests hall capacity se zyada hain." << endl;
            return;
        }

        showPackages();
        cout << "\nSelect package: ";
        cin >> packageChoice;
        cin.ignore(1000, '\n');

        EventPackage* package = createPackage(packageChoice);
        if (package == 0) {
            cout << "Invalid package." << endl;
            return;
        }

        int bill = selectedHall.getRent()
                 + package->getDecorationCharges()
                 + guests * package->getPricePerGuest();

        cout << "\nTotal Bill: Rs. " << bill << endl;
        cout << "Enter advance payment: ";
        cin >> advancePayment;
        cin.ignore(1000, '\n');

        if (advancePayment < 0 || advancePayment > bill) {
            cout << "Invalid payment amount." << endl;
            delete package;
            return;
        }

        Booking booking(nextBookingId, customer, selectedHall, date,
                        guests, package->getName(), bill, advancePayment);

        bookings[totalBookings] = booking;
        totalBookings++;
        booking.showBooking();
        saveAllBookings();
        cout << "\nBooking saved successfully." << endl;

        nextBookingId++;
        delete package;
    }

    void addPayment() {
        int id, amount;

        cout << "\nEnter booking ID: ";
        cin >> id;
        cin.ignore(1000, '\n');

        for (int i = 0; i < totalBookings; i++) {
            if (bookings[i].getBookingId() == id) {
                cout << "Current balance: Rs. " << bookings[i].getBalance() << endl;

                if (bookings[i].getBalance() == 0) {
                    cout << "Is booking ki full payment already ho chuki hai." << endl;
                    return;
                }

                cout << "Enter payment amount: ";
                cin >> amount;
                cin.ignore(1000, '\n');

                bookings[i].addPayment(amount);
                saveAllBookings();
                bookings[i].showBooking();
                return;
            }
        }

        cout << "Booking ID nahi mili. Pehle isi run mein booking create karein." << endl;
    }

    void viewBookings() {
        ifstream file("marriage_bookings.txt");
        string line;

        if (!file) {
            cout << "No booking record found." << endl;
            return;
        }

        cout << "\nSaved Bookings" << endl;
        while (getline(file, line)) cout << line << endl;
        file.close();
    }

    void menu() {
        int choice;

        do {
            cout << "\n===== Marriage Hall Booking System =====" << endl;
            cout << "1. Show Halls" << endl;
            cout << "2. Show Packages" << endl;
            cout << "3. Book Hall" << endl;
            cout << "4. View Bookings" << endl;
            cout << "5. Add Payment" << endl;
            cout << "0. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore(1000, '\n');

            if (choice == 1) showHalls();
            else if (choice == 2) showPackages();
            else if (choice == 3) bookHall();
            else if (choice == 4) viewBookings();
            else if (choice == 5) addPayment();
            else if (choice == 0) cout << "Program closed." << endl;
            else cout << "Invalid choice." << endl;
        } while (choice != 0);
    }
};

int main() {
    MarriageHallSystem system;
    system.menu();
    return 0;
}
