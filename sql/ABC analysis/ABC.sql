with amount as 
    (
    select product, 
    case
        when sum(amount) over(order by amount desc)/ 
        sum(amount) over() <= 0.8 then 'A'
        when sum(amount) over(order by amount desc)/ 
        sum(amount) over() <= 0.95 then 'B'
        else 'C'
    end amount_abc
    from (
    select dr_ndrugs as product, sum(dr_kol) as amount from sales
    group by dr_ndrugs
        ) a
    ),
profit as (
    select product, 
    case
        when sum(profit) over(order by profit desc)/ 
        sum(profit) over() <= 0.8 then 'A'
        when sum(profit) over(order by profit desc)/ 
        sum(profit) over() <= 0.95 then 'B'
        else 'C'
    end profit_abc
    from (
    select dr_ndrugs as product, sum(dr_kol * (dr_croz - dr_czak) - dr_sdisc) as profit from sales
    group by dr_ndrugs
        ) b
    ),
revenue as (
    select product, 
    case
        when sum(revenue) over(order by revenue desc)/ 
        sum(revenue) over() <= 0.8 then 'A'
        when sum(revenue) over(order by revenue desc)/ 
        sum(revenue) over() <= 0.95 then 'B'
        else 'C'
    end revenue_abc
    from (
    select dr_ndrugs as product, sum(dr_kol * dr_croz - dr_sdisc) as revenue from sales
    group by dr_ndrugs
    ) c
)
select a.product, a.amount_abc, p.profit_abc, r.revenue_abc from amount a
join profit p on a.product = p.product
join revenue r on a.product = r.product