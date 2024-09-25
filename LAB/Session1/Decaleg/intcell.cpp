#include "intcell.hpp"

IntCell::IntCell(int initialValue) {
    _storedValue = initialValue;
}
int IntCell::read() const {
    return _storedValue;
}
void IntCell::write(int x) {
    _storedValue = x;
}
IntCell IntCell::operator+(const IntCell &ic) const {
    IntCell res(_storedValue + ic._storedValue);
    return res;
}