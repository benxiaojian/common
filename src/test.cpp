#include <iostream>
#include <cstdio>
#include <memory>
#include <ConfigurationFile.h>
using namespace std;
using namespace hj;

int main()
{
    ConfigurationFile file("tr069_agent.ini");
    string str;
    file.GetParameterValue("ManagementServer.URL", str);

    cout << str << endl;
}
