#include "app.h"
#include"headers.h"
using namespace dHeader ;
int main()
{
    std :: cout << "Enter current date : " ;
    int day, month , year ;
    std :: cin >> day >> month >> year ;
    dHeader :: socialNetworkApp app(day,month,year);
    app.run();
    return 0;
}