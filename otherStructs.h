//
// Created by Laner on 16/05/2024.
//

#ifndef FINAL_OTHERSTRUCTS_H
#define FINAL_OTHERSTRUCTS_H

#include "iostream"

class Book {
private:
    std::string title;
    int rate;
    std::string description;
    std::string UPC;
    double priceWithTax;
    double priceWithoutTax;
    std::string currency;
    double tax;
    std::string availability;
    int available;
    int numberOfReviews;
public:
    Book(): title(""), rate(0), description(""), UPC("0000000000"), priceWithTax(0), priceWithoutTax(0),
    currency("USD"), tax(0), availability("Not available"), available(0), numberOfReviews(0) {}

    Book(const std::string& title, const int& rate, const std::string& description, const std::string& UPC,
         const double& priceWithTax, const double& priceWithoutTax, const std::string& currency, const double& tax,
         const std::string& availability, const int& available, const int& numberOfReviews):
         title(title), rate(rate), description(description), UPC(UPC), priceWithTax(priceWithTax),
         priceWithoutTax(priceWithoutTax), currency(currency), tax(tax), availability(availability),
         available(available), numberOfReviews(numberOfReviews) {}

    Book(const Book& book): title(book.title), rate(book.rate), description(book.description), UPC(book.UPC),
    priceWithTax(book.priceWithTax), priceWithoutTax(book.priceWithoutTax), currency(book.currency), tax(book.tax),
    availability(book.availability), available(book.available), numberOfReviews(book.numberOfReviews) {}

    ~Book() {}

    void setTitle(const std::string& title) {
        this->title = title;
    }

    void setRate(const int& rate) {
        this->rate = rate;
    }

    void setDescription(const std::string& description) {
        this->description = description;
    }

    void setUPC(const std::string& UPC) {
        this->UPC = UPC;
    }

    void setPriceWithTax(const double& priceWithTax) {
        this->priceWithTax = priceWithTax;
    }

    void setPriceWithoutTax(const double& priceWithoutTax) {
        this->priceWithoutTax = priceWithoutTax;
    }

    void setCurrency(const std::string& currency) {
        this->currency = currency;
    }

    void setTax(const double& tax) {
        this->tax = tax;
    }

    void setAvailability(const std::string& availability) {
        this->availability = availability;
    }

    void setAvailable(const int& available) {
        this->available = available;
    }

    void setNumberOfReviews(const int& numberOfReviews) {
        this->numberOfReviews = numberOfReviews;
    }

    std::string getTitle() const {
        return title;
    }

    int getRate() const {
        return rate;
    }

    std::string getDescription() const {
        return description;
    }

    std::string getUPC() const {
        return UPC;
    }

    double getPriceWithTax() const {
        return priceWithTax;
    }

    double getPriceWithoutTax() const {
        return priceWithoutTax;
    }

    std::string getCurrency() const {
        return currency;
    }

    double getTax() const {
        return tax;
    }

    std::string getAvailability() const {
        return availability;
    }

    int getAvailable() const {
        return available;
    }

    int getNumberOfReviews() const {
        return numberOfReviews;
    }
};

#endif //FINAL_OTHERSTRUCTS_H
