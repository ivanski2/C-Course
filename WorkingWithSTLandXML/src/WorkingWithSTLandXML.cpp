#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>

#include "pugixml.hpp"

typedef std::map<std::string, int> TypeToQuantity;

enum MinMax {
    MIN,
    MAX
};

template <typename Key, typename Value>
bool isKeyInMap(std::map<Key, Value> &theMap, const Key &key) {
    return theMap.find(key) != theMap.end();
}

template <typename Key, typename Value>
Value &getFromMap(std::map<Key, Value> &theMap, const Key &key) {
    return theMap.find(key)->second;
}

template <typename Key, typename Value>
void putInMap(std::map<Key, Value> &theMap, const Key &key, const Value &val) {
    theMap[key] = val;
    // theMap.insert(make_pair(key, val));
}

template <typename Key, typename Value>
void delKeyInMap(std::map<Key, Value> theMap, const Key &key) {
    theMap.erase(theMap.find(key));
}


class Item {
public:
    Item(const std::string &_type, const std::string &_make,
            const std::string &_model,
            double _price, int _quantity)
        : type(_type), make(_make), model(_model),
            price(_price), quantity(_quantity) {
    }

    std::string getType() const {
        return type;
    }

    double getProfit() const {
        return price * quantity;
    }

    int getQuantity() const {
        return quantity;
    }

    void print() const {
        std::cout << type << " " << make << " " << model << " "
            << price << " " << quantity << std::endl;
    }

private:
    std::string type;
    std::string make;
    std::string model;

    double price;
    int quantity;
};

class Store {
public:
    Store(std::string xmlFilename) {
        pugi::xml_document doc;

        if (!doc.load_file(xmlFilename.c_str())) {
            std::cerr << "The file could not be read !" << std::endl;
            exit(1);
        } else {
            std::cout << "The file is readed successfully !" << std::endl;
        }

        pugi::xml_node store = doc.child("catalog");

        for (pugi::xml_node article = store.first_child(); article;
                article = article.next_sibling()) {
            std::string name = article.child("name").text().as_string();
            std::string brand = article.child("brand").text().as_string();
            std::string model = article.child("model").text().as_string();
            int sales = article.child("quantity").text().as_int();
            double price = article.child("priceItem").text().as_double();

            std::cout << name << brand << model << sales << price << std::endl;
            Item item(name, brand, model, sales, price);
            items.push_back(item);
        }
        // TODO: Close document.
    }

    double dailyRevenue() {
        double res = 0;
        for (int i = 0; i < (int) items.size(); ++i) {
            res = res + items[i].getProfit();
        }
        return res;
    }

    TypeToQuantity quantitiesPerType() {
        TypeToQuantity res;
        for (int i = 0; i < (int) items.size(); ++i) {
            std::string itemType = items[i].getType();
            int itemQuantity = items[i].getQuantity();
            if (isKeyInMap(res, itemType)) {
                putInMap(res, itemType, getFromMap(res, itemType) + itemQuantity);
            } else
			{
                putInMap(res, itemType, itemQuantity);
            }
        }
        return res;
    }

    void print() const {
        for (int i = 0; i < items.size(); ++i) {
            items[i].print();
        }
    }
private:
    std::vector<Item> items;
};

class Company {
public:
    Company(std::vector<std::string> storeXMLs) {
        for (int i = 0; i < (int) storeXMLs.size(); ++i) {
            stores.push_back(Store(storeXMLs[i]));
        }
    }

    double dailyRevenue() {
        double res = 0;
        for (int i = 0; i < (int) stores.size(); ++i) {
            res += stores[i].dailyRevenue();
        }
        return res;
    }

    TypeToQuantity quantitiesPerType() {
        TypeToQuantity res;
        for (int i = 0; i < (int) stores.size(); ++i) {
            TypeToQuantity perStore = stores[i].quantitiesPerType();
            for (TypeToQuantity::const_iterator it = perStore.begin();
                    it != perStore.end();
                    ++it) {
                std::string itemType = it->first;
                int itemQuantity = it->second;

                if (isKeyInMap(res, itemType)) {
                    putInMap(res, itemType, getFromMap(res, itemType) + itemQuantity);
                } else {
                    putInMap(res, itemType, itemQuantity);
                }
            }
        }

        return res;
    }

    std::pair<std::string, int> extremeQuantityType(MinMax minMax) {
        TypeToQuantity res = quantitiesPerType();
        if (res.empty()) {
            return std::make_pair("", 0);
        }

        std::string extremeType = res.begin()->first;
        int extremeQuantity = res.begin()->second;

        for (TypeToQuantity::const_iterator it = res.begin();
                it != res.end();
                ++it) {

            std::string itemType = it->first;
            int itemQuantity = it->second;

            if (minMax == MAX) {
                if (itemQuantity > extremeQuantity) {
                    extremeQuantity = itemQuantity;
                    extremeType = itemType;
                }
            } else {
                if (itemQuantity < extremeQuantity) {
                    extremeQuantity = itemQuantity;
                    extremeType = itemType;
                }
            }
        }

        return std::make_pair(extremeType, extremeQuantity);
    }

    std::vector<int> countsPerStore(std::string type) {
        std::vector<int> res;
        for (int i = 0; i < (int) stores.size(); ++i) {
            TypeToQuantity perStore = stores[i].quantitiesPerType();
            if (isKeyInMap(perStore, type)) {
                res.push_back(getFromMap(perStore, type));
            } else {
                res.push_back(0);
            }
        }
        return res;
    }

    void print() const {
        for (int i = 0; i < stores.size(); ++i) {
            std::cout << "Store " << i << std::endl;
            stores[i].print();
        }
    }

private:
    std::vector<Store> stores;
};


int main() {
    std::vector<std::string> xmlFiles;
    xmlFiles.push_back("file1.xml");
    xmlFiles.push_back("file2.xml");
    xmlFiles.push_back("file3.xml");
    Company c(xmlFiles);
    c.print();

    std::string key = "TV";
    std::pair<std::string, int> res = c.extremeQuantityType(MIN);
    std::cout << res.first << " " << res.second << std::endl;
    // std::vector<int> counts = c.countsPerStore(key);
    // for (int i = 0; i < (int) counts.size(); ++i) {
    //     std::cout << "Store " << i << " " << key << "s " << counts[i] << std::endl;
    // }

    return 0;
}
