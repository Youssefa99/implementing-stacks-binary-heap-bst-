#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union{
float fData;
char cData;
}Item;


typedef struct{
char var[100];
char value[100];
int Ivalue;
float Fvalue;
}data;

// Stack
typedef struct
{
    Item Arr[100];
    int top;
} Stack;

// initialize stack
void init(Stack *s)
{
    s->top=0;
}

// check if stack is empty
int isempty(Stack *s)
{
    if(s->top<=0)
    {

        return 1;
    }
    else
    {
        return 0;
    }
}

// view element on top of stack
Item top(Stack *s)
{
    Item top;
    top = s->Arr[s->top-1];
    return top;
}

// pop top element from stack
Item pop(Stack *s)
{

    s->top--;
    Item lastchar;

    lastchar = s->Arr[s->top];
    // s->top--;
    return lastchar;
}

// push element into stack
void push(Stack *s, Item val)
{

    s->Arr[s->top] = val;
    s->top++;
}

// de-allocate stack pointer from memory
void destroy(Stack *s)
{
    while(s->top!=-1)
    {
        free(s);
        s->top--;
    }
    free(s);
}

// decide operator precedence in a mathematical equation
int precedence(char X)
{
    switch(X)
    {
    case '*':
        return 2;
    case '/':
        return 2;
    case '%':
        return 2;
    case '+':
        return 1;
    case '-':
        return 1;
    case '(':
        return 3;
    }
}

// evaluate precedence order
float fer(char symbol,float op1,float op2)
{
    //printf("line 97");
    if(symbol == '+')/* exponent operator, highest precedence*/
    {
        return(op1+op2);
    }
    else if(symbol == '-')
    {
        return(op1-op2);
    }
    else if(symbol == '*')          /* lowest precedence */
    {
        return(op1*op2);
    }
    else if(symbol == '/'){
        return op1/op2;
    }
    else
    {
        return(0);
    }
}

// convert to string
char* createString(char arr[], int size){
char* str = malloc(size);
for(int i = 0 ; i < size ; i++){
    str[i] = arr[i];
}
str[size] = '\0';
return str;
}

