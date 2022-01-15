/**
 * @file controller.c
 * @brief camada responsável pela ordem de execução correta da aplicação em função dos desejos dos utilizadores
 */

#include "controller.h"
#include "view.h"


#define BUFFSIZE 128


/**
 * @brief função de leitura de um inteiro para questões de controlo
 * @param min limite mínimo
 * @param max limite máximo
 * @param buffer porção de memória utilizada para armazenar temporariamente os dados necessários
 * @return inteiro a utilizar pelo interpretador
 */
int lerInt(int min, int max, char* buffer) {
    int n = -1;

    if(!(min>=max || min<0)) {
        do {
            printLerInt(min, max);
            n = atoi(fgets(buffer, BUFFSIZE, stdin));
        } while (n < min || n >max);
    }

    return n;
}

/**
 * @brief função responsável por carregar os ficheiros para o SGR
 * @return estrutura SGR carregada
 */
SGR carregarFicheiros() {
    menuPath();
    char* buffer = malloc(sizeof (char) * BUFFSIZE);
    int n = lerInt(1, 2, buffer);
    clock_t start, end;
    SGR sgr;

    char *users_path = "Files/users_full.csv", *business_path = "Files/business_full.csv", *reviews_path = "Files/reviews_1M.csv";

    if(n==2) {
        printUsersPath();
        users_path = strtok(fgets(buffer, BUFFSIZE, stdin),"\n");
        printBusinessPath();
        business_path = strtok(fgets(buffer, BUFFSIZE, stdin),"\n");
        printReviewPath();
        reviews_path = strtok(fgets(buffer, BUFFSIZE, stdin),"\n");
    }

    start = clock();
    sgr = load_sgr(users_path, business_path, reviews_path);
    end = clock();

    printTime(start, end);

    return sgr;
}

/**
 * @brief função responsável por remover os espaços iniciais desnecessários
 * @param str string a remover oos espaços
 */
void removeSpaces(char *str){
    if(str) {
        int count = 0;
        for (int i = 0; str[i]; i++)
            if (str[i] != ' ')
                str[count++] = str[i];
        str[count] = '\0';
    }
}

/**
 * @brief função que desempenha o papel de parse dos argumentos do sgr
 * @param line linha a dar parse
 * @param argv array onde é guardada a informação retirada pelo parser
 * @param argc tamanho do array
 * @param mid delimitador do meio
 * @param end delimitador do fim
 * @return vetor argv
 */
char** parseArgs(char* line, char** argv, int* argc, char* mid, char* end) {
    char* aux;
    while((aux = strsep(&line,mid)) && line){
        argv = realloc(argv, sizeof(char *) * ((*argc) + 1));
        argv[(*argc)++] = strdup(aux);
    }
    strtok(aux,end);
    argv = realloc(argv, sizeof(char*) * ((*argc)+1));
    argv[(*argc)++] = strdup(aux);

    return argv;
}

/**
 * @brief função responsável pela formação da estrutura table
 * @param t table a utilizar pela função
 */
void controllerTable(TABLE t) {
    int page=0, max=6, size=getLine(t), maxpage = (size-1)/max, r=1, aux;
    char buffer[32];

    while(r) {
        printTable(t, page, max, maxpage, size);

        fgets(buffer, 32 ,stdin);
        strtok(buffer, "\n");

        if((strcmp(buffer,"n")==0 || strcmp(buffer,"N")==0) && page<maxpage)
            page++;
        else if((strcmp(buffer,"p")==0 || strcmp(buffer,"P")==0) && page>0)
            page--;
        else if(strcmp(buffer,"f")==0 || strcmp(buffer,"F")==0)
            page = 0;
        else if(strcmp(buffer,"l")==0 || strcmp(buffer,"L")==0)
            page = maxpage;
        else if(strcmp(buffer,"q")==0 || strcmp(buffer,"Q")==0)
            r=0;
        else if(isdigit(buffer[0]) && (aux=atoi(buffer))>0 && aux<=maxpage+1)
            page = aux-1;
    }
}

/**
 * @brief função responsável por lidar com um comando inserido pelo utilizador do sistema
 * @param comando comando a ser lido pelo controller
 * @param sgr estrutura sgr
 * @param vars estrutura table com as variáveis em questão
 * @return inteiro resultante da interpretação do comando
 */
