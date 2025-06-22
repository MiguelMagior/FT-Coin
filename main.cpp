#include "Controller.hpp"
#include "DataBaseType.hpp"

int main(){
    Controller* control = new Controller(MEMORY);
    control->start();
    delete(control);
	return 0;
}
