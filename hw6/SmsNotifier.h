#pragma once

#include "INotifier.h"
#include <string>

class SmsNotifier : INotifier {
    std::string _number;

    void SendSms(const std::string &number, const std::string &message);

public:
    SmsNotifier(const std::string &number);

    void Notify(const std::string &message) override;
};