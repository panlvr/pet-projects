# User Retention Cohort Analysis

A SQL query that performs cohort analysis to track user retention rates over time. This analysis calculates the percentage of users who return to the platform on specific days after their initial registration.

## 📜 Description

This query performs cohort analysis on user data to measure retention rates. It groups users by their registration month (cohort) and calculates the percentage of users who return on days 0, 1, 3, 7, 14, 30, 60, and 90 after their first use.

## 📊 What is Cohort Analysis?

Cohort analysis is a method of analyzing user behavior by grouping users who share common characteristics (typically registration date) and tracking their behavior over time. This helps answer questions like:
- **How many users return after 7 days?**
- **Does retention vary by registration month?**
- **How effective are our user engagement strategies?**

### Key Metrics Calculated

| Metric | Day | Meaning |
|--------|-----|---------|
| Day 0 | 0 | First-time users (baseline) |
| Day 1 | 1 | Next-day retention |
| Day 3 | 3 | 3-day retention |
| Day 7 | 7 | Weekly retention |
| Day 14 | 14 | 2-week retention |
| Day 30 | 30 | Monthly retention |
| Day 60 | 60 | 2-month retention |
| Day 90 | 90 | Quarterly retention |

## 🗄️ Database Schema

The query assumes the following table structure:

### users Table
| Column | Description | Data Type |
|--------|-------------|-----------|
| `id` | User ID (primary key) | INT/UUID |
| `date_joined` | User registration date | DATE/TIMESTAMP |

### userentry Table
| Column | Description | Data Type |
|--------|-------------|-----------|
| `user_id` | Foreign key to users table | INT/UUID |
| `entry_at` | User activity timestamp | DATE/TIMESTAMP |

## 📈 How It Works

### Step 1: Clean and Prepare Data
```sql
WITH clean_data AS (
    SELECT 
        user_id,
        DATE(u.date_joined) as date_joined,
        DATE(ue.entry_at) as entry_at,
        EXTRACT(DAYS FROM ue.entry_at - u.date_joined) as diff,
        TO_CHAR(u.date_joined, 'YYYY-MM') as cohort
    FROM userentry ue
    JOIN users u ON u.id = ue.user_id
    WHERE EXTRACT(YEAR FROM u.date_joined) = 2022
)
```
This CTE:

* Joins user and activity data

* Calculates days between registration and each activity

* Formats registration date as YYYY-MM for cohort grouping

* Filters for users who registered in 2022

### Step 2: Calculate Retention Rates
For each cohort and day interval, the query calculates:

```text
Retention Rate = (Users active on day X / Users active on day 0) × 100
```
## 📋 Query Output
The query returns a table with the following structure:

|cohort|0 (%)|1 (%)|3 (%)|7 (%)|14 (%)|30 (%)|60 (%)|90 (%)|
|--|--|--|--|--|--|--|--|--|
|2022-01|100.00|45.23|32.10|28.45|24.67|18.92|15.34|12.78|
|2022-02|100.00|47.89|33.45|29.12|25.33|19.45|16.12|13.45|
|2022-03|100.00|44.56|31.78|27.89|23.45|17.89|14.56|11.89|

#### Sample Interpretation

* Day 0: Always 100% (baseline)

* Day 1: ~45% of users return the next day

* Day 7: ~28% of users return after one week

* Day 30: ~18% of users return after one month

## 🚀 How to Run
### Prerequisites

* PostgreSQL (or other database with similar SQL syntax)

* Users and userentry tables with data

* Read access to both tables

### Execution
```sql
-- Copy and paste the entire query into your SQL client
-- Or save to a .sql file and run:
psql -d database_name -f cohort_analysis.sql
```
## 🎯 Use Cases
This analysis helps with:

* User Engagement Tracking

* Measure the effectiveness of onboarding processes

* Identify drop-off points in user journey

* Product Improvement

* Compare retention across different cohorts

* Test impact of feature releases on retention

* Marketing ROI

* Evaluate quality of users acquired in different months

* Optimize acquisition channels based on retention

* Business Forecasting

* Predict long-term user engagement

* Calculate Customer Lifetime Value (LTV)

## ⚠️ Important Notes
### Database Compatibility
* PostgreSQL: Fully compatible

* MySQL: Use DATE_DIFF and DATE_FORMAT functions

* SQL Server: Use DATEDIFF and FORMAT functions

* Oracle: Use MONTHS_BETWEEN and TO_CHAR

### Performance Considerations
* Large datasets may require indexing on user_id and entry_at

* Consider partitioning by date for better performance

* Filtering by year (2022) reduces data volume

## 📝 Sample Data
Creating Test Data
```sql
-- Create sample users
INSERT INTO users (id, date_joined) VALUES
(1, '2022-01-15'),
(2, '2022-01-20'),
(3, '2022-02-10');

-- Create sample user entries
INSERT INTO userentry (user_id, entry_at) VALUES
-- User 1 activity
(1, '2022-01-15'),  -- Day 0
(1, '2022-01-16'),  -- Day 1
(1, '2022-01-18'),  -- Day 3
(1, '2022-01-22'),  -- Day 7
-- User 2 activity
(2, '2022-01-20'),  -- Day 0
(2, '2022-01-21'),  -- Day 1
-- User 3 activity
(3, '2022-02-10');  -- Day 0
```
## 🔧 Troubleshooting
|Issue|Solution|
|---|---|
|NULL values in cohort|Ensure date_joined has valid dates|
|Division by zero|Check that day 0 users exist for each cohort|
|Date calculation errors|Verify timestamp data types are compatible|
|Performance issues|Add indexes on user_id and entry_at columns|

## 📄 License
This query is provided for business intelligence and analytical purposes.