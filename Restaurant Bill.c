#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items {
    char item[20];
    float price;
    int qty;
};

struct orders {
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

// Functions to generate bills
void generateBillHeader(char name[50], char date[30]) {
    printf("\n\n");
    printf("\t    Nayon's Restaurant");
    printf("\n\t   ----------------------");
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("-----------------------------------------------\n");
    printf("Items\t\tQty\t\tTotal (TK)");
    printf("\n-----------------------------------------------\n\n");
}

void generateBillBody(char item[30], int qty, float price) {
    printf("%s\t\t%d\t\t%.2f TK\n", item, qty, qty * price);
}

void generateBillFooter(float total) {
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal;
    float grandTotal = netTotal + 2 * cgst;
    printf("-----------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f TK\n", total);
    printf("Discount @10%%\t\t\t%.2f TK\n", dis);
    printf("\t\t\t\t-------\n");
    printf("Net Total\t\t\t%.2f TK\n", netTotal);
    printf("CGST @9%%\t\t\t%.2f TK\n", cgst);
    printf("SGST @9%%\t\t\t%.2f TK\n", cgst);
    printf("-----------------------------------------------\n");
    printf("Grand Total\t\t\t%.2f TK\n", grandTotal);
    printf("-----------------------------------------------\n");
}

int main() {

    int opt, n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y', contFlag = 'y';
    char name[50];
    FILE *fp;

    while (contFlag == 'y') {
        system("clear"); // Use "cls" if you're on Windows
        float total = 0;
        int invoiceFound = 0;

        printf("\t============NAYON'S RESTAURANT============");
        printf("\n\nPlease select your preferred operation");
        printf("\n\n1. Generate Invoice");
        printf("\n2. Show all Invoices");
        printf("\n3. Search Invoice");
        printf("\n4. Exit");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);
        fgetc(stdin);

        switch (opt) {
            case 1:
                system("clear");
                printf("\nPlease enter the name of the customer:\t");
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer) - 1] = 0;
                strcpy(ord.date, __DATE__);
                printf("\nPlease enter the number of items:\t");
                scanf("%d", &n);
                ord.numOfItems = n;

                for (int i = 0; i < n; i++) {
                    fgetc(stdin);
                    printf("\n\n");
                    printf("Please enter the item %d:\t", i + 1);
                    fgets(ord.itm[i].item, 20, stdin);
                    ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                    printf("Please enter the quantity:\t");
                    scanf("%d", &ord.itm[i].qty);
                    printf("Please enter the unit price:\t");
                    scanf("%f", &ord.itm[i].price);
                    total += ord.itm[i].qty * ord.itm[i].price;
                }

                generateBillHeader(ord.customer, ord.date);
                for (int i = 0; i < ord.numOfItems; i++) {
                    generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                }
                generateBillFooter(total);

                printf("\nDo you want to save the invoice [y/n]:\t");
                scanf(" %c", &saveBill);

                if (saveBill == 'y') {
                    fp = fopen("RestaurantBill.dat", "a+");
                    fwrite(&ord, sizeof(struct orders), 1, fp);
                    if (fwrite != 0)
                        printf("\nSuccessfully saved\n");
                    else
                        printf("\nError saving\n");
                    fclose(fp);
                }
                break;

            case 2:
                system("clear");
                fp = fopen("RestaurantBill.dat", "r");
                printf("\n  ***** Your Previous Invoices *****\n");
                while (fread(&order, sizeof(struct orders), 1, fp)) {
                    float tot = 0;
                    generateBillHeader(order.customer, order.date);
                    for (int i = 0; i < order.numOfItems; i++) {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                }
                fclose(fp);
                break;

            case 3:
                printf("Enter the name of the customer:\t");
                fgets(name, 50, stdin);
                name[strlen(name) - 1] = 0;
                system("clear");
                fp = fopen("RestaurantBill.dat", "r");
                printf("\t***** Invoice of %s *****\n", name);
                while (fread(&order, sizeof(struct orders), 1, fp)) {
                    float tot = 0;
                    if (!strcmp(order.customer, name)) {
                        generateBillHeader(order.customer, order.date);
                        for (int i = 0; i < order.numOfItems; i++) {
                            generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                            tot += order.itm[i].qty * order.itm[i].price;
                        }
                        generateBillFooter(tot);
                        invoiceFound = 1;
                    }
                }
                if (!invoiceFound) {
                    printf("Sorry, the invoice for %s does not exist.\n", name);
                }
                fclose(fp);
                break;

            case 4:
                printf("\n\t\t Thank you!\n\n");
                exit(0);
                break;

            default:
                printf("Sorry, invalid option\n");
                break;
        }

        printf("\nDo you want to perform another operation? [y/n]:\t");
        scanf(" %c", &contFlag);
    }

    printf("\n\t\t Thank you!\n\n");
    return 0;
}
