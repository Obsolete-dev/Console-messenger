#include <iostream>
#include <string>
#include <vector>

class User {
private:
    std::string login;
    std::string password;
    std::string name;

public:
    User(const std::string& login, const std::string& password, const std::string& name) : login(login), password(password), name(name) {}

    std::string getLogin() const {
        return login;
    }

    std::string getPassword() const {
        return password;
    }

    std::string getName() const {
        return name;
    }
};

const User* findUserByLogin(const std::vector<User>& users, const std::string& login) {
    for (const auto& user : users) {
        if (user.getLogin() == login) {
            return &user;
        }
    }
    return nullptr;
}

int main() {
    std::vector<User> users;
    std::string login, password, name;
    std::string choice;

    while (true) {
        std::cout << "Enter login: ";
        std::cin >> login;

        std::cout << "Enter password:: ";
        std::cin >> password;

        std::cout << "Enter name: ";
        std::cin >> name;

        const User* currentUser = findUserByLogin(users, login);

        if (currentUser == nullptr) {
            users.push_back(User(login, password, name));
            currentUser = &users.back();
        } else {
            if (currentUser->getPassword() != password) {
                std::cout << "Error: wrong password\n";
                continue;
            }
            std::cout << "Welcome back, " << currentUser->getName() << "!\n";
        }

        while (true) {
            std::cout << "Select action: \n"
                      << "a) Send a message to another user\n"
                      << "b) Send a message to the general chat\n"
                      << "c) Change user\n"
                      << "d) Exit the program\n"
                      << "Your choice is: ";

            std::cin >> choice;

            if (choice == "a") {
                std::string recipient;
                std::cout << "Enter the name of the recipient: ";
                std::cin >> recipient;

                const User* recipientUser = findUserByLogin(users, recipient);
                if (recipientUser == nullptr) {
                    std::cout << "Error: user '" << recipient << "' not found\n";
                    continue;
                }

                std::string message;
                std::cout << "Type the message: ";
                std::cin.ignore();
                std::getline(std::cin, message);

                std::cout << "Message for " << recipientUser->getName() << ": " << message << '\n';
            } else if (choice == "b") {
                std::string message;
                std::cout << "Type a message into the general chat: ";
                std::cin.ignore();
                std::getline(std::cin, message);

                for (auto& user : users) {
                    std::cout << "Message for " << user.getName() << ": " << message << '\n';
                }
            } else if (choice == "c") {
                break;
            } else if (choice == "d") {
                return 0;
            } else {
                std::cout << "Error: wrong choice\n";
            }
        }
    }

    return 0;
}
