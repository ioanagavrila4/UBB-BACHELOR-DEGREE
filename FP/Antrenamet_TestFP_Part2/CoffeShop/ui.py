from functions import *

import texttable as tt

def ui_add_coffee(list_coffee:[]):
    try:
        name = input("Please type a name for the coffee: ")
        if not name:
            name = "none"
        else:
            if not verify_name(name, list_coffee):
                raise ValueError("A coffee with this name already exists!!")
        country_of_origin = input("Please type the country of origin of the coffee: ")
        if not country_of_origin:
            raise ValueError("This field must not be empty! Please introduce the country of the coffee!")
        price = float(input("Please type the price: "))
        if price < 0:
            raise ValueError("Invalid input! The price must be > 0 and has to be a floating number!")
        if not price:
            price = 0
        add_coffe_shop(list_coffee, name, country_of_origin, price)
        print("The coffee shop was added!!")
    except ValueError as e:
        print(e)

def display_coffees(coffees_list: []):
    sort_coffees(coffees_list)
    table = tt.Texttable()
    table.header(["Index", "Name","Country of origin", "Price"])
    for i, p in enumerate(coffees_list):
        table.add_row([i, coffees_list[i]['name'], coffees_list[i]['country_of_origin'], coffees_list[i]['price']])
    print(table.draw())
def ui_filter_coffee(coffee_list: []):
    try:
        country = input("Please give a country name:")
        if not country:
            raise ValueError("Please give an valid input!")
        price = float(input("Please type a price: "))
        if not price or price <= 0:
            raise ValueError("Invalid input!!")
        new_array = filter_by_country_and_price(coffee_list, country, price)
        if len(new_array) == 0:
            print("nada")
        else:
            display_coffees(new_array)
    except ValueError as e:
        print(e)
def main():
    coffee_shops = []
    add_coffe_shop(coffee_shops, "Brew", "Romania", 65.8)
    add_coffe_shop(coffee_shops, "Meron", "Romania", 5.898)
    add_coffe_shop(coffee_shops, "Olivo", "Franta", 69.45)
    add_coffe_shop(coffee_shops, "Five", "Brazil", 125.3)
    add_coffe_shop(coffee_shops, "Marty", "Bali", 25.5)

    try:
        while True:
            print("\nMenu")
            print("1. Add a coffee")
            print("2. Display all coffees aorted by country of origin")
            print("3. Filter the countries based on country of origin and price")
            print("4. EXIT")
            choice = int(input("Choose an option: "))
            if choice == 1:
                ui_add_coffee(coffee_shops)
            elif choice == 2:
                display_coffees(coffee_shops)
            elif choice == 3:
                ui_filter_coffee(coffee_shops)
            elif choice == 4:
                break
            else:
                raise ValueError("Invalid input!Please put a number between 1 and 4!!")

    except ValueError as e:
        print(e)
