#include "SmsNotifier.h"
#include "EmailNotifier.h"

int main() {
    SmsNotifier sms{"+7-923-228-38-72"};
    EmailNotifier email{"m.Filippov@g.nsu.ru"};
    sms.Notify("I know lessons in C++");
    email.Notify("And want the lesson one");
    return 0;
}
