struct labelTable *labelStart = NULL;
struct labelTable *labelEnd = NULL;

int lineCache = 2056;

void labelInstall(int labelId, int labelAddress){

    struct labelTable *newLabel = malloc(sizeof(struct labelTable));
    newLabel->labelId = labelId;
    newLabel->labelAddress = labelAddress;
    newLabel->NEXT = NULL;

    if (labelEnd == NULL){
        labelStart = labelEnd = newLabel;
    }else{
        labelEnd->NEXT = newLabel;
        labelEnd = newLabel;
    }
}


int getLabel(int labelId){
    struct labelTable *iterator = NULL;
    iterator = labelStart;

    while(iterator != NULL){
        if(iterator->labelId == labelId)
            return iterator->labelAddress;
        iterator = iterator -> NEXT;
    }
}



void parse1(){
	fp = fopen("intermediate.xsm", "r+");
	target = fopen("target1.xsm", "w+");
	char line[280];
	int i = 8;
	int labelId;
	while(i--){
		fgets(line, sizeof(line), fp);
		fprintf(target, "%s", line);
	}

	while(fgets(line, sizeof(line), fp)){
		if(line[0]=='L' && line[1] != 'E' && line[1] != 'T'){
			labelId = 0;
			i = 1;
			while(line[i] != ':'){
				labelId *= 10;
				labelId += (line[i]-48);
				i++;
			}
			printf("Found L%d\n", labelId);
			labelInstall(labelId, lineCache);
		}
		else{
			fprintf(target, "%s", line);
			lineCache += 2;
		}
	}
	fclose(target);
	fclose(fp);
}

void parse2(){
	target = fopen("target.xsm","w+");
	fp = fopen("target1.xsm","r+");

	char line[280];
	int i,labelId,registerId;

	while(fgets(line, sizeof(line),fp)){
		if(line[0] == 'J'){
			if(line[1] == 'M' && line[2] == 'P'){
				labelId = 0;
				i = 5;
				while(line[i]!='\n' && line[i]!='\0'){
					labelId *= 10;
					labelId += (line[i]-48);
					i++;
				}
				labelId = getLabel(labelId);
				fprintf(target,"JMP %d\n",labelId);
			}
			if(line[1]=='Z'){
				registerId = 0;
				i = 4;
				while(line[i] != ',' && line[i] != ' '){
					registerId *= 10;
					registerId += (line[i]-48);
					i++;
				}
				while(line[i] != 'L') i++;
				i++;

				labelId = 0;
				while(line[i]!='\n' && line[i]!='\0'){
					labelId *= 10;
					labelId += (line[i]-48);
					i++;
				}
				labelId = getLabel(labelId);
				fprintf(target,"JZ R%d, %d\n", registerId, labelId);

			}
		}else{
			fprintf(target,"%s",line);
		}
	}
}
