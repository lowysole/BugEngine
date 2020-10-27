#include <iostream>
#include "String.h"

int main()
{
    String n = String();

    String a("hello");
    String b(a);
    
    String c = a + b;
    
    bool equal = a == b;
    
    size_t  len = c.GetLength();

    c.Clear();
}