// Convert mathematical equation from infix expression to postfix expression 
char* infixToPostfix(char* infix)
{
    char* str;
    char test[100];
    //printf("\nto be converted: %s\n",infix);
    int k = 0;
int i;
int j=0;
Stack s;
char postfix2[100];
char a;
init(&s);
Item temp;
int beforebracket = 0;
int sign = 0;
for(i=0;i<strlen(infix);i++)
{
	// check if number is positive or negative	
    if(infix[i] == '-'){
        if(!isdigit(infix[i-1]) || infix[i-1] == '(' || i - 1 < 0)
                sign = 1;
    }
// check if character is followed by brackets 
if(infix[i+1] == '('){
beforebracket = 1;
}
// if it's a digit add to postfix
    if(isdigit(infix[i])){
	    
postfix2[j]= '(';
 j++;
// add expression between the brackets to postfix expression
 while(isdigit(infix[i]) || infix[i] == '.'){
    postfix2[j] = infix[i];
    j++;
    i++;
}
 postfix2[j] = ')';
 j++;
 i = i - 1; // resume parsing string starting from ')'
 }
else if(infix[i]==')')
{
    // if closed bracket pop the stack until the top is '('
     while(!isempty(&s)&&top(&s).cData!='(')
          {

   postfix2[j] = pop(&s).cData;
	j++;
           }
    pop(&s);
/*if(beforebracket == 1){
postfix2[j] = pop(&s).cData;
j++;
}*/
}
// if number is negative sorround it with brackets in postfix expression
else if(infix[i] == '-' && sign == 1){
    postfix2[j] = '(';
    j++;
    postfix2[j] = infix[i];
    j++;
    i++;
	// if it's a negative decimal put whole decimal before closing brackets
    while(isdigit(infix[i]) || infix[i] == '.'){
        postfix2[j] = infix[i];
        j++;
        i++;
        //printf("i:%d\n",i);
    }
    postfix2[j] = ')';
    j++;

    i = i - 1;
    sign = 0;
}
// if stack is empty push the current to the stack regardless
else if(isempty(&s)){
        //printf("\n gowa el empty\n");
temp.cData = infix[i];
push(&s,temp);

}
else
{
	// no special cases: negatives, decimals or brackets
    while(!isempty(&s)&&precedence(top(&s).cData)>=precedence(infix[i])&&top(&s).cData!='('){
postfix2[j]=pop(&s).cData;
j++;         }
temp.cData = infix[i];
push(&s,temp);
}
}
while(!isempty(&s)){
    if(top(&s).cData == ')' || top(&s).cData == '('){
        pop(&s);
    }
    else{
        postfix2[j] = pop(&s).cData;
        j++;
    }
}
postfix2[j]='\0';
str = createString(postfix2,strlen(postfix2));
        return str;

}
// evaluate postfix expression
float evaluatePostfix (char* exp)
{
    Stack s;
    init(&s);
    char number[100];
    int j = 0;
 Item temp;
 int check;
    float op1,op2,val;
    int i;
    for(i=0; i<strlen(exp); i++)
    {
	    // handle brackets in postfix expression
        if(exp[i] == '('){
                i++;
                while(exp[i] != ')'){
                  number[j] = exp[i];
                  j++;
                  i++;
                }
                number[j] = '\0';
                j++;
            temp.fData = atof(number);
            push(&s,temp);
           j = 0;
           strcpy(number,"");


        }
        else
        {
            op2 = pop(&s).fData;
            op1 = pop(&s).fData;

            val = fer(exp[i],op1,op2);
temp.fData = val;
push(&s,temp);



        }
    }
    return val;
}
// compare strings if identical or not
int compareStrings(char string1[],char string2[]){
int count1 = 0;
int count2 = 0;
int check = 0;
for(int i = 0 ; i < strlen(string1) ; i++){
    count1++;
}

for(int j = 0 ; j < strlen(string2) ; j++){
    count2++;
}
// if not same size then not equal without checking for values
if(count1 != count2 - 1)
    return -1;
for(int k = 0 ; k < strlen(string1) ; k++){
    if(string1[k] == string2[k] && k != count2 - 1)
        check++;
}
if(check == count1)
    return 0;
else{
    return -1;
}
}

// copy string
char* copyString(char* string,int size){
char* str;
for(int i = 0 ; i < size ; i++){
    str[i] = string[i];
}
return str;
}

