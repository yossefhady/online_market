




#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

int flag = 0;
int choice;
float total_cost = 0.0;
int num_products = 0;
int array_choice[MAX_PRODUCTS];

typedef struct
{
  char name[50];
  float price;
  int amount;
} Product;

typedef struct
{
  Product products[MAX_PRODUCTS];
  int num_products;
} ProductList;

typedef struct
{
  char name[50];
  char city[50];
  char phone[20];
  ProductList order_list;
  float delivery_fee;
} Customer;

ProductList available_products = {
    .products = {
        {"sugar", 2.5, 1},
        {"shampoo", 7, 1},
        {"tea", 0.75, 1},
        {"meat", 15.6, 1},
        {"cola", 3, 1},
        {"chocolate", 13.5, 1},
        {"potato", 4, 1}},
    .num_products = 7};

Customer customer;

void print_product_list(ProductList list)
{
  for (int i = 0; i < list.num_products; i++)
  {
    printf("%d - %s ($%.2f)\n", i + 1, list.products[i].name, list.products[i].price);
  }
}

void get_customer_info()
{
  printf("Welcome to our market!\n");
  printf("-----------------\n");
  printf("Enter your name: ");
  scanf("%s", customer.name);
  printf("Enter your city: ");
  scanf("%s", customer.city);
  printf("Enter your phone number: ");
  scanf("%s", customer.phone);
  printf("-----------------\n");
}

int get_order()
{
  int i = 0;
  while (1)
  {
    printf("Enter the product number (0 to finish): ");
    scanf("%d", &choice);
    if (choice == 0)
    {
      break;
    }

    if (choice > available_products.num_products)
    {
      printf("Invalid product number. Please try again.\n");
      continue;
    }

    array_choice[i] = choice;
    i++;

    // Check if the selected product is already in the order list
    int product_index = -1;
    for (int j = 0; j < customer.order_list.num_products; j++)
    {
      if (!strcmp(customer.order_list.products[j].name, available_products.products[choice - 1].name))
      {
        product_index = j;
        break;
      }
    }

    // Add the selected product to the customer's order list
    if (product_index == -1)
    {
      Product selected_product = available_products.products[choice - 1];
      customer.order_list.products[customer.order_list.num_products++] = selected_product;
    }
    else
    {
      customer.order_list.products[product_index].amount++;
    }
    // Calculate the delivery fee if necessary
    if (strcmp(customer.city, "Mansoura") != 0 && strcmp(customer.city, "mansoura") != 0)
      customer.delivery_fee = 5.0;
    else
      customer.delivery_fee = 2.0;
    printf("%s added to your order!\n", available_products.products[choice - 1].name);
  }
  return i;
}

void print_receipt()
{
  printf("----- RECEIPT -----\n");
  printf("| %-15s | %-10s | %-10s| %-10s |\n", "Product Name", "Price", "Quantity", "Total Cost");
  printf("-----------------------------------------\n");
  for (int i = 0; i < customer.order_list.num_products; i++)
  {
    Product product = customer.order_list.products[i];
    printf("| %-15s | $%-9.2f | %-9d | $%-9.2f |\n", product.name, product.price, product.amount, product.price * product.amount);
    total_cost += product.price * product.amount;
  }
  printf("-----------------------------------------\n");
  printf("| %-35s \t   | $%-9.2f |\n", "Delivery fee", customer.delivery_fee);
  total_cost += customer.delivery_fee;
  printf("-----------------------------------------\n");
  printf("| %-35s \t   | $%-9.2f |\n", "Total", total_cost);
  printf("-----------------------------------------\n");
}

int main()
{
  get_customer_info();
  int ensure;
  while (ensure)
  {
    printf("Please choose from the following available products:\n");
    print_product_list(available_products);
    printf("-----------------------------------------\n");
    int num_order_products = get_order();
    printf("\nThank you for your order, %s!\n\n", customer.name);
    if (num_order_products > 0)
    {
      print_receipt();
    }
    else
    {
      printf("Your order is empty. Goodbye!\n");
    }
    printf("(1) continue  (0) checkout : ");
    scanf("%d", &ensure);
    total_cost = 0;
  }
  printf("Thank you for your ordar. Goodbye!\n");
}
