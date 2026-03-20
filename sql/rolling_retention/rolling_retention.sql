with clean_data as
    (
select 
    user_id,
    date(u.date_joined) as date_joined,
    date(ue.entry_at) as entry_at,
    extract(days from ue.entry_at-u.date_joined) as diff,
    to_char(u.date_joined, 'YYYY-MM') as cohort
from userentry ue
join users u 
on u.id = ue.user_id
where extract(year from u.date_joined) = 2022
    )
select 
    cohort,
    round(count(distinct case when diff >= 0 then user_id end) * 100.0 / count(distinct case when diff >= 0 then user_id end), 2) as "0 (%)",
round(count(distinct case when diff >= 1 then user_id end) * 100.0 / count(distinct case when diff >= 0 then user_id end), 2) as "1 (%)",
round(count(distinct case when diff >= 3 then user_id end) * 100.0 / count(distinct case when diff >= 0 then user_id end), 2) as "3 (%)",
round(count(distinct case when diff >= 7 then user_id end) * 100.0 / count(distinct case when diff >= 0 then user_id end), 2) as "7 (%)",
round(count(distinct case when diff >= 14 then user_id end) * 100.0 / count(distinct case when diff >= 0 then user_id end), 2) as "14 (%)",
round(count(distinct case when diff >= 30 then user_id end) * 100.0 / count(distinct case when diff >= 0 then user_id end), 2) as "30 (%)",
round(count(distinct case when diff >= 60 then user_id end) * 100.0 / count(distinct case when diff >= 0 then user_id end), 2) as "60 (%)",
round(count(distinct case when diff >= 90 then user_id end) * 100.0 / count(distinct case when diff >= 0 then user_id end), 2) as "90 (%)"
from clean_data
group by cohort