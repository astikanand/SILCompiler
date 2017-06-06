typedef struct tnode {
	int TYPE;
	// For Slist : "-1",
    // For stmt, variable : "0" at start later modified
	// For true & false : "BOOL"
	// For number : "INT"
	// For Expression : "INT" or "BOOL" depending on expression

    int NODETYPE;
    // For Stmtlist : "-1"
    // For true, false, number : "CONST"
    // For Variable : "ID"
    // For Stmt : It can be "READ", "WRITE", "ASSGN", "IF", "WHILE"
    // For expression: It can be "PLUS", "MINUS", "MUL", "DIV", "MOD", "LT", "GT", "LE", "GE" etc

	int VALUE;
	// For true "1" and false "0"
	// For number it is it's absolute value
	// For variable "0"
	// For Stlist, stmt and expressions their value : "0"

	char *NAME;
	// For variable name is is their name
	// For others : "\0"

	struct tnode *Ptr1, *Ptr2, *Ptr3;
	// Maximum of three subtrees 3 required for IF THEN ELSE

	struct Gsymbol *Gentry;
	// For global identifiers/functions

}tnode;


// Create an empty Tree node
struct tnode* createEmptyTreeNode();

/* Creating nodes for identified tokens */
struct tnode *treeCreate(int TYPE, int NODETYPE, int VALUE, char *NAME, struct tnode* Ptr1, struct tnode* Ptr2, struct tnode* Ptr3);

// Evaluate the Tree
void evaluate(struct tnode* T);

// Evaluating Expressions
int evaluateExpression(struct tnode* T);

void updateEntry(struct tnode* T);

void typeCheckNodes(struct tnode* LEFT, struct tnode* RIGHT, int INT_BOOL);

void typeCheckNode(struct tnode* LEFT, int INT_BOOL);

void typeCheckNodesEq(struct tnode* LEFT, struct tnode* RIGHT);
