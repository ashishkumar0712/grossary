#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct product{
    int id;
    char product_name[50];
    int quantity;
    float MRP;
    char expire_date[20];
    
}p;

FILE *fp;

int main(){
    int ch;
    while(1){
        system("cls");
        printf("<==grocery store management==>>\n");
        printf("1.Add product\n");
        printf("2.Display product\n");
        printf("3.Update product\n");
        printf("4.Delete product\n");
        printf("5.Buy product\n");
        printf("0.Exit\n\n");
        printf("Enter your chioce: ");
        scanf("%d" ,&ch);

        switch(ch){
        case 0:
            exit(0);
            
        case 1:
            add_product();
            break;
        case 2:
            display_product();
            break;
        case 3:
            update_product();
            break;
        case 4:
            delete_product();
            break;
        case 5:
            buy_product();
            break;
        default:
            printf("Invalid choice....\n\n");

        }
        printf("\n\npress Any Key to Continue..");
        getch();
    }
    return 0;
}



void add_product(){
    char name[50];
    fp=fopen("product.txt","ab+");
    printf("Enter Product id : ");
    scanf("%d",&p.id);
    fflush(stdin);
    printf("Enter Product Name : ");
    gets(name);
    strcpy(p.product_name,name);
    printf("Enter MRP : ");
    scanf("%f",&p.MRP);
    printf("Enter Expire Date : ");
    scanf("%s",&p.expire_date);
    printf("Enter the product quantity : ");
    scanf("%d",&p.quantity);
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);

    printf("\n\n!!! Product added successfully !!!\n");
    
}



void display_product(){
    fp=fopen("product.txt","rb");
      if(fp==NULL){
        printf("file not found");
        exit(1);
      }
        printf("\n---- Product List ----\n\n");
        printf("%-10s %-30s %-10s %-15s %-10s\n","id","Product Name","MRP","Expire Date","Quantity");
        printf("------------------------------------------------------------------------------\n");
        fp=fopen("product.txt","rb");
        while(fread(&p,sizeof(p),1,fp)==1){
            printf("%-10d %-30s %-10.2f %-15s %d\n",p.id ,p.product_name,p.MRP,p.expire_date,p.quantity);
        }
        printf("------------------------------------------------------------------------------\n");
        fclose(fp);
    }




    void delete_product(){
        int id,f;
        
        printf("<==Delete product ==>\n\n");
        printf("Enter product id to delete: ");
        scanf("%d",&id);

        FILE *ft;

        fp = fopen("product.txt","rb");
        while(fread(&p,sizeof(p),1,fp)==1){
             if(id==p.id){
                f=1;
                fclose(fp);
                break;
             }
        }
        if(f==1){
            printf("\nproduct deleted successfully...");
            del(id);
        }
        else
            printf("\n\nproduct not found !");
    }



    void del(int id){
        int f=0;
        
        FILE *ft;
        fp = fopen("product.txt", "rb");
        ft = fopen("temp.txt","wb");

        while(fread(&p,sizeof(p),1,fp)==1){
             if(id==p.id){
                f=1;
             }
             else{
                fwrite(&p,sizeof(p),1,ft);
             }
    }

    fclose(fp);
    fclose(ft);
    remove("product.txt");
    rename("temp.txt","product.txt");
    }



    void update_product(){
        int id , f;
        printf("<== update products ==>\n\n");
        printf("Enter product id to update: ");
        scanf("%d" , &id);
        
        FILE *ft;
        
        fp = fopen("product.txt", "rb+");

        while(fread(&p, sizeof(p), 1, fp) == 1){

             if(id == p.id){
                f=1;
                printf("Enter new product name: ");
                fflush(stdin);
                gets(p.product_name);

                printf("Enter new MRP : ");
                fflush(stdin);
                scanf("%f", &p.MRP);

                printf("Enter new expire date: ");
                fflush(stdin);
                scanf("%s", &p.expire_date);
                
                printf("Enter new product quantity: ");
                fflush(stdin);
                scanf("%d", &p.quantity);
                
                fseek(fp,-sizeof(p),1);
                fwrite(&p, sizeof(p), 1, fp);
                fclose(fp);
                break;
             }
    }
    if(f==1)
        printf("\nproduct updated successfully...");
    else
        printf("\n\nproduct Not Found !");
    }



    void buy_product(){
        int id,quantity,f=0;
        printf("<== Buy product ==>\n\n");
        printf("\nEnter produt id to buy: ");
        printf("\nEnter how much quantity to buy: ");
        scanf("%d %d",&id,&quantity);

        fp = fopen("product.txt","rb+");
        
        while(fread(&p,sizeof(p),1,fp)==1){

            if(id==p.id){
                f=1;
                p.quantity=p.quantity-quantity;
                fseek(fp,-sizeof(p),1);
                fwrite(&p, sizeof(p), 1, fp);
                fclose(fp);
                if(p.quantity==0){
                    del(p.id);
                }
                break;

            }
        }

        if(f==1)
           printf("\nproduct bought successfully...");
        else
           printf("\n\npround not found !");

    

    }




