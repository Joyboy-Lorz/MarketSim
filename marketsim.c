#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <stdbool.h>

#define NUM_ITEMS 5
#define INITIAL_STOCK 120
#define MAX_ITEMS 100

// Category names
char *categories[] = {"Fruits and Vegetables", "Dairy", "Meat", "Bakery", "Frozen", "Drinks", "Snacks"};

int fruitsnveggies_stocks[NUM_ITEMS];
int dairy_stocks[NUM_ITEMS];
int meat_stocks[NUM_ITEMS];
int bakery_stocks[NUM_ITEMS];
int frozen_stocks[NUM_ITEMS];
int drinks_stocks[NUM_ITEMS];
int snacks_stocks[NUM_ITEMS];

// Item names
char *fruitsnveggies[NUM_ITEMS] = {"Apples", "Oranges", "Carrots", "Lettuce", "Tomatoes"};
char *dairy[NUM_ITEMS] = {"Milk", "Cheese", "Yogurt", "Butter", "Cream"};
char *meat[NUM_ITEMS] = {"Chicken", "Beef", "Pork", "Lamb", "Fish"};
char *bakery[NUM_ITEMS] = {"Bread", "Buns", "Scones", "Muffins", "Cakes"};
char *frozen[NUM_ITEMS] = {"Pizza", "Nuggets", "Gelato", "Popsicles", "Sherbet"};
char *drinks[NUM_ITEMS] = {"Water", "Juice", "Soda", "Tea", "Coffee"};
char *snacks[NUM_ITEMS] = {"Chips", "Popcorn", "Pretzels", "Crackers", "Nuts"};

// items arrays
char **items[] =
    {
        fruitsnveggies,
        dairy,
        meat,
        bakery,
        frozen,
        drinks,
        snacks,
};
// Stock arrays
int *stocks[] =
    {
        fruitsnveggies_stocks,
        dairy_stocks,
        meat_stocks,
        bakery_stocks,
        frozen_stocks,
        drinks_stocks,
        snacks_stocks};

// Price arrays
float prices[NUM_ITEMS] = {3.0, 5.5, 8.5, 5.2, 4.8};

// Global variables
int continue_shopping = 1;
int continue_admin = 1;
int cart_items = 0;
char cart_names[MAX_ITEMS][50];
int cart_quantities[MAX_ITEMS];
float cart_prices[MAX_ITEMS];
float total_price = 0.0;
float payment;
FILE *file;
FILE *stock_file;

// Function to initialize stock for each category
void init_stock(int *stocks, int size, int initial_stock)
{
    for (int i = 0; i < size; i++)
    {
        stocks[i] = initial_stock;
    }
}

// stock_report function
void load_stock()
{
    FILE *stock_file = fopen("stock_report.csv", "r");
    if (stock_file == NULL)
    {
        // File doesn't exist yet, initialize with default values
        for (int i = 0; i < 7; i++)
        {
            init_stock(stocks[i], NUM_ITEMS, INITIAL_STOCK);
        }
        return;
    }

    char line[256];

    // Skip header line
    fgets(line, sizeof(line), stock_file);

    int item_num;
    int stock_val;
    char category[50], item_name[50];

    while (fgets(line, sizeof(line), stock_file))
    {
        char *token = strtok(line, "|");
        if (token != NULL)
        {
            item_num = atoi(token);

            token = strtok(NULL, "|"); // Category
            if (token != NULL)
            {
                strcpy(category, token);

                token = strtok(NULL, "|"); // Item name
                if (token != NULL)
                {
                    strcpy(item_name, token);

                    token = strtok(NULL, "|"); // Stock value
                    if (token != NULL)
                    {
                        stock_val = atoi(token);

                        // Calculate category and item index
                        int cat_index = (item_num - 1) / NUM_ITEMS;
                        int item_index = (item_num - 1) % NUM_ITEMS;

                        if (cat_index >= 0 && cat_index < 7 && item_index >= 0 && item_index < NUM_ITEMS)
                        {
                            stocks[cat_index][item_index] = stock_val;
                        }
                    }
                }
            }
        }
    }
    fclose(stock_file);
}

float calculate_total(float prices[], int quantities[], int start, int end)
{
    float total = 0.0;
    for (int i = start; i < end; i++)
    {
        total += prices[i] * quantities[i];
    }
    return total;
}

