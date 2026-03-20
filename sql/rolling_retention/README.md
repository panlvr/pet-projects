# Cumulative User Retention Cohort Analysis

A SQL query that performs cumulative cohort analysis to track user retention rates over time. This analysis calculates the percentage of users who return at any point on or after specific days from their initial registration.

## 📜 Description

This query performs cumulative cohort analysis on user data to measure retention rates. Unlike point-in-time retention, cumulative retention shows the percentage of users who have returned at least once by each milestone. Users are grouped by their registration month (cohort), and retention is calculated for cumulative periods.

## 📊 What is Cumulative Retention?

Rolling retention measures the percentage of users who have returned **at least once** by a specific day, regardless of when they returned. This differs from point-in-time retention which only counts users who return exactly on that specific day.

### Key Differences

| Metric Type | Definition | Example |
|-------------|------------|---------|
| **Cumulative Retention** | Users who returned at any point on or before day X | Users who returned on day 1, 2, or 3 by day 3 |
| **Point-in-Time Retention** | Users who returned exactly on day X | Users who returned specifically on day 3 |

## 📈 Retention Milestones Calculated

| Metric | Day | Meaning |
|--------|-----|---------|
| Day 0 | ≥ 0 | All users who ever used the platform (baseline) |
| Day 1 | ≥ 1 | Users who returned on or after day 1 |
| Day 3 | ≥ 3 | Users who returned on or after day 3 |
| Day 7 | ≥ 7 | Users who returned on or after day 7 |
| Day 14 | ≥ 14 | Users who returned on or after day 14 |
| Day 30 | ≥ 30 | Users who returned on or after day 30 |
| Day 60 | ≥ 60 | Users who returned on or after day 60 |
| Day 90 | ≥ 90 | Users who returned on or after day 90 |

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

### Step 2: Calculate Cumulative Retention
```sql
CASE WHEN diff >= 30 THEN user_id END
```
This counts users who have ever returned on or after day 30.

### Step 3: Calculate Retention Rate
```text
Retention Rate = (Users active on or after day X / Users active at any time) × 100
```
## 📋 Query Output
The query returns a table with the following structure:

|cohort|0 (%)|1 (%)|3 (%)|7 (%)|14 (%)|30 (%)|60 (%)|90 (%)|
|--|--|--|--|--|--|--|--|--|
|2022-01|100.00|65.23|52.10|48.45|44.67|38.92|35.34|32.78|
|2022-02|100.00|67.89|53.45|49.12|45.33|39.45|36.12|33.45|
|2022-03|100.00|64.56|51.78|47.89|43.45|37.89|34.56|31.89|

### Sample Interpretation

* Day 0: Always 100% (all users who ever used the platform)

* Day 1: ~65% of users return at least once after day 0

* Day 7: ~48% of users return at least once after week 1

* Day 30: ~38% of users return at least once after month 1

* Day 90: ~32% of users return at least once after quarter 1

## 🚀 How to Run

### Prerequisites

* PostgreSQL (or other database with similar SQL syntax)

* Users and userentry tables with data

* Read access to both tables

### Execution
```sql
-- Copy and paste the entire query into your SQL client
-- Or save to a .sql file and run:
psql -d database_name -f cumulative_retention.sql
```
## 🎯 Key Insights

### Why Cumulative Retention Matters

* True User Engagement

    *  Shows how many users eventually find value

    * Accounts for users who return later

* Better Metrics for

    * Subscription services (users may return weekly)

    * E-commerce (users may purchase after days of browsing)

    * Content platforms (users may consume content irregularly)

* Business Insights

    * More realistic retention picture

    * Better for long-term forecasting

## ⚠️ Important Notes

### Database Compatibility

* PostgreSQL: Fully compatible

* MySQL: Use DATEDIFF and DATE_FORMAT functions

* SQL Server: Use DATEDIFF and FORMAT functions

* Oracle: Use MONTHS_BETWEEN and TO_CHAR

## 🔧 Troubleshooting
|Issue|Solution|
|---|---|
|Null values in date columns|Use COALESCE or filter out nulls|
|Duplicate entries per user|DISTINCT handles duplicates automatically|
|Day 0 counting incorrectly|Ensure baseline includes all users with any activity|
|Performance issues|Add indexes on user_id, date_joined, entry_at|

## 📄 License
This query is provided for analytical and business intelligence purposes.