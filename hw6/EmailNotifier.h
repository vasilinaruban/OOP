#pragma once

#include "INotifier.h"

class EmailNotifier : INotifier {
    std::string _email;

    void SendEmail(const std::string &email, const std::string &message);

public:
    EmailNotifier(const std::string &email);

    void Notify(const std::string &message) override;
};