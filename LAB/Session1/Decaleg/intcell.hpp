#ifndef INTCELL
#define INTCELL

#include <string>

class IntCell {
public:
    explicit IntCell(int initialValue = 0);

    int read() const;
    void write(int x);
    IntCell operator+(const IntCell &ic) const;

private:
 
 #include "intcell.rep"

};
#endif