typedef struct labelTable {
    int labelId;
    int labelAddress;
    struct labelTable *NEXT;
}labelTable;

void labelInstall (int labelId, int labelAddress);

int getLabel(int labelId);

void parse1();

void parse2();
