//
// Created by Laner on 16/05/2024.
//

#ifndef FINAL_SCRAPER_H
#define FINAL_SCRAPER_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include "rbnTree.h"

// curl callback settings
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// getting HTML content
std::string fetchHtml(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

// strip HTML tags
std::string findBetween(const std::string& data, const std::string& startDelim, const std::string& endDelim) {
    size_t start = data.find(startDelim);
    if (start == std::string::npos) return "";
    start += startDelim.length();
    size_t end = data.find(endDelim, start) - 1;
    if (end == std::string::npos) return "";
    return data.substr(start, end - start);
}

// strip spaces around tag
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// parse book data
void parseBook(const std::string& html, RBNTree& tree) {
    size_t pos = 0;
    int i = 0;
    string title = html.substr(html.find("<h1>"), html.find("</h1>") - html.find("<h1>"));
    title = findBetween(title, "<h1>", "</h1>");

    string rate = html.substr(html.find("star-rating "),  5);
    rate = findBetween(rate, "star-rating ", "\">");
    int rateInt = 0;
    if (rate == "One") rateInt = 1;
    else if (rate == "Two") rateInt = 2;
    else if (rate == "Three") rateInt = 3;
    else if (rate == "Four") rateInt = 4;
    else if (rate == "Five") rateInt = 5;

    std::shared_ptr<Book> book = std::make_shared<Book>();
    book->setTitle(title);
    book->setRate(rateInt);
//    cout << title << endl;
//    cout << rate << endl;
    while ((pos = html.find("<td", pos)) != std::string::npos) {
        std::string data = html.substr(pos, html.find("</td>", pos) - pos);
        data = trim(findBetween(data, "<td>", "</td>"));
        switch (i) {
            case 0: {
                book->setUPC(data);
                break;
            }
            case 2: {
                data.erase(0, 2);
                double price = std::stod(data);
                book->setPriceWithoutTax(price);
                break;
            }
            case 3: {
                data.erase(0, 2);
                double priceWithTax = std::stod(data);
                book->setPriceWithTax(priceWithTax);
                break;
            }
            case 4: {
                data.erase(0, 2);
                book->setTax(std::stod(data));
                break;
            }
            case 5: {
                book->setAvailability(data);
                break;
            }
            case 6: {
                book->setNumberOfReviews(std::stoi(data));
                break;
            }
        }
        i++;
        pos += data.length();
    }
//    cout << book->getUPC() << endl;
//    cout << book->getPriceWithoutTax() << endl;
//    cout << book->getPriceWithTax() << endl;
//    cout << book->getTax() << endl;
//    cout << book->getAvailability() << endl;
//    cout << book->getNumberOfReviews() << endl;
//    cout << "--------------------------------" << endl;
    tree.insert(book);
}

// parse catalogue data
void parseCatalogue(const std::string& html, RBNTree& tree) {
    size_t pos = 0;
    while ((pos = html.find("<article class=\"product_pod\"", pos)) != std::string::npos) {
        std::string article = html.substr(pos, html.find("</article>", pos) - pos);
        std::string href = findBetween(article, "<h3><a href=\"", " title=\"");
        std::string url = "https://books.toscrape.com/catalogue/" + href;
        std::string html = fetchHtml(url);
        parseBook(html, tree);
        pos += article.length();
    }
}

#endif //FINAL_SCRAPER_H
