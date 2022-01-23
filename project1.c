// Serkan Koc  150118073
// Atila İlhan Yatagan 150118033
// Enes Uzun 150119607
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
// Struct codes for project, customer,basket and product list.

typedef struct customer_list{
    int id;
    char *name;
    char *surname;
    struct customer_list* customer_next;
    struct basket_list* basket_ptr;
}customer_list;

typedef struct basket_list{
    int id;
    int amount;
    struct basket_list* basket_next;
    struct product_list* product_ptr;
}basket_list;

typedef struct product_list{
    int id;
    char *name;
    char *category;
    int price;
    struct product_list* product_next;
}product_list;

typedef customer_list* customer_listPtr;
typedef basket_list* basket_listPtr;
typedef product_list* product_listPtr;

void addCustomer(customer_listPtr* root_customerPtr,char *customerName,char *customerSurname,int customerId );
void printCustomerList(customer_listPtr currentPtr);
void addProduct(product_listPtr * root_productPtr,char *productName,char *productCategory,int productId,int productPrice);
void addBasket(int customerID,int basketID,customer_listPtr* root_customerPtr);
void addProductToBasket (int customerID,int basketID,customer_listPtr* root_customerPtr,product_listPtr * root_productPtr,int productID);
int isEmptyProduct(product_listPtr sPtr);
int isEmptyCustomer(customer_listPtr sPtr);
int hasBasket(customer_listPtr currentCustomer);
void printProductList(product_listPtr currentPtr);
void instructions();
void addCustomerFromMenu(customer_listPtr* currentPtr);
void removeCustomerFromMenu(customer_listPtr* currentPtr);
void customersWhoBoughtaProduct(int productID,customer_listPtr *root_customerPtr,product_listPtr *root_productPtr);
void func2(customer_listPtr *root_customerPtr,product_listPtr *root_productPtr,int customerID3);
void totalShoppingAmount(customer_listPtr *root_customerPtr);

