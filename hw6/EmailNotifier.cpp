#include "EmailNotifier.h"
#include <iostream>

EmailNotifier::EmailNotifier(const std::string &email) {
    _email = email;
}

void EmailNotifier::Notify(const std::string &message) {
    SendEmail(_email, message);
}

void EmailNotifier::SendEmail(const std::string &email, const std::string &message) {
    std::cout << "Send " << message << " e-mail " << email << std::endl;
}