char* replaceVariables(data d[],char arr[],int size){
  int end;
int parse = 0;
int iter = 0;
char temp[100];
int idx_temp = 0;
int anchor1 = 0;
int anchor2;
int anchor3;
char neoequ[100];
int cmp;
char* convert;
char* afterconversion;
int count = 0;
float current;
    for(int k = 0 ; k < strlen(arr) ; k++){
            //printf("current variable %s:\n",d[i].value);
            //printf("%c:\n",d[i].value[k]);
            //printf("k before parsing %d\n",k);

        if(!isdigit(arr[k]) && arr[k] != '+' && arr[k] != '-' && arr[k] != '*' && arr[k] != '/' && arr[k] != '(' && arr[k] != ')' && arr[k] != '.'){
            anchor1 = k;
            //printf("gowa el if\n");
            while(!isdigit(arr[k]) && arr[k] != '+' && arr[k] != '-' && arr[k] != '*' && arr[k] != '/' && arr[k] != '(' && arr[k] != ')' && arr[k] != '.'){
              //  printf("gowa el while el oola\n");
                temp[idx_temp] = arr[k];
                idx_temp++;
                k++;

            }
            temp[idx_temp] = '\0';
            idx_temp++;
            //printf("temp is:%s\n",temp);
            k = k - 1;
            //printf("k after parsing %d\n",k);
            anchor2 = k;
            //printf("%d\n",k);

            for(int j = 0 ; j < size ; j++){
                    cmp = compareStrings(temp,d[j].var);
                  //  printf("gowa el for\n");
                  //  printf("%s......%s\n",temp,d[j].var);
                    //anchor3 = cmp;
                    //printf("%d\n",anchor3);
                    //printf("length of %s is %d\n",temp,strlen(temp));
                    //printf("length of %s is %d\n",d[j].var,strlen(d[j].var));
                    //printf("\n %c \n",d[j].var[5]);
                if(cmp == 0){
                //printf("gowa el if beta3et el for\n");
                    anchor3 = j;

                }
            }
            //printf("%s\n",d[anchor3].value);
            //printf("anchor3 is %d",anchor3);
            //printf("anchor1:%d \n",anchor1);
            //printf("length of new:%d \n",strlen(d[anchor3].value));
            //printf("value of parse: %d",parse);
            anchor2 = anchor1;
                while( parse < strlen(d[anchor3].value)){
                 //       printf("gowa el while el tanya\n");
               //     printf("%c",d[anchor3].value[parse]);
                    neoequ[anchor2] = d[anchor3].value[parse];
                    parse++;
                    anchor2++;
                }
                printf("new equation mid replacing: %s\n",neoequ);

       //         printf("neoequ is %s\n",neoequ);
         //       printf("\n 5alast el while\n");
                iter = anchor1 + 1;
                k = k + strlen(temp);
           //     printf("value iter is %d\n",iter);
             //   printf("value of parse is %d\n",parse);
               // printf("old equation is %s\n",d[i].value);
                //printf("value of k is %d\n",k);
                while(iter < strlen(arr)){
                        printf("el new equation abl ma nekamel 3aleiha: %s\n",neoequ);
                    neoequ[anchor2] = arr[iter];
                    anchor2++;
                    iter++;
                }
               /* while(parse < strlen(d[i].value)){
                    neoequ[parse] = d[i].value[anchor2];
                    anchor2++;
                    parse++;
                }*/
                strcpy(arr,neoequ);
                temp[idx_temp] = '\0';
                strcpy(temp,"");
          //      printf("d[i].value after replacing variables: %s\n", d[i].value);
            //    printf("new equation: %s\n",neoequ);


                anchor1 = 0;
                anchor2 = 0;
                anchor3 = 0;

                idx_temp = 0;
                parse = 0;
              //  k = k + strlen(d[i].value);
            //  printf("new equation after replacing variable names with values: %s",d[i].value);
        }

//printf("5alasna el leila el tanya\n");
}
printf("new equation after removing it: %s\n",neoequ);

          //  printf("expression to be converted: %s",d[i].value);
        convert = createString(arr,strlen(arr));
     //   printf("el 7an3'ayarha %s\n",convert);
        //printf("size of convert: %d\n",sizeof(convert));
        //printf("size of conversion: %d\n",sizeof(infixToPostfix(convert)));
       // convert = copyString(infixToPostfix(convert),strlen(infixToPostfix(convert)));
        //strcpy(convert,infixToPostfix(convert));

        afterconversion = infixToPostfix(convert);
        printf("\nafter conversion: %s \n",afterconversion);
        current = evaluatePostfix(afterconversion);
        printf("evaluation:%f\n",current);
        gcvt(current,10,arr);
        arr[strlen(arr) - 1] = '\0';
        //printf("%s:%s\n",d[i].var,d[i].value);

    count = 0;
    char* str;
    str = createString(neoequ,strlen(neoequ));
    return str;
    }



