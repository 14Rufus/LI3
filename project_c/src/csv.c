#include "csv.h"

/**
 * @brief Forma um ficheiro csv através de uma table dada
 * @param x Table que pretendemos guardar
 * @param delim Delimitador usado no ficheiro
 * @param filepath Path onde ficará guardado o ficheiro
 */
void toCSV(TABLE x, char delim, char* filepath) {
    FILE* f = fopen(filepath, "w");

    for(int i=0; i<getCol(x); i++) {
        if (i == getCol(x) - 1)
            fprintf(f, "%s\n", getInfo(x, i));
        else
            fprintf(f, "%s%c", getInfo(x, i), delim);
    }

    for(int i=0; i<getLine(x); i++) {
        for (int j = 0; j < getCol(x); j++) {
            if (j == getCol(x)-1)
                fprintf(f, "%s", getList(x, i, j));
            else
                fprintf(f, "%s%c", getList(x, i, j), delim);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

/**
 * @brief Lê um ficheiro csv e retorna uma tabela com o seu conteúdo
 * @param filepath Path onde está o ficheiro
 * @param delim Delimitador usado no ficheiro
 * @return Table com os dados que estavam no ficheiro
 */
TABLE fromCSV(char* filepath, char delim) {
    FILE *f = fopen(filepath, "r");

    int size = 1024;
    char *buffer = malloc(sizeof(char) * size);

    int line=0, col=0, i;
    char **info=NULL, *aux, *aux2, ***list=NULL;

    fgets(buffer, size, f);
    aux2 = buffer;
    while((aux=strsep(&aux2, &delim)) && aux2) {
        info=realloc(info, sizeof(char*)*(col+1));
        info[col++] = strdup(aux);
    }
    strtok(aux, "\n");
    info=realloc(info, sizeof(char*)*(col+1));
    info[col++] = strdup(aux);

    while(fgets(buffer, size, f)){
        unsigned long len = strlen(buffer);
        if (len == size-1 && buffer[len-2] != '\n') {
            fseek(f, -len, SEEK_CUR);
            size *= 2;
            buffer = realloc(buffer, size);
            continue;
        }

        i=0;
        list = realloc(list, sizeof(char**) * (line+1));
        list[line] = malloc(sizeof(char*) * col);

        aux2 = buffer;
        while((aux=strsep(&aux2, &delim)) && aux2)
            list[line][i++] = strdup(aux);

        strtok(aux, "\n");
        list[line][i++] = strdup(aux);

        line++;
    }
    free(buffer);
    fclose(f);

    return newCSV(line, col, info, list);
}