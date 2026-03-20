# ABC Analysis for Pharmaceutical Sales

A SQL query that performs ABC analysis on pharmaceutical sales data, categorizing products based on their contribution to total amount, profit, and revenue using the Pareto principle (80/20 rule).

## 📜 Description

This SQL query performs ABC analysis on sales data to classify products into three categories:
- **A Category**: Top products that contribute to 80% of the total value
- **B Category**: Products that contribute to the next 15% (80-95%)
- **C Category**: Remaining products that contribute to the last 5%

The analysis is performed on three key metrics:
1. **Sales Amount** - Total quantity sold
2. **Profit** - Total profit generated
3. **Revenue** - Total revenue generated

## 📊 What is ABC Analysis?

ABC analysis is an inventory categorization technique based on the Pareto principle:
- **A items**: High-value products (80% of total value, 20% of items)
- **B items**: Medium-value products (15% of total value, 30% of items)
- **C items**: Low-value products (5% of total value, 50% of items)

## 🗄️ Database Schema

The query assumes a `sales` table with the following structure:

| Column | Description | Data Type |
|--------|-------------|-----------|
| `dr_ndrugs` | Product identifier/name | VARCHAR/INT |
| `dr_kol` | Quantity sold | NUMERIC/DECIMAL |
| `dr_croz` | Selling price | NUMERIC/DECIMAL |
| `dr_czak` | Purchase cost | NUMERIC/DECIMAL |
| `dr_sdisc` | Discount amount | NUMERIC/DECIMAL |

## 📈 Calculations

### 1. Sales Amount
```sql
SUM(dr_kol) as amount
Total quantity of each product sold.
```
2. Revenue
```sql
SUM(dr_kol * dr_croz - dr_sdisc) as revenue
Total revenue from product sales after discounts.
```
3. Profit
```sql
SUM(dr_kol * (dr_croz - dr_czak) - dr_sdisc) as profit
Total profit = (Quantity × (Selling price - Cost price)) - Discounts
```
## 🔍 ABC Classification Logic
|Category|Cumulative %|Meaning|
|---|---|---|
|A|≤ 80%|Critical products generating most value|
|B|≤ 95%|Important but not critical products|
|C|> 95%|Low-value products|

### Classification Algorithm
```sql
CASE
    WHEN SUM(value) OVER(ORDER BY value DESC) / SUM(value) OVER() <= 0.8 THEN 'A'
    WHEN SUM(value) OVER(ORDER BY value DESC) / SUM(value) OVER() <= 0.95 THEN 'B'
    ELSE 'C'
END
```
## 📋 Query Output
The query returns a table with the following columns:

|Column|Description|
|---|---|
|product|Product name/identifier|
|amount_abc|ABC category based on sales quantity|
|profit_abc|ABC category based on profit|
|revenue_abc|ABC category based on revenue|

### Sample Output
```text
product    | amount_abc | profit_abc | revenue_abc
-----------+------------+------------+------------
Aspirin    | A          | A          | A
Ibuprofen  | A          | B          | A
Paracetamol| B          | A          | B
Vitamin C  | C          | C          | C
```
## 🚀 How to Run
### Prerequisites
* SQL database (PostgreSQL, MySQL, SQL Server, Oracle, etc.)

* Sales table with required columns

* Execute permissions

### Execution
```sql
-- Copy and paste the entire query into your SQL client
-- Or save to a .sql file and run:
psql -d database_name -f abc_analysis.sql
```
## 🔧 Query Breakdown
### Step 1: Calculate Sales Amount per Product
```sql
SELECT dr_ndrugs as product, SUM(dr_kol) as amount 
FROM sales 
GROUP BY dr_ndrugs
```
### Step 2: Calculate Profit per Product
```sql
SELECT dr_ndrugs as product, 
       SUM(dr_kol * (dr_croz - dr_czak) - dr_sdisc) as profit 
FROM sales 
GROUP BY dr_ndrugs
```
### Step 3: Calculate Revenue per Product
```sql
SELECT dr_ndrugs as product, 
       SUM(dr_kol * dr_croz - dr_sdisc) as revenue 
FROM sales 
GROUP BY dr_ndrugs
```
### Step 4: Apply ABC Classification
* Using window functions to calculate running totals and percentages.

## 📊 Window Functions Explained
Cumulative Sum
```sql
SUM(amount) OVER(ORDER BY amount DESC)
```
Calculates running total from highest to lowest value.

Total Sum
```sql
SUM(amount) OVER()
```
Calculates the overall sum across all products.

Percentage Calculation
```sql
SUM(amount) OVER(ORDER BY amount DESC) / SUM(amount) OVER()
```
Determines the cumulative percentage contribution.

## 🎯 Use Cases
This analysis helps with:

* Inventory Management

* Focus on A-category products for stock optimization

* Reduce inventory of C-category items

* Pricing Strategy

* Identify which products drive most profit

* Adjust pricing for different categories

* Marketing Focus

* Allocate marketing budget to A and B products

* Consider discontinuing C products

* Supplier Negotiation

* Negotiate better terms for A-category products

* Optimize supplier relationships

## ⚠️ Important Notes
Database Compatibility
* PostgreSQL: Fully compatible

* MySQL: Compatible (requires MySQL 8+ for window functions)

* SQL Server: Fully compatible

* Oracle: Fully compatible

* SQLite: Not compatible (no window function support)


## 📝 Sample Data
Sales Table Sample
```sql
CREATE TABLE sales (
    dr_ndrugs VARCHAR(50),
    dr_kol INT,
    dr_croz DECIMAL(10,2),
    dr_czak DECIMAL(10,2),
    dr_sdisc DECIMAL(10,2)
);

INSERT INTO sales VALUES
('Aspirin', 1000, 5.00, 2.00, 0.50),
('Ibuprofen', 800, 8.00, 3.00, 1.00),
('Paracetamol', 500, 4.00, 1.50, 0.25),
('Vitamin C', 100, 10.00, 5.00, 0.00);
```

## 🔍 Troubleshooting
|Issue|Solution|
|---|---|
|Window function errors|Check database version (MySQL 8+, PostgreSQL 8.4+)|
|Division by zero|Ensure total sum > 0|
|Performance issues|Add indexes, consider batch processing|
|NULL values|Handle with COALESCE() if needed|

## 📄 License
This query is provided for educational and business intelligence purposes.