int main(int argc, char *argv[]){
    // Codes for product list
    FILE *fptr1;
    fptr1 = fopen("/Users/enesuzun/Desktop/product.txt","r");
    if (fptr1 == NULL) {
        printf("Error! Can not find the file!!");
        /* Program exits if file pointer returns NULL. */
        exit(1);
    }
    product_listPtr root_productPtr = NULL;
    int productId;
    int productPrice;
    char productName[50];
    char productCategory[50];
    char *ptrProductName = productName;
    char *ptrProductCategory = productCategory;
    char line1[128];
    while(fgets(line1,sizeof(line1),fptr1)){
        sscanf(line1,"%d\t%s\t%s\t%d",&productId,productName,productCategory,&productPrice);
        addProduct(&root_productPtr,ptrProductName,ptrProductCategory,productId,productPrice);
    } // End of product
    
    // Codes for customer list
    FILE *fptr2;
    fptr2 = fopen("/Users/enesuzun/Desktop/customer.txt","r");
    if(fptr2 == NULL){
        printf("Error! Can not find the file!!");
        /* Program exits if file pointer returns NULL. */
        exit(1);
    }
    customer_listPtr root_customerPtr = NULL;
    int customerId;
    char customerName[50];
    char customerSurname[50];
    char *ptrCustomerName = customerName;
    char *ptrCustomerSurname = customerSurname;
    char line2[128];
    while (fgets(line2,sizeof(line2),fptr2)){
        sscanf(line2,"%d\t%s\t%s",&customerId,customerName,customerSurname);
        addCustomer(&root_customerPtr,ptrCustomerName,ptrCustomerSurname,customerId);
    } // end of customer

    //codes for basket
    FILE *fptr3;
    fptr3 = fopen("/Users/enesuzun/Desktop/basket.txt","r");
    if(fptr3 == NULL){
        printf("Error! Can not find the file!!");
        /* Program exits if file pointer returns NULL. */
        exit(1);
    }
    int customerId2;
    int BasketId;
    int productId2;
    char line3[128];
    int temp = 0;
    int temp2 = 1;
    
    while(fgets(line3,sizeof(line3),fptr3)){
        sscanf(line3,"%d\t%d\t%d",&customerId2,&BasketId,&productId2);
        if(customerId2>temp2 || customerId2< temp2){
            temp2 = customerId2;
            temp=0;
            if(customerId2 == temp2){
                if(BasketId != temp){
                addBasket(customerId2,BasketId,&root_customerPtr);
                temp++;
                }
            }
        }else {
            if(BasketId != temp){
                addBasket(customerId2,BasketId,&root_customerPtr);
                temp++;
                }
        }

        addProductToBasket(customerId2,BasketId,&root_customerPtr,&root_productPtr,productId2);
    }
    // Codes  for main menu
    instructions();
    unsigned int choice;
    scanf("%u",&choice);
    int productIDforcheck;
    int customerID3;
    while (choice != 6){
       switch (choice){
       
           case 1:
    printCustomerList(root_customerPtr);
    addCustomerFromMenu(&root_customerPtr);
    printCustomerList(root_customerPtr);
              
        break;

           case 2:
           printCustomerList(root_customerPtr);
           func2(&root_customerPtr,&root_productPtr,customerID3);
        
           break;

       case 3:
    printCustomerList(root_customerPtr);
    removeCustomerFromMenu(&root_customerPtr);
    printCustomerList(root_customerPtr);
                  
        break;

           case 4:
    
    printProductList(root_productPtr);
    printf("Please enter the product id that you want to check:");
    scanf("%d",&productIDforcheck);
    customersWhoBoughtaProduct(productIDforcheck,&root_customerPtr,&root_productPtr);
    
        break;
       
        case 5:
    
    totalShoppingAmount(&root_customerPtr);
    
        break;
             
       default:
       puts("Invalid choice.");
            break;
       }
       printf("--------------\n");
       instructions();
       printf("%s","? ");
       scanf("%u",&choice);
       
   }
    
    return 0;
}
void func2(customer_listPtr *root_customerPtr,product_listPtr *root_productPtr,int customerID3){
            customer_listPtr currentCustomerPtr = *root_customerPtr;
           printf("Enter the id of the customer that you want to add basket:");
           scanf("%d",&customerID3);
           printf("\nxxxxxxxxxxx");
           printf("%d",customerID3);
           while(currentCustomerPtr != NULL && currentCustomerPtr->id !=customerID3){
               currentCustomerPtr = currentCustomerPtr->customer_next;
           }
           basket_listPtr currentBasketPtr = currentCustomerPtr->basket_ptr;
           int basketID;
           if(currentBasketPtr != NULL){
           while(currentBasketPtr->basket_next != NULL ){
               currentBasketPtr = currentBasketPtr->basket_next;
           }
           basketID = currentBasketPtr->id;
           }else
           {
               basketID = 0;
           }
           
           addBasket(customerID3,basketID+1,root_customerPtr);
           printProductList(*root_productPtr);
           int customerChoice = 0;
           int chosenProduct;
           while(customerChoice != -1){
               printf("Enter the product id that product will be added to the basket: ");
               scanf("%d",&chosenProduct);
               addProductToBasket(customerID3,basketID+1,root_customerPtr,root_productPtr,chosenProduct);
               printf("Do you want to continue shopping? (Enter 1 for yes, -1 for no) ");
               scanf("%d",&customerChoice);
           }

}
// Void function for adding a product to basket
void addProductToBasket (int customerID,int basketID,customer_listPtr* root_customerPtr,product_listPtr * root_productPtr,int productID){
   
    product_listPtr currentPtr2 = *root_productPtr;                   //Synchhronized Product
    while (currentPtr2->id != productID && currentPtr2 != NULL) {
       currentPtr2 = currentPtr2->product_next;
    }

    customer_listPtr currentPtr = *root_customerPtr;                 //Synchhronized customer
    while (currentPtr != NULL && currentPtr->id != customerID){
        currentPtr = currentPtr->customer_next;
    }
    basket_listPtr currentBasketPtr = currentPtr->basket_ptr;
    while(currentBasketPtr != NULL && currentBasketPtr->id != basketID){
        currentBasketPtr = currentBasketPtr->basket_next;
    }                                                             //Synchhronized basket

    if(currentPtr->basket_ptr != NULL && currentPtr->basket_ptr->id == basketID){
        product_listPtr newPtr = malloc(sizeof(product_list));
        if(newPtr != NULL){
            newPtr->category = currentPtr2->category;
            newPtr->id = currentPtr2->id;
            newPtr->name = currentPtr2->name;
            newPtr->price = currentPtr2->price;
            newPtr->product_next = NULL;

            product_listPtr previousPtr = NULL;
            product_listPtr currentPtr3 = currentPtr->basket_ptr->product_ptr;

            while (currentPtr3 != NULL && currentPtr3->id != productID){
            previousPtr = currentPtr3;
            currentPtr3 = currentPtr3->product_next;
            }
            if(previousPtr == NULL){
            newPtr->product_next = currentPtr->basket_ptr->product_ptr;
            currentPtr->basket_ptr->product_ptr = newPtr;
            }else{
            previousPtr->product_next = newPtr;
            newPtr->product_next = currentPtr3;
            }
        }else
        printf("No memory available");
    }else if (currentPtr->basket_ptr != NULL && currentPtr->basket_ptr->id != basketID){
// Product list codes
        product_listPtr newPtr = malloc(sizeof(product_list));
        if(newPtr != NULL){
            newPtr->category = currentPtr2->category;
            newPtr->id = currentPtr2->id;
            newPtr->name = currentPtr2->name;
            newPtr->price = currentPtr2->price;
            newPtr->product_next = NULL;

            product_listPtr previousPtr = NULL;
            product_listPtr currentPtr3 =currentBasketPtr->product_ptr;

            while (currentPtr3 != NULL && currentPtr3->id != productID){
                previousPtr = currentPtr3;
                currentPtr3 = currentPtr3->product_next;
            }
            if(previousPtr == NULL){
            newPtr->product_next = currentBasketPtr->product_ptr;
            currentBasketPtr->product_ptr = newPtr;
            }else{
            previousPtr->product_next = newPtr;
            newPtr->product_next = currentPtr3;
            }
        }else
        printf("No memory available");
    }
    
}
// Void function for adding basket
void addBasket(int customerID,int basketID,customer_listPtr* root_customerPtr){
    customer_listPtr previousPtr = NULL;
    customer_listPtr currentPtr = *root_customerPtr;
    while (currentPtr != NULL && currentPtr->id != customerID){
        previousPtr =currentPtr;
        currentPtr = currentPtr->customer_next;
    }

    basket_listPtr newPtr = malloc(sizeof(basket_list));
    if(newPtr != NULL){

        newPtr->id = basketID;
        newPtr->basket_next = NULL;

        basket_listPtr previousPtr2 = NULL;
        basket_listPtr currentPtr2= currentPtr->basket_ptr;

        while(currentPtr2 != NULL && currentPtr2->id != basketID){
            previousPtr2 = currentPtr2;
            currentPtr2 = currentPtr2->basket_next;
        }
        if(previousPtr2 == NULL){
            newPtr->basket_next = currentPtr->basket_ptr;
            currentPtr->basket_ptr = newPtr;
        }else{
            previousPtr2->basket_next = newPtr;
            newPtr->basket_next = currentPtr2;
        }
    }else{
        printf("No memory available");
    }
}
// Void function for adding customer to code
void addCustomer(customer_listPtr* root_customerPtr,char *customerName,char *customerSurname,int customerId ){
    customer_listPtr newPtr = malloc(sizeof(customer_list));
    if(newPtr != NULL){
        newPtr->id =customerId;
        newPtr->name = strdup(customerName);
        newPtr->surname = strdup(customerSurname);
        newPtr->customer_next =NULL;
        newPtr->basket_ptr = NULL;

        customer_listPtr previousPtr = NULL;
        customer_listPtr currentPtr = *root_customerPtr;

        while (currentPtr != NULL && currentPtr->id < customerId){
            previousPtr = currentPtr;
            currentPtr = currentPtr->customer_next;
        }
        if(previousPtr == NULL){
            newPtr->customer_next = *root_customerPtr;
            *root_customerPtr = newPtr;
        }else{
            previousPtr->customer_next = newPtr;
            newPtr->customer_next = currentPtr;
        }
    }else{
        printf("No memory available");
    }
}
// Void function for printing all customer list that we have
void printCustomerList(customer_listPtr currentPtr){
    if(isEmptyCustomer(currentPtr)){
        puts("Customer list is empty.\n");
    }else
    {
        puts("The customer list in id order:");
        puts("ID\tName\tSurname");
        while (currentPtr != NULL){
            printf("%d\t%s\t%s\n",currentPtr->id,currentPtr->name,currentPtr->surname);
            currentPtr = currentPtr->customer_next;
        }
    }
    
}
// Void function for adding a product
void addProduct(product_listPtr * root_productPtr,char *productName,char *productCategory,int productId,int productPrice){
    product_listPtr newPtr = malloc(sizeof(product_list));
    if(newPtr != NULL){
        newPtr->id =productId;
        newPtr->price = productPrice;
        newPtr->name = strdup(productName);
        newPtr->category = strdup(productCategory);
        newPtr->product_next = NULL;

        product_listPtr previousPtr = NULL;
        product_listPtr currentPtr = *root_productPtr;

        while(currentPtr != NULL && strcmp(currentPtr->name,productName)<0){
            previousPtr = currentPtr;
            currentPtr = currentPtr->product_next;
        }

        if(previousPtr == NULL){
            newPtr->product_next = *root_productPtr;
            *root_productPtr = newPtr;
        }else
        {
            previousPtr->product_next = newPtr;
            newPtr->product_next = currentPtr;
        }
        
    }else
    {
        printf("No memory available");
    }
}
// Void function for  printing all product that we have
void printProductList(product_listPtr currentPtr){
    if(isEmptyProduct (currentPtr)){
        puts("Product list is empty.\n");
    }else
    {
        puts("The product list in name-alphabetical order:");
        puts("ID\tName\tCategory\tPrice");
        while (currentPtr != NULL){
            printf("%d\t%s\t%s\t%d\n",currentPtr->id,currentPtr->name,currentPtr->category,currentPtr->price);
            currentPtr = currentPtr->product_next;
        }
    }
    
}
// This void function works for showing a customers who bought something
void customersWhoBoughtaProduct(int productID,customer_listPtr *root_customerPtr,product_listPtr *root_productPtr){
        
        customer_listPtr currentCustomer = *root_customerPtr;
        product_listPtr  currentProduct  =  *root_productPtr;
        basket_listPtr currentBasket = currentCustomer->basket_ptr;
        product_listPtr currentProduct1 = currentBasket->product_ptr;
        while (currentProduct != NULL && currentProduct->id != productID)
        currentProduct = currentProduct->product_next;
        
        printf("%d\t%s\t%s\t%d\n",currentProduct->id,currentProduct->name,currentProduct->category,currentProduct->price);
        
        
        while (currentCustomer != NULL){
        
            while (currentBasket != NULL){
            
                while (currentProduct1 != NULL){
        
                    if(currentProduct1->id == productID)
                        printf("%d\t%s\t%s\n",currentCustomer->id,currentCustomer->name,currentCustomer->surname);
                    if(currentProduct1 != NULL)
                currentProduct1 = currentProduct1->product_next;
                }
            
            currentBasket  =    currentBasket->basket_next;
            if(currentBasket != NULL)
            currentProduct1 = currentBasket->product_ptr;
            }
                
        currentCustomer = currentCustomer->customer_next;
        if(currentCustomer == NULL)
        break;
        currentBasket = currentCustomer->basket_ptr;
        if(currentBasket != NULL)
            currentProduct1 = currentBasket->product_ptr;
        }
}
// After  all  shopping, this void function works  for total amount.
void totalShoppingAmount(customer_listPtr *root_customerPtr){
    
        int totalShoppingAmount = 0;
        int totalBasketAmount = 0;
        
        customer_listPtr currentCustomer = *root_customerPtr;
        basket_listPtr currentBasket = currentCustomer->basket_ptr;
        product_listPtr currentProduct1 = currentBasket->product_ptr;
        
        while (currentCustomer != NULL){
        
        if (hasBasket(currentCustomer)==0){
        printf("%s %s does not have a shopping amount \n",currentCustomer->name,currentCustomer->surname);
        currentCustomer = currentCustomer->customer_next;
        }
        else{
        
        while (currentBasket != NULL){
            
                while (currentProduct1 != NULL){
                totalBasketAmount += currentProduct1->price;
                currentProduct1 = currentProduct1->product_next;
                }
        
            totalShoppingAmount += totalBasketAmount;
            totalBasketAmount = 0;
            
            currentBasket  =    currentBasket->basket_next;
            
            if(currentBasket != NULL)
            currentProduct1 = currentBasket->product_ptr;
            
            }
                
        printf("Total shopping amount of %s %s : %d TL \n",currentCustomer->name,currentCustomer->surname,totalShoppingAmount);
        totalShoppingAmount = 0;
        currentCustomer = currentCustomer->customer_next;
        
        if(currentCustomer == NULL) break;
        
        currentBasket = currentCustomer->basket_ptr;
       
        if(currentBasket != NULL)
        currentProduct1 = currentBasket->product_ptr;
    
        }
    }
}