// update stock_report
void update_stock()
{
    int i;

    FILE *stock_file = fopen("stock_report.csv", "w");
    if (stock_file == NULL)
    {
        printf("    Error opening stock report file!\n");
        return;
    }

    fprintf(stock_file, "No.|Category|Item|Stock\n");

    int item_number = 1;
    for (int cat = 0; cat < 7; cat++)
    {
        for (int i = 0; i < NUM_ITEMS; i++)
        {
            fprintf(stock_file, "%d|%s|%s|%d\n", item_number++, categories[cat], items[cat][i], stocks[cat][i]);
        }
    }
    fprintf(stock_file, "-------------------------------------------------------------\n");

    fclose(stock_file);
}
// display and main functions
void MarketSim()
{

    printf("\t--------------------------------------------------------------------------------------------------------------\n");
    printf("\t||###    ###  ##########  ##########   ##     ## ######### ############    ###########  ########  ###    ###||\n");
    printf("\t||##  ##  ##  ##      ##  ##       ##  ##    ##  ##             ##         ##              ##     ##  ##  ##||\n");
    printf("\t||##  ##  ##  ## #### ##  #########    ## ###    ######         ##         ###########     ##     ##  ##  ##||\n");
    printf("\t||##      ##  ##      ##  ##      ##   ##    ##  ##             ##                  ##     ##     ##      ##||\n");
    printf("\t||##      ##  ##      ##  ##       ##  ##     ## #########      ##         ###########  ########  ##      ##||\n");
    printf("\t--------------------------------------------------------------------------------------------------------------\n");
}
void FruitsnVeg()
{
    printf("/////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("||...########### ############   ###############     //  ##           ##  ###########   ##########  ... ||\n");
    printf("||...##          ##         ##        ##           //    ##         ##   ##          ##          ##... ||\n");
    printf("||...##          ##         ##        ##          //      ##       ##    ##          ##            ... ||\n");
    printf("||...##########  ###########          ##         //        ##     ##     ##########  ##        ####... ||\n");
    printf("||...##          ##         ##        ##        //          ##   ##      ##          ##          ##... ||\n");
    printf("||...##          ##         ##        ##       //             ###        ###########   ##########  ... ||\n");
    printf("/////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
}
void Dairy()
{

    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("||...#############      ############    ###############  ###############   ##           ##...||\n");
    printf("||...##           ##   ##           ##         ##        ##            ##   ##         ##  ...||\n");
    printf("||...##            ##  ##           ##         ##        ##             ##    ##      ##   ...||\n");
    printf("||...##            ##  ###############         ##        ###############        ##  ##     ...||\n");
    printf("||...##           ##   ##           ##         ##        ##           ##          ##       ...||\n");
    printf("||... ############     ##           ##  ###############  ##             ##        ##       ...||\n");
    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
}
void Meat()
{

    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("||..................##          ## ###########   ##########   ##############..................||\n");
    printf("||..................####      #### ##          ##          ##       ##      ..................||\n");
    printf("||..................##  ##  ##  ## ##          ##          ##       ##      ..................||\n");
    printf("||..................##    ##    ## ########    ##############       ##      ..................||\n");
    printf("||..................##    ##    ## ##          ##          ##       ##      ..................||\n");
    printf("||..................##          ## ########### ##          ##       ##      ..................||\n");
    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
}
void Bakery()
{

    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("||...........#############     ##          ##   #############   ##                ##...........||\n");
    printf("||...........##           ##   ##        ##    ##            ##   ##            ##  ...........||\n");
    printf("||...........##           ##   ##     ###      ##            ##     ##        ##    ...........||\n");
    printf("||...........#############     #######         ###############       ####  ####     ...........||\n");
    printf("||...........##           ##   ##     ###      ##          ##            ##         ...........||\n");
    printf("||...........##           ##   ##        ##    ##           ##           ##         ...........||\n");
    printf("||...........#############     ##         ##   ##            ##          ##         ...........||\n");
    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
}
void Frozen()
{

    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("||.............##############  #############    ###############  ###          ##..............||\n");
    printf("||.............##             ##            ##             ###   ## ##        ##..............||\n");
    printf("||.............##             ##            ##          ###      ##   ##      ##..............||\n");
    printf("||.............############   ##############         ###         ##     ##    ##..............\n");
    printf("||.............##             ##           ##      ###           ##       ##  ##..............||\n");
    printf("||.............##             ##            ##   ############### ##          ###..............||\n");
    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
}
void Drinks()
{
    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("||...##############    ###############    ###          ##  ##         ##   #############  ...||\n");
    printf("||...##            ##  ##             ##  ## ##        ##  ##       ##   ##            ## ...||\n");
    printf("||...##             ## ##             ##  ##   ##      ##  ##     ##     ##               ...||\n");
    printf("||...##             ## ###############    ##     ##    ##  #######       ###############  ...||\n");
    printf("||...##             ## ##           ##    ##      ##   ##  ##     ##                    ##...||\n");
    printf("||...##            ##  ##            ##   ##        ## ##  ##       ##   ##             ##...||\n");
    printf("||...#############     ##             ##  ##           ##  ##         ##   #############  ...||\n");
    printf("////////////////////////////////////////////////////////////////////////////////////////////////\n");
}
void Snacks()
{
    printf("/////////////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("||... #############    ###           ##  ###############  ##           ##    #############  ...||\n");
    printf("||...##            ##  ## ##         ##  ##               ##         ##    ##            ## ...||\n");
    printf("||...##                ##   ##       ##  ##               ##       ##      ##               ...||\n");
    printf("||...###############   ##     ##     ##  ##               ########         ###############  ...||\n");
    printf("||...              ##  ##       ##   ##  ##               ##       ##                     ##...||\n");
    printf("||...##            ##  ##         ## ##  ##               ##         ##    ##             ##...||\n");
    printf("||... #############    ##           ###  ###############  ##           ##    #############  ...||\n");
    printf("/////////////////////////////////////////////////////////////////////////////////////////////////\n");
}
void Cart()
{
    system("cls");
    printf("\t-------------------------------------------------------------------------------------- ----------\n");
    printf("\t||************ ##############     ##########    ##############  ################# ************||\n");
    printf("\t||************ ##               ##          ##  ##          ##         ##         ************||\n");
    printf("\t||************ ##               ##          ##  ##           ##        ##         ************||\n");
    printf("\t||************ ##               ##############  #############          ##         ************||\n");
    printf("\t||************ ##               ##          ##  ##         ##          ##         ************||\n");
    printf("\t||************ ##############   ##          ##  ##           ##        ##         ************||\n");
    printf("\t------------------------------------------------------------------------------------------------\n");
}
void LoadingBar()
{
    int i;
    printf("\t\n\n\n\n");
    printf("\n\tL o a d i n g...\n");

    fflush(stdout);
    printf("\t[]");
    for (i = 0; i < 22; i++)
    {
        printf("[]");
        fflush(stdout);
        Sleep(15);
        printf("\b[]");
        fflush(stdout);
        Sleep(15);
        printf("\b[]");
        fflush(stdout);
    }
    printf("[]");
    printf("\t");
}
void Checkout()
{
    system("cls");
    printf("\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("\t___________    ############                    ##     #############     ____________  \n");
    printf("\t___________  ##            ##               ##     ##               ##  ____________  \n");
    printf("\t___________  ##                           ##       ##               ##  ____________  \n");
    printf("\t___________  ##                         ##         ##               ##  ____________  \n");
    printf("\t___________  ##                       ##           ##               ##  ____________  \n");
    printf("\t___________  ##                     ##             ##               ##  ____________  \n");
    printf("\t___________  ##            ##     ##               ##               ##  ____________  \n");
    printf("\t___________    ############     ##                   ###############    ____________  \n");
    printf("\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
}
void pressContinue()
{
    printf("   [Press any key to view the next category]\n");
    getchar();
}
void Receipt()
{
    system("cls");
    printf("\t.____________________________________________________________.\n");
    printf("\t[--------------------------RECEIPT---------------------------]\n");
    printf("\t[____________________________________________________________]\n");
    printf("\t[--------------Thanks for Shopping with us!------------------]\n");
    printf("\t[____________________________________________________________]\n");
    printf("\n");
    for (int i = 0; i < cart_items; i++)
    {
        printf("\t[%d]-----\t[%s]------\t[%d]\tx\t[%.2f]\n", i + 1, cart_names[i], cart_quantities[i], cart_prices[i]);
    }
    printf("\n");
    printf("\t[____________________________________________________________]\n");
    printf("\t[---[Total Purchases: $%.2f__________________________________\n", total_price);
    printf("\t[____________________________________________________________\n");
    printf("\t[---[Payment Amount: $%.2f___________________________________\n", payment);
    printf("\t[____________________________________________________________]\n");
    printf("\t[---[Change: $%.2f___________________________________________\n", payment - total_price);
    printf("\t[____________________________________________________________\n");
    printf("\t[_______________________Come again <3________________________]\n");
    printf("\t[_________________Deo & Caballero Market Sim_________________]\n");
}
void shoppingMenu(char *current_customername, char *current_customernumber)
{
    const char *aisle[] = {"Fruits and Vegetables", "Dairy", "Meat", "Bakery", "Frozen", "Drinks", "Snacks"};

    char *categories[][NUM_ITEMS] = {
        {"Apples", "Oranges", "Carrots", "Lettuce", "Tomatoes"},
        {"Milk", "Cheese", "Yogurt", "Butter", "Cream"},
        {"Chicken", "Beef", "Pork", "Lamb", "Fish"},
        {"Bread", "Buns", "Scones", "Muffins", "Cakes"},
        {"Pizza", "Nuggets", "Gelato", "Popsicles", "Sherbet"},
        {"Water", "Juice", "Soda", "Tea", "Coffee"},
        {"Chips", "Popcorn", "Pretzels", "Crackers", "Nuts"}};

    float prices[NUM_ITEMS] = {3.0, 5.5, 8.5, 5.2, 4.8};
    int stocks_temp[7][NUM_ITEMS]; // Temporary array to hold stock values
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < NUM_ITEMS; j++)
        {
            stocks_temp[i][j] = stocks[i][j];
        }
    }

    int item_choice;
    load_stock();
    while (continue_shopping)
    {
        system("cls");
        printf("\n");
        MarketSim();
        printf("\t______________________________________________________________________________________________________________\n");
        printf("\n\t                                  What aisle would you want to shop in?\n");
        printf("\t______________________________________________________________________________________________________________\n");
        printf("\n");
        printf("\t[1]. Fruits and Vegetables____________________________________________________________________________________\n");
        printf("\n");
        printf("\t[2]. Dairy____________________________________________________________________________________________________\n");
        printf("\n");
        printf("\t[3]. Meat_____________________________________________________________________________________________________\n");
        printf("\n");
        printf("\t[4]. Bakery___________________________________________________________________________________________________\n");
        printf("\n");
        printf("\t[5]. Frozen___________________________________________________________________________________________________\n");
        printf("\n");
        printf("\t[6]. Drinks___________________________________________________________________________________________________\n");
        printf("\n");
        printf("\t[7]. Snacks___________________________________________________________________________________________________\n");
        printf("\n");
        printf("\t[8]. View Cart________________________________________________________________________________________________\n");
        printf("\n");
        printf("\t[9]. Checkout_________________________________________________________________________________________________\n");
        printf("\n");
        printf("\n\t->Choose Where to go or What to do: ");

        int choice;
        if (scanf("%d", &choice) != 1)
        {
            printf("\tInvalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ; // Clear input buffer
            continue;
        }

        if (choice >= 1 && choice <= 7)
        {
            // Product aisles
            system("cls");
            switch (choice)
            {
            case 1:
                FruitsnVeg();
                break;
            case 2:
                Dairy();
                break;
            case 3:
                Meat();
                break;
            case 4:
                Bakery();
                break;
            case 5:
                Frozen();
                break;
            case 6:
                Drinks();
                break;
            case 7:
                Snacks();
                break;
            }

            printf("\n\t\t\t   You are in the %s aisle\n", aisle[choice - 1]);
            printf("\n");

            for (int i = 0; i < NUM_ITEMS; i++)
            {
                printf("\t[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("\t|[%d]\t---|   %s   |---\t---|   $%.2f   |---\t---|   Stock: %d\n", i + 1, categories[choice - 1][i], prices[i], stocks_temp[choice - 1][i]);
                printf("\n");
            }
            printf("\n");
            printf("\t[[6]~~~~~~~~~~~~~~~~~~~~~~~~[..... Back to main menu.....]~~~~~~~~~~~~~~~~~~~~~~~~]\n");

            printf("\n");
            printf("\t[]~~~~~~~~~~~~~~~~~[Choose Product (1-5) or Return to Main Menu (6)]~~~~~~~~~~~~~[]\n");
            printf("\n\t\t[Input]:");

            if (scanf("%d", &item_choice) != 1 || item_choice < 1 || item_choice > 6)
            {
                printf("Invalid input. Returning to main menu...\n");
                while (getchar() != '\n')
                    ;
                continue;
            }

            if (item_choice == 6)
                continue;

            printf("\n");
            printf("\t[]Enter quantity: ");
            int quantity;
            if (scanf("%d", &quantity) != 1 || quantity < 1 || quantity > stocks_temp[choice - 1][item_choice - 1])
            {
                printf("\t[]____________________________Invalid quantity. Returning to main menu____________________________[]\n");
                while (getchar() != '\n')
                    ;
                continue;
            }

            // Update stock and cart
            stocks_temp[choice - 1][item_choice - 1] -= quantity;
            strcpy(cart_names[cart_items], categories[choice - 1][item_choice - 1]);
            cart_quantities[cart_items] = quantity;
            cart_prices[cart_items] = prices[item_choice - 1];
            cart_items++;

            printf("\n");
            printf("\tAdded %d %s to cart.\n", quantity, categories[choice - 1][item_choice - 1]);
            printf("\t[]__________________________Press Enter to Continue__________________________[]");
            while (getchar() != '\n')
                getchar();
        }
        else if (choice == 8)
        {
            // View Cart
            system("cls");
            LoadingBar();
            Cart();

            printf("\n");
            printf("\t[______________________________________________________________________________________________]\n");
            printf("\t[-----------------------------------------Viewing Cart-----------------------------------------]\n");
            printf("\t[______________________________________________________________________________________________]\n");
            printf("\n");

            total_price = 0.0;

            printf("\n");

            for (int i = 0; i < cart_items; i++)
            {
                printf("\t[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("\t|[%d]\t---|   %s   |---\t---|     %d     |---x---|     $%.2f      ]-==-[   $%.2f   ]\t\n", i + 1, cart_names[i], cart_quantities[i], cart_prices[i], cart_quantities[i] * cart_prices[i]);
                printf("\t[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");

                // Calculate total price
                total_price += cart_prices[i] * cart_quantities[i];
            }

            printf("\n");
            printf("\tTotal Price: $%.2f\n", total_price);
            printf("\n");
            printf("\t1. Remove an item from the cart\n");
            printf("\t2. Clear the cart\n");
            printf("\t3. Back to main menu\n");

            int cart_choice;
            int remove_index;
            printf("\n");

            printf("\tEnter your choice: ");
            if (scanf("%d", &cart_choice) != 1)
            {
                printf("\tInvalid input. Please enter a number.\n");
                while (getchar() != '\n')
                    ; // clear the input buffer
                continue;
            }

            switch (cart_choice)
            {
            case 1:
                printf("\tEnter the item number to remove: ");
                if (scanf("%d", &remove_index) != 1 || remove_index < 1 || remove_index > cart_items)
                {
                    printf("\tInvalid input. Please enter a valid item number.\n");
                    while (getchar() != '\n')
                        ; // clear the input buffer
                    continue;
                }

                // Remove the item from the cart
                for (int i = remove_index - 1; i < cart_items - 1; i++)
                {
                    strcpy(cart_names[i], cart_names[i + 1]);
                    cart_quantities[i] = cart_quantities[i + 1];
                }
                cart_items--;
                printf("\tItem removed from the cart.\n");
                break;
            case 2:

                cart_items = 0;
                total_price = 0.0;

                for (int i = 0; i < MAX_ITEMS; i++)
                {
                    cart_quantities[i] = 0;
                }
                for (int i = 0; i < MAX_ITEMS; i++)
                {
                    cart_names[i][0] = '\0';
                }
                for (int i = 0; i < MAX_ITEMS; i++)
                {
                    cart_prices[i] = 0.0;
                }
                printf("\tCart cleared.\n");
                ;
                break;
            case 3:
                printf("\tReturning to main menu...\n");
                break;
            default:
                printf("\tInvalid choice. Returning to main menu...\n");
                break;
            }

            printf("\t[]__________________________Press Enter to Continue__________________________[]");
            getchar();
            getchar();
        }
        else if (choice == 9)
        {
            // Checkout
            system("cls");
            LoadingBar();
            Checkout();

            // Display current cart and total
            printf("\n");
            printf("\t[___________________________________________________________________________________]\n");
            printf("\t[--------------------------------------Checkout-------------------------------------]\n");
            printf("\t[___________________________________________________________________________________]\n");
            printf("\n");
            printf("\t\t\t\t\tYou have %d items in your cart\n", cart_items);

            total_price = 0.0;
            // Display cart items
            for (int i = 0; i < cart_items; i++)
            {
                printf("\t[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("\t|[%d]\t---|   %s   |---\t---|     %d     |---x---|     $%.2f      ]-==-[   $%.2f   ]\t\n", i + 1, cart_names[i], cart_quantities[i], cart_prices[i], cart_quantities[i] * cart_prices[i]);
                printf("\t[~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");

                total_price += cart_prices[i] * cart_quantities[i];
            }

            printf("\n");
            printf("\n\tTotal Price: $%.2f\n", total_price);
            printf("\n");
            printf("\n\t Enter payment amount: $");

            if (scanf("%f", &payment) != 1 || payment < total_price)
            {
                printf("\tInvalid payment. Amount must be greater than or equal to total price.\n");
                printf("\tPress any key to return to main menu...\n");
                while (getchar() != '\n')
                    ;
                getchar();
                continue;
            }

            // Update global stocks with the temporary stocks
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < NUM_ITEMS; j++)
                {
                    stocks[i][j] = stocks_temp[i][j];
                }
            }
            update_stock();

            printf("\n");
            printf("\n\t[]____________Payment Successful!____________[]");
            Sleep(2000);
            system("cls");

            printf("\n\n\n\t\t\t\t\t[]Printing Receipt[]");
            LoadingBar();
            Sleep(2000);
            Receipt();
            Sleep(5000);
            printf("\n");
            printf("\n\t[]__________________________Press Enter to Finish Shopping__________________________[]");
            while (getchar() != '\n')
                ;
            getchar();

            // change the file cart_items.csv to purchase_history.csv
            file = fopen("purchase_history.csv", "a");
            if (file != NULL)
            {

                fprintf(file, "\n\tPurchase History\n");

                fprintf(file, "\n\tCustomer: %s\n", current_customername);
                fprintf(file, "\n\tCustomer's contact number: %s\n", current_customernumber);
                fprintf(file, "\n\tItems purchased:\n");
                fprintf(file, "\n\t-----------------------------------------------------\n");
                for (int i = 0; i < cart_items; i++)
                {
                    fprintf(file, "\n\t%d. %s - %d\n", i + 1, cart_names[i], cart_quantities[i]);
                }
                fprintf(file, "\n\tTotal Price: $%.2f\n", total_price);
                fprintf(file, "\n\tPayment: $%.2f\n", payment);
                fprintf(file, "\n\tChange: $%.2f\n", payment - total_price);
                fprintf(file, "\n\t-----------------------------------------------------\n");
                fclose(file);
            }

            printf("\n");
            continue_shopping = 0;
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }
        continue;
    }
}
void Adminban()
{
    printf("\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n");
    printf("\t--------  ##############    ###############   ##            ##  ################ ###            ##--------\n");
    printf("\t--------##              ##  ##             ## ## ##      ## ##         ##        ## ##          ##--------\n");
    printf("\t--------##              ##  ##             ## ##   ##  ##   ##         ##        ##   ##        ##--------\n");
    printf("\t--------##              ##  ##             ## ##     ##     ##         ##        ##     ##      ##--------\n");
    printf("\t--------##################  ##             ## ##            ##         ##        ##       ##    ##--------\n");
    printf("\t--------##              ##  ##             ## ##            ##         ##        ##         ##  ##--------\n");
    printf("\t--------##              ##  ###############   ##            ##  ################ ##           ####--------\n");
    printf("\t[][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][]\n");
}
void admin_menu()
{
    int admin_choice;

    while (continue_admin)
    {
        system("cls");
        Adminban();
        printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
        printf("\t1. View Customer Purchases\n");
        printf("\t2. View Stock Report\n");
        printf("\t3. View Remaining Stocks\n");
        printf("\t4. Add Stocks\n");
        printf("\t5. Exit\n");
        printf("\n");
        printf("\tEnter number command: ");

        if (scanf("%d", &admin_choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                getchar();
            continue;
        }

        getchar();

        switch (admin_choice)
        {
        case 1:
        {
            // View Customer Purchases
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]==================================[]__CUSTOMER_PURCHASES__[]=========================================[]\n");
            FILE *cart_file = fopen("purchase_history.csv", "r");
            if (cart_file == NULL)
            {
                printf("Error: Unable to open purchase_history.csv\n");
            }
            else
            {
                char line[256];
                printf("\n\tCustomer Purchases:\n");
                while (fgets(line, sizeof(line), cart_file))
                {
                    printf("%s", line);
                }
                fclose(cart_file);
            }
            printf("\n\tPress any key to return to Admin Menu");
            getchar();
            break;
        }
        case 2:
        {
            // View Stock Report
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]=====================================[]__STOCK_REPORT__[]=========================================[]\n");
            FILE *stock_file = fopen("stock_report.csv", "r");
            if (stock_file == NULL)
            {
                printf("Error: Unable to open stock_report.csv\n");
            }
            else
            {
                char line[256];
                printf("\nStock Report:\n");
                while (fgets(line, sizeof(line), stock_file))
                {
                    printf("%s", line);
                }
                fclose(stock_file);
            }
            printf("\nPress any key to return to Admin Menu");
            getchar();
            break;
        }
        case 3:
        {
            // View Remaining Stocks
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]===================================[]__REMAINING_STOCKS__[]=========================================[]\n");
            printf("\n\tRemaining Stocks:\n");

            printf("Fruits & Vegetables:\n");
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("            +--[%d]\t---|   %s   |---\t---|     Stock: %d --+\t\n", i + 1, fruitsnveggies[i], fruitsnveggies_stocks[i]);
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
            }
            pressContinue();
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]===================================[]__REMAINING_STOCKS__[]=========================================[]\n");
            printf("\nDairy:\n");
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("            +--[%d]\t---|   %s   |---\t---|     Stock: %d --+\t\n", i + 1, dairy[i], dairy_stocks[i]);
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
            }
            pressContinue();
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]===================================[]__REMAINING_STOCKS__[]=========================================[]\n");
            printf("\nMeat:\n");
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("            +--[%d]\t---|   %s   |---\t---|     Stock: %d --+\t\n", i + 1, meat[i], meat_stocks[i]);
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
            }
            pressContinue();
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]===================================[]__REMAINING_STOCKS__[]=========================================[]\n");
            printf("\nBakery:\n");
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("            +--[%d]\t---|   %s   |---\t---|     Stock: %d --+\t\n", i + 1, bakery[i], bakery_stocks[i]);
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
            }
            pressContinue();
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]===================================[]__REMAINING_STOCKS__[]=========================================[]\n");
            printf("\nFrozen:\n");
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("            +--[%d]\t---|   %s   |---\t---|     Stock: %d --+\t\n", i + 1, frozen[i], frozen_stocks[i]);
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
            }
            pressContinue();
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]===================================[]__REMAINING_STOCKS__[]=========================================[]\n");
            printf("\nDrinks:\n");
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("            +--[%d]\t---|   %s   |---\t---|     Stock: %d --+\t\n", i + 1, drinks[i], drinks_stocks[i]);
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
            }
            pressContinue();
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]===================================[]__REMAINING_STOCKS__[]=========================================[]\n");
            printf("\nSnacks:\n");
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
                printf("            +--[%d]\t---|   %s   |---\t---|     Stock: %d --+\t\n", i + 1, snacks[i], snacks_stocks[i]);
                printf("            [~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~]\n");
            }
            printf("\n");
            printf("\n\tPress any key to return to Admin Menu");
            getchar();
            break;
        }
        case 4:
        {
            // Add Stocks
            system("cls");
            Adminban();
            printf("\t[]========================================[]__ADMIN_MENU__[]=========================================[]\n");
            printf("\t[]======================================[]__ADD_STOCKS__[]===========================================[]\n");
            int category_choice, item_choice, additional_stock;
            printf("\nSelect a category to add stocks:\n");
            printf("\n\t1. Fruits & Vegetables\n");
            printf("\n\t2. Dairy\n");
            printf("\n\t3. Meat\n");
            printf("\n\t4. Bakery\n");
            printf("\n\t5. Frozen\n");
            printf("\n\t6. Drinks\n");
            printf("\n\t7. Snacks\n");
            printf("\n\t8. Return to Admin Menu");
            printf("\n\tEnter your choice: ");
            if (scanf("%d", &category_choice) != 1 || category_choice < 1 || category_choice > 8)
            {
                printf("Invalid category choice.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            if (category_choice == 8)
            {
                break;
            }

            printf("\n\tSelect an item to add stocks:\n");
            char **selected_category;
            int *selected_stocks;
            switch (category_choice)
            {
            case 1:
                selected_category = fruitsnveggies;
                selected_stocks = fruitsnveggies_stocks;
                break;
            case 2:
                selected_category = dairy;
                selected_stocks = dairy_stocks;
                break;
            case 3:
                selected_category = meat;
                selected_stocks = meat_stocks;
                break;
            case 4:
                selected_category = bakery;
                selected_stocks = bakery_stocks;
                break;
            case 5:
                selected_category = frozen;
                selected_stocks = frozen_stocks;
                break;
            case 6:
                selected_category = drinks;
                selected_stocks = drinks_stocks;
                break;
            case 7:
                selected_category = snacks;
                selected_stocks = snacks_stocks;
                break;
            default:
                printf("\n\tInvalid category.\n");
                break;
            }
            for (int i = 0; i < NUM_ITEMS; i++)
            {
                printf("\n\t______________________________________________________________________________________");
                printf("\n\t [%d].___ %s___\t (Current Stock: %d)\n", i + 1, selected_category[i], selected_stocks[i]);
                printf("\n\t______________________________________________________________________________________");
            }
            printf("\n\tEnter your choice: ");
            if (scanf("%d", &item_choice) != 1 || item_choice < 1 || item_choice > NUM_ITEMS)
            {
                printf("\n\tInvalid item choice.\n");
                while (getchar() != '\n')
                    ;
                break;
            }

            printf("\n\tEnter the number of stocks to add: ");
            if (scanf("%d", &additional_stock) != 1 || additional_stock < 0)
            {
                printf("\n\t\tInvalid stock value.\n");
                while (getchar() != '\n')
                    ;
                break;
            }

            selected_stocks[item_choice - 1] += additional_stock;
            update_stock();
            printf("\n\tStock updated. %s now has %d units.\n", selected_category[item_choice - 1], selected_stocks[item_choice - 1]);

            printf("\n");
            printf("\n\tPress any key to return to Admin Menu");
            getchar();
            break;
        }
        case 5:
            system("cls");
            LoadingBar();
            system("cls");
            printf("\n\t[]___________________________Exiting admin menu_____________________________[]\n");
            Sleep(2000);
            system("cls");
            LoadingBar();
            system("cls");
            continue_admin = 0;
            break;

        default:
            printf("\n\tInvalid choice. Please try again.\n");
            Sleep(1000);
            break;
        }
    }
}
void homepage()
{
    system("cls");
    printf("\t_________________________________________________________________________________________________________________________\n");
    printf("\t##           ##  ############# ##               ###########      #############    ##              ##  #############  ####\n");
    printf("\t##           ##  ##            ##             ##           ##  ##             ##  ## ##        ## ##  ##             ####\n");
    printf("\t##     #     ##  ##            ##             ##               ##             ##  ##   ##    ##   ##  ##             ####\n");
    printf("\t##    ###    ##  ############  ##             ##               ##             ##  ##     ## ##    ##  ############   ####\n");
    printf("\t##   ## ##   ##  ##            ##             ##               ##             ##  ##       #      ##  ##                 \n");
    printf("\t## ##     ## ##  ##            ##             ##           ##  ##             ##  ##              ##  ##             ####\n");
    printf("\t ##         ##   ############# ##############   ###########      #############    ##              ##  #############   ## \n");
    printf("\t__________________________________________________What User type?________________________________________________________\n");
    printf("\t                                       Customer [C]      OR     Admin [A]                                                 \n");
    printf("\t------------------------------------------------------Exit [E]-----------------------------------------------------------\n");
}
int user_entry(char *user_type)
{
    printf("\t[][][][][][[][][][][][][][][][][][][][][[----------Enter user type----------][][][][][][][][][][][[[][][][][][[][][][][][]\n");
    printf("\n");
    printf("\t\t\t\t\t\t\t   ->User Type: ");
    if (scanf(" %c", user_type) != 1)
    {
        printf("Invalid input. Please enter a valid user type.\n");
        while (getchar() != '\n')
            ;
    }
    return 0;
}
struct Customer
{
    char name[30];           // Customer's name
    char contact_number[20]; // Customer's contact number
    char password[12];       // Customer's password
};

