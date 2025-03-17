#ifndef INVENTORY_H
#define INVENTORY_H

#include <QMainWindow>
#include <QVector>

namespace Ui {
class inventory;
}

class inventory : public QMainWindow
{
    Q_OBJECT

public:
    explicit inventory(QWidget *parent = nullptr);
    ~inventory();

private slots:
    void on_add_btn_clicked();        // Add Product Page
    void on_next_btn_clicked();       // Next Button (Product Page -> Checkout Page)
    void on_checkout_btn_clicked();   // Customer Checkout Page
    void on_nex_btn_clicked();        // Next Button (Checkout Page -> Revenue Page)
    void on_calculate_btn_clicked();  // Revenue Calculation Page
    void on_exits_btn_clicked();      // Exit Button
    void on_addc_btn_clicked();       // Add to Cart Button

private:
    Ui::inventory *ui;
    QVector<QString> productList;     // List of Product Names
    QVector<double> costPriceList;    // List of Cost Prices
    QVector<double> sellPriceList;    // List of Selling Prices

    // Cart Variables
    QVector<QString> cartProducts;   // Products in Cart
    QVector<int> cartQuantities;     // Quantities in Cart
    QVector<double> cartSellPrices;  // Selling Prices in Cart
    QVector<double> cartCostPrices;  // Cost Prices in Cart

    // Cumulative Totals
    double totalRevenue;             // Total Revenue
    double totalProfit;              // Total Profit
};

#endif // INVENTORY_H