int handleCommand (char * comando, SGR sgr, TABLE* vars){
    comando = strtok(comando, "\n");
    removeSpaces(comando);

    if(strcmp("quit",comando)==0)
        return 1;

    char* var, *function;
    char** argv = NULL;
    int argc=0;

    if(strstr(comando,"=")){
        var = strsep(&comando,"=");
        // indexação
        if(strstr(comando, "[")) {
            function = strsep(&comando, "[");

            argv = realloc(argv, sizeof(char *) * (argc + 1));
            argv[argc++] = strdup(strsep(&comando,"]"));
            strsep(&comando,"[");
            argv = realloc(argv, sizeof(char*) * (argc +1));
            argv[argc++] = strdup(strsep(&comando,"]"));

            TABLE t = vars[function[0] - 'a'];
            if(argc==2 && t && isdigit(argv[0][0]) && isdigit(argv[1][0])) {
                int i = atoi(argv[0]);
                int j = atoi(argv[1]);
                if(i>=0 && i<getLine(t) && j>=0 && j<getCol(t)) {
                    vars[var[0] - 'a'] = newIndex(t, i, j);
                    printIndexacaoExecutada();
                }
                else
                    printErro();
            } else
                printErro();
        }
        else {
            function = strsep(&comando, "(");
            argv = parseArgs(comando, argv, &argc, ",", ")");
            //proj
            if(strcmp("proj", function)==0){
                TABLE t = vars[argv[0][0]-'a'];
                if(argc==2 && t && isdigit(argv[1][0])) {
                    int j = atoi(argv[1]);
                    if(j>=0 && j<getCol(t)) {
                        vars[var[0] - 'a'] = newCollumn(t, j);
                        printProjecaoExecutada();
                    }
                    else
                        printErro();
                }
                else
                    printErro();
            }
            //fromCSV
            else if(strcmp("fromCSV",function)==0){
                if(argc==2 && strlen(argv[1])==1) {
                    vars[var[0] - 'a'] = fromCSV(argv[0], argv[1][0]);
                    printLoadFromCSV();
                }
                else
                    printErro();
            }
            //query 2
            else if(strcmp("businesses_started_by_letter", function)==0){
                if(argc==2 && strcmp(argv[0], "sgr")==0 && strlen(argv[1])==1) {
                    if (vars[var[0] - 'a'])
                        freeTable(vars[var[0] - 'a']);
                    vars[var[0] - 'a'] = businesses_started_by_letter(sgr, argv[1][0]);
                    printQuerieExecutada();
                }
                else
                    printErro();
            }
            //query 3
            else if(strcmp("business_info", function)==0){
                if(argc==2 && strcmp(argv[0], "sgr")==0) {
                    if (vars[var[0] - 'a'])
                        freeTable(vars[var[0] - 'a']);
                    vars[var[0] - 'a'] = business_info(sgr,argv[1]);
                    printQuerieExecutada();
                }
                else
                    printErro();
            }
            //query 4
            else if(strcmp("businesses_reviewed",function)==0){
                if(argc==2 && strcmp(argv[0], "sgr")==0) {
                    if (vars[var[0] - 'a'])
                        freeTable(vars[var[0] - 'a']);
                    vars[var[0] - 'a'] = businesses_reviewed(sgr, argv[1]);
                    printQuerieExecutada();
                }
                else
                    printErro();
            }
            //query 5
            else if(strcmp("businesses_with_stars_and_city",function)==0){
                if(argc==3 && strcmp(argv[0], "sgr")==0) {
                    if (vars[var[0] - 'a'])
                        freeTable(vars[var[0] - 'a']);
                    vars[var[0] - 'a'] = businesses_with_stars_and_city(sgr, atof(argv[1]), argv[2]);
                    printQuerieExecutada();
                }
                else
                    printErro();
            }
            //query 6
            else if(strcmp("top_businesses_by_city",function)==0){
                if(argc==2 && strcmp(argv[0], "sgr")==0) {
                    if (vars[var[0] - 'a'])
                        freeTable(vars[var[0] - 'a']);
                    vars[var[0] - 'a'] = top_businesses_by_city(sgr, atoi(argv[1]));
                    printQuerieExecutada();
                }
                else
                    printErro();
            }
            //query 7
            else if(strcmp("international_users",function)==0){
                if(argc==1 && strcmp(argv[0], "sgr")==0) {
                    if (vars[var[0] - 'a'])
                        freeTable(vars[var[0] - 'a']);
                    vars[var[0] - 'a'] = international_users(sgr);
                    printQuerieExecutada();
                }
                else
                    printErro();
            }
             //query 8
            else if(strcmp("top_businesses_with_category",function)==0){
                if(argc==3 && strcmp(argv[0], "sgr")==0) {
                    if (vars[var[0] - 'a'])
                        freeTable(vars[var[0] - 'a']);
                    vars[var[0] - 'a'] = top_businesses_with_category(sgr, atoi(argv[1]), argv[2]);
                    printQuerieExecutada();
                }
                else
                    printErro();
            }
             //query 9
            else if(strcmp("reviews_with_word",function)==0) {
                if (argc == 3 && strcmp(argv[0], "sgr") == 0) {
                    if (vars[var[0] - 'a'])
                        freeTable(vars[var[0] - 'a']);
                    vars[var[0] - 'a'] = reviews_with_word(sgr, atoi(argv[1]), argv[2]);
                    printQuerieExecutada();
                } else
                    printErro();
            }
        }

    }
    else if(strstr(comando,"show")){
        strsep(&comando, "(");
        var = strsep(&comando, ")");
        if(vars[var[0]-'a'])
            controllerTable(vars[var[0] - 'a']);
    }
    else if(strstr(comando,"toCSV")){
        strsep(&comando, "(");
        char** argv = NULL;
        int argc=0;
        argv = parseArgs(comando, argv, &argc, ",", ")");

        if(argc==3 && strlen(argv[0])==1 && vars[argv[0][0]-'a']) {
            toCSV(vars[argv[0][0] - 'a'], argv[1][0], argv[2]);
            printLoadToCSV();
        }
        else
            printErro();
    }
    else
        printErro();

    return 0;
}


/**
 * @brief interpretador do sistema
 */
void interpretador() {
    ssize_t tamComando;
    size_t len = 0;
    char* comando = NULL;
    const char spliter[2]=";";
    char* split;
    int size, r=0;
    char **buffer;
    TABLE *vars = malloc(sizeof(TABLE) * 26);
    SGR sgr = carregarFicheiros();

    printInsert();
    while ((tamComando = getline(&comando,&len, stdin))){
        if(comando[tamComando-2]==';'){
            size=0;
            buffer = NULL;

            while((split = strsep(&comando,spliter)) && comando){
                buffer = realloc(buffer, sizeof(char*) * (size+1));
                buffer[size++] = strdup(split);
            }

            for(int j =0;j<size;j++) {
                if (buffer[j]) {
                    r = handleCommand(buffer[j], sgr, vars);
                    if (r)
                        break;
                    free(buffer[j]);
                }
            }
            free(buffer);

            if(r)
                break;

            printInsert();
        }
        else
            printErro();
    }

    free_sgr(sgr);
    printSair();
}