int regnum = -1;

int labelCount = 0;

int registerAlloc(){
    regnum++;
    return regnum;
}

void registerDealloc(){
    regnum--;
    return;
}

void writeHeader(){
    fprintf(fp, "0\n2056\n0\n0\n0\n0\n0\n0\n");
    fprintf(fp,"MOV SP, %d\n",currentStack-1);
    fprintf(fp,"MOV BP, %d\n",currentStack);
    fprintf(fp,"PUSH R0\n");
    return;
}

int codeGenerate(struct tnode* T){
    int reg1, reg2;

    struct Gsymbol* Gptr;
    int startLabel, endLabel;

    if(T == NULL)
        return -1;

    if(T->TYPE == -1){
        codeGenerate(T->Ptr1);
        codeGenerate(T->Ptr2);
    }else{
        switch (T->NODETYPE) {
            case PLUS:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "ADD R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case MINUS:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "SUB R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case MUL:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "MUL R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case DIV:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "DIV R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case LT:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "LT R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case GT:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "GT R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case EQ:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "EQ R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case LE:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "LE R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case GE:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "GE R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;



            case NEQ:
                reg1 = codeGenerate(T->Ptr1);
                reg2 = codeGenerate(T->Ptr2);
                fprintf(fp, "NEQ R%d, R%d\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case CONST:
                reg1 = registerAlloc();
                fprintf(fp, "MOV R%d, %d\n", reg1, T->VALUE );
                return reg1;
                break;


            case ID:
                reg1 = registerAlloc();
                reg2 = getStackAddress(T);
                fprintf(fp, "MOV R%d, [R%d]\n", reg1, reg2 );
                registerDealloc();
                return reg1;
                break;


            case READ:
                reg1 = registerAlloc();

                fprintf(fp, "MOV R%d, \"Read\"\n", reg1 );
                fprintf(fp, "PUSH R%d\n", reg1 );

                fprintf(fp, "MOV R%d, -1\n", reg1 );
                fprintf(fp, "PUSH R%d\n", reg1 );

                reg2 = getStackAddress(T->Ptr1);
                fprintf(fp, "MOV R%d, R%d\n", reg1, reg2 );
                fprintf(fp, "PUSH R%d\n", reg1 );

                fprintf(fp, "PUSH R%d\n", reg1 );
                fprintf(fp, "PUSH R%d\n", reg1 );

                fprintf(fp, "CALL 0\n");
                fprintf(fp, "POP R%d\n", reg1);
                fprintf(fp, "POP R%d\n", reg1);
                fprintf(fp, "POP R%d\n", reg1);
                fprintf(fp, "POP R%d\n", reg1);
                fprintf(fp, "POP R%d\n", reg1);
                registerDealloc();
                registerDealloc();
                return -1;


            case WRITE:
                reg1 = codeGenerate(T->Ptr1);

                fprintf(fp, "MOV [%d], R%d\n", 1024, reg1 );

                fprintf(fp, "MOV R%d, \"Write\"\n", reg1);
                fprintf(fp, "PUSH R%d\n", reg1);             // FUNC CODE

                fprintf(fp,"MOV R%d, -2\n",reg1);
                fprintf(fp,"PUSH R%d\n",reg1);                   //1st ARG
                fprintf(fp,"MOV R%d, 1024\n",reg1);
                fprintf(fp,"PUSH R%d\n",reg1);                   //2nd ARG ADDR of RESULT

                fprintf(fp,"PUSH R%d\n",reg1);                   // 3rd ARG
                fprintf(fp,"PUSH R%d\n",reg1);                   // RESULT

                fprintf(fp,"CALL 0\n");
                fprintf(fp,"POP R%d\n",reg1);
                fprintf(fp,"POP R%d\n",reg1);
                fprintf(fp,"POP R%d\n",reg1);
                fprintf(fp,"POP R%d\n",reg1);
                fprintf(fp,"POP R%d\n",reg1);
                registerDealloc();
                return -1;


            case IF:
                startLabel = labelCount+1;
                endLabel = labelCount+2;
                labelCount += 2;

                reg1 = codeGenerate(T->Ptr1);
                fprintf(fp,"JZ R%d, L%d\n", reg1, startLabel);

                codeGenerate(T->Ptr2);
                fprintf(fp,"JMP L%d\n", endLabel);

                ////ELSE PART
                fprintf(fp,"L%d:\n", startLabel);
                codeGenerate(T->Ptr3);

                fprintf(fp,"L%d:\n", endLabel);
                registerDealloc();
                return -1;



            case WHILE:
                startLabel = labelCount+1;
                endLabel = labelCount+2;
                labelCount+=2;

                fprintf(fp,"L%d:\n",startLabel);
                reg1 = codeGenerate(T->Ptr1);

                fprintf(fp,"JZ R%d, L%d\n",reg1, endLabel);
                codeGenerate(T->Ptr2);

                fprintf(fp,"JMP L%d\n",startLabel);
                fprintf(fp,"L%d:\n",endLabel);
                registerDealloc();
                return -1;



            case ASSGN:
                reg1 = codeGenerate(T->Ptr2);
                reg2 = getStackAddress(T->Ptr1);

                fprintf(fp,"MOV [R%d], R%d\n",reg2,reg1);


                registerDealloc();
                registerDealloc();
                return -1;


        }
    }
}



int getStackAddress(struct tnode* T){
    int reg1, reg2;

    reg1 = registerAlloc();
    struct Gsymbol *Gentry;
    Gentry = Glookup(T->NAME);

    fprintf(fp,"MOV R%d, %d\n",reg1,Gentry->stackAddress);

    if(T->Ptr1 != NULL){
        reg2 = codeGenerate(T->Ptr1);
        fprintf(fp,"ADD R%d, R%d\n",reg1,reg2);
        registerDealloc();
    }
    return reg1;
}



void targetGenerate(struct tnode* T){
    fp = fopen("intermediate.xsm","w+");
    writeHeader();
    codeGenerate(T);
    fclose(fp);
    printf("Intermediate Code Generation Complete\n");

    parse1();
    printf("Label Table Created\n");

    parse2();
    printf("Target Code Generated\n");
    //exit(1);
    return;
}
