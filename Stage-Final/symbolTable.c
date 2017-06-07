//globalStart and globalEnd to keep record of  start and end of Symbol table
struct Gsymbol *globalStart = NULL;
struct Gsymbol *globalEnd = NULL;

struct Gsymbol* Glookup(char *NAME){
    struct Gsymbol *iterator = NULL;
    iterator = globalStart;

    while(iterator != NULL){
        if(strcmp(iterator->NAME, NAME)== 0)     // Variable found
            break;

        iterator = iterator->NEXT;
    }
    return iterator;
}

int currentStack = 4096;

void Ginstall (char *NAME, int TYPE, int SIZE){

    if(Glookup(NAME) != NULL){
        printf("Variable %s already exists\n", NAME);
        exit(1);

        return;
    }
    struct Gsymbol *newSymbol = malloc(sizeof(struct Gsymbol));

    newSymbol->NAME = NAME;
    newSymbol->TYPE = TYPE;
    newSymbol->SIZE = SIZE;
    newSymbol->BINDING = malloc(SIZE*sizeof(int));
    newSymbol->stackAddress = currentStack;
    currentStack += SIZE;
    newSymbol->NEXT = NULL;

    if(globalEnd == NULL){
        globalEnd = globalStart = newSymbol;
    }else{
        globalEnd->NEXT = newSymbol;
        globalEnd = newSymbol;
    }
}
