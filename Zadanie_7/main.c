#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stock_ Stock;

struct Stock_
{
    int index;
    char* name;
    float starting_price;
    float ending_price;
    int trades;
};

void print_trades(const int trades)
{
    char str[20];
    sprintf(str, "%d", trades);
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++)
    {
        if (i > 0 && (len - i) % 3 == 0)
        {
            printf("_");
        }
        printf("%c", str[i]);
    }
}

Stock* stock_new(const int index, const char* name, const float starting_price, const float ending_price,
                 const int trades)
{
    Stock* stock = malloc(sizeof(Stock));
    if (!stock) return NULL;

    stock->index = index;
    stock->name = strdup(name);
    stock->starting_price = starting_price;
    stock->ending_price = ending_price;
    stock->trades = trades;

    return stock;
}

Stock* stock_parse(char* line)
{
    char* id_str = strtok(line, ",");
    int index = atoi(id_str);
    char* name = strtok(NULL, ",");
    float starting_price = (float)atof(strtok(NULL, ","));
    float ending_price = (float)atof(strtok(NULL, ","));
    int trades = atoi(strtok(NULL, "\n"));

    Stock* stock = stock_new(index, name, starting_price, ending_price, trades);
    return stock;
}

Stock* stock_find_highest(Stock* stocks, const int rows, const char* target_stock)
{
    Stock* highest_stock = NULL;
    int highest_trade = -1;

    for (int i = 0; i < rows; i++)
    {
        if (strcmp(stocks[i].name, target_stock) == 0)
        {
            if (stocks[i].trades > highest_trade)
            {
                highest_trade = stocks[i].trades;
                highest_stock = &stocks[i];
            }
        };
    }

    return highest_stock;
}

void print_template(const Stock* stocks, const int rows, const Stock* highest, char* target_stock)
{
    printf("<html>\n");
    printf("<body>\n");
    printf("<div>\n");

    if (highest == NULL)
    {
        printf("Ticker %s was not found\n", target_stock);
    }
    else
    {
        printf("<h1>%s: highest volume</h1>\n", target_stock);
        printf("<div>Day: %d</div>\n", highest->index);
        printf("<div>Start price: %.2f</div>\n", highest->starting_price);
        printf("<div>End price: %.2f</div>\n", highest->ending_price);
        printf("<div>Volume: ");
        print_trades(highest->trades);
        printf("</div>\n");
    }

    printf("</div>\n");
    printf("<table>\n");
    printf("<thead>\n");
    printf("<tr><th>Day</th><th>Ticker</th><th>Start</th><th>End</th><th>Diff</th><th>Volume</th></tr>\n");
    printf("</thead>\n");
    printf("<tbody>\n");

    for (int i = rows - 1; i >= 0; i--)
    {
        float result_price = stocks[i].ending_price - stocks[i].starting_price;
        int is_stock_correct = (strcmp(stocks[i].name, target_stock) == 0);

        printf("<tr>\n");

        if (is_stock_correct) printf("\t<td><b>%d</b></td>\n", stocks[i].index);
        else printf("\t<td>%d</td>\n", stocks[i].index);

        if (is_stock_correct) printf("\t<td><b>%s</b></td>\n", stocks[i].name);
        else printf("\t<td>%s</td>\n", stocks[i].name);

        if (is_stock_correct) printf("\t<td><b>%.2f</b></td>\n", stocks[i].starting_price);
        else printf("\t<td>%.2f</td>\n", stocks[i].starting_price);

        if (is_stock_correct) printf("\t<td><b>%.2f</b></td>\n", stocks[i].ending_price);
        else printf("\t<td>%.2f</td>\n", stocks[i].ending_price);
        if (is_stock_correct) printf("\t<td><b>%.2f</b></td>\n", result_price);
        else printf("\t<td>%.2f</td>\n", result_price);

        if (is_stock_correct) printf("\t<td><b>");
        else printf("\t<td>");
        print_trades(stocks[i].trades);
        if (is_stock_correct) printf("</b></td>\n");
        else printf("</td>\n");

        printf("</tr>\n");
    }

    printf("</tbody>\n");
    printf("</table>\n");
    printf("</body>\n");
    printf("</html>\n");
}


int main(const int argc, char* argv[])
{
    int rows = 0;
    Stock* stocks = NULL;
    char buff[100];

    if (argc != 3)
    {
        printf("Wrong parameters\n");
        return 1;
    }

    rows = atoi(argv[2]);
    char* target_stock = argv[1];
    stocks = malloc(rows * sizeof(Stock));

    for (int i = 0; i < rows; i++)
    {
        fgets(buff, sizeof buff, stdin);
        buff[strcspn(buff, "\n")] = '\0';
        Stock* stock = stock_parse(buff);
        stocks[i] = *stock;

        free(stock);
        stock = NULL;
    }

    const Stock* highest_stock = stock_find_highest(stocks, rows, target_stock);
    print_template(stocks, rows, highest_stock, target_stock);


    for (int i = 0; i < rows; i++)
    {
        free(stocks[i].name);
    }
    free(stocks);

    return 0;
}
