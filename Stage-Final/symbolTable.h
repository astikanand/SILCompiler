typedef struct Gsymbol {
	char *NAME;
	int TYPE; 		// INT OR BOOLEAN
	int SIZE; 		// Size field for arrays
	int *BINDING; 	// Address of the Identifier in Memory
	int stackAddress; 
	struct Gsymbol *NEXT; // Pointer to next Symbol Table Entry */
}Gsymbol;

struct Gsymbol* Glookup(char *NAME); // Look up for a global identifier

void Ginstall (char *NAME, int TYPE, int SIZE); // Installation
