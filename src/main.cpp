#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUtil.h"
#include "clsLoginScreen.h"

int main(){

    while (clsLoginScreen::ShowLoginScreen()) {}
     

    return 0;
}