int main()
{
    // Initialize variables
    int fruitsnveggies_choice;
    int dairy_choice;
    int meat_choice;
    int bakery_choice;
    int frozen_choice;
    int drinks_choice;
    int snacks_choice;
    int admin_choice;
    char user_type;
    char customer_entry;
    struct Customer customer0;
    char customer_password[50];

    // Initialize stock arrays
    load_stock();

    // File pointers
    FILE *file;
    FILE *stock_file;

    // utility variables
    int i;
    int j;
    int temp;
    char text[1000];

    // Main program loop
    bool program_running = true;

    // Main program loop
    while (program_running)
    {
        // Reset variables for each iteration
        continue_admin = 1;
        continue_shopping = 1;
        cart_items = 0;
        total_price = 0.0;

        homepage();

        // Get user type
        if (user_entry(&user_type) != 0)
        {
            break; // Invalid input, restart loop
        }

        // Process based on user type
        if (user_type == 'C' || user_type == 'c')
        {
            system("cls");
            LoadingBar();
            system("cls");
            MarketSim();
            printf("\n");
            printf("\t      []--------------------------------------User Type: Customer--------------------------------------[]\n");
            printf("\t      []---------------------------------------Sign Up or Login----------------------------------------[]\n");
            printf("\n");
            printf("\t\t\t\t1. Sign Up\n");
            printf("\n");
            printf("\t\t\t\t2. Login\n");
            printf("\n");
            printf("\t\t\t\t3. Return to Main Menu\n");

            printf("\n");
            printf("\t\t\t\t->Enter your entry: ");
            if (scanf("%d", &customer_entry) != 1)
            {
                printf("\t[]_________________________Invalid input. Please enter a number._____________________[]\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            while (getchar() != '\n')
                ;

            switch (customer_entry)
            {
            case 1:
                // Customer Sign in
                system("cls");
                MarketSim();
                printf("\n");
                printf("\t[]=============================================SIGN UP==============================================[]\n");
                printf("\t[]........................................Enter your Details!.......................................[]\n");
                printf("\n");
                printf("\t\tEnter name: ");
                if (fgets(customer0.name, sizeof(customer0.name), stdin) != NULL)
                {
                    customer0.name[strcspn(customer0.name, "\n")] = '\0';
                }
                printf("\n");
                printf("\t\tEnter Contact Number: ");
                if (fgets(customer0.contact_number, sizeof(customer0.contact_number), stdin) != NULL)
                {
                    customer0.contact_number[strcspn(customer0.contact_number, "\n")] = '\0';
                }
                else
                {
                    printf("\t\tError reading contact number. Please try again.\n");
                    Sleep(2000);
                    return 1;
                }
                printf("\n");
                printf("\t\tMake password: ");
                if (fgets(customer0.password, sizeof(customer0.password), stdin) != NULL)
                {
                    customer0.password[strcspn(customer0.password, "\n")] = '\0';
                }
                else
                {
                    printf("Error reading password. Please try again.\n");
                    Sleep(2000);
                    return 1;
                }

                file = fopen("customerinfo.csv", "a");
                if (file == NULL)
                {
                    perror("Error opening customerinfo.csv for writing");
                    Sleep(2000);
                    return 1;
                }

                fprintf(file, "Customer_Name|Customer_Contact_Number|Customer_Password \n");
                fprintf(file, "%s|%s|%s\n", customer0.name, customer0.contact_number, customer0.password);
                fclose(file);
                system("cls");
                LoadingBar();
                printf("\n\t\t\tInfo Saved!\n");

                printf("\n\t\t\tProceeding to the shopping menu...\n");
                Sleep(2000);
                system("cls");
                LoadingBar();
                system("cls");
                MarketSim();
                shoppingMenu(customer0.name, customer0.contact_number);
                break;

            case 2:
                // Customer Login

                system("cls");
                LoadingBar();
                Sleep(1000);
                system("cls");
                MarketSim();
                printf("\n");
                printf("\t[]===========================================[]__LOGIN__[]============================================[]\n");
                printf("\t[]........................................Enter your Details!.......................................[]\n");

                printf("\n");
                printf("\t\tEnter username: ");
                fgets(customer0.name, sizeof(customer0.name), stdin);
                customer0.name[strcspn(customer0.name, "\n")] = '\0';

                printf("\n");
                printf("\t\tEnter password: ");
                fgets(customer0.password, sizeof(customer0.password), stdin);
                customer0.password[strcspn(customer0.password, "\n")] = '\0';

                FILE *customerinfoFile = fopen("customerinfo.csv", "r");
                if (customerinfoFile == NULL)
                {
                    printf("Error: Unable to open customerinfo.csv. Please ensure the file exists.\n");
                    Sleep(2000);
                    return 1;
                }

                bool isMatch = false;
                char buffer[2048];

                rewind(customerinfoFile);
                if (fgets(buffer, sizeof(buffer), customerinfoFile) == NULL)
                {
                    printf("Error: customerinfo.csv is empty\n");
                    fclose(customerinfoFile);
                    Sleep(2000);
                    return 1;
                }

                while (fgets(buffer, sizeof(buffer), customerinfoFile))
                {
                    size_t len = strcspn(buffer, "\n");
                    buffer[len] = '\0';

                    char *storedName = strtok(buffer, "|");
                    strtok(NULL, "|");
                    char *storedPassword = strtok(NULL, "|");

                    if (storedName != NULL && storedPassword != NULL &&
                        strcmp(customer0.name, storedName) == 0 &&
                        strcmp(customer0.password, storedPassword) == 0)
                    {
                        isMatch = true;
                        break;
                    }
                }

                fclose(customerinfoFile);

                if (isMatch)
                {
                    printf("\n\t\t\t\t   []______________Login successful!_______________[]\n");
                    printf("\n\t\t\t\t   []_________Proceeding to the shopping menu______[]\n");
                    Sleep(2000);
                    system("cls");
                    LoadingBar();
                    system("cls");
                    shoppingMenu(customer0.name, customer0.contact_number);
                }
                else
                {
                    system("cls");
                    printf("\n\t\t\tInvalid username or password. Please try again.\n");
                    Sleep(2000);
                    LoadingBar();
                    printf("\n\t\t\tReturning to Main menu....");
                    system("cls");
                    LoadingBar();
                    system("cls");
                    break;
                }
                break;

            case 3:
                printf("\n\t\tReturning to main menu...\n");
                Sleep(2000);
                system("cls");
                LoadingBar();
                system("cls");
                break;

            default:
                printf("\n\tInvalid choice. Please try again.\n");
                Sleep(2000);
                break;
            }
        }
        else if (user_type == 'A' || user_type == 'a')
        {
            system("cls");
            LoadingBar();
            system("cls");
            Adminban();
            printf("\n");
            printf("\n\t\t\t   User Type: Admin\n");
            printf("\n");
            printf("\t[]=======================================[]__ADMIN|LOGIN__[]=========================================[]\n");

            while (getchar() != '\n')
                ;
            {
                char admin_username[20];
                char admin_password[20];
                printf("\n");
                printf("\tEnter Admin Username: ");
                fgets(admin_username, sizeof(admin_username), stdin);
                admin_username[strcspn(admin_username, "\n")] = '\0';

                printf("\n\tEnter Admin Password: ");
                fgets(admin_password, sizeof(admin_password), stdin);
                admin_password[strcspn(admin_password, "\n")] = '\0';

                FILE *admin_file = fopen("admin.csv", "r");
                if (admin_file == NULL)
                {
                    printf("\n\t\tError: Unable to open admin.csv. Please ensure the file exists.\n");
                    Sleep(2000);
                    return 1;
                }

                bool isAdminMatch = false;
                char buffer[2048];

                if (fgets(buffer, sizeof(buffer), admin_file) == NULL)
                {
                    printf("Error: admin.csv is empty or corrupted.\n");
                    fclose(admin_file);
                    Sleep(2000);
                    return 1;
                }

                while (fgets(buffer, sizeof(buffer), admin_file))
                {
                    size_t len = strcspn(buffer, "\n");
                    buffer[len] = '\0';

                    char *storedUsername = strtok(buffer, "|");
                    char *storedPassword = strtok(NULL, "|");

                    if (storedUsername != NULL && storedPassword != NULL &&
                        strcmp(admin_username, storedUsername) == 0 &&
                        strcmp(admin_password, storedPassword) == 0)
                    {
                        isAdminMatch = true;
                        break;
                    }
                }
                fclose(admin_file);

                if (isAdminMatch)
                {
                    printf("\n\t\t\tAdmin login successful!\n");
                    printf("\n\t\t\tProceeding to the admin menu...");
                    Sleep(2000);
                    system("cls");
                    LoadingBar();
                    Sleep(2000);
                    system("cls");

                    // Admin menu loop
                    bool admin_session = true;
                    while (admin_session)
                    {
                        system("cls");
                        Adminban();
                        admin_menu();
                        admin_session = false;
                    }
                }
                else
                {
                    system("cls");
                    printf("\n\tInvalid admin username or password. Please try again.\n");
                    Sleep(2000);
                    continue;
                    ;
                }
            }
        }
        else if (user_type == 'E' || user_type == 'e')
        {
            printf("\n\t\t\tExiting the program.\n");
            system("cls");
            LoadingBar();
            system("cls");
            printf("\n\t[]______________________________________________________________________________[]\n");
            printf("\n\t[]_____________________________________bye______________________________________[]\n");
            printf("\n\t[]______________________________________________________________________________[]\n");
            printf("\n\t[]_____________________________________</3______________________________________[]\n");
            Sleep(2000);
            system("cls");
            program_running = false;
        }
        else
        {
            system("cls");
            LoadingBar();
            system("cls");
            printf("\n\t[]______________________________________________________________________________[]\n");
            printf("\n\t[]_____________________________Invalid user input_______________________________[]\n");
            printf("\n\t[]______________________________Please try again________________________________[]\n");
            printf("\n\t[]_____________________________________</3______________________________________[]\n");
            Sleep(2000);
        }

        // Ask if user wants to continue using the program
        if (program_running && user_type != 'E')
        {
            system("cls");
            printf("\n");
            printf("\n\t[]______________________________________________________________________________[]\n");
            printf("\n\t[]_____________Do you want to continue using the program? (Y/N)_________________[]\n");
            printf("\n\t[]______________________________________________________________________________[]\n");
            printf("\n\t                                    ->:");
            char continue_choice;
            scanf("%c", &continue_choice);
            if (continue_choice != 'Y' && continue_choice != 'y')
            {
                program_running = false;
                system("cls");
                printf("\n\t[]______________________________________________________________________________[]\n");
                printf("\n\t[]_____________________________________bye______________________________________[]\n");
                printf("\n\t[]______________________________________________________________________________[]\n");
                printf("\n\t[]_____________________________________</3______________________________________[]\n");
                Sleep(5000);
            }
        }
    }

    return 0;
}