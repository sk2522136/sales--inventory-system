#include "inventory.h"
#include "ui_inventory.h"
#include <QMessageBox>
#include <QDebug>

inventory::inventory(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::inventory)
    , totalRevenue(0.0)
    , totalProfit(0.0)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);  // Start at Product Add Page
    ui->value_ed->setMinimum(1);           // Set minimum quantity to 1
    ui->value_ed->setValue(1);             // Default quantity = 1
}

inventory::~inventory()
{
    delete ui;
}

// ========================
// PRODUCT ADD PAGE (Index 0)
// ========================
void inventory::on_add_btn_clicked()
{
    QString productName = ui->pro_edit->text().trimmed();
    QString costStr = ui->cost_edit->text().trimmed();
    QString sellStr = ui->sell_edit->text().trimmed();

    // Validate inputs
    if (productName.isEmpty() || costStr.isEmpty() || sellStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "All fields are mandatory!");
        return;
    }

    bool ok1, ok2;
    double cost = costStr.toDouble(&ok1);
    double sell = sellStr.toDouble(&ok2);

    if (!ok1 || !ok2 || cost <= 0 || sell <= 0) {
        QMessageBox::warning(this, "Error", "Invalid price values!");
        return;
    }

    if (productList.contains(productName)) {
        QMessageBox::warning(this, "Error", "Product already exists!");
        return;
    }

    // Add product to inventory
    productList.append(productName);
    costPriceList.append(cost);
    sellPriceList.append(sell);

    QMessageBox::information(this, "Success", "Product added to inventory!");
    ui->pro_edit->clear();
    ui->cost_edit->clear();
    ui->sell_edit->clear();
}

void inventory::on_next_btn_clicked()
{
    if (productList.isEmpty()) {
        QMessageBox::warning(this, "Error", "Add a product first!");
        return;
    }
    ui->stackedWidget->setCurrentIndex(1);  // Go to Checkout Page
}

// ========================
// CUSTOMER CHECKOUT PAGE (Index 1)
// ========================
void inventory::on_addc_btn_clicked()
{
    QString productName = ui->product_edit->text().trimmed();
    int quantity = ui->value_ed->value();

    if (productName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Product name is required!");
        return;
    }

    int index = productList.indexOf(productName);
    if (index == -1) {
        QMessageBox::warning(this, "Error", "Product not found in inventory!");
        return;
    }

    // Add product to cart
    cartProducts.append(productName);
    cartQuantities.append(quantity);
    cartCostPrices.append(costPriceList[index]);
    cartSellPrices.append(sellPriceList[index]);

    QMessageBox::information(this, "Cart", "Product added to cart!");
    ui->product_edit->clear();
    ui->value_ed->setValue(1);
}

void inventory::on_checkout_btn_clicked()
{
    QString customerName = ui->cus_edit->text().trimmed();

    if (customerName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Customer name required!");
        return;
    }

    if (cartProducts.isEmpty()) {
        QMessageBox::warning(this, "Error", "Cart is empty!");
        return;
    }

    double transactionRevenue = 0.0, transactionCost = 0.0;
    QString summary = QString("Customer: %1\nProducts:\n").arg(customerName);

    for (int i = 0; i < cartProducts.size(); ++i) {
        double itemRevenue = cartSellPrices[i] * cartQuantities[i];
        double itemCost = cartCostPrices[i] * cartQuantities[i];
        transactionRevenue += itemRevenue;
        transactionCost += itemCost;
        summary += QString("- %1 x%2\n").arg(cartProducts[i]).arg(cartQuantities[i]);
    }

    double profit = transactionRevenue - transactionCost;
    totalRevenue += transactionRevenue;
    totalProfit += profit;

    summary += QString("\nTotal Revenue: $%1\nProfit: $%2")
                   .arg(transactionRevenue, 0, 'f', 2)
                   .arg(profit, 0, 'f', 2);

    QMessageBox::information(this, "Checkout Complete", summary);

    // Clear cart and fields
    cartProducts.clear();
    cartQuantities.clear();
    cartCostPrices.clear();
    cartSellPrices.clear();
    ui->cus_edit->clear();
}

void inventory::on_nex_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);  // Go to Revenue Page
}

// ========================
// REVENUE PAGE (Index 2)
// ========================
void inventory::on_calculate_btn_clicked()
{
    ui->revenue_edit->setText(QString::number(totalRevenue, 'f', 2));
    ui->profit_n->setText(QString::number(totalProfit, 'f', 2));
}

void inventory::on_exits_btn_clicked()
{
    QApplication::quit();
}
