/*  
 *  @author: dwclake
 */

#include <string.h>
#include "scanner/test_scanner.h"

int main(int argv, char** argc) {
    if (argv <= 2) return -1;

    if (strncmp(argc[1], "scanner", 8) == 0) {
        return test_scanner(argc[2]);       
    }

    return 0;
}
