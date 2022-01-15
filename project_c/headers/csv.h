#ifndef __csv_h
#define __csv_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sgr.h"

void toCSV(TABLE x, char delim, char* filepath);
TABLE fromCSV(char* filepath, char delim);

#endif //PROJECT_C_CSV_H
