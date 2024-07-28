-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Query to find out the description of the crime happened on the specific day of the theft and in the specific street.
select description from crime_scene_reports where year = 2023 and month = 7 and day = 28 and street = "Humphrey Street";

--After getting the description of the theft, we know that ther were three witnesses, whose inteview contains the word
--"bakery" in it, so we do a query to know the full transcript of the interview and know more about the crime
select transcript from interviews where year = 2023 and month = 7 and day = 28 and transcript like "%bakery%";

--After reading the transcriptions of the interviews, the first one gave me a hint about the car activity between 10.15 and 10.25 am,
--so i ran a query to know all vehicles that exited the parking lot in said time span
select activity, license_plate from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 10 and minute <= 25
and minute >= 15;
--The results where:
/*
+----------+---------------+
| activity | license_plate |
+----------+---------------+
| exit     | 5P2BI95       |
| exit     | 94KL13X       |
| exit     | 6P58WS2       |
| exit     | 4328GD8       |
| exit     | G412CB7       |
| exit     | L93JTIZ       |
| exit     | 322W7JE       |
| exit     | 0NTHK55       |
+----------+---------------+
*/

--The second inteview transcript gave us a hint about a certain withdawing of money in Leggett Street, so we run a query to
--find more about it
select account_number, transaction_type, amount from atm_transactions where year = 2023 and month = 7 and day = 28 and atm_location =
 "Leggett Street" and transaction_type = "withdraw";
--The results were
/*
+----------------+------------------+--------+
| account_number | transaction_type | amount |
+----------------+------------------+--------+
| 28500762       | withdraw         | 48     |
| 28296815       | withdraw         | 20     |
| 76054385       | withdraw         | 60     |
| 49610011       | withdraw         | 50     |
| 16153065       | withdraw         | 80     |
| 25506511       | withdraw         | 20     |
| 81061156       | withdraw         | 30     |
| 26013199       | withdraw         | 35     |
+----------------+------------------+--------+
*/

--The last interview mentioned a phone call that lasted less that 60 seconds, so we run a query to find the numbers of the caller
--and the receiver
select caller, receiver from phone_calls where year = 2023 and month = 7 and day = 28 and duration < 60;
--The results were:
/*
+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+
*/
--On top of that, we know that littering took place at 16.36 on the crime scene, so we run a query to see if there is
--any matching license plate from the car activity in both time spans
select activity, license_plate from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 16 and minute > 36 and license_plate in (select license_plate from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 10 and minute <=
25 and minute >= 15);
--Unluckily, the query didnt return a result, meaning there is no matching license plate.

--Next we run a query to see what flights took early in the morning of the day 29 july 2023, and we want to know the destination and time
SELECT destination_airport_id, hour, minute FROM flights JOIN airports ON airports.id = flights.origin_airport_id WHERE airports.city = "Fiftyville" AND flights.year = 2023 AND flights.month = 7 AND flights.day = 29;
--The result were:
/*
+------------------------+------+--------+
| destination_airport_id | hour | minute |
+------------------------+------+--------+
| 6                      | 16   | 0      |
| 11                     | 12   | 15     |
| 4                      | 8    | 20     |
| 1                      | 9    | 30     |
| 9                      | 15   | 20     |
+------------------------+------+--------+

We can discard the flights that took place at 12, 15 or 16, because its not early in the morning
*/
--Nnow we will find out the destination of the two targeted flights with the following query
select id, full_name, city from airports where airports.id = 1 or airports.id = 4;
--The results were:
/*
+----+------------------------------+---------------+
| id |          full_name           |     city      |
+----+------------------------------+---------------+
| 1  | O'Hare International Airport | Chicago       |
| 4  | LaGuardia Airport            | New York City |
+----+------------------------------+---------------+
*/

--Now we run a query to find out about the person id of each of the people that did a transaction on the day and time that we
--found about before
select * from bank_accounts where account_number in (select account_number  from atm_transactions where year = 2023 and month = 7 and
day = 28 and atm_location = "Leggett Street" and transaction_type = "withdraw")
--The results were:
/*
+----------------+-----------+---------------+
| account_number | person_id | creation_year |
+----------------+-----------+---------------+
| 49610011       | 686048    | 2010          |
| 26013199       | 514354    | 2012          |
| 16153065       | 458378    | 2012          |
| 28296815       | 395717    | 2014          |
| 25506511       | 396669    | 2014          |
| 28500762       | 467400    | 2014          |
| 76054385       | 449774    | 2015          |
| 81061156       | 438727    | 2018          |
+----------------+-----------+---------------+
*/

--Now that we know many details about people that were in many situations related to the crime, we can filter
--everyone and see which people did a transaction, went to the bakery and did a call that day, and took a flight the next morning
select * from people
where people.license_plate in (select license_plate from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 10 and minute <= 25 and minute >= 15)
and people.phone_number in (select caller from phone_calls where year = 2023 and month = 7 and day = 28 and duration < 60)
and people.id in (select person_id from bank_accounts where account_number in (select account_number  from atm_transactions where year = 2023 and month = 7 and day = 28 and atm_location = "Leggett Street" and transaction_type = "withdraw"))
and people.passport_number in (select passengers.passport_number from passengers where flight_id = 36 or flight_id = 43);

--The results were:
/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+-------+----------------+-----------------+---------------+
*/
--NOW WE FOUND THE THIEF!!!

--Last steps are to find the accomplice and the city where they went. To do this we find the person with the phone_number of the receiver of the call
--from the thief, and the place where Bruce traveled through the flight table:
--Accomplice:
select * from people where phone_number in (select receiver from phone_calls where year = 2023 and month = 7 and day = 28 and duration < 60 and caller = "(
367) 555-5533");
--The results were:
/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 | NULL            | 4V16VO0       |
+--------+-------+----------------+-----------------+---------------+
*/
--ROBIN IS THE ACCOMPLICE!!!

--City:
select city from airports where id in (select destination_airport_id from flights where id = 36);
--The results were:
/*
+---------------+
|     city      |
+---------------+
| New York City |
+---------------+
*/