int main()
{
   // printf("kosom el a5tara3 el c");
    char var[100];
    char val[100];
    data d[100];
    int dec = 0;
    int sign = 0;
    int size = 0;
    char str;
    FILE* fptr;
    char* filename = "src.txt";
    fptr = fopen(filename,"r");

    if(fptr == NULL)
        printf("Could not open file");

   // while(!feof(fp)){
     //   fscanf("%[^=],%s",&var, &val);
    //}
  //  printf("yen3al deen omak \n");
while(!feof(fptr)){
    //    printf("kosom 2erayet el file\n");
fscanf(fptr, " %[^=]s  ", &d[size].var );
//printf("var name: %s",d[size].var);
fscanf(fptr, " %[^\n]s", &val);
strcpy(d[size].value,&val[2]);
//printf("\n var value: %s",d[size].value);
size++;
}
  // fscanf(fptr, " %[^=]s %[^\n]s ", &var, &val );
//printf("kosomeen 2omak yabn el 3ars");
    fclose(fptr);

    //printf("kosom el a5tara3 el c");
size = size - 1;

    //strcpy(d.value,&val[2]);
//printf("%d\n",size);
  for(int j = 0 ; j < size ; j++){
  printf("%s",d[j].var);
  printf("%s \n",d[j].value);
  }
/*  int end;
int parse = 0;
int iter = 0;
char temp[100];
int idx_temp = 0;
int anchor1 = 0;
int anchor2;
int anchor3;
char neoequ[100];
int cmp;
char* convert;
char* afterconversion;
int count = 0;
for(int i = 0 ; i < size ; i++){
        printf("original expression: %s\n",d[i].value);
        printf("new equation before modification: %s\n",neoequ);
    for(int k = 0 ; k < strlen(d[i].value) ; k++){
            //printf("current variable %s:\n",d[i].value);
            //printf("%c:\n",d[i].value[k]);
            //printf("k before parsing %d\n",k);

        if(!isdigit(d[i].value[k]) && d[i].value[k] != '+' && d[i].value[k] != '-' && d[i].value[k] != '*' && d[i].value[k] != '/' && d[i].value[k] != '(' && d[i].value[k] != ')' && d[i].value[k] != '.'){
            anchor1 = k;
            //printf("gowa el if\n");
            while(!isdigit(d[i].value[k]) && d[i].value[k] != '+' && d[i].value[k] != '-' && d[i].value[k] != '*' && d[i].value[k] != '/' && d[i].value[k] != '(' && d[i].value[k] != ')' && d[i].value[k] != '.'){
              //  printf("gowa el while el oola\n");
                temp[idx_temp] = d[i].value[k];
                idx_temp++;
                k++;

            }
            temp[idx_temp] = '\0';
            idx_temp++;
            //printf("temp is:%s\n",temp);
            k = k - 1;
            //printf("k after parsing %d\n",k);
            anchor2 = k;
            //printf("%d\n",k);

            for(int j = 0 ; j < size ; j++){
                    cmp = compareStrings(temp,d[j].var);
                  //  printf("gowa el for\n");
                  //  printf("%s......%s\n",temp,d[j].var);
                    //anchor3 = cmp;
                    //printf("%d\n",anchor3);
                    //printf("length of %s is %d\n",temp,strlen(temp));
                    //printf("length of %s is %d\n",d[j].var,strlen(d[j].var));
                    //printf("\n %c \n",d[j].var[5]);
                if(cmp == 0){
                //printf("gowa el if beta3et el for\n");
                    anchor3 = j;

                }
            }
            //printf("%s\n",d[anchor3].value);
            //printf("anchor3 is %d",anchor3);
            //printf("anchor1:%d \n",anchor1);
            //printf("length of new:%d \n",strlen(d[anchor3].value));
            //printf("value of parse: %d",parse);
            anchor2 = anchor1;
                while( parse < strlen(d[anchor3].value)){
                 //       printf("gowa el while el tanya\n");
               //     printf("%c",d[anchor3].value[parse]);
                    neoequ[anchor2] = d[anchor3].value[parse];
                    parse++;
                    anchor2++;
                }
                printf("new equation mid replacing: %s\n",neoequ);

       //         printf("neoequ is %s\n",neoequ);
         //       printf("\n 5alast el while\n");
                iter = anchor1 + 1;
                k = k + strlen(temp);
           //     printf("value iter is %d\n",iter);
             //   printf("value of parse is %d\n",parse);
               // printf("old equation is %s\n",d[i].value);
                //printf("value of k is %d\n",k);
                while(iter < strlen(d[i].value)){
                        printf("el new equation abl ma nekamel 3aleiha: %s\n",neoequ);
                    neoequ[anchor2] = d[i].value[iter];
                    anchor2++;
                    iter++;
                }
               /* while(parse < strlen(d[i].value)){
                    neoequ[parse] = d[i].value[anchor2];
                    anchor2++;
                    parse++;
                }*/
       /*         strcpy(d[i].value,neoequ);
                temp[idx_temp] = '\0';
                strcpy(temp,"");
                printf("d[i].value after replacing variables: %s\n", d[i].value);
                printf("new equation: %s\n",neoequ);


                anchor1 = 0;
                anchor2 = 0;
                anchor3 = 0;

                idx_temp = 0;
                parse = 0;
              //  k = k + strlen(d[i].value);
            //  printf("new equation after replacing variable names with values: %s",d[i].value);
        }

//printf("5alasna el leila el tanya\n");
}
end = strlen(neoequ);
                neoequ[end] = '\0';
                strcpy(neoequ,"");
printf("new equation after removing it: %s\n",neoequ);

            for(int l = 0 ; l < strlen(d[i].value) ; l++){
        //printf("gowa el for loop el nested\n");
        //printf("current variable value: %s\n",d[i].value);
       // printf("current  element: %s\n",d[x].value[l]);
        if(isdigit(d[i].value[l]) || d[i].value[l] == '.' || d[i].value[l] == '-')
            count++;
    }
  //  printf("real length: %d\n",count);
   // printf("supposed length: %d\n",strlen(d[i].value));
    if(count != strlen(d[i].value)){
          //  printf("expression to be converted: %s",d[i].value);
        convert = createString(d[i].value,strlen(d[i].value));
     //   printf("el 7an3'ayarha %s\n",convert);
        //printf("size of convert: %d\n",sizeof(convert));
        //printf("size of conversion: %d\n",sizeof(infixToPostfix(convert)));
       // convert = copyString(infixToPostfix(convert),strlen(infixToPostfix(convert)));
        //strcpy(convert,infixToPostfix(convert));
        afterconversion = infixToPostfix(convert);
        //printf("\nafter conversion: %s \n",afterconversion);
        d[i].Fvalue = evaluatePostfix(afterconversion);
        gcvt(d[i].Fvalue,10,d[i].value);
        d[i].value[strlen(d[i].value) - 1] = '\0';
        //printf("%s:%s\n",d[i].var,d[i].value);
    }
    count = 0;

    }/*

//printf("5alasna el leila dy\n");

/*
for(int x = 0 ; x < size ; x++){
        //printf("gowa el for loop\n");
    for(int l = 0 ; l < strlen(d[x].value) ; l++){
        printf("gowa el for loop el nested\n");
        printf("current variable value: %s\n",d[x].value);
       // printf("current  element: %s\n",d[x].value[l]);
        if(isdigit(d[x].value[l]) || d[x].value[l] == '.' || d[x].value[l] == '-')
            count++;
    }
    printf("real length: %d\n",count);
    printf("supposed length: %d\n",strlen(d[x].value));
    if(count != strlen(d[x].value)){
        convert = createString(d[x].value,strlen(d[x].value));
        printf("el 7an3'ayarha %s\n",convert);
        //printf("size of convert: %d\n",sizeof(convert));
        //printf("size of conversion: %d\n",sizeof(infixToPostfix(convert)));
       // convert = copyString(infixToPostfix(convert),strlen(infixToPostfix(convert)));
        //strcpy(convert,infixToPostfix(convert));
        afterconversion = infixToPostfix(convert);
        printf("\nafter conversion: %s \n",afterconversion);
        d[x].Fvalue = evaluatePostfix(afterconversion);
    }
    count = 0;
printf("5alasna el leila el tanya\n");
}*/
int count = 0;
char* current;
for(int i = 0 ; i < size ; i++){
            for(int l = 0 ; l < strlen(d[l].value) ; l++){
        //printf("gowa el for loop el nested\n");
        //printf("current variable value: %s\n",d[i].value);
       // printf("current  element: %s\n",d[x].value[l]);
        if(isdigit(d[i].value[l]) || d[i].value[l] == '.' || d[i].value[l] == '-')
            count++;
            }
  //  printf("real length: %d\n",count);
   // printf("supposed length: %d\n",strlen(d[i].value));
    if(count != strlen(d[i].value)){
        current = replaceVariables(d,d[i].value,size);
        printf("xxxx:%s",current);
    }
}
printf("final values:\n");
for(int i = 0 ; i < size ; i++){
    printf("%s",d[i].var);
    printf("%f\n",d[i].Fvalue);
}
    return 0;
}
