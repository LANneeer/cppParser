#include <iostream>
#include <fstream>
#include <string>
#include "rbnTree.h"
#include "scraper.h"

void saveToCsv(const RBNTree& tree, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Title,UPC,ProductType,PriceWithoutTax,PriceWithTax,Tax,Availability,NumberOfReviews\n";
        tree.inorder([&file](const std::shared_ptr<Book>& book) {
            file << "\"" << book->getTitle() << "\","
                 << book->getUPC() << ","
                 << book->getDescription() << ","
                 << book->getPriceWithoutTax() << ","
                 << book->getPriceWithTax() << ","
                 << book->getTax() << ","
                 << book->getAvailability() << ","
                 << book->getNumberOfReviews() << "\n";
        });
        file.close();
    } else {
        std::cerr << "ERROR";
    }
}

int main() {
    RBNTree tree;
    for(int i = 1; i < 2; i++) {
        std::string url = "https://books.toscrape.com/catalogue/page-" + std::to_string(i) + ".html";
        std::string html = fetchHtml(url);
        parseCatalogue(html, tree);
    }
    tree.inorder();
    saveToCsv(tree, "books.csv");
    return 0;
}
