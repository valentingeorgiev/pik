#include <stdio.h>
#include <stdlib.h>

void write();
int read(char ***name_product, char ***barcode, double **price_product);
void print(char ***name_product, char ***barcode, double **price_product, int counter);

int main(){
  char **name_product;
  char **barcode;
  double *price_product;
  char choise;
  int counter = 0;
  int i = 0;
  do{
    printf("\n");
    printf("------------------\n");
    printf("Press 0 to exit\n");
    printf("Press 1 to write\n");
    printf("Press 2 to read\n");
    printf("------------------\n");
    printf("Your choice: ");

    choise=getchar();
    fflush(stdin);
    printf("------------------\n");

    switch(choise){
      case '1':
        write();
        break;
      case '2':
        counter = read(&name_product, &barcode, &price_product);
        print(&name_product, &barcode, &price_product, counter);
        break;
      case '0':
        printf("Goodbye\n");
        break;
      default:
        printf("Wrong Choice. Enter again.\n");
        break;
    }
  }while(choise!='0');

  for(i = 0; i < counter; i++){
    free(name_product[i]);
    free(barcode[i]);
  }
  free(name_product);
  free(barcode);
  free(price_product);

  return 0;
}

void write(){
  char *name_product = NULL;
  char *barcode = NULL;
  double price_product;
  int size_name_product = 1;
  int size_barcode = 1;

  name_product = (char *) malloc(1);
  barcode = (char *) malloc(1);

  FILE *fp;
  fp = fopen("shop.bin", "ab");
  if (fp == NULL){
    printf("the file cant open for writing\n");
    exit(1);
  }

  printf("Enter product name: ");
  while(1){
    name_product[size_name_product-1]  = getchar();
    if(name_product[size_name_product-1] == '\n'){
      name_product[size_name_product-1]='\0';
      break;
    }
    name_product = (char*) realloc(name_product, ++size_name_product);
  }

  if(fwrite(&size_name_product, sizeof(int), 1, fp) != 1){
    printf("unsuccesful writing of the size of name_product");
    exit(1);
  }

  if(fwrite(name_product, 1, size_name_product, fp) != size_name_product){
    printf("unsuccesful writing the string name_product\n");
    exit(1);
  }

  printf("Enter barcode: ");
  while(1){
    barcode[size_barcode-1]  = getchar();
    if(barcode[size_barcode-1] == '\n'){
      barcode[size_barcode-1]='\0';
      break;
    }
    barcode = (char*) realloc(barcode, ++size_barcode);
  }

  if(fwrite(&size_barcode, sizeof(int), 1, fp) != 1){
    printf("unsuccesful writing of the size of barcode");
    exit(1);
  }

  if(fwrite(barcode, 1, size_barcode, fp) != size_barcode){
    printf("unsuccesful writing the string name_product\n");
    exit(1);
  }

  printf("Enter the price of the product: ");
  scanf("%lf", &price_product);
  fflush(stdin);
  if(fwrite(&price_product, 8, 1, fp) != 1){
    printf("writening error price");
    exit(1);
  }

  fclose(fp);
  free(name_product);
  free(barcode);
}

int read(char ***name_product, char ***barcode, double **price_product){

  int i=0;
  int counter = 0;
  int sizeof_name_product = 0;
  int sizeof_barcode = 0;
  int size = 5;

  *name_product =  malloc(sizeof(int*) * size);
  *barcode =  malloc(sizeof(int*) * size);
  *price_product = (double *) malloc(sizeof(double) * size);

  for(i=0; i < size ;i++){
    (*name_product)[i] = (char *) malloc(50);
    (*barcode)[i] = (char *) malloc(50);
  }

  FILE *fp;
  fp = fopen ("shop.bin","rb");
  if (fp == NULL){
    printf("the file cant open for reading\n");
    exit(1);
  }

  while(1){
    if (fread (&sizeof_name_product, sizeof(int), 1, fp) != 1){
      break;
    }

    if (fread ((*name_product)[counter], 1, sizeof_name_product, fp) != sizeof_name_product){
      puts("error reading the name_product\n");
      break;
		}

    if (fread (&sizeof_barcode, sizeof(int), 1, fp ) != 1){
      break;
    }

    if (fread ((*barcode)[counter], 1, sizeof_barcode, fp ) != sizeof_barcode){
      puts("Error reading the barcode\n");
      break;
    }

    if (fread (&(*price_product)[counter], 8 , 1 , fp ) != 1) {
      printf("readung error price");
      exit (1);
    }

    counter++;

    if ( counter == size){
      size *= 2;

      *name_product = realloc(*name_product, sizeof(int*) * size);
      *barcode = realloc(*barcode, sizeof(int*) * size);

      for( ; i < size ; i++ ){
        (*name_product)[i] = (char *) malloc(30);
        (*barcode)[i] = (char *) malloc(30);
      }
      *price_product = (double *) realloc(*price_product, sizeof(double) * size);
    }
  }

  return counter;
}

void print(char ***name_product, char ***barcode, double **price_product, int counter){
  int i = 0;
  for (i = 0; i < counter; i++) {
    printf("Product name: %s\t",(*name_product)[i]);
    printf("Barcode: %s\t",(*barcode)[i]);
    printf("Price: %f\t \n",(*price_product)[i]);
  }
}