int hasBasket(customer_listPtr currentCustomer){
    
    if ( currentCustomer->basket_ptr == NULL) return 0;
    else return 1;
}

void addCustomerFromMenu(customer_listPtr *root_customerPtr){
    char name[50];
    char surname[50];
    int id =1;
    customer_listPtr currentPtr = *root_customerPtr;

    printf("Enter the name and surname of the new customer \n" );
    scanf("%s %s",name,surname);
    
    if(isEmptyCustomer(currentPtr)){
        puts("Customer list is empty.\n");
    }else
    {
        while (currentPtr != NULL){
            if(strcmp(currentPtr->name,name) == 0 && strcmp(currentPtr->surname,surname)== 0 ){
                printf("%s %s already exist in the system.",name,surname );
            return;
            }
            
            currentPtr = currentPtr->customer_next;
            id++;
        }
   }
   
       addCustomer(root_customerPtr,name,surname,id);
    return;
}
// This void function  works for removing a customer who we want.
void removeCustomerFromMenu(customer_listPtr *root_customerPtr){
    char name[50];
    char surname[50];
    
    printf("Enter the name and surname of the customer that will be deleted.\n" );
    scanf("%s %s",name,surname);
    
    if(isEmptyCustomer(*root_customerPtr)){
        puts("Customer list is empty.\n");
    }
    else{
    
    if(strcmp((*root_customerPtr)->name,name) == 0 && strcmp((*root_customerPtr)->surname,surname)== 0){
    
    customer_listPtr temp = *root_customerPtr;
    *root_customerPtr = (*root_customerPtr)->customer_next;
    free(temp);
    return;
    }
    
    else {
    customer_listPtr previousPtr = *root_customerPtr;
    customer_listPtr currentPtr     = (*root_customerPtr)->customer_next;
    
    while (currentPtr != NULL && strcmp(currentPtr->name,name) != 0 && strcmp(currentPtr->surname,surname) != 0){
    previousPtr = currentPtr;
    currentPtr     = currentPtr->customer_next;
    }
    
    if(currentPtr != NULL){
    customer_listPtr temp = currentPtr;
    previousPtr->customer_next = currentPtr->customer_next;
    free(temp);
    return;
        }

    }
}
printf("Customer can not Found!! \n");

}

void instructions(){
    puts("Enter your choice:\n"
    "1 to add a Customer to the CustomerList .\n"
    "2 to add a Basket to the Customer.\n"
    "3 to remove a Customer from the CustomerList.\n"
    "4 to List the customers who bought a specific product.\n"
    "5 to List the total shopping amounts of each customer.\n"
    "6 to EXIT");
}

int isEmptyProduct(product_listPtr sPtr){
    return sPtr ==NULL;
}

int isEmptyCustomer(customer_listPtr sPtr){
    return sPtr ==NULL;
}



