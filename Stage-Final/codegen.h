int registerAlloc();

void registerDealloc();

void writeHeader();

int getStackAddress(struct tnode* T);

int codeGenerate(struct tnode* T);

void targetGenerate(struct tnode* T);
