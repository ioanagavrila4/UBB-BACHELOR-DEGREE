def create_coffe(name: str, country: str, price: float):
    return {'name': name , 'country_of_origin': country, 'price': price}
def add_coffe_shop(coffe_shops_list: [], name: str, country_origin: str, price: float):
    coffe_shop_dict = create_coffe(name, country_origin, price)
    coffe_shops_list.append(coffe_shop_dict)

def sort_coffees(coffe_shop_list: []):
    for i in range (0, len(coffe_shop_list)):
        for j in range(i+1, len(coffe_shop_list)):
            if coffe_shop_list[i]['country_of_origin'] > coffe_shop_list[j]['country_of_origin']:
                aux = coffe_shop_list[i]
                coffe_shop_list[i] = coffe_shop_list[j]
                coffe_shop_list[j] = aux
            elif coffe_shop_list[i]['country_of_origin'] == coffe_shop_list[j]['country_of_origin']:
                if coffe_shop_list[i]['price'] > coffe_shop_list[j]['price']:
                    aux = coffe_shop_list[i]
                    coffe_shop_list[i] = coffe_shop_list[j]
                    coffe_shop_list[j] = aux

def filter_by_country_and_price(list_coffee:[], country: str, price: float):
    new_list = []
    for i in range(0, len(list_coffee)):
        if list_coffee[i]['country_of_origin'] == country and list_coffee[i]['price'] <= price:
            new_list.append(list_coffee[i])
        if list_coffee[i]['country_of_origin'] == country and list_coffee[i]['price'] == 0:
            new_list.append(list_coffee[i])
        if list_coffee[i]['country_of_origin'] == "none" and list_coffee[i]['price'] <= price:
            new_list.append(list_coffee[i])
    return new_list

def verify_name(name:str, listcof: []):
    for i in range(0, len(listcof)):
        if name == listcof[i]['name']:
            return False
    return True