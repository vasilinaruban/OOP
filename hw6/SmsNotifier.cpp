#include "SmsNotifier.h"
#include <iostream>

SmsNotifier::SmsNotifier(const std::string &number) {
    _number = number;
}

void SmsNotifier::Notify(const std::string &message) {
    SendSms(_number, message);
}

void SmsNotifier::SendSms(const std::string &number, const std::string &message) {
    std::cout << "Send " << message << " to number " << number << std::endl